workspace "Saffron"
    architecture "x64"
    startproject "Sandbox"

    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Glad"
    location "Saffron/vendor/glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "Saffron/vendor/glad/src/glad.c" }
    includedirs { "Saffron/vendor/glad/include" }

project "ImGui"
    location "Saffron/vendor/imgui"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "Saffron/vendor/imgui/*.cpp",
        "Saffron/vendor/imgui/backends/imgui_impl_glfw.cpp",
        "Saffron/vendor/imgui/backends/imgui_impl_opengl3.cpp"
    }

    includedirs {
        "Saffron/vendor/imgui",
        "Saffron/vendor/imgui/backends",
        "Saffron/vendor/glad/include",
        "Saffron/src"
    }


project "Saffron"
    location "Saffron"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src/",
        "Saffron/vendor/glad/include",
        "Saffron/vendor/imgui"
    }

    links {
        "Glad",
        "ImGui"
    }

    filter "system:linux"
        pic "On"
        -- defines {
        --     "SF_PLATFORM_LINUX",
        --     "SF_BUILD_STATIC"
        -- }

    filter "configurations:Debug"
        defines "SF_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "SF_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "SF_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Saffron/src",
        "Saffron/vendor/glad/include",
        "Saffron/vendor/imgui"
    }

    links {
        "Saffron",
        "glfw",
        "Glad",
        "ImGui"
    }
