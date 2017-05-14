
#include <Winsock2.h>
#include <Windows.h>
#include <gtest/gtest.h>
#include <ZZUtility/ConcurrencyModel/IoCompletionPortModel.h>
#include <ZZUtility/ConcurrencyModel/TcpIOCP/TcpListenerHandler.h>
#include <ZZUtility/ConcurrencyModel/TcpIOCP/TcpSessionClientHandler.h>

#pragma comment(lib,"ws2_32.lib")
class TcpIOCPModelTest : public testing::Test
{
protected:
	CIoCompletionPortModel *m_pIOCPModel;

	TcpIOCPModelTest() : m_pIOCPModel(CIoCompletionPortModel::Instance())
	{}

	virtual void SetUp() override
	{
		WSADATA wsaData = { 0 };
		WSAStartup(MAKEWORD(2, 2), &wsaData);
	}

	virtual void TearDown() override
	{
		WSACleanup();
	}
};

TEST_F(TcpIOCPModelTest, TcpListener)
{
	CTcpListenerHandler *pTcpListener = CTcpListenerHandler::CreateAndAttachToIocp(8888);
	m_pIOCPModel->AttachHandler(pTcpListener);
}


TEST_F(TcpIOCPModelTest, TcpSessionClient)
{
	CTcpSessionClientHandler *pSession = CTcpSessionClientHandler::NewConnection("127.0.0.1", 8888);
	m_pIOCPModel->AttachHandler(pSession);
}