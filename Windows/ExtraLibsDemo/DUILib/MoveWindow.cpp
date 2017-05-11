#include <Windows.h>
#include "DUITest.h"

class CMoveWindowCorner :
	public WindowImplBase
{

	friend class CMoveWindow;
public:
	CMoveWindowCorner(void)
	{
		CreateDuiWindow(NULL, L"CMoveWindowCorner", WS_POPUP | WS_VISIBLE, WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
		m_hWnd;
	}
	~CMoveWindowCorner(void)
	{}


	virtual UINT GetClassStyle() const override
	{
		return CS_DROPSHADOW | __super::GetClassStyle();
	}

protected:

	virtual CDuiString	GetSkinFile()
	{
		return  _T("MoveWindowCorner.xml");
	}

	virtual LPCTSTR		GetWindowClassName(void) const
	{
		return L"CMoveWindowCornerWindowClassName";
	}

	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam)
	{
		return FALSE; 
	};


	virtual CDuiString GetSkinFolder() override
	{
		return L"";
	}

public:

	CHorizontalLayoutUI*	m_pTopLayout;
private:
	bool			m_bIsShow;



};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
class CMoveWindow
{
#define MW_WINDOW_CLASS_NAME L"MOVE_WINDOW_TEST_CLASS_NAME"
public:
	CMoveWindow() : m_bDrag(false)
	{
		WNDCLASSEX wndClassEx = { 0 };
		wndClassEx.cbSize = sizeof(wndClassEx);
		wndClassEx.style = CS_CLASSDC | CS_PARENTDC | CS_NOCLOSE | CS_DROPSHADOW;
		wndClassEx.hInstance = GetModuleHandle(NULL);
		wndClassEx.lpszClassName = MW_WINDOW_CLASS_NAME;
		wndClassEx.lpfnWndProc = WindowProc;
		wndClassEx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
		wndClassEx.hCursor = ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));

		if (RegisterClassEx(&wndClassEx) == 0)
			return;

		POINT ptPos = { 100, 100};

		m_hMainWnd = CreateWindowEx(WS_EX_TOOLWINDOW,MW_WINDOW_CLASS_NAME, L"MainWnd", WS_POPUP | WS_VISIBLE, ptPos.x, ptPos.y, 100, 100, NULL, NULL, wndClassEx.hInstance, NULL);
		SetWindowLong(m_hMainWnd, GWL_USERDATA, (LONG)this);

		m_pLTCorner = new CMoveWindowCorner();
		m_pRTCorner = new CMoveWindowCorner();
		m_pLBCorner = new CMoveWindowCorner();
		m_pRBCorner = new CMoveWindowCorner();
		MoveCorner();
// 		MoveWindow(m_pLTCorner->m_hWnd, ptPos.x - 13, ptPos.y - 13, 26, 26, true);
// 		MoveWindow(m_pRTCorner->m_hWnd, ptPos.x + 87, ptPos.y - 13, 26, 26, true);
// 		MoveWindow(m_pLBCorner->m_hWnd, ptPos.x - 13, ptPos.y + 87, 26, 26, true);
// 		MoveWindow(m_pRBCorner->m_hWnd, ptPos.x + 87, ptPos.y + 87, 26, 26, true);
	}
	~CMoveWindow(){}

	void Move(const POINT &ptOffset)
	{
		POINT ptPos = { m_rcDragPos.left + ptOffset.x, m_rcDragPos.top + ptOffset.y };
		SetWindowPos(m_hMainWnd, HWND_TOPMOST, ptPos.x, ptPos.y, 100, 100, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOSIZE);
// 		SetWindowPos(m_pLTCorner->m_hWnd, HWND_TOPMOST, ptPos.x - 13, ptPos.y - 13, 0, 0, SWP_NOSIZE);
// 		SetWindowPos(m_pRTCorner->m_hWnd, HWND_TOPMOST, ptPos.x + 87, ptPos.y - 13, 0, 0, SWP_NOSIZE);
// 		SetWindowPos(m_pLBCorner->m_hWnd, HWND_TOPMOST, ptPos.x - 13, ptPos.y + 87, 0, 0, SWP_NOSIZE);
// 		SetWindowPos(m_pRBCorner->m_hWnd, HWND_TOPMOST, ptPos.x + 87, ptPos.y + 87, 0, 0, SWP_NOSIZE);
// 		MoveWindow(m_pLTCorner->m_hWnd, ptPos.x - 13, ptPos.y - 13, 26, 26, true);
// 		MoveWindow(m_pRTCorner->m_hWnd, ptPos.x + 87, ptPos.y - 13, 26, 26, true);
// 		MoveWindow(m_pLBCorner->m_hWnd, ptPos.x - 13, ptPos.y + 87, 26, 26, true);
// 		MoveWindow(m_pRBCorner->m_hWnd, ptPos.x + 87, ptPos.y + 87, 26, 26, true);
	}

	void MoveCorner()
	{
		RECT rcPos;
		GetWindowRect(m_hMainWnd,&rcPos);
		SetWindowPos(m_pLTCorner->m_hWnd, HWND_TOPMOST, rcPos.left - 13, rcPos.top - 13, 0, 0, SWP_NOSIZE);
		SetWindowPos(m_pRTCorner->m_hWnd, HWND_TOPMOST, rcPos.left + 87, rcPos.top - 13, 0, 0, SWP_NOSIZE);
		SetWindowPos(m_pLBCorner->m_hWnd, HWND_TOPMOST, rcPos.left - 13, rcPos.top + 87, 0, 0, SWP_NOSIZE);
		SetWindowPos(m_pRBCorner->m_hWnd, HWND_TOPMOST, rcPos.left + 87, rcPos.top + 87, 0, 0, SWP_NOSIZE);
// 		MoveWindow(m_pLTCorner->m_hWnd, rcPos.left - 13, rcPos.top - 13, 26, 26, true);
// 		MoveWindow(m_pRTCorner->m_hWnd, rcPos.left + 87, rcPos.top - 13, 26, 26, true);
// 		MoveWindow(m_pLBCorner->m_hWnd, rcPos.left - 13, rcPos.top + 87, 26, 26, true);
// 		MoveWindow(m_pRBCorner->m_hWnd, rcPos.left + 87, rcPos.top + 87, 26, 26, true);
	}

	bool m_bDrag;
	RECT m_rcDragPos;
	POINT m_ptDragStart;
	HWND m_hMainWnd;
	CMoveWindowCorner *m_pLTCorner;
	CMoveWindowCorner *m_pRTCorner;
	CMoveWindowCorner *m_pLBCorner;
	CMoveWindowCorner *m_pRBCorner;
};


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOVE:
	{
		CMoveWindow *pThis = (CMoveWindow*)::GetWindowLong(hwnd, GWL_USERDATA);
		if (pThis->m_bDrag)
		{
			pThis->MoveCorner();
		}
	}
		break;

	case WM_LBUTTONDOWN:
	{
		CMoveWindow *pThis = (CMoveWindow*)::GetWindowLong(hwnd, GWL_USERDATA);
		pThis->m_bDrag = true;
		::SetCapture(hwnd);
		::GetCursorPos(&pThis->m_ptDragStart);
		GetWindowRect(pThis->m_hMainWnd, &pThis->m_rcDragPos);
		pThis->MoveCorner();
	}
	break;

	case WM_MOUSEMOVE:
	{
		CMoveWindow *pThis = (CMoveWindow*)::GetWindowLong(hwnd, GWL_USERDATA);
		if (pThis->m_bDrag)
		{
			POINT ptOffset;
			::GetCursorPos(&ptOffset);
			ptOffset.x -= pThis->m_ptDragStart.x;
			ptOffset.y -= pThis->m_ptDragStart.y;
			pThis->Move(ptOffset);
		}
	}
	break;

	case WM_LBUTTONUP:
		{
			::ReleaseCapture();
			CMoveWindow *pThis = (CMoveWindow*)::GetWindowLong(hwnd, GWL_USERDATA);
			pThis->m_bDrag = false;
		}
		break;
	default:
		break;
	}

	return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
}

TEST_F(CDUITest, MultiWindowSyncMove)
{
	CMoveWindow *pMoveWindow = new CMoveWindow();
}