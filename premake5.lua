#!lua

includeDirList = {
    "shared",
    "shared/gl3w",
    "shared/imgui",
    "shared/soloud/include",
    "shared/include"
}

libDirectories = {
    "lib"
}

buildOptions = {"-std=c++17"}

-- Build glfw3 static library and copy it into ./lib if it is not already present.
if not os.isfile("lib/libglfw3.a") then
    os.chdir("shared/glfw-3.3.8")
    os.mkdir("build")
    os.chdir("build")
    os.execute("cmake ../")
    os.execute("make")
    os.chdir("../../../")
    os.mkdir("lib")
    os.execute("cp shared/glfw-3.3.8/build/src/libglfw3.a lib/")
end

linkLibs = {
    "imgui",
    "soloud",
    "glfw3",
    "GL",
    "Xinerama",
    "Xcursor",
    "Xxf86vm",
    "Xi",
    "Xrandr",
    "X11",
    "stdc++",
    "dl",
    "pthread",
}

solution "BuildStaticLibs"
    configurations { "Debug", "Release" }

    filter "Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "Release"
        defines { "NDEBUG" }
        optimize "On"

    -- build imgui static library
    project "imgui"
        kind "StaticLib"
        language "C++"
        location "build"
        objdir "build"
        targetdir "lib"
        includedirs (includeDirList)
        includedirs {
            "shared/imgui/examples/example_glfw_opengl3",
            "shared/imgui/examples/libs/glfw/",
        }
        files {
            "shared/imgui/*.cpp",
            "shared/imgui/backends/imgui_impl_glfw.cpp",
            "shared/imgui/backends/imgui_impl_opengl3.cpp",
            "shared/gl3w/GL/gl3w.c",
        }

    -- build soloud static library
    project "soloud"
        kind "StaticLib"
        language "C++"
        location "build"
        objdir "build"
        targetdir "lib"
        includedirs (includeDirList)
        defines {"WITH_MINIAUDIO"}
        files {
           "shared/soloud/src/core/*.cpp",
           "shared/soloud/src/audiosource/wav/*.cpp",
           "shared/soloud/src/audiosource/wav/*.c",
           "shared/soloud/src/backend/miniaudio/**.c*",
        }

    -- build fps application
    project "fps"
        kind "ConsoleApp"
        language "C++"
        location "build"
        objdir "build"
        targetdir "."
        buildoptions (buildOptions)
        libdirs (libDirectories)
        links (linkLibs)
        linkoptions (linkOptionList)
        includedirs (includeDirList)
        files { "src/*.cpp" }

