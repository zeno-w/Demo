
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

	TcpIOCPModelTest() : m_pIOCPModel(CIoCompletionPortModel::GetInstance())
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

class CTcpServerSession : public CTcpServerSessionHandler
{

protected:
	virtual BOOL DataTransferTrigger(DWORD dwNumOfTransportBytes) override
	{
		return TRUE;
	}
};

class CTcpServerSessionFactory : public CTcpListenerHandler::INewConnectionCallback
{

	virtual void NewConnectionTrigger(SOCKET sAccepted) override
	{
		CTcpServerSession *pSession = new CTcpServerSession();
		EXPECT_TRUE(pSession->Create(sAccepted, 2096, CIoCompletionPortModel::GetInstance())) << "CTcpServerSession::Create(..)";
	}

};


TEST_F(TcpIOCPModelTest, TcpListener)
{
	CTcpServerSessionFactory *pFactory = new CTcpServerSessionFactory();
	CTcpListenerHandler *pTcpListener = new CTcpListenerHandler();
	pTcpListener->Create(1234, pFactory, m_pIOCPModel);
	USHORT uPos = pTcpListener->GetListenPort();
	uPos = uPos;
}


TEST_F(TcpIOCPModelTest, TcpSessionClient)
{
	CTcpClientSessionHandler *pSession = new CTcpClientSessionHandler();
	EXPECT_TRUE(pSession->Connect("127.0.0.1", 1234, m_pIOCPModel))<<"CTcpClientSessionHandler::Connect";
	EXPECT_TRUE(pSession->Send("abcdefg", 5));
}