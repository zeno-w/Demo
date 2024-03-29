#include <gtest/gtest.h>
#include <Windows.h>

#pragma comment(lib,"googletest/gtest/v1.8.0/vc12_Debug_Unicode_MD_x86/gtestd.lib")
int wmain(int argc, wchar_t *argv[])
{
	{
		wchar_t wszFile[MAX_PATH] = { 0 };
		if (GetModuleFileName(GetModuleHandle(NULL), wszFile, MAX_PATH) != 0)
		{
			*wcsrchr(wszFile, L'\\') = L'\0';
			SetCurrentDirectory(wszFile);
		}
	}
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
