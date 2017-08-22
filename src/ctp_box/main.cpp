#include "ThostFtdcMdApi.h"
#include "mymdspi.h"
#include <iostream>

#define FRONT_ADDR "tcp://180.168.146.187:10031"

TThostFtdcBrokerIDType	 BROKER_ID   = "9999";           // ���͹�˾����
TThostFtdcInvestorIDType INVESTOR_ID = "100753";         // ע�������������Լ���Ͷ���ߴ���
TThostFtdcPasswordType   PASSWORD    = "ilovecode@";     // ע�������������Լ����û�����

char *ppInstrumentID[] = {"ni1701", "rb1701"};			 // ���鶩���б�ע�⣬�����ԼID���ʱ�ģ�ע����ʱ����޸�
int iInstrumentID = 2;									 // ���鶩������

// ������
int iRequestID = 0;

int main(int argc, char* argv[])
{
	std::cout << "version: " << CThostFtdcMdApi::GetApiVersion() << std::endl;

	CThostFtdcMdApi* mdapi = CThostFtdcMdApi::CreateFtdcMdApi();
	CThostFtdcMdSpi* myspi = new MyMdSpi(mdapi);
	mdapi->RegisterSpi(myspi);
	mdapi->RegisterFront(FRONT_ADDR);

	mdapi->Init();
	mdapi->Join();
	return 0;
}
