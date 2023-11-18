import pathlib
import http.server
import socketserver
import ssl

import sys
if sys.version_info < (3, 8):
    # not sure if it is actually required to have Python not older than 3.8
    raise SystemExit(
        " ".join((
            "[ERROR] Python version 3.8 or newer is required",
            f"(found {sys.version_info.major}.{sys.version_info.minor})"
        ))
    )

currentPath = pathlib.Path(__file__).resolve().parent


class HttpRequestHandler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=currentPath/"web", **kwargs)

    extensions_map = {
        ".html": "text/html",
        ".css": "text/css",
        ".js": "application/javascript",
        ".json": "application/json",
        ".wasm": "application/wasm",
        ".png": "image/png",
        ".jpg": "image/jpg",
        # ".svg": "image/svg+xml",
        # ".xml": "application/xml",
        "": "application/octet-stream"
    }

    def send_response(self, *args, **kwargs):
        http.server.SimpleHTTPRequestHandler.send_response(
            self,
            *args,
            **kwargs
        )
        # self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")
        if self.path.endswith(".wasmz"):
            self.send_header("Content-Encoding", "gzip")


certificate = currentPath / "certificates/" / "localhost.crt"
key = currentPath / "certificates/" / "localhost.key"
# certificatePassword = "CERTIFICATE-PASSWORD-IF-ANY"

host = "127.0.0.1"
port = 8000

httpd = socketserver.TCPServer((host, port), HttpRequestHandler)
context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
context.load_cert_chain(
    certfile=certificate,
    keyfile=key
    # password=certificatePassword
)
httpd.socket = context.wrap_socket(httpd.socket, server_side=True)

try:
    print(f"Serving at https://{host}:{port}")
    httpd.serve_forever()
except KeyboardInterrupt:
    pass
