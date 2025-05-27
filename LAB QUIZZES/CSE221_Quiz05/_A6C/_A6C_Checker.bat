@echo off
for %%a in (py cpp java) do (
    powershell -command "if (Select-String -Path '.\EnterIDandLanguage.txt' -Pattern '%%a') { exit 1 } else { exit 0 }" || (
        for /f %%b in ('powershell -command "Get-Content 'EnterIDandLanguage.txt' -TotalCount 1"') do (
            powershell -command "if (Get-ChildItem -Path . -Filter '_A6C_%%b.%%a' -File) { exit 1 } else { exit 0 }" && (
                if %%a==py (
                    echo # %%b 0 >_A6C_%%b.%%a
                    echo # %COMPUTERNAME% %USERNAME%>>_A6C_%%b.%%a
                ) else (
                    echo // %%b 0 >_A6C_%%b.%%a
                    echo // %COMPUTERNAME% %USERNAME%>>_A6C_%%b.%%a
                )
                powershell -command "Get-Content '_A6C_Solution.%%a' | Add-Content '_A6C_%%b.%%a'"
            )
        )
        for /f "delims=" %%b in (_A6C_ForbiddenKeywords.txt) do (
            for %%c in (%%b) do (
                powershell -command "if (Select-String -Path '.\_A6C_Solution.%%a' -Pattern '%%c') { exit 1 } else { exit 0 }" || (
                    echo Code contains forbidden keyword: %%c
                    echo Score = 0/1
                    goto Ending
                )
            )
        )
        c++ _A6C_Gen.cpp -Wl,--stack,536870912 -o _A6C_Gen.out -w
        c++ _A6C_Judge.cpp -Wl,--stack,536870912 -o _A6C_Judge.out -w 
        type nul > _A6C_input.txt
        type nul > _A6C_output.txt
        if %%a==py (
            pypy -m py_compile _A6C.py
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else pypy _A6C.py
            rd /q /s __pycache__ >nul
        )
        if %%a==cpp (
            c++ -Wl,--stack,536870912 _A6C_Solution.cpp _A6C.cpp
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else .\a.exe
            del /q /s /a /f .\*.exe >nul
        )
        if %%a==java (
            javac _A6C_Solution.java _A6C.java
            if errorlevel 1 (
                echo CompilationError
                echo Score = 0/1
            ) else java _A6C
            del /q /s /a /f .\*.class >nul
        )
        del  _A6C_Gen.out
        del  _A6C_Judge.out
        del  _A6C_input.txt
        del  _A6C_output.txt
        
    )
)
:Ending
pause
