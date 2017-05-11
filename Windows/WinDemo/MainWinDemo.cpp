#include <gtest/gtest.h>
#include <Windows.h>

#pragma comment(lib,"googletest/gtest/v1.8.0/vc12_Debug_Unicode_MD_x86/gtestd.lib")
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
