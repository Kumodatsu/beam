workspace "beam"
    architecture "x64"
    startproject "beam"
    configurations {
        "debug",
        "profile",
        "release"
    }

    project "beam"
        location      "beam"
        kind          "ConsoleApp"
        language      "C++"
        cppdialect    "C++17"
        staticruntime "on"
        systemversion "latest"
        pchheader     "Common.hpp"
        pchsource     "beam/src/Common.hpp"
        warnings      "extra"
        targetdir     "_out/bin/%{cfg.buildcfg}-%{cfg.architecture}/%{prj.name}"
        objdir        "_out/obj/%{cfg.buildcfg}-%{cfg.architecture}/%{prj.name}"
        defines {
            
        }
        files {
            "%{prj.name}/src/**.hpp",
            "%{prj.name}/src/**.cpp"
        }
        includedirs {
            "%{prj.name}/src"
        }
        links {

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
