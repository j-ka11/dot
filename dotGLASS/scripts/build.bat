:: Change to dotGLASS visual studio solution binary premake root
:: and build dotGLASS visual studio solution.
cd ../bin/premake
premake5 vs2019

:: Copy vendor dll to dotGLASS visual studio project binary Debug folder.
cd ../../dotGLASS
mkdir bin
cd bin
mkdir Debug
cp ../vendor/assimp/bin/x64/assimp-vc143-mt.dll Debug
