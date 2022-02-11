@echo off
pushd %~dp0\..\

copy premake5_GLFW.lua "Hexagon\vendor\GLFW\premake5.lua"
copy premake5_imgui.lua "Hexagon\vendor\imgui\premake5.lua"

popd
PAUSE