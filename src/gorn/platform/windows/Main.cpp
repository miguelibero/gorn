#include <windows.h>
#include <gorn/render/Gl.hpp>
#include <gorn/base/Application.hpp>

HDC hDC;
HGLRC hGLRC;
HPALETTE hPalette;
std::unique_ptr<gorn::Application> app;
_int64 timeStamp;
_int64 timeStampFreq;

void
load() {
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		MessageBox(NULL, (char*)glewGetErrorString(err), NULL, NULL);
	}
	else
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&timeStamp);
		QueryPerformanceFrequency((LARGE_INTEGER *)&timeStampFreq);
		app->realLoad();
	}
}

void unload()
{
	if (app) {
		app->realUnload();
	}
}

void update()
{
	_int64 oldTimeStamp = timeStamp;
	QueryPerformanceCounter((LARGE_INTEGER*)&timeStamp);
	if (app) {
		double dt = (double)(timeStamp - oldTimeStamp)/timeStampFreq;
		app->realUpdate(dt);
	}
}

void draw()
{
	SwapBuffers(hDC);
}

void foreground()
{
	if (app) {
		app->realForeground();
	}
}

void background()
{
	if (app) {
		app->realBackground();
	}
}

void
resize(int width, int height)
{
	/* set viewport to cover the window */
	glViewport(0, 0, width, height);
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
			resize((int)LOWORD(lParam), (int)HIWORD(lParam));
			return 0;
		}
	case WM_PALETTECHANGED:
		/* realize palette if this is *not* the current window */
		if (hGLRC && hPalette && (HWND)wParam != hWnd) {
			UnrealizeObject(hPalette);
			SelectPalette(hDC, hPalette, FALSE);
			RealizePalette(hDC);
			draw();
			break;
		}
		break;
	case WM_QUERYNEWPALETTE:
		/* realize palette if this is the current window */
		if (hGLRC && hPalette) {
			UnrealizeObject(hPalette);
			SelectPalette(hDC, hPalette, FALSE);
			RealizePalette(hDC);
			draw();
			return TRUE;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		if (hGLRC) {
			draw();
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
	update();
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int APIENTRY
WinMain(
HINSTANCE hCurrentInst,
HINSTANCE hPreviousInst,
LPSTR lpszCmdLine,
int nCmdShow)
{
	app = gorn::main();
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
	wndClass.lpszClassName = app->getName().c_str();
	RegisterClass(&wndClass);

	/* create window */
	hWnd = CreateWindow(
		app->getName().c_str(), app->getName().c_str(),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		0, 0, app->getSize().x, app->getSize().y,
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