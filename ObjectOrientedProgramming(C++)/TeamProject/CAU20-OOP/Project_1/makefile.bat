@echo off

echo Compiling sources and generating executables... 

g++ -std=c++11 src/*.cpp -o out/a

echo Build complete (out/a.exe).