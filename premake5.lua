local REPO_DIR = path.getabsolute "."
local DEP_DIR  = REPO_DIR .. "/dependencies"
local PROJ_DIR = REPO_DIR .. "/beam"
local OUT_DIR  = REPO_DIR .. "/_out"
local BIN_DIR  = OUT_DIR  ..
    "/bin/%{cfg.buildcfg}-%{cfg.architecture}/%{prj.name}"
local OBJ_DIR  = OUT_DIR  ..
    "/obj/%{cfg.buildcfg}-%{cfg.architecture}/%{prj.name}"

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
            DEP_DIR .. "/glad/glad/include/glad/glad.h",
            DEP_DIR .. "/glad/glad/include/KHR/khrplatform.h",
            DEP_DIR .. "/glad/glad/src/glad.c",
        }
        includedirs {
            DEP_DIR .. "/glad/glad/include",
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
            location      (DEP_DIR .. "/glfw")
            kind          "StaticLib"
            language      "C"
            staticruntime "on"
            systemversion "latest"
            warnings      "off"
            targetdir     (BIN_DIR)
            objdir        (OBJ_DIR)
            files {
                DEP_DIR .. "/glfw/glfw/include/GLFW/glfw3.h",
                DEP_DIR .. "/glfw/glfw/include/GLFW/glfw3native.h",
                DEP_DIR .. "/glfw/glfw/src/glfw_config.h",
                DEP_DIR .. "/glfw/glfw/src/context.c",
                DEP_DIR .. "/glfw/glfw/src/init.c",
                DEP_DIR .. "/glfw/glfw/src/input.c",
                DEP_DIR .. "/glfw/glfw/src/monitor.c",
                DEP_DIR .. "/glfw/glfw/src/vulkan.c",
                DEP_DIR .. "/glfw/glfw/src/window.c",
            }
            filter "system:windows"
                files {
                    DEP_DIR .. "/glfw/glfw/src/win32_init.c",
                    DEP_DIR .. "/glfw/glfw/src/win32_joystick.c",
                    DEP_DIR .. "/glfw/glfw/src/win32_monitor.c",
                    DEP_DIR .. "/glfw/glfw/src/win32_time.c",
                    DEP_DIR .. "/glfw/glfw/src/win32_thread.c",
                    DEP_DIR .. "/glfw/glfw/src/win32_window.c",
                    DEP_DIR .. "/glfw/glfw/src/wgl_context.c",
                    DEP_DIR .. "/glfw/glfw/src/egl_context.c",
                    DEP_DIR .. "/glfw/glfw/src/osmesa_context.c",
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
        pchsource     (PROJ_DIR .. "/src/Common.cpp")
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
            PROJ_DIR .. "/src/**.hpp",
            PROJ_DIR .. "/src/**.cpp",
        }
        includedirs {
            PROJ_DIR .. "/src",
            DEP_DIR  .. "/include",
            DEP_DIR  .. "/glad/glad/include",
            DEP_DIR  .. "/glfw/glfw/include",
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

newaction {
    trigger     = "clean",
    description = "Removes generated project files and build output.",

    onStart = function()
        local is_dep = function(path)
            return path:find(
                string.format("%s/[^/]+/[^/]+/", DEP_DIR), 1
            ) == 1 or path:find(
                string.format("%s\\[^\\]+\\[^\\]+\\", DEP_DIR), 1
            ) == 1
        end
        os.rmdir(OUT_DIR)
        local file_patterns = {
            "**.sln",
            "**.vcxproj",
            "**.vcxproj.user",
            "**.vcxproj.filters",
            "**Makefile",
        }
        for _, pattern in ipairs(file_patterns) do
            local matches = os.matchfiles(
                string.format("%s/%s", REPO_DIR, pattern)
            )
            for _, file in ipairs(matches) do
                if not is_dep(file) then
                    os.remove(file)
                end
            end
        end
    end
}
