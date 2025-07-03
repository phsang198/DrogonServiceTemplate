@echo off
REM Usage: replaceName.bat NewName [OldName]

setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Usage: %0 NewName [OldName]
    exit /b 1
)

set "NEWNAME=%~1"

if "%~2"=="" (
    set "OLDNAME=TemplateService"
) else (
    set "OLDNAME=%~2"
)

REM Kiểm tra file và folder gốc
if not exist "%OLDNAME%.sln" (
    echo File %OLDNAME%.sln not found!
    exit /b 2
)
if not exist "%OLDNAME%" (
    echo Folder %OLDNAME% not found!
    exit /b 3
)

REM 2. Đổi tên file .sln
ren "%OLDNAME%.sln" "%NEWNAME%.sln"

REM 2.1 Thay nội dung trong file .sln
powershell -Command "(Get-Content '%NEWNAME%.sln') -replace '%OLDNAME%', '%NEWNAME%' | Set-Content '%NEWNAME%.sln'"

REM 3. Đổi tên folder TemplateService thành xxx
ren "%OLDNAME%" "%NEWNAME%"

REM 4. Đổi tên các file project trong thư mục mới
pushd "%NEWNAME%"
for %%F in (".vcxproj" ".vcxproj.filters" ".vcxproj.user") do (
    if exist "%OLDNAME%%%F" ren "%OLDNAME%%%F" "%NEWNAME%%%F"
)
REM Thay TemplateService thành tên mới trong nội dung các file project vừa đổi tên
for %%F in ("%NEWNAME%.vcxproj" "%NEWNAME%.vcxproj.filters" "%NEWNAME%.vcxproj.user") do (
    if exist "%%F" (
        powershell -Command "(Get-Content '%%F') -replace '%OLDNAME%', '%NEWNAME%' | Set-Content '%%F'"
    ) else (
		echo File %%F not found
	)
)
popd

REM 5. Xử lý trong folder Source
if not exist "%NEWNAME%\Source" (
    echo Folder %NEWNAME%\Source not found!
    goto :skip_source
)

REM 5.1 Thay nội dung Main.cpp
if exist "%NEWNAME%\Source\Main.cpp" (
    powershell -Command "(Get-Content '%NEWNAME%\Source\Main.cpp') -replace '%OLDNAME%', '%NEWNAME%' | Set-Content '%NEWNAME%\Source\Main.cpp'"
) else (
    echo File %NEWNAME%\Source\Main.cpp not found
)

REM 5.2 Đổi tên TemplateService.h/.cpp thành xxx.h/.cpp
if exist "%NEWNAME%\Source\%OLDNAME%.h" ren "%NEWNAME%\Source\%OLDNAME%.h" "%NEWNAME%.h"
if exist "%NEWNAME%\Source\%OLDNAME%.cpp" ren "%NEWNAME%\Source\%OLDNAME%.cpp" "%NEWNAME%.cpp"

REM 5.3 Thay nội dung trong 2 file mới đổi tên
for %%F in ("%NEWNAME%\Source\%NEWNAME%.h" "%NEWNAME%\Source\%NEWNAME%.cpp") do (
    if exist %%F (
        powershell -Command "(Get-Content '%%F') -replace '%OLDNAME%', '%NEWNAME%' | Set-Content '%%F'"
    )
)

:skip_source

REM 6. Thay nội dung trong file .vcxproj.filters
if exist "%NEWNAME%\%NEWNAME%.vcxproj.filters" (
    powershell -Command "(Get-Content '%NEWNAME%\%NEWNAME%.vcxproj.filters') -replace '%OLDNAME%', '%NEWNAME%' | Set-Content '%NEWNAME%\%NEWNAME%.vcxproj.filters'"
) else (
    echo File %NEWNAME%\%NEWNAME%.vcxproj.filters not found
)

REM 7. Thay TemplateService thành tên mới trong các batch cài đặt/dỡ cài đặt service nếu có
if exist "%NEWNAME%\Install\installService.bat" (
    powershell -Command "(Get-Content '%NEWNAME%\Install\installService.bat') -replace '%OLDNAME%', '%NEWNAME%' | Set-Content '%NEWNAME%\Install\installService.bat'"
)
if exist "%NEWNAME%\Install\uninstallService.bat" (
    powershell -Command "(Get-Content '%NEWNAME%\Install\uninstallService.bat') -replace '%OLDNAME%', '%NEWNAME%' | Set-Content '%NEWNAME%\Install\uninstallService.bat'"
)

echo.
echo ==== Da thay doi ten va noi dung thanh cong! ====
endlocal
pause