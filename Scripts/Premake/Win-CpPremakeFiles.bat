@echo off
pushd %~dp0\..\..\

copy Scripts\Premake\premake5_GLFW.lua "Hexagon\vendor\GLFW\premake5.lua"
IF %ERRORLEVEL% NEQ 0 (PAUSE)

copy Scripts\Premake\premake5_imgui.lua "Hexagon\vendor\imgui\premake5.lua"
IF %ERRORLEVEL% NEQ 0 (PAUSE)

popd