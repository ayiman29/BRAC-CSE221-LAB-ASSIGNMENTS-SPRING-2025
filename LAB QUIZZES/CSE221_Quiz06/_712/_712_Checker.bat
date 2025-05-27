@echo off
for %%a in (py cpp java) do (
    powershell -command "if (Select-String -Path '.\EnterIDandLanguage.txt' -Pattern '%%a') { exit 1 } else { exit 0 }" || (
        for /f %%b in ('powershell -command "Get-Content 'EnterIDandLanguage.txt' -TotalCount 1"') do (
            powershell -command "if (Get-ChildItem -Path . -Filter '_712_%%b.%%a' -File) { exit 1 } else { exit 0 }" && (
                if %%a==py (
                    echo # %%b 0 >_712_%%b.%%a
                    echo # %COMPUTERNAME% %USERNAME%>>_712_%%b.%%a
                ) else (
                    echo // %%b 0 >_712_%%b.%%a
                    echo // %COMPUTERNAME% %USERNAME%>>_712_%%b.%%a
                )
                powershell -command "Get-Content '_712_Solution.%%a' | Add-Content '_712_%%b.%%a'"
            )
        )
        for /f "delims=" %%b in (_712_ForbiddenKeywords.txt) do (
            for %%c in (%%b) do (
                powershell -command "if (Select-String -Path '.\_712_Solution.%%a' -Pattern '%%c') { exit 1 } else { exit 0 }" || (
                    echo Code contains forbidden keyword: %%c
                    echo Score = 0/1
                    goto Ending
                )
            )
        )
        c++ _712_Gen.cpp -Wl,--stack,536870912 -o _712_Gen.out -w
        c++ _712_Judge.cpp -Wl,--stack,536870912 -o _712_Judge.out -w 
        type nul > _712_input.txt
        type nul > _712_output.txt
        if %%a==py (
            pypy -m py_compile _712.py
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else pypy _712.py
            rd /q /s __pycache__ >nul
        )
        if %%a==cpp (
            c++ -Wl,--stack,536870912 _712_Solution.cpp _712.cpp
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else .\a.exe
            del /q /s /a /f .\*.exe >nul
        )
        if %%a==java (
            javac _712_Solution.java _712.java
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else java _712
            del /q /s /a /f .\*.class >nul
        )
        del  _712_Gen.out
        del  _712_Judge.out
        del  _712_input.txt
        del  _712_output.txt
        
    )
)
:Ending
pause
