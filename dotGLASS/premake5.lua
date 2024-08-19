-- premake5.lua
workspace "dotGLASS"
   configurations { "Debug", "Release" }

   platforms { "x64" }

    --Set architecture
    filter { "platforms:x64" }
        system "Windows"
        architecture "x64"

    filter { }

project "dotGLASS"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"

   targetdir "bin/%{cfg.buildcfg}"

   files {
      "dotGLASS/include/**.h",
      "dotGLASS/src/**.cpp"
   }

   includedirs {
	   "dotGLASS/include",
       "dotGLASS/vendor/assimp/include",
       "dotGLASS/vendor/glew/include",
       "dotGLASS/vendor/glfw/x64/include",
       "dotGLASS/vendor/glm/"
   }

   libdirs {
       "dotGLASS/vendor/assimp/lib/x64",
       "dotGLASS/vendor/glew/x64/lib",
       "dotGLASS/vendor/glfw/x64/lib"
   }

   links {
       "assimp-vc143-mt",
       "glew32s",
       "glu32",
       "opengl32",
       "glfw3"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
