@echo off
for %%a in (py cpp java) do (
    powershell -command "if (Select-String -Path '.\EnterIDandLanguage.txt' -Pattern '%%a') { exit 1 } else { exit 0 }" || (
        for /f %%b in ('powershell -command "Get-Content 'EnterIDandLanguage.txt' -TotalCount 1"') do (
            powershell -command "if (Get-ChildItem -Path . -Filter '_A7E_%%b.%%a' -File) { exit 1 } else { exit 0 }" && (
                if %%a==py (
                    echo # %%b 0 >_A7E_%%b.%%a
                    echo # %COMPUTERNAME% %USERNAME%>>_A7E_%%b.%%a
                ) else (
                    echo // %%b 0 >_A7E_%%b.%%a
                    echo // %COMPUTERNAME% %USERNAME%>>_A7E_%%b.%%a
                )
                powershell -command "Get-Content '_A7E_Solution.%%a' | Add-Content '_A7E_%%b.%%a'"
            )
        )
        for /f "delims=" %%b in (_A7E_ForbiddenKeywords.txt) do (
            for %%c in (%%b) do (
                powershell -command "if (Select-String -Path '.\_A7E_Solution.%%a' -Pattern '%%c') { exit 1 } else { exit 0 }" || (
                    echo Code contains forbidden keyword: %%c
                    echo Score = 0/1
                    goto Ending
                )
            )
        )
        c++ _A7E_Gen.cpp -Wl,--stack,536870912 -o _A7E_Gen.out -w
        c++ _A7E_Judge.cpp -Wl,--stack,536870912 -o _A7E_Judge.out -w 
        type nul > _A7E_input.txt
        type nul > _A7E_output.txt
        if %%a==py (
            pypy -m py_compile _A7E.py
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else pypy _A7E.py
            rd /q /s __pycache__ >nul
        )
        if %%a==cpp (
            c++ -Wl,--stack,536870912 _A7E_Solution.cpp _A7E.cpp
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else .\a.exe
            del /q /s /a /f .\*.exe >nul
        )
        if %%a==java (
            javac _A7E_Solution.java _A7E.java
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else java _A7E
            del /q /s /a /f .\*.class >nul
        )
        del  _A7E_Gen.out
        del  _A7E_Judge.out
        del  _A7E_input.txt
        del  _A7E_output.txt
        
    )
)
:Ending
pause
