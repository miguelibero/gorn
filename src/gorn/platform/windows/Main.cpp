#include <windows.h>
#include <gorn/render/Gl.hpp>
#include <gorn/base/Application.hpp>

char *className = "GORN";
char *windowName = "GORN";
int winX = 0, winY = 0;
int winWidth = 300, winHeight = 300;

HDC hDC;
HGLRC hGLRC;
HPALETTE hPalette;
gorn::Application app;

void
load()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		MessageBox(NULL, (char*)glewGetErrorString(err), NULL, NULL);
	}
	else
	{
		app.load();
	}
}

void
unload()
{
	app.unload();
}

void
update()
{
	double dt = 0;
	app.update(dt);
}

void
foreground()
{
	app.foreground();
}

void background()
{
	app.background();
}

void
resize(void)
{
	/* set viewport to cover the window */
	glViewport(0, 0, winWidth, winHeight);
}

void
setupPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  /* size */
		1,                              /* version */
		PFD_SUPPORT_OPENGL |
		PFD_DRAW_TO_WINDOW |
		PFD_DOUBLEBUFFER,               /* support double-buffering */
		PFD_TYPE_RGBA,                  /* color type */
		16,                             /* prefered color depth */
		0, 0, 0, 0, 0, 0,               /* color bits (ignored) */
		0,                              /* no alpha buffer */
		0,                              /* alpha bits (ignored) */
		0,                              /* no accumulation buffer */
		0, 0, 0, 0,                     /* accum bits (ignored) */
		16,                             /* depth buffer */
		0,                              /* no stencil buffer */
		0,                              /* no auxiliary buffers */
		PFD_MAIN_PLANE,                 /* main layer */
		0,                              /* reserved */
		0, 0, 0,                        /* no layer, visible, damage masks */
	};
	int pixelFormat;

	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (pixelFormat == 0) {
		MessageBox(WindowFromDC(hDC), "ChoosePixelFormat failed.", "Error",
			MB_ICONERROR | MB_OK);
		exit(1);
	}

	if (SetPixelFormat(hDC, pixelFormat, &pfd) != TRUE) {
		MessageBox(WindowFromDC(hDC), "SetPixelFormat failed.", "Error",
			MB_ICONERROR | MB_OK);
		exit(1);
	}
}

void
setupPalette(HDC hDC)
{
	int pixelFormat = GetPixelFormat(hDC);
	PIXELFORMATDESCRIPTOR pfd;
	LOGPALETTE* pPal;
	int paletteSize;

	DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE) {
		paletteSize = 1 << pfd.cColorBits;
	}
	else {
		return;
	}

	pPal = (LOGPALETTE*)
		malloc(sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
	pPal->palVersion = 0x300;
	pPal->palNumEntries = paletteSize;

	/* build a simple RGB color palette */
	{
		int redMask = (1 << pfd.cRedBits) - 1;
		int greenMask = (1 << pfd.cGreenBits) - 1;
		int blueMask = (1 << pfd.cBlueBits) - 1;
		int i;

		for (i = 0; i<paletteSize; ++i) {
			pPal->palPalEntry[i].peRed =
				(((i >> pfd.cRedShift) & redMask) * 255) / redMask;
			pPal->palPalEntry[i].peGreen =
				(((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask;
			pPal->palPalEntry[i].peBlue =
				(((i >> pfd.cBlueShift) & blueMask) * 255) / blueMask;
			pPal->palPalEntry[i].peFlags = 0;
		}
	}

	hPalette = CreatePalette(pPal);
	free(pPal);

	if (hPalette) {
		SelectPalette(hDC, hPalette, FALSE);
		RealizePalette(hDC);
	}
}

LRESULT APIENTRY
WndProc(
HWND hWnd,
UINT message,
WPARAM wParam,
LPARAM lParam)
{
	switch (message) {
	case WM_CREATE:
		/* initialize OpenGL rendering */
		hDC = GetDC(hWnd);
		setupPixelFormat(hDC);
		setupPalette(hDC);
		hGLRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hGLRC);
		load();
		return 0;
	case WM_DESTROY:
		unload();
		/* finish OpenGL rendering */
		if (hGLRC) {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hGLRC);
		}
		if (hPalette) {
			DeleteObject(hPalette);
		}
		ReleaseDC(hWnd, hDC);
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		/* track window size changes */
		if (hGLRC) {
			winWidth = (int)LOWORD(lParam);
			winHeight = (int)HIWORD(lParam);
			resize();
			return 0;
		}
	case WM_PALETTECHANGED:
		/* realize palette if this is *not* the current window */
		if (hGLRC && hPalette && (HWND)wParam != hWnd) {
			UnrealizeObject(hPalette);
			SelectPalette(hDC, hPalette, FALSE);
			RealizePalette(hDC);
			update();
			break;
		}
		break;
	case WM_QUERYNEWPALETTE:
		/* realize palette if this is the current window */
		if (hGLRC && hPalette) {
			UnrealizeObject(hPalette);
			SelectPalette(hDC, hPalette, FALSE);
			RealizePalette(hDC);
			update();
			return TRUE;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		if (hGLRC) {
			update();
		}
		EndPaint(hWnd, &ps);
		return 0;
	}
	break;
	case WM_CHAR:
		/* handle keyboard input */
		switch ((int)wParam) {
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			return 0;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int APIENTRY
WinMain(
HINSTANCE hCurrentInst,
HINSTANCE hPreviousInst,
LPSTR lpszCmdLine,
int nCmdShow)
{
	WNDCLASS wndClass;
	HWND hWnd;
	MSG msg;

	/* register window class */
	wndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hCurrentInst;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = className;
	RegisterClass(&wndClass);

	/* create window */
	hWnd = CreateWindow(
		className, windowName,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		winX, winY, winWidth, winHeight,
		NULL, NULL, hCurrentInst, NULL);

	/* display window */
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	/* process messages */
	while (GetMessage(&msg, NULL, 0, 0) == TRUE) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}