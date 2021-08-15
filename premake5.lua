local BIN_DIR = "_out/bin/%{cfg.buildcfg}-%{cfg.architecture}/%{prj.name}"
local OBJ_DIR = "_out/obj/%{cfg.buildcfg}-%{cfg.architecture}/%{prj.name}"

workspace "beam"
    architecture "x64"
    startproject "beam"
    configurations {
        "debug",
        "profile",
        "release",
    }

    project "glad"
        location      "dependencies/glad"
        kind          "StaticLib"
        language      "C"
        staticruntime "on"
        systemversion "latest"
        warnings      "off"
        targetdir     (BIN_DIR)
        objdir        (OBJ_DIR)
        files {
            "dependencies/glad/glad/include/glad/glad.h",
            "dependencies/glad/glad/include/KHR/khrplatform.h",
            "dependencies/glad/glad/src/glad.c",
        }
        includedirs {
            "dependencies/glad/glad/include",
        }
        filter "configurations:debug"
            runtime  "debug"
            symbols  "on"
            optimize "off"
        filter "configurations:profile"
            runtime  "release"
            symbols  "on"
            optimize "on"
        filter "configurations:release"
            runtime  "release"
            symbols  "off"
            optimize "on"

        project "GLFW"
            location      "dependencies/glfw"
            kind          "StaticLib"
            language      "C"
            staticruntime "on"
            systemversion "latest"
            warnings      "off"
            targetdir     (BIN_DIR)
            objdir        (OBJ_DIR)
            files {
                "dependencies/glfw/glfw/include/GLFW/glfw3.h",
                "dependencies/glfw/glfw/include/GLFW/glfw3native.h",
                "dependencies/glfw/glfw/src/glfw_config.h",
                "dependencies/glfw/glfw/src/context.c",
                "dependencies/glfw/glfw/src/init.c",
                "dependencies/glfw/glfw/src/input.c",
                "dependencies/glfw/glfw/src/monitor.c",
                "dependencies/glfw/glfw/src/vulkan.c",
                "dependencies/glfw/glfw/src/window.c",
            }
            filter "system:windows"
                files {
                    "dependencies/glfw/glfw/src/win32_init.c",
                    "dependencies/glfw/glfw/src/win32_joystick.c",
                    "dependencies/glfw/glfw/src/win32_monitor.c",
                    "dependencies/glfw/glfw/src/win32_time.c",
                    "dependencies/glfw/glfw/src/win32_thread.c",
                    "dependencies/glfw/glfw/src/win32_window.c",
                    "dependencies/glfw/glfw/src/wgl_context.c",
                    "dependencies/glfw/glfw/src/egl_context.c",
                    "dependencies/glfw/glfw/src/osmesa_context.c",
                }
                defines {
                    "_GLFW_WIN32",
                }
            filter "configurations:debug"
                runtime  "debug"
                symbols  "on"
                optimize "off"
            filter "configurations:profile"
                runtime  "release"
                symbols  "on"
                optimize "on"
            filter "configurations:release"
                runtime  "release"
                symbols  "off"
                optimize "on"    

    project "beam"
        location      "beam"
        kind          "ConsoleApp"
        language      "C++"
        cppdialect    "C++17"
        staticruntime "on"
        systemversion "latest"
        pchheader     "Common.hpp"
        pchsource     "beam/src/Common.cpp"
        targetdir     (BIN_DIR)
        objdir        (OBJ_DIR)
        warnings      "extra"
        disablewarnings {
            4068
        }
        defines {
            "GLFW_INCLUDE_NONE",
        }
        files {
            "%{prj.name}/src/**.hpp",
            "%{prj.name}/src/**.cpp",
        }
        includedirs {
            "%{prj.name}/src",
            "dependencies/include",
            "dependencies/glad/glad/include",
            "dependencies/glfw/glfw/include",
        }
        links {
            "glad",
            "glfw",
        }
        filter "system:windows"
            links {
                "gdi32",
            }
        filter "configurations:debug"
            runtime  "debug"
            symbols  "on"
            optimize "off"
            defines  { "BEAM_CONFIG_DEBUG" }
        filter "configurations:profile"
            runtime  "release"
            symbols  "on"
            optimize "on"
            defines  { "BEAM_CONFIG_PROFILE" }
        filter "configurations:release"
            runtime  "release"
            symbols  "off"
            optimize "on"
            defines  { "BEAM_CONFIG_RELEASE" }
