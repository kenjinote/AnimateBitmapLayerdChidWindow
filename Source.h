//
// AnimateLayeredChildWindow.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once

#define _WIN32_WINNT 0x06000000
// Modify the following definitions if you need to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER              // Allow use of features specific to Windows 7 or later.
#define WINVER 0x0700       // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT        // Allow use of features specific to Windows 7 or later.
#define _WIN32_WINNT 0x0700 // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used items from Windows headers

// Windows Header Files:
#include <windows.h>
#include <wincodec.h>

// C RunTime Header Files
#include <math.h>

// DirectComposition Header File
#include <dcomp.h>

// Direct2D Header Files
#include <d2d1.h>
#include <d2d1helper.h>

// Desktop Window Manager (DWM) Header File
#include <dwmapi.h>


/******************************************************************
*                                                                 *
*  Macros                                                         *
*                                                                 *
******************************************************************/
template<class Interface>
inline void
SafeRelease(
    Interface** ppInterfaceToRelease
)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

/******************************************************************
*                                                                 *
*  DemoApp                                                        *
*                                                                 *
******************************************************************/

class DemoApp
{
public:
    DemoApp();
    ~DemoApp();

    HRESULT InitializeMainWindow();
    HRESULT InitializeLayeredChildWindow();

    void RunMessageLoop();

private:
    HRESULT InitializeDirectCompositionObjects();

    HRESULT CreateDeviceIndependentResources();
    HRESULT CreateDeviceResources();
    void DiscardDeviceResources();

    HRESULT OnChildClick();
    HRESULT OnChildRender();

    HRESULT LoadResourceD2DBitmap(
        ID2D1RenderTarget* pRenderTarget,
        IWICImagingFactory* pIWICFactory,
        PCWSTR resourceName,
        PCWSTR resourceType,
        ID2D1Bitmap** ppBitmap
    );

    static LRESULT CALLBACK MainWndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

    static LRESULT CALLBACK ChildWndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

private:
    int m_dpiX;
    int m_dpiY;
    int m_childOffsetX;
    int m_childOffsetY;

    HWND m_hwndMain;
    HWND m_hwndLayeredChild;

    IDCompositionDevice* m_pDevice;
    IDCompositionTarget* m_pCompTarget;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    ID2D1Factory* m_pD2DFactory;
    ID2D1Bitmap* m_pBitmap;
    IWICImagingFactory* m_pWICFactory;

};
