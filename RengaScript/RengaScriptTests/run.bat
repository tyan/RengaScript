@echo off
SET lua_library_path=%1
SET tests_outdir=%2
XCOPY %lua_library_path%\*.lua %tests_outdir%\LibraryScript /s /i /y

CALL %tests_outdir%\RengaScriptTests.exe