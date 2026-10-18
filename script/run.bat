@echo off
setlocal
set "EXE=%~dp0..\build\tests\training_main.exe"
if not exist "%EXE%" (
	echo training_main.exe not exists! Please build first.
	exit /b 1
)
"%EXE%"
exit /b %errorlevel%
