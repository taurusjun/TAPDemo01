#include "Trade.h"
#include "TapAPIError.h"
#include "TradeConfig.h"
#include <iostream>
#include <string.h>
#include <boost/locale.hpp>

using namespace std;

Trade::Trade(void):
	m_pAPI(NULL),
	m_bIsAPIReady(false)
{
}


Trade::~Trade(void)
{
}


void Trade::SetAPI(ITapTradeAPI *pAPI)
{
	m_pAPI = pAPI;
}


void Trade::RunTest()
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
	TapAPITradeLoginAuth stLoginAuth;
	memset(&stLoginAuth, 0, sizeof(stLoginAuth));
	strcpy(stLoginAuth.UserNo, DEFAULT_USERNAME);
	strcpy(stLoginAuth.Password, DEFAULT_PASSWORD);
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
		cout << "API is not ready";
		return;
	}

	//�µ�
	TapAPINewOrder stNewOrder;
	memset(&stNewOrder, 0, sizeof(stNewOrder));

	strcpy(stNewOrder.AccountNo, DEFAULT_ACCOUNT_NO);			
	strcpy(stNewOrder.ExchangeNo, DEFAULT_EXCHANGE_NO);		
	stNewOrder.CommodityType = DEFAULT_COMMODITY_TYPE;		
	strcpy(stNewOrder.CommodityNo, DEFAULT_COMMODITY_NO);		
	strcpy(stNewOrder.ContractNo, DEFAULT_CONTRACT_NO);		
	strcpy(stNewOrder.StrikePrice, "");		
	stNewOrder.CallOrPutFlag = TAPI_CALLPUT_FLAG_NONE;		
	strcpy(stNewOrder.ContractNo2, "");		
	strcpy(stNewOrder.StrikePrice2, "");		
	stNewOrder.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;	
	stNewOrder.OrderType = DEFAULT_ORDER_TYPE;//�м�			
	// stNewOrder.OrderType = TAPI_ORDER_TYPE_LIMIT;//�޼�			
	stNewOrder.OrderSource = TAPI_ORDER_SOURCE_ESUNNY_API;		
	stNewOrder.TimeInForce = TAPI_ORDER_TIMEINFORCE_GFD;		
	strcpy(stNewOrder.ExpireTime, "");		
	stNewOrder.IsRiskOrder = APIYNFLAG_NO;		
	stNewOrder.OrderSide = DEFAULT_ORDER_SIDE; //��
	// stNewOrder.OrderSide = DEFAULT_ORDER_SIDE_SELL; //��
				
	stNewOrder.PositionEffect = DEFAULT_POSITION_EFFECT;//����
	// stNewOrder.PositionEffect = DEFAULT_POSITION_EFFECT_COVER;//ƽ��

	stNewOrder.PositionEffect2 = TAPI_PositionEffect_NONE;	
	strcpy(stNewOrder.InquiryNo,"");			
	stNewOrder.HedgeFlag = TAPI_HEDGEFLAG_T;			
	stNewOrder.OrderPrice = DEFAULT_ORDER_PRICE;		
	stNewOrder.OrderPrice = 3840;		

	stNewOrder.OrderPrice2;		
	stNewOrder.StopPrice = 13000;			
	stNewOrder.OrderQty = DEFAULT_ORDER_QTY;			
	stNewOrder.OrderMinQty ;		
	stNewOrder.MinClipSize;		
	stNewOrder.MaxClipSize;		
	stNewOrder.RefInt;				
	strcpy(stNewOrder.RefString, "TXQQ00000001");//�����ַ���			
	stNewOrder.TacticsType = TAPI_TACTICS_TYPE_NONE; // ������Ч
	// stNewOrder.TacticsType = TAPI_TACTICS_TYPE_READY; // Ԥ��
	// stNewOrder.TacticsType = TAPI_TACTICS_TYPE_ATUO; // �Զ�����
	// stNewOrder.TacticsType = TAPI_TACTICS_TYPE_CONDITION; // ��������

	// stNewOrder.TriggerCondition = TAPI_TRIGGER_CONDITION_NONE;	
	stNewOrder.TriggerCondition = TAPI_TRIGGER_CONDITION_GREAT;	

	// stNewOrder.TriggerPriceType = TAPI_TRIGGER_PRICE_NONE;	
	stNewOrder.TriggerPriceType = TAPI_TRIGGER_PRICE_LAST;	

	stNewOrder.AddOneIsValid = APIYNFLAG_NO;	
	stNewOrder.OrderQty2;
	stNewOrder.HedgeFlag2 = TAPI_HEDGEFLAG_NONE;
	stNewOrder.MarketLevel = TAPI_MARKET_LEVEL_0;
	stNewOrder.FutureAutoCloseFlag = APIYNFLAG_NO; // V9.0.2.0 20150520
	
	m_uiSessionID = 0;

	// iErr = m_pAPI->InsertOrder(&m_uiSessionID, &stNewOrder);
	// if(TAPIERROR_SUCCEED != iErr) {
	// 	cout << "InsertOrder Error:" << iErr <<endl;
	// 	return;
	// }

	// TapAPIOrderActivateReq stActiveOrder;
	// memset(&stActiveOrder, 0, sizeof(stActiveOrder));
	// strcpy(stActiveOrder.OrderNo,"OC191023UR00015013");
	// // stCancelOrder.ServerFlag='C';
	// // stCancelOrder.RefInt=0;
	// iErr = m_pAPI->ActivateOrder(&m_uiSessionID,&stActiveOrder);
	// if(TAPIERROR_SUCCEED != iErr) {
	// 	cout << "ActivateOrder Error:" << iErr <<endl;
	// 	return;
	// }

	// m_uiSessionID2 = 0;
	TapAPIOrderCancelReq stCancelOrder;
	memset(&stCancelOrder, 0, sizeof(stCancelOrder));
	strcpy(stCancelOrder.OrderNo,"OC191023UR00019103");
	// strcpy(stCancelOrder.RefString,"TXQQ00000001");
	// stCancelOrder.ServerFlag='C';
	// stCancelOrder.RefInt=0;
	iErr = m_pAPI->CancelOrder(&m_uiSessionID,&stCancelOrder);
	if(TAPIERROR_SUCCEED != iErr) {
		cout << "CancelOrder Error:" << iErr <<endl;
		return;
	}

	// TapAPIPositionQryReq stQryPosReq;
	// memset(&stQryPosReq, 0, sizeof(stQryPosReq));
	// iErr = m_pAPI->QryPosition(&m_uiSessionID,&stQryPosReq);
	// if(TAPIERROR_SUCCEED != iErr) {
	// 	cout << "QryPosition Error:" << iErr <<endl;
	// 	return;
	// }

	//
	// TapAPIAccQryReq stQryReq;
	// memset(&stQryReq, 0, sizeof(stQryReq));
	// iErr = m_pAPI->QryAccount(&m_uiSessionID,&stQryReq);
	// if(TAPIERROR_SUCCEED != iErr) {
	// 	cout << "QryAccount Error:" << iErr <<endl;
	// 	return;
	// }

	// TapAPIFundReq stFundReq;
	// memset(&stFundReq, 0, sizeof(stFundReq));
	// strcpy(stFundReq.AccountNo ,"Q48753284");
	// iErr = m_pAPI->QryFund(&m_uiSessionID,&stFundReq);
	// if(TAPIERROR_SUCCEED != iErr) {
	// 	cout << "QryFund Error:" << iErr <<endl;
	// 	return;
	// }

	//
	// iErr = m_pAPI->QryCommodity(&m_uiSessionID);
	// if(TAPIERROR_SUCCEED != iErr) {
	// 	cout << "QryCommodity Error:" << iErr <<endl;
	// 	return;
	// }
	

	while (true)
	{
		m_Event.WaitEvent();
	}	
}

void TAP_CDECL Trade::OnConnect()
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspLogin( TAPIINT32 errorCode, const TapAPITradeLoginRspInfo *loginRspInfo )
{
	if(TAPIERROR_SUCCEED == errorCode) {
		// cout << "��¼�ɹ����ȴ�API��ʼ��..." << endl;
		cout << "Login success, wait for API initialization..." << endl;

	} else {
		cout << "��¼ʧ�ܣ�������:" << errorCode << endl;
		m_Event.SignalEvent();	
	}
}

void TAP_CDECL Trade::OnAPIReady()
{
	// cout << "API��ʼ�����" << endl;
	cout << "API initialization success" << endl;
	m_bIsAPIReady = true;
	m_Event.SignalEvent();	
}

void TAP_CDECL Trade::OnDisconnect( TAPIINT32 reasonCode )
{
	cout << "API�Ͽ�,�Ͽ�ԭ��:"<<reasonCode << endl;
}

void TAP_CDECL Trade::OnRspChangePassword( TAPIUINT32 sessionID, TAPIINT32 errorCode )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspSetReservedInfo( TAPIUINT32 sessionID, TAPIINT32 errorCode, const TAPISTR_50 info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRspQryAccount( TAPIUINT32 sessionID, TAPIUINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << ""
		<< "AccountNo:"<<info->AccountNo << ","
		<< "AccountType:"<<info->AccountType << ","
		<< "AccountState:"<<info->AccountState<< ","
		<< "AccountShortName:"<<info->AccountShortName<< ","
		<< "AccountIsDocHolder:"<<info->AccountIsDocHolder<< ","
		<< "IsMarketMaker:"<<info->IsMarketMaker<< ","
		<< "AccountFamilyType:"<<info->AccountState<< ","
		<<endl;
}

void TAP_CDECL Trade::OnRspQryFund( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFundData *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << "(isLast:" << isLast<<"):" << endl;
	printTapAPIFundData(info);
}

void TAP_CDECL Trade::OnRtnFund( const TapAPIFundData *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	printTapAPIFundData(info);
}

void TAP_CDECL Trade::OnRspQryExchange( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIExchangeInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << "(isLast:" << isLast<<"):" << endl;
	printTapAPIExchangeInfo(info);
}

void TAP_CDECL Trade::OnRspQryCommodity( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICommodityInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << ""
		<< "CommodityName:"<<info->CommodityName << ","
		<< "CommodityNo:"<<info->CommodityNo << ","
		<< "ExchangeNo:"<<info->ExchangeNo
		<<endl;
}

void TAP_CDECL Trade::OnRspQryContract( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPITradeContractInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRtnContract( const TapAPITradeContractInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
}

void TAP_CDECL Trade::OnRtnOrder( const TapAPIOrderInfoNotice *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	if(NULL == info){
		cout << "info is null" << endl;
		return;
	}

	if (info->ErrorCode != 0) {
		cout << "������������һ������ί����Ϣ�Ĵ���" << info->ErrorCode << endl;
	} else {
		if (info->OrderInfo) {
			// if (info->SessionID == m_uiSessionID)
			{
				if (0!= info->OrderInfo->ErrorCode){
					cout << "����ʧ�ܣ�[sessionId=" << info->SessionID <<", m_uiSessionID= "<<m_uiSessionID<<"]: "
						<< "״̬:"<<info->OrderInfo->OrderState << ","
						<< "������:"<<info->OrderInfo->ErrorCode << ","
						<< "ί�б��:"<<info->OrderInfo->OrderNo << ","
						<< "������Ϣ:" << boost::locale::conv::to_utf<char>(info->OrderInfo->ErrorText, "GB2312") <<""
						<<endl;
					printTapAPIOrderInfo(info->OrderInfo);	

				} else{
					cout << "�����ɹ���[sessionId=" << info->SessionID <<", m_uiSessionID= "<<m_uiSessionID<<"]: "
						<< "״̬:"<<info->OrderInfo->OrderState << ","
						<< "ί�б��:"<<info->OrderInfo->OrderNo << ","
						<< "�ɽ��۸�:"<<info->OrderInfo->OrderMatchPrice << ","
						<< "�ɽ�����:"<<info->OrderInfo->OrderMatchQty
						<<endl;

					printTapAPIOrderInfo(info->OrderInfo);	

					// TapAPIOrderCancelReq stCancelOrder;
					// memset(&stCancelOrder, 0, sizeof(stCancelOrder));
					// strcpy(stCancelOrder.OrderNo,info->OrderInfo->OrderNo);
					// TAPIINT32 iErr = TAPIERROR_SUCCEED;
					// iErr = m_pAPI->CancelOrder(&m_uiSessionID,&stCancelOrder);
					// if(TAPIERROR_SUCCEED != iErr) {
					// 	cout << "CancelOrder Error:" << iErr <<endl;
					// 	return;
					// }else{
					// 	cout << "CancelOrder returned" <<endl;
					// }
				}
				m_Event.SignalEvent();
			}
		}
	}
}

void TAP_CDECL Trade::OnRspOrderAction( TAPIUINT32 sessionID, TAPIUINT32 errorCode, const TapAPIOrderActionRsp *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	if (errorCode != TAPIERROR_SUCCEED) {
		cout << "������������һ������" << errorCode << endl;
	} else {
		cout << "ActionType: " << info->ActionType <<endl;
		printTapAPIOrderInfo(info->OrderInfo);
	}
}

void TAP_CDECL Trade::OnRspQryOrder( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	if (errorCode != TAPIERROR_SUCCEED) {
		cout << "������������һ������" << errorCode << endl;
	} else {
		printTapAPIOrderInfo(info);
	}
}

void TAP_CDECL Trade::OnRspQryOrderProcess( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	if (errorCode != TAPIERROR_SUCCEED) {
		cout << "������������һ������" << errorCode << endl;
	} else {
		printTapAPIOrderInfo(info);
	}
}

void TAP_CDECL Trade::OnRspQryFill( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFillInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	if (errorCode != TAPIERROR_SUCCEED) {
		cout << "������������һ������" << errorCode << endl;
	} else {
		printTapAPIFillInfo(info);
	}
}

void TAP_CDECL Trade::OnRtnFill( const TapAPIFillInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	printTapAPIFillInfo(info);
}

void TAP_CDECL Trade::OnRspQryPosition( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	if(NULL == info){
		return;
	}

	if (errorCode != TAPIERROR_SUCCEED) {
		cout << "������������һ�����ڲ�ѯ�ֲֵĴ���" << errorCode << endl;
	} else {
		cout << "�ֲ���Ϣ"<< "(isLast=" << isLast <<"): "<< endl;
		printTapAPIPositionInfo(info);
	}
}

void TAP_CDECL Trade::OnRtnPosition( const TapAPIPositionInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	printTapAPIPositionInfo(info);
}

void TAP_CDECL Trade::OnRspQryClose( TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICloseInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	printTapAPICloseInfo(info);
}

void TAP_CDECL Trade::OnRtnClose( const TapAPICloseInfo *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	printTapAPICloseInfo(info);
}

void TAP_CDECL Trade::OnRtnPositionProfit( const TapAPIPositionProfitNotice *info )
{
	cout << __FUNCTION__ << " is called." << endl;
	cout << "isLast=" << info->IsLast <<": "<< endl;
	printTapAPIPositionProfit(info->Data);
}

void TAP_CDECL Trade::OnRspQryDeepQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIDeepQuoteQryRsp *info)
{
	cout << __FUNCTION__ << " is called." << endl;
	if(NULL == info){
		return;
	}

	if (errorCode != TAPIERROR_SUCCEED) {
		cout << "������������һ������" << errorCode << endl;
	} else {
		cout << "isLast=" << isLast <<": "<< endl;
		printTapAPIContract(&info->Contract);
		printTapAPIDeepQuoteInfo(&info->DeepQuote);
	}
}

void TAP_CDECL Trade::OnRspQryExchangeStateInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast,const TapAPIExchangeStateInfo * info)
{
	cout << __FUNCTION__ << " is called." << endl;
	if(NULL == info){
		return;
	}

	if (errorCode != TAPIERROR_SUCCEED) {
		cout << "������������һ������" << errorCode << endl;
	} else {
		cout << "isLast=" << isLast <<": "<< endl;
		printTapAPIExchangeStateInfo(info);
	}
}

void TAP_CDECL Trade::OnRtnExchangeStateInfo(const TapAPIExchangeStateInfoNotice * info)
{
		cout << __FUNCTION__ << " is called." << endl;
		cout << "isLast=" << info->IsLast <<": "<< endl;
		printTapAPIExchangeStateInfo(&info->ExchangeStateInfo);
}

void TAP_CDECL Trade::OnRtnReqQuoteNotice(const TapAPIReqQuoteNotice *info)
{
		cout << __FUNCTION__ << " is called." << endl;
		printTapAPIReqQuoteNotice(info);
}

void TAP_CDECL Trade::OnRspUpperChannelInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIUpperChannelInfo * info)
{
	cout << __FUNCTION__ << " is called." << endl;
	if(NULL == info){
		return;
	}

	if (errorCode != TAPIERROR_SUCCEED) {
		cout << "������������һ������" << errorCode << endl;
	} else {
		cout << "isLast=" << isLast <<": "<< endl;
		printTapAPIUpperChannelInfo(info);
	}
}

void TAP_CDECL Trade::OnRspAccountRentInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountRentInfo * info)
{
	cout << __FUNCTION__ << " is called." << endl;
	if(NULL == info){
		return;
	}

	if (errorCode != TAPIERROR_SUCCEED) {
		cout << "������������һ������" << errorCode << endl;
	} else {
		cout << "isLast=" << isLast <<": "<< endl;
		printTapAPIAccountRentInfo(info);
	}
}

