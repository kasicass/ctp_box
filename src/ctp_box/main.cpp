#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	//CThostFtdcMdApi * mdapi = CThostFtdcMdApi::CreateFtdcMdApi();
	//mdapi->Init();
	//mdapi->Release();

	printf("version: %s\n", CThostFtdcMdApi::GetApiVersion());
	return 0;
}