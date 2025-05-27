@echo off
for %%a in (py cpp java) do (
    powershell -Command "if (Select-String -Path '.\EnterIDandLanguage.txt' -Pattern '%%a') { exit 1 } else { exit 0 }" || (
        for %%b in (sort main scan print input output file read write thread process) do (
            powershell -Command "if (Select-String -Path '.\_A1E_Solution.%%a' -Pattern '%%b') { exit 1 } else { exit 0 }" || (
                echo Code contains forbidden keyword: %%b
                echo Score = 0/1
                goto Ending
            )
        )
        if %%a==py (
            pypy _A1E.py
            rd /q /s __pycache__ >nul
        )
        if %%a==cpp (
            c++ _A1E_Solution.cpp _A1E.cpp && .\a.exe
            del /q /s /a /f .\*.exe >nul
        )
        if %%a==java (
            javac _A1E_Solution.java _A1E.java && java _A1E
            del /q /s /a /f .\*.class >nul
        )
    )
)
:Ending
pause
