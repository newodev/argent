@echo off
set compiler="D:/Vulkan/Bin/glslc.exe"

%compiler% %cd%/triangle.frag -o trianglef.spv
%compiler% %cd%/triangle.vert -o trianglev.spv
pause