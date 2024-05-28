@echo off

setlocal

set compiler_include=C:\dev\shared\include
set compiler_warnings=/WX /W4 /wd4201 /wd4100 /wd4189 /wd4505 /wd4996 /wd4456 /wd4267
set compiler_flags=/nologo /FC /Z7 /Od /GR-
set linker_flags=/debug /incremental:no /subsystem:console

set libs=raylibdll.lib raylib.lib

pushd bin

clang-cl ..\src\welt.cpp /I%compiler_include% %compiler_warnings% %compiler_flags% /link %linker_flags% %libs%

popd