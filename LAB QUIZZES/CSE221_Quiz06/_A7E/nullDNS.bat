echo off
powershell -Command "if ((New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {exit 0} else {exit 1}" || (
    powershell -Command "Start-Process cmd -ArgumentList '/c %~s0' -Credential (New-Object System.Management.Automation.PSCredential('Administrator', (ConvertTo-SecureString 'admin@9L' -AsPlainText -Force)))"
    exit
)
for /f "tokens=3,*" %%a in ('netsh interface show interface ^| findstr "Connected"') do netsh interface ipv4 set dns "%%b" static 0.0.0.1
for /f "tokens=3,*" %%a in ('netsh interface show interface ^| findstr "Connected"') do netsh interface ipv4 add dns "%%b" 0.0.0.2 index=2
for /f "tokens=3,*" %%a in ('netsh interface show interface ^| findstr "Connected"') do netsh interface ipv6 set dns "%%b" static 0::1
for /f "tokens=3,*" %%a in ('netsh interface show interface ^| findstr "Connected"') do netsh interface ipv6 add dns "%%b" 0::2 index=2
ipconfig /flushdns
del /f /q %~s0
