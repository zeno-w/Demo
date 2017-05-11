#include <Windows.h>
#include <gtest/gtest.h>

class CMoveWindowTest : public testing::Test
{

protected:
	virtual void SetUp() override
	{
	}


	virtual void TearDown() override
	{
	}

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

		RECT rcPos = { 100, 100, 50, 50 };

		m_hMainWnd = CreateWindowEx(WS_EX_TOOLWINDOW|WS_EX_TOPMOST,MW_WINDOW_CLASS_NAME, L"MainWnd", WS_POPUP | WS_VISIBLE, rcPos.left, rcPos.top, 100, 100, NULL, NULL, wndClassEx.hInstance, NULL);
		SetWindowLong(m_hMainWnd, GWL_USERDATA, (LONG)this);

		m_hLTSibling = CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, MW_WINDOW_CLASS_NAME, L"LTSibling", WS_POPUP | WS_VISIBLE, rcPos.left - 13, rcPos.top - 13, 26, 26, NULL, NULL, wndClassEx.hInstance, NULL);
		SetWindowLong(m_hLTSibling, GWL_USERDATA, (LONG)this);

		m_hRTSibling = CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, MW_WINDOW_CLASS_NAME, L"RTSibling", WS_POPUP | WS_VISIBLE, rcPos.left + 87, rcPos.top - 13, 26, 26, NULL, NULL, wndClassEx.hInstance, NULL);
		SetWindowLong(m_hRTSibling, GWL_USERDATA, (LONG)this);

		m_hLBSibling = CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, MW_WINDOW_CLASS_NAME, L"LBSibling", WS_POPUP | WS_VISIBLE, rcPos.left - 13, rcPos.top + 87, 26, 26, NULL, NULL, wndClassEx.hInstance, NULL);
		SetWindowLong(m_hLBSibling, GWL_USERDATA, (LONG)this);

		m_hRBSibling = CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, MW_WINDOW_CLASS_NAME, L"RBSibling", WS_POPUP | WS_VISIBLE, rcPos.left + 87, rcPos.top + 87, 26, 26, NULL, NULL, wndClassEx.hInstance, NULL);
		SetWindowLong(m_hRBSibling, GWL_USERDATA, (LONG)this);
	}
	~CMoveWindow(){}

	void Move(const POINT &ptOffset)
	{
		POINT ptPos = { m_rcDragPos.left + ptOffset.x, m_rcDragPos.top + ptOffset.y };
		MoveWindow(m_hMainWnd, ptPos.x, ptPos.y, 100, 100, true);
		MoveWindow(m_hLTSibling, ptPos.x - 13, ptPos.y - 13, 26, 26, true);
		MoveWindow(m_hRTSibling, ptPos.x + 87, ptPos.y - 13, 26, 26, true);
		MoveWindow(m_hLBSibling, ptPos.x - 13, ptPos.y + 87, 26, 26, true);
		MoveWindow(m_hRBSibling, ptPos.x + 87, ptPos.y + 87, 26, 26, true);
	}

	bool m_bDrag;
	RECT m_rcDragPos;
	POINT m_ptDragStart;
	HWND m_hMainWnd;
	HWND m_hLTSibling;
	HWND m_hRTSibling;
	HWND m_hLBSibling;
	HWND m_hRBSibling;
};


LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	CMoveWindow *pThis;
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			pThis = (CMoveWindow*)::GetWindowLong(hwnd, GWL_USERDATA);
			pThis->m_bDrag = true;
			::GetCursorPos(&pThis->m_ptDragStart);
			GetWindowRect(pThis->m_hMainWnd, &pThis->m_rcDragPos);
			::SetCapture(hwnd);
		}	
		break;

	case WM_MOUSEMOVE:
	{
			pThis = (CMoveWindow*)::GetWindowLong(hwnd, GWL_USERDATA);
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
			pThis = (CMoveWindow*)::GetWindowLong(hwnd, GWL_USERDATA);
			pThis->m_bDrag = false;
			::ReleaseCapture();
		}	
		break;
	default:
		break;
	}

	return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
}


TEST_F(CMoveWindowTest,MultiWindowSyncMove)
{
	CMoveWindow *pMoveWindow = new CMoveWindow();
}