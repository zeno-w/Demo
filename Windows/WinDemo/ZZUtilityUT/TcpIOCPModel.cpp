
#include <Winsock2.h>
#include <Windows.h>
#include <gtest/gtest.h>
#include <ZZUtility/ConcurrencyModel/IoCompletionPortModel.h>
#include <ZZUtility/ConcurrencyModel/TcpIOCP/TcpListenerHandler.h>
#include <ZZUtility/ConcurrencyModel/TcpIOCP/TcpClientSessionHandler.h>
#include <ZZUtility/ConcurrencyModel/TcpIOCP/TcpServerSessionHandler.h>

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
	}
};


class CTcpServerSessionFactory : public CTcpListenerHandler::ITcpServerSessionFactory
{


	virtual CTcpServerSessionHandler * CreateSession() override
	{
		return new CTcpServerSessionHandler();
	}


	virtual void NewSessionTrigger(CTcpServerSessionHandler *pTcpServerSession) override
	{
	}

};


TEST_F(TcpIOCPModelTest, TcpListener)
{
	CTcpServerSessionFactory *pFactory = new CTcpServerSessionFactory();
	CTcpListenerHandler *pTcpListener = new CTcpListenerHandler();
	pTcpListener->Create(8888, pFactory, m_pIOCPModel);
	// m_pIOCPModel->DetachHandler(pTcpListener);
}


TEST_F(TcpIOCPModelTest, TcpSessionClient)
{
	CTcpClientSessionHandler *pSession = new CTcpClientSessionHandler();
	BOOL bRes = pSession->Connect("127.0.0.1", 8888, m_pIOCPModel);
	bRes = bRes;
}