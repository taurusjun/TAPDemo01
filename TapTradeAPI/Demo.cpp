#include "TapTradeAPI.h"
#include "TapAPIError.h"
#include "Trade.h"
#include "TradeConfig.h"

#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char* argv[])
{
	//ȡ��API�İ汾��Ϣ
	cout << GetTapTradeAPIVersion() << endl;

	//����APIʵ��
	TAPIINT32 iResult = TAPIERROR_SUCCEED;
	TapAPIApplicationInfo stAppInfo;
	strcpy(stAppInfo.AuthCode, DEFAULT_AUTHCODE);
	strcpy(stAppInfo.KeyOperationLogPath, "log");
	ITapTradeAPI *pAPI = CreateTapTradeAPI(&stAppInfo, iResult);
	if (NULL == pAPI){
		cout << "����APIʵ��ʧ�ܣ������룺" << iResult <<endl;
		return -1;
	}

	//�趨ITapTradeAPINotify��ʵ���࣬�����첽��Ϣ�Ľ���
	Trade objTrade;
	pAPI->SetAPINotify(&objTrade);
	

	//�������ԣ��µ�
	objTrade.SetAPI(pAPI);
	objTrade.RunTest();


	return 0;
}