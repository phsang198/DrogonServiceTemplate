@ECHO OFF
SET SDKDIR=%~dp0
ECHO %SDKDIR%

cd /d "%~dp0"

SET SERVICE_NAME=TemplateService
SET SERVICE_EXE=%SDKDIR%%SERVICE_NAME%.exe
ECHO Uninstalling service "%SERVICE_EXE%"

"%SERVICE_EXE%" -remove

pause