#include "stdafx.h"
#include "TBSwitcher.h"

namespace tbctrl
{
	//----------------------------------------------------------------
	// Get taskbar stauts.
	// Ret: ABS_AUTOHIDE    0x0000001
	//      ABS_ALWAYSONTOP 0x0000002
	//----------------------------------------------------------------
	UINT getTaskbarState()
	{
		// Initialize structure data.
		APPBARDATA pData;
		ZeroMemory(&pData, sizeof(APPBARDATA));
		pData.cbSize = sizeof(APPBARDATA);

		// Get status.
		return SHAppBarMessage(ABM_GETSTATE, &pData);
	}

	//----------------------------------------------------------------
	// Set taskbar status.
	// In: param - ABM_NEW     Show taskbar.
	//             ABM_REMOVE  Auto hide taskbar.
	//----------------------------------------------------------------
	void setTaskbarState(LPARAM param)
	{
		auto hWnd = FindWindow(_T("Shell_TrayWnd"), NULL);
		if (hWnd != NULL)
		{
			// Taskbar settings.
			APPBARDATA pData;
			ZeroMemory(&pData, sizeof(APPBARDATA));
			pData.cbSize = sizeof(APPBARDATA);
			pData.hWnd = hWnd;
			pData.lParam = param;

			// Send message.
			SHAppBarMessage(ABM_SETSTATE, &pData);
		}
	}
};


using namespace tbctrl;

//----------------------------------------------------------------
// Entry point.
//----------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// Switch taskbar status.
	UINT status = getTaskbarState();
	if (status == ABS_AUTOHIDE)
	{
		// Show taskbar.
		setTaskbarState(ABM_NEW);
	}
	else
	{
		// Auto hide taskbar.
		setTaskbarState(ABM_REMOVE);
	}

	return 0;
}

