#include <stdio.h>

/*
int main(int argc, char** argv)
{
printf("hello\n");
return 0;
}


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
_In_opt_ HINSTANCE hPrevInstance,
_In_ LPTSTR    lpCmdLine,
_In_ int       nCmdShow)

*/


// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// path: "C:\Program Files\aaa\bbb.exe"
// cygRootPath: "/cygdrive/"   (or "/" for gnupack)
int convertToCygwinPath(const char* path, const char* cygRootPath, char* converted)
{
	char quoted = '\0';
	if (path[0] == '\"' || path[0] == '\'') {
		quoted = path[0];
		path++;

		converted[0] = quoted;
		converted++;
	}

	if (path[1] == ':' && path[2] == '\\') {
		// absolute path
		sprintf_s(converted, 1024, "%s", cygRootPath);
		converted += strlen(converted - 1);
		if (*converted != '/') {
			converted++;
			*converted = '/';
		}
		converted++;
	} else {
		// relative path
	}

	while (*path != '\0') {
		char ch = *path++;
		if (ch == '\\') {
			ch = '/';
		}
		*converted = ch;
		converted++;
	}
	*converted = '\0';

	return 0;
}

//Windows アプリケーションの場合
//int _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int WINAPI WinMain(HINSTANCE hInstCurrent, HINSTANCE hinstPrevious, LPSTR lpszCmdLine, int nCmdShow)
//int WinMain(int argc, char** argv)
{
	printf("hello\n");

	// http://win32lab.com/tips/tips3.html
	char    szStrTmp[1024 + 1];
	int     i;

	sprintf_s(szStrTmp, "コマンドライン引数の数 %d", __argc);
	//MessageBox(NULL, szStrTmp, "tips3", MB_OK);

	for (i = 0; i<__argc; i++)
	{
		sprintf_s(szStrTmp, "第%lu引数\n%s", i, __argv[i]);
		MessageBoxA(NULL, szStrTmp, "tips3", MB_OK);
	}
	return 0;
}
