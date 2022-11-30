#define _CRT_SECURE_NO_WARNINGS
  /**************************************/
 /*WARNING__该程序无法正常退出__WARNING*/
/**************************************/

#include<Windows.h>
#include<stdio.h>

HINSTANCE staticHIns = NULL;

LRESULT CALLBACK WinProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
		//消息处理，在此添加处理

	case WM_DESTROY:
		//PostQuitMessage(0);关闭程序

		//弹出新窗口
		HWND hWnd = CreateWindowEx(0, "TheWnd", "This Is Window", WS_OVERLAPPEDWINDOW, 
			//数字项除0外可随意更改
			(((int)GetTickCount()) * 12) % (1920 - 500), (((int)GetTickCount()) * 34) % (1080 - 500), 500, 500, 
			NULL, NULL, staticHIns, NULL);
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
		break;
	}

	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	//注册窗口类
	WNDCLASS wc{ 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(0xFFCC98);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WinProc;
	wc.lpszClassName = "TheWnd";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&wc);

	staticHIns = hIns;

	//在内存中创建窗口
	char pszText[] = "Hello data";
	HWND hWnd = CreateWindowEx(0, "TheWnd", "This Is Window", WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, NULL, NULL, hIns, pszText);

	//显示刷新窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//消息获取与处理-非阻塞处理
	MSG nMsg{ 0 };
	while (TRUE)
	{
		if (PeekMessage(&nMsg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&nMsg, NULL, 0, 0))
			{
				TranslateMessage(&nMsg);
				DispatchMessage(&nMsg);
			}
			else
			{
				break;
			}
		}
	}

	return 0;
}