@echo off
chcp 65001 >nul
cd /d "%~dp0"
git add -A
git commit -m "每日提交 day1"
git push
echo.
echo 已完成，按任意键关闭
pause >nul
