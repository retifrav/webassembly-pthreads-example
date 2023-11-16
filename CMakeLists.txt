cmake_minimum_required(VERSION 3.22)

project("some"
    DESCRIPTION "An example application with pthreads"
    VERSION 0.9.1
)

option(WITH_PTHREADS "Build with pthreads" 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(${CMAKE_PROJECT_NAME})

set(sources
    src/some-shit.cpp
)

if(WITH_PTHREADS)
    list(APPEND sources ${CMAKE_SOURCE_DIR}/src/with-pthreads.cpp)

    set(EMSCRIPTEN_PTHREADS_FLAGS "-pthread")

    string(APPEND CMAKE_C_FLAGS " ${EMSCRIPTEN_PTHREADS_FLAGS}")
    string(APPEND CMAKE_CXX_FLAGS " ${EMSCRIPTEN_PTHREADS_FLAGS}")
    # documentation says `-pthread` needs to be passed both when compiling AND linking (although it doesn't seem to have any effect)
    # https://emscripten.org/docs/porting/pthreads.html#compiling-with-pthreads-enabled
    # and without `-s PROXY_TO_PTHREAD` there will be no output from the spawned threads
    string(APPEND CMAKE_EXE_LINKER_FLAGS " ${EMSCRIPTEN_PTHREADS_FLAGS} -s PROXY_TO_PTHREAD")

    # set(THREADS_PREFER_PTHREAD_FLAG 1)
    # set(THREADS_LIBRARIES_NAME "Threads::Threads")
    # if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    #     set(CMAKE_USE_PTHREADS_INIT 1)
    #     set(THREADS_LIBRARIES_NAME "-lpthread")
    #     set(CMAKE_THREAD_LIBS_INIT ${THREADS_LIBRARIES_NAME})
    # else()
    #     find_package(Threads REQUIRED)
    # endif()
    # target_link_libraries(${CMAKE_PROJECT_NAME}
    #     PRIVATE
    #         ${THREADS_LIBRARIES_NAME}
    # )
else()
    list(APPEND sources ${CMAKE_SOURCE_DIR}/src/without-pthreads.cpp)
endif()

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${sources}
)

set_target_properties(${CMAKE_PROJECT_NAME}
    PROPERTIES
        RUNTIME_OUTPUT_NAME $<IF:$<BOOL:${WITH_PTHREADS}>,${CMAKE_PROJECT_NAME}-with-pthreads,${CMAKE_PROJECT_NAME}-without-pthreads>
        # can also be set here
        #LINK_FLAGS "-s PROXY_TO_PTHREAD"
)

if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(INSTALLATION_PREFIX $<IF:$<BOOL:${EMSCRIPTEN}>,${CMAKE_SOURCE_DIR}/web,${CMAKE_SOURCE_DIR}/install>)
    message(
        STATUS
            "CMAKE_INSTALL_PREFIX is not set (default value is ${CMAKE_INSTALL_PREFIX})"
    )
    set(CMAKE_INSTALL_PREFIX "${INSTALLATION_PREFIX}"
        CACHE PATH "Installation prefix" FORCE
    )
else()
    message(
        STATUS
            "CMAKE_INSTALL_PREFIX has been already set, "
            "current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

include(GNUInstallDirs)

install(TARGETS ${CMAKE_PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
)
if(EMSCRIPTEN)
    install(FILES
        ${CMAKE_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${CMAKE_PROJECT_NAME}>.wasm
        DESTINATION ${CMAKE_INSTALL_PREFIX}
    )
    if(WITH_PTHREADS)
        install(FILES
            ${CMAKE_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${CMAKE_PROJECT_NAME}>.worker.js
            DESTINATION ${CMAKE_INSTALL_PREFIX}
        )
    endif()
endif()
