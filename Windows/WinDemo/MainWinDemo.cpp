#include <gtest/gtest.h>
#include <Windows.h>

#pragma comment(lib,"googletest/gtest/v1.8.0/vc12_Debug_Unicode_MD_x86/gtestd.lib")
int wmain(int argc, wchar_t *argv[])
{
	printf("Running wmain() from gtest_main.cc/n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}