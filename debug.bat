@ECHO OFF

IF NOT EXIST E:\Programming\TowerDefense\bin (
	MKDIR E:\Programming\TowerDefense\bin
	ECHO "Debug dir Created"
) ELSE (
	ECHO "Debug already exists"
)

CD E:\Programming\TowerDefense\bin

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

CD E:\Programming\TowerDefense
XCOPY graphics bin\graphics /s /i
ECHO "Graphics Copied to Debug"

XCOPY path bin\path /s /i
ECHO "Path Copied to Debug"

CD "E:\Programming\TowerDefense\SFML\bin"
COPY sfml-graphics-d-2.dll "../..\bin\" /b
COPY sfml-system-d-2.dll "../..\bin\" /b
COPY sfml-window-d-2.dll "../..\bin\" /b

ECHO "sfml dlls copied to Debug

CD "E:\Programming\TowerDefense\resources"
COPY libgcc_s_dw2-1.dll "../bin/" /b
COPY "libstdc++-6.dll" "../bin/" /b