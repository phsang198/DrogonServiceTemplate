@ECHO OFF
SET SDKDIR=%~dp0
ECHO %SDKDIR%

cd /d "%~dp0"

SET SERVICE_NAME=ServiceTemplate
SET SERVICE_EXE=%SDKDIR%%SERVICE_NAME%.exe
ECHO Installing service "%SERVICE_EXE%"

"%SERVICE_EXE%" -install

net start %SERVICE_NAME%

pause