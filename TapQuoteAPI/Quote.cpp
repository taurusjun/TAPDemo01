#include "Quote.h"
#include "TapAPIError.h"
#include "QuoteConfig.h"
//#include <Windows.h>
#include <iostream>
#include <string.h>

using namespace std;

Quote::Quote(void):
	m_pAPI(NULL),
	m_bIsAPIReady(false)
{
}


Quote::~Quote(void)
{
}


void Quote::SetAPI(ITapQuoteAPI *pAPI)
{
	m_pAPI = pAPI;
}


void Quote::RunTest()
{
	if(NULL == m_pAPI) {
		cout << "Error: m_pAPI is NULL." << endl;
		return;
	}

	TAPIINT32 iErr = TAPIERROR_SUCCEED;


	//�趨������IP���˿�
	iErr = m_pAPI->SetHostAddress(DEFAULT_IP, DEFAULT_PORT);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "SetHostAddress Error:" << iErr <<endl;
		return;
	}

	//��¼������
	TapAPIQuoteLoginAuth stLoginAuth;
	memset(&stLoginAuth, 0, sizeof(stLoginAuth));
	APIStrncpy(stLoginAuth.UserNo, DEFAULT_USERNAME);
	APIStrncpy(stLoginAuth.Password, DEFAULT_PASSWORD);
	stLoginAuth.ISModifyPassword = APIYNFLAG_NO;
	stLoginAuth.ISDDA = APIYNFLAG_NO;
	iErr = m_pAPI->Login(&stLoginAuth);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "Login Error:" << iErr <<endl;
		return;
	}
	

	//�ȴ�APIReady
	m_Event.WaitEvent();
	if (!m_bIsAPIReady){
		return;
	}

	//��������
	TapAPIContract stContract;
	memset(&stContract, 0, sizeof(stContract));
	APIStrncpy(stContract.Commodity.ExchangeNo, DEFAULT_EXCHANGE_NO);
	stContract.Commodity.CommodityType = DEFAULT_COMMODITY_TYPE;
	APIStrncpy(stContract.Commodity.CommodityNo, DEFAULT_COMMODITY_NO);
	APIStrncpy(stContract.ContractNo1, DEFAULT_CONTRACT_NO);
	stContract.CallOrPutFlag1 = TAPI_CALLPUT_FLAG_NONE;
	stContract.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;
	m_uiSessionID = 0;

	iErr = m_pAPI->SubscribeQuote(&m_uiSessionID, &stContract);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "SubscribeQuote Error:" << iErr <<endl;
		return;
	}

	//��ѯ����Ʒ����Ϣ
	// iErr = m_pAPI->QryCommodity(&m_uiSessionID);
	// if(TAPIERROR_SUCCEED != iErr) {
	// 	cout << "QryCommodity Error:" << iErr <<endl;
	// 	return;
	// }

	//��ѯ��Լ��Ϣ
	// TapAPICommodity stCommodity;
	// memset(&stCommodity, 0, sizeof(stCommodity));
	// APIStrncpy(stCommodity.ExchangeNo, DEFAULT_EXCHANGE_NO);
	// iErr = m_pAPI->QryContract(&m_uiSessionID, &stCommodity);
	// if(TAPIERROR_SUCCEED != iErr) {
	// 	cout << "QryContract Error:" << iErr <<endl;
	// 	return;
	// }

        while(true) {
                m_Event.WaitEvent();
        }
}



void TAP_CDECL Quote::OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info)
{
	if(TAPIERROR_SUCCEED == errorCode) {
		cout << "��¼�ɹ����ȴ�API��ʼ��..." << endl;
		m_bIsAPIReady = true;

	} else {
		cout << "��¼ʧ�ܣ�������:" << errorCode << endl;
		m_Event.SignalEvent();	
	}
}

void TAP_CDECL Quote::OnAPIReady()
{
	cout << "API��ʼ�����" << endl;
	m_Event.SignalEvent();	
}

void TAP_CDECL Quote::OnDisconnect(TAPIINT32 reasonCode)
{
	cout << "API�Ͽ�,�Ͽ�ԭ��:"<<reasonCode << endl;
}

void TAP_CDECL Quote::OnRspChangePassword(TAPIUINT32 sessionID, TAPIINT32 errorCode)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Quote::OnRspQryExchange(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIExchangeInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Quote::OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info)
{
	// cout << __FUNCTION__ << " is called." << endl;
	if (NULL != info)
	{
		cout<< info->Commodity.ExchangeNo << " "
			<< info->Commodity.CommodityType << " "
			<< info->Commodity.CommodityNo << " "
			<< info->CommodityTickSize << " "
			// ...		
			<<endl;
	}
}

void TAP_CDECL Quote::OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info)
{
	// cout << __FUNCTION__ << " is called." << endl;
	if (NULL != info)
	{
		cout << info->Contract.Commodity.ExchangeNo << " "
			<< info->Contract.Commodity.CommodityType << " "
			<< info->Contract.Commodity.CommodityNo << " "
			<< info->Contract.ContractNo1 << " "
			// ...		
			<<endl;
	}
}

void TAP_CDECL Quote::OnRtnContract(const TapAPIQuoteContractInfo *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Quote::OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info)
{
	cout << __FUNCTION__ << " is called." << endl;
	if (TAPIERROR_SUCCEED == errorCode)
	{
		cout << "���鶩�ĳɹ� ";
		if (NULL != info)
		{
			cout << info->DateTimeStamp << " "
				<< info->Contract.Commodity.ExchangeNo << " "
				<< info->Contract.Commodity.CommodityType << " "
				<< info->Contract.Commodity.CommodityNo << " "
				<< info->Contract.ContractNo1 << " "
				<< info->QLastPrice
				// ...		
				<<endl;
		}

	} else{
		cout << "���鶩��ʧ�ܣ������룺" << errorCode <<endl;
	}
}

void TAP_CDECL Quote::OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info)
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Quote::OnRtnQuote(const TapAPIQuoteWhole *info)
{
	cout << __FUNCTION__ << " is called." << endl;
	if (NULL != info)
	{
		cout << "�������:" 
			<< info->DateTimeStamp << " "
			<< info->Contract.Commodity.ExchangeNo << " "
			<< info->Contract.Commodity.CommodityType << " "
			<< info->Contract.Commodity.CommodityNo << " "
			<< info->Contract.ContractNo1 << " "
			<< info->QLastPrice
			// ...		
			<<endl;
	}
}
