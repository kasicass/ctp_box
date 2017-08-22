#include "mymdspi.h"
#include "ThostFtdcUserApiStruct.h"
#include <iostream>

extern TThostFtdcBrokerIDType	BROKER_ID;
extern TThostFtdcInvestorIDType INVESTOR_ID;
extern TThostFtdcPasswordType	PASSWORD;
extern char* ppInstrumentID[];	
extern int iInstrumentID;

// 请求编号
extern int iRequestID;

MyMdSpi::MyMdSpi(CThostFtdcMdApi *mdapi) : mdapi_(mdapi)
{
}

void MyMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void MyMdSpi::OnFrontDisconnected(int nReason)
{
	std::cout << "--->>> " << __FUNCTION__ << std::endl;
	std::cout << "--->>> Reason = " << nReason << std::endl;
}

void MyMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	std::cout << "--->>> " << __FUNCTION__ << std::endl;
	std::cout << "--->>> nTimeLapse = " << nTimeLapse << std::endl;
}

void MyMdSpi::OnFrontConnected()
{
	std::cout << "--->>> " << __FUNCTION__ << std::endl;

	// user login
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.UserID, INVESTOR_ID);
	strcpy(req.Password, PASSWORD);
	int ok = mdapi_->ReqUserLogin(&req, ++iRequestID);
	std::cout << "--->>> 发送用户登录请求: " << ((ok == 0) ? "成功" : "失败") << std::endl;
	if (ok != 0)
	{
		std::cout << "--->>> error code: " << ok << std::endl;
	}
}

void MyMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cout << "--->>> " << __FUNCTION__ << std::endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///获取当前交易日
		std::cout << "--->>> 获取当前交易日 = " << mdapi_->GetTradingDay() << std::endl;
		// 请求订阅行情
		SubscribeMarketData();
	}
}

void MyMdSpi::SubscribeMarketData()
{
	int ok = mdapi_->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	std::cout << "--->>> 发送行情订阅请求: " << ((ok == 0) ? "成功" : "失败") << std::endl;
}

void MyMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cout << "--->>> " << __FUNCTION__ << std::endl;
}

void MyMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cout << "--->>> " << __FUNCTION__ << std::endl;
}

void MyMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	std::cout << "--->>> " << __FUNCTION__ << std::endl;
	std::cout << "--->>> 最新价=" << pDepthMarketData->LastPrice << std::endl;
}

bool MyMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		std::cout << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
	return bResult;
}
