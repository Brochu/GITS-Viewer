@echo off

cl /Od /Ob1 /DBUILD_DEBUG=1 /I.\include\ /I.\include\assimp /nologo /FC /Z7 /MD .\src\main.c ^
/link /MANIFEST:EMBED /INCREMENTAL:NO /LIBPATH:libs\ /NODEFAULTLIB:MSVCRTD ^
assimp-vc143-mt.lib raylib.lib gdi32.lib winmm.lib opengl32.lib kernel32.lib user32.lib shell32.lib ^
/out:GITS-Viewer.exe

del main.obj
