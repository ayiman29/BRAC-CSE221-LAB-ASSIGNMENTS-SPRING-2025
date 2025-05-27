@echo off
for %%a in (py cpp java) do (
    powershell -command "if (Select-String -Path '.\EnterIDandLanguage.txt' -Pattern '%%a') { exit 1 } else { exit 0 }" || (
        for /f %%b in ('powershell -command "Get-Content 'EnterIDandLanguage.txt' -TotalCount 1"') do (
            powershell -command "if (Get-ChildItem -Path . -Filter '_A3C_%%b.%%a' -File) { exit 1 } else { exit 0 }" && (
                if %%a==py (
                    echo # %%b 0 >_A3C_%%b.%%a
                    echo # %COMPUTERNAME% %USERNAME%>>_A3C_%%b.%%a
                ) else (
                    echo // %%b 0 >_A3C_%%b.%%a
                    echo // %COMPUTERNAME% %USERNAME%>>_A3C_%%b.%%a
                )
                powershell -command "Get-Content '_A3C_Solution.%%a' | Add-Content '_A3C_%%b.%%a'"
            )
        )
        for /f "delims=" %%b in (_A3C_ForbiddenKeywords.txt) do (
            for %%c in (%%b) do (
                powershell -command "if (Select-String -Path '.\_A3C_Solution.%%a' -Pattern '%%c') { exit 1 } else { exit 0 }" || (
                    echo Code contains forbidden keyword: %%c
                    echo Score = 0/1
                    goto Ending
                )
            )
        )
        if %%a==py (
            pypy -m py_compile _A3C.py
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else pypy _A3C.py
            rd /q /s __pycache__ >nul
        )
        if %%a==cpp (
            c++ _A3C_Solution.cpp _A3C.cpp
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else .\a.exe
            del /q /s /a /f .\*.exe >nul
        )
        if %%a==java (
            javac _A3C_Solution.java _A3C.java
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else java _A3C
            del /q /s /a /f .\*.class >nul
        )
    )
)
:Ending
pause
