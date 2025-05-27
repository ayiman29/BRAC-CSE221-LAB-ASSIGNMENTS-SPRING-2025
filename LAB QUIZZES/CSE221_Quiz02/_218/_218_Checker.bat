@echo off
for %%a in (py cpp java) do (
    powershell -command "if (Select-String -Path '.\EnterIDandLanguage.txt' -Pattern '%%a') { exit 1 } else { exit 0 }" || (
        for /f %%b in ('powershell -command "Get-Content 'EnterIDandLanguage.txt' -TotalCount 1"') do (
            powershell -command "if (Get-ChildItem -Path . -Filter '_218_%%b.%%a' -File) { exit 1 } else { exit 0 }" && (
                if %%a==py (
                    echo # %%b 0 >_218_%%b.%%a
                    echo # %COMPUTERNAME% %USERNAME%>>_218_%%b.%%a
                ) else (
                    echo // %%b 0 >_218_%%b.%%a
                    echo // %COMPUTERNAME% %USERNAME%>>_218_%%b.%%a
                )
                powershell -command "Get-Content '_218_Solution.%%a' | Add-Content '_218_%%b.%%a'"
            )
        )
        for /f "delims=" %%b in (_218_ForbiddenKeywords.txt) do (
            for %%c in (%%b) do (
                powershell -command "if (Select-String -Path '.\_218_Solution.%%a' -Pattern '%%c') { exit 1 } else { exit 0 }" || (
                    echo Code contains forbidden keyword: %%c
                    echo Score = 0/1
                    goto Ending
                )
            )
        )
        if %%a==py (
            pypy -m py_compile _218.py
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else pypy _218.py
            rd /q /s __pycache__ >nul
        )
        if %%a==cpp (
            c++ _218_Solution.cpp _218.cpp
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else .\a.exe
            del /q /s /a /f .\*.exe >nul
        )
        if %%a==java (
            javac _218_Solution.java _218.java
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else java _218
            del /q /s /a /f .\*.class >nul
        )
    )
)
:Ending
pause