@ECHO OFF

IF NOT EXIST C:\micwis\TowerDefense\trunk\bin\Debug (
	MKDIR C:\micwis\TowerDefense\trunk\bin\Debug
	ECHO "Debug dir Created"
) ELSE (
	ECHO "Debug already exists"
)

CD C:\micwis\TowerDefense\trunk\bin\Debug

IF EXIST graphics (
	rmdir /s /q graphics
	ECHO "Debug/Graphics Deleted"
) ELSE (
	ECHO "Graphics already deleted"
)

IF EXIST "path" (
	rmdir /s /q "path"
	ECHO "Debug/path Deleted"
) ELSE (
	ECHO "Path already Deleted"
)

CD C:\micwis\TowerDefense\trunk
XCOPY graphics bin\Debug\graphics /s /i
ECHO "Graphics Copied to Debug"

XCOPY "path" "bin\Debug\path" /s /i
ECHO "Path Copied to Debug"

CD "C:\micwis\TowerDefense\trunk\SFML-2.0\bin"
COPY sfml-graphics-d-2.dll "..\..\bin\Debug\" /b
COPY sfml-system-d-2.dll "..\..\bin\Debug\" /b
COPY sfml-window-d-2.dll "..\..\bin\Debug\" /b