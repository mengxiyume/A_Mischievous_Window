#define _CRT_SECURE_NO_WARNINGS
  /**************************************/
 /*WARNING__�ó����޷������˳�__WARNING*/
/**************************************/

#include<Windows.h>
#include<stdio.h>

HINSTANCE staticHIns = NULL;

LRESULT CALLBACK WinProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
		//��Ϣ�����ڴ���Ӵ���

	case WM_DESTROY:
		//PostQuitMessage(0);�رճ���

		//�����´���
		HWND hWnd = CreateWindowEx(0, "TheWnd", "This Is Window", WS_OVERLAPPEDWINDOW, 
			//�������0����������
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
	//ע�ᴰ����
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

	//���ڴ��д�������
	char pszText[] = "Hello data";
	HWND hWnd = CreateWindowEx(0, "TheWnd", "This Is Window", WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, NULL, NULL, hIns, pszText);

	//��ʾˢ�´���
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//��Ϣ��ȡ�봦��-����������
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