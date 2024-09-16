@echo off

cl /Od /Ob1 /DBUILD_DEBUG=1 /I.\include\ /nologo /FC /Z7 .\src\main.c /link /MANIFEST:EMBED /INCREMENTAL:NO /out:GITS-Viewer.exe
del main.obj
