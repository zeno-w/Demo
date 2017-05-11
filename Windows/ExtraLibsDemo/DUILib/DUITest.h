
#define UILIB_STATIC
#include <Windows.h>
#include <gtest/gtest.h>
#include <DUILib/UIlib.h>

using namespace DuiLib;

class CDUITest : public testing::Test
{
protected:
	virtual void SetUp() override
	{
		CPaintManagerUI::SetInstance(GetModuleHandle(NULL));
		CPaintManagerUI::SetResourcePath(_T("DUILib"));
	}


	virtual void TearDown() override
	{

	}

};