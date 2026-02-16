workspace "http-server"
   configurations { "Debug", "Release" }
   location "build"

project "http-server"
   kind "ConsoleApp"
   language "C"
   files { "src/**.h", "src/**.c" }

   filter { "configurations:Debug" }
      buildoptions {"-Wall", "-Wextra", "-Werror", "-Wpedantic"}
      defines { "DEBUG" }
      symbols "On"

   filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"