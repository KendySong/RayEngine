workspace "RayEngine"
    location "build"
    architecture "x64"
    configurations { "Debug", "Release" }
    cppdialect "C++20"

project "RayEngine"
    kind "ConsoleApp"
    language "C++"
    location "build"    

    defines "SFML_STATIC"
    files { "src/**.cpp", "src/**.hpp", "src/**.h", "libraries/include/ImGui/**.cpp", "assets/**.*", "src/shaders/**.*" }

    includedirs { "libraries/*", "*"}
    libdirs "libraries/lib"
    links {
        "opengl32",
        "winmm",
        "raylib",
        "raylibdll",
        "box3d"
    }

filter "configurations:Debug"
    defines "DEBUG"
    symbols "On"


filter "configurations:Release"
    defines "RELEASE"
    optimize "Speed"
