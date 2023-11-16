const statusesElement = document.getElementById("statuses");
const statusElement = document.getElementById("status");
const spinnerElement = document.getElementById("spinner");

//export var Module = {
var Module =
{
    preRun: [],
    postRun: [],
    print: (
        function()
        {
            var element = document.getElementById("output");
            if (element) element.value = ""; // clear browser cache
            return function(text)
            {
                if (arguments.length > 1) { text = Array.prototype.slice.call(arguments).join(" "); }
                // These replacements are necessary if you render to raw HTML
                //text = text.replace(/&/g, "&amp;");
                //text = text.replace(/</g, "&lt;");
                //text = text.replace(/>/g, "&gt;");
                //text = text.replace("\n", "<br>", "g");
                console.log(text);
                if(element)
                {
                    element.value += `${text}\n`;
                    element.scrollTop = element.scrollHeight; // focus on bottom
                }
            };
        }
    )(),
    setStatus: function(text)
    {
        if(!Module.setStatus.last)
        {
            Module.setStatus.last =
            {
                time: Date.now(),
                text: ""
            };
        }
        if(text === Module.setStatus.last.text) { return; }
        var m = text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
        var now = Date.now();
        if (m && now - Module.setStatus.last.time < 30)
        {
            // if this is a progress update, skip it if too soon
            return;
        }
        Module.setStatus.last.time = now;
        Module.setStatus.last.text = text;
        if(m)
        {
            text = m[1];
            spinnerElement.hidden = false;
        }
        else
        {
            if (!text)
            {
                spinnerElement.style.display = "none";
                statusesElement.style.display = "none";
            }
        }
        statusElement.innerHTML = text;
    },
    totalDependencies: 0,
    monitorRunDependencies: function(left)
    {
        this.totalDependencies = Math.max(this.totalDependencies, left);
        Module.setStatus(
            left
                ? `Preparing... (${(this.totalDependencies-left)}/${this.totalDependencies})`
                : "All downloads complete"
        );
    }
};

Module.setStatus("Downloading...");
window.onerror = function(event)
{
    // TODO: do not warn on OK-events like simulating an infinite loop or exitStatus
    Module.setStatus("Exception thrown, see JavaScript console");
    spinnerElement.style.display = "none";
    Module.setStatus = function(text)
    {
        if(text) { console.error(`[post-exception status] ${text}`); }
    };
};
