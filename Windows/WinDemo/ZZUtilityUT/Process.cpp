
#include <gtest/gtest.h>
#include <ZZUtility/Process/SingleProcessGuard.h>

class ProcessTest : public testing::Test
{
protected:

	ProcessTest()

	{}

	virtual void SetUp() override
	{
	}

	virtual void TearDown() override
	{
	}
};

TEST_F(ProcessTest,SingleProcessGuid)
{
	CSingleProcessGuard guid;
	EXPECT_TRUE(guid.Guard(L"SingleProcessGuid.lock")) <<"Single process guid falied!";


	CSingleProcessGuard guid1;
	EXPECT_TRUE(guid1.Guard(L"SingleProcessGuid.lock")) << "Single process guid falied!";


}


TEST_F(ProcessTest, SingleProcessIsGuid)
{
	CSingleProcessGuard guid1;
	EXPECT_FALSE(guid1.IsGuarded(L"SingleProcessGuid.lock")) << "Single process guid falied!";
}

