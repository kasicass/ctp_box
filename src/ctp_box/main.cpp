#include "ThostFtdcMdApi.h"
#include "mymdspi.h"
#include <iostream>

#define FRONT_ADDR "tcp://180.168.146.187:10031"

TThostFtdcBrokerIDType	 BROKER_ID   = "9999";           // 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "100753";         // 注意这里输入你自己的投资者代码
TThostFtdcPasswordType   PASSWORD    = "ilovecode@";     // 注意这里输入你自己的用户密码

char *ppInstrumentID[] = {"ni1701", "rb1701"};			 // 行情订阅列表，注意，这个合约ID会过时的，注意与时俱进修改
int iInstrumentID = 2;									 // 行情订阅数量

// 请求编号
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
