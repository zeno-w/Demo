#include <gtest/gtest.h>
#include <Windows.h>

int wmain(int argc, wchar_t *argv[])
{
	printf("Running wmain() from gtest_main.cc/n");
	testing::InitGoogleTest(&argc, argv);

	RUN_ALL_TESTS();

	BOOL fGotMessage;
	MSG msg;

	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

#pragma comment(lib,"googletest/gtest/v1.8.0/vc12_Debug_Unicode_MD_x86/gtestd.lib")
#pragma comment(lib,"DuiLib/v1.0/vc12.0_U_MD_Debug_Lib/DuiLib.lib")
