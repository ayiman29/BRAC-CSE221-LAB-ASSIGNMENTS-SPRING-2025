@echo off
for %%a in (py cpp java) do (
    powershell -command "if (Select-String -Path '.\EnterIDandLanguage.txt' -Pattern '%%a') { exit 1 } else { exit 0 }" || (
        for /f %%b in ('powershell -command "Get-Content 'EnterIDandLanguage.txt' -TotalCount 1"') do (
            powershell -command "if (Get-ChildItem -Path . -Filter '_312_%%b.%%a' -File) { exit 1 } else { exit 0 }" && (
                if %%a==py (
                    echo # %%b 0 >_312_%%b.%%a
                    echo # %COMPUTERNAME% %USERNAME%>>_312_%%b.%%a
                ) else (
                    echo // %%b 0 >_312_%%b.%%a
                    echo // %COMPUTERNAME% %USERNAME%>>_312_%%b.%%a
                )
                powershell -command "Get-Content '_312_Solution.%%a' | Add-Content '_312_%%b.%%a'"
            )
        )
        for /f "delims=" %%b in (_312_ForbiddenKeywords.txt) do (
            for %%c in (%%b) do (
                powershell -command "if (Select-String -Path '.\_312_Solution.%%a' -Pattern '%%c') { exit 1 } else { exit 0 }" || (
                    echo Code contains forbidden keyword: %%c
                    echo Score = 0/1
                    goto Ending
                )
            )
        )
        if %%a==py (
            pypy -m py_compile _312.py
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else pypy _312.py
            rd /q /s __pycache__ >nul
        )
        if %%a==cpp (
            c++ _312_Solution.cpp _312.cpp
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else .\a.exe
            del /q /s /a /f .\*.exe >nul
        )
        if %%a==java (
            javac _312_Solution.java _312.java
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else java _312
            del /q /s /a /f .\*.class >nul
        )
    )
)
:Ending
pause