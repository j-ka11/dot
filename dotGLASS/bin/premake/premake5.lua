-- premake5.lua

relsolutiondir = "../.."
relprojectdir = "../../dotGLASS"

workspace "dotGLASS"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   location ( relsolutiondir )

    --Set architecture
    filter { "platforms:x64" }
        system "Windows"
        architecture "x64"
    filter { }

project "dotGLASS"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   location ( relprojectdir )

   targetdir ( relprojectdir .. "/bin/%{cfg.buildcfg}" )

   files {
      relprojectdir .. "/include/**.h",
      relprojectdir .. "/src/**.cpp"
   }
   includedirs {
	   relprojectdir .. "/include",
       relprojectdir .. "/vendor/assimp/include",
       relprojectdir .. "/vendor/glew/include",
       relprojectdir .. "/vendor/glfw/x64/include",
       relprojectdir .. "/vendor/glm/"
   }
   libdirs {
       relprojectdir .. "/vendor/assimp/lib/x64",
       relprojectdir .. "/vendor/glew/x64/lib",
       relprojectdir .. "/vendor/glfw/x64/lib"
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
