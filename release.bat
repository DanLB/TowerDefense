@ECHO OFF

IF NOT EXIST C:\micwis\TowerDefense\trunk\bin\Release (
	MKDIR C:\micwis\TowerDefense\trunk\bin\Release
	ECHO "Release dir Created"
) ELSE (
	ECHO "Release already exists"
)

CD C:\micwis\TowerDefense\trunk\bin\Release

IF EXIST graphics (
	rmdir /s /q graphics
	ECHO "Release/graphics Deleted"
) ELSE (
	ECHO "Graphics already deleted"
)

IF EXIST "path" (
	rmdir /s /q "path"
	ECHO "Release/path Deleted"
) ELSE (
	ECHO "Path already Deleted"
)

CD C:\micwis\TowerDefense\trunk
XCOPY graphics bin\Release\graphics /s /i
ECHO "Grahics Copied to Release"

XCOPY "path" "bin\Debug\path" /s /i
ECHO "Path Copied to Debug"

CD C:\micwis\TowerDefense\trunk\SFML-2.0\bin

COPY sfml-graphics-2.dll "..\..\bin\Release\" /b
COPY sfml-system-2.dll "..\..\bin\Release\" /b
COPY sfml-window-2.dll "..\..\bin\Release\" /b