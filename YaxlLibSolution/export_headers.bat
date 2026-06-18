@echo off
setlocal enabledelayedexpansion

:: カレントディレクトリをバッチファイルのある場所に変更
cd /d "%~dp0"

:: フォルダパスの設定
set "SRC_DIR=%~dp0YaxlLib"
set "DEST_DIR=%~dp0Output\inc"

echo ==========================================
echo  YaxlLib Header Exporter
echo ==========================================
echo.

:: Output\inc フォルダが存在する場合は一度削除
if exist "%DEST_DIR%" rmdir /s /q "%DEST_DIR%"
mkdir "%DEST_DIR%"

:: SRC_DIR内のすべての .h ファイルを再帰的に検索してループ処理
for /f "delims=" %%F in ('dir /s /b /a-d "%SRC_DIR%\*.h"') do (
    
    :: 絶対パスから YaxlLib\ までの文字列を消去し、相対パスを取得
    set "FULL_PATH=%%F"
    set "REL_PATH=!FULL_PATH:%SRC_DIR%\=!"

    :: 相対パスの先頭が "ExternalLibrary\" かどうかを判定（大文字小文字を区別しない）
    if /I "!REL_PATH:~0,16!"=="ExternalLibrary\" (
        :: 先頭の "ExternalLibrary\" を削ったものをターゲットパスにする
        set "TARGET_REL_PATH=!REL_PATH:~16!"
    ) else (
        :: それ以外のフォルダはそのままの階層を維持する
        set "TARGET_REL_PATH=!REL_PATH!"
    )

    set "TARGET_PATH=%DEST_DIR%\!TARGET_REL_PATH!"

    :: コピー先のフォルダ階層が存在しない場合は自動生成する
    for %%D in ("!TARGET_PATH!") do (
        if not exist "%%~dpD" mkdir "%%~dpD"
    )

    :: ファイルをコピー
    copy /y "%%F" "!TARGET_PATH!" > nul
    
    :: ログの出力
    echo Copied: !TARGET_REL_PATH!
)

echo.
echo ==========================================
echo  Export completed!
echo ==========================================
pause