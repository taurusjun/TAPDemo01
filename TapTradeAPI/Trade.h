#ifndef TRADE_H
#define TRADE_H

#include "TapTradeAPI.h"
#include "../Common/SimpleEvent.h"

#include <iostream>
using namespace std;
class Trade : public ITapTradeAPINotify
{
public:
	Trade(void);
	~Trade(void);

	void SetAPI(ITapTradeAPI *pAPI);
	void RunTest();

public:
	//对ITapTradeAPINotify的实现
	virtual void TAP_CDECL OnConnect();
	virtual void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPITradeLoginRspInfo *loginRspInfo);
	virtual void TAP_CDECL OnAPIReady();
	virtual void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode);
	virtual void TAP_CDECL OnRspChangePassword(TAPIUINT32 sessionID, TAPIINT32 errorCode);
	virtual void TAP_CDECL OnRspSetReservedInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, const TAPISTR_50 info);
	virtual void TAP_CDECL OnRspQryAccount(TAPIUINT32 sessionID, TAPIUINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountInfo *info);
	virtual void TAP_CDECL OnRspQryFund(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFundData *info);
	virtual void TAP_CDECL OnRtnFund(const TapAPIFundData *info);
	virtual void TAP_CDECL OnRspQryExchange(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIExchangeInfo *info);
	virtual void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICommodityInfo *info);
	virtual void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPITradeContractInfo *info);
	virtual void TAP_CDECL OnRtnContract(const TapAPITradeContractInfo *info);
	virtual void TAP_CDECL OnRtnOrder(const TapAPIOrderInfoNotice *info);
	virtual void TAP_CDECL OnRspOrderAction(TAPIUINT32 sessionID, TAPIUINT32 errorCode, const TapAPIOrderActionRsp *info);
	virtual void TAP_CDECL OnRspQryOrder(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info);
	virtual void TAP_CDECL OnRspQryOrderProcess(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *info);
	virtual void TAP_CDECL OnRspQryFill(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIFillInfo *info);
	virtual void TAP_CDECL OnRtnFill(const TapAPIFillInfo *info);
	virtual void TAP_CDECL OnRspQryPosition(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionInfo *info);
	virtual void TAP_CDECL OnRtnPosition(const TapAPIPositionInfo *info);
	virtual void TAP_CDECL OnRspQryClose(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPICloseInfo *info);
	virtual void TAP_CDECL OnRtnClose(const TapAPICloseInfo *info);
	virtual void TAP_CDECL OnRtnPositionProfit(const TapAPIPositionProfitNotice *info);
	virtual void TAP_CDECL OnRspQryDeepQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIDeepQuoteQryRsp *info);
	virtual void TAP_CDECL OnRspQryExchangeStateInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast,const TapAPIExchangeStateInfo * info);
	virtual void TAP_CDECL OnRtnExchangeStateInfo(const TapAPIExchangeStateInfoNotice * info);
	virtual void TAP_CDECL OnRtnReqQuoteNotice(const TapAPIReqQuoteNotice *info); //V9.0.2.0 20150520
	virtual void TAP_CDECL OnRspUpperChannelInfo(TAPIUINT32 sessionID,TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIUpperChannelInfo * info);
	virtual void TAP_CDECL OnRspAccountRentInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIAccountRentInfo * info);
    virtual void TAP_CDECL OnRspSubmitUserLoginInfo(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPISubmitUserLoginRspInfo * info);

private:
	ITapTradeAPI *m_pAPI;
	TAPIUINT32	m_uiSessionID;
	TAPIUINT32	m_uiSessionID2;
	SimpleEvent m_Event;
	bool		m_bIsAPIReady;
};

static void printTapAPIOrderInfo(const TapAPIOrderInfo* info)
{
		cout << "Details: "
			<< "[AccountNo=" << info->AccountNo << "],"
			<< "[ExchangeNo=" << info->ExchangeNo << "],"
			<< "[CommodityType=" << info->CommodityType << "],"
			<< "[CommodityNo=" << info->CommodityNo << "],"
			<< "[ContractNo=" << info->ContractNo << "],"
			<< "[StrikePrice=" << info->StrikePrice << "],"
			<< "[CallOrPutFlag=" << info->CallOrPutFlag << "],"
			<< "[ContractNo2=" << info->ContractNo2 << "],"
			<< "[StrikePrice2=" << info->StrikePrice2 << "],"
			<< "[CallOrPutFlag2=" << info->CallOrPutFlag2 << "],"
			<< "[OrderType=" << info->OrderType << "],"
			<< "[OrderSource=" << info->OrderSource << "],"
			<< "[TimeInForce=" << info->TimeInForce << "],"
			<< "[ExpireTime=" << info->ExpireTime << "],"
			<< "[IsRiskOrder=" << info->IsRiskOrder << "],"
			<< "[OrderSide=" << info->OrderSide << "],"
			<< "[PositionEffect=" << info->PositionEffect << "],"
			<< "[PositionEffect2=" << info->PositionEffect2 << "],"
			<< "[InquiryNo=" << info->InquiryNo << "],"
			<< "[HedgeFlag=" << info->HedgeFlag << "],"
			<< "[OrderPrice=" << info->OrderPrice << "],"
			<< "[OrderPrice2=" << info->OrderPrice2 << "],"
			<< "[StopPrice=" << info->StopPrice << "],"
			<< "[OrderQty=" << info->OrderQty << "],"
			<< "[OrderMinQty=" << info->OrderMinQty << "],"
			<< "[OrderCanceledQty=" << info->OrderCanceledQty << "],"
			<< "[MinClipSize=" << info->MinClipSize << "],"
			<< "[MaxClipSize=" << info->MaxClipSize << "],"
			<< "[LicenseNo=" << info->LicenseNo << "],"
			<< "[RefInt=" << info->RefInt << "],"
			<< "[RefString=" << info->RefString << "],"
			<< "[ParentAccountNo=" << info->ParentAccountNo << "],"
			<< "[ServerFlag=" << info->ServerFlag << "],"
			<< "[OrderNo=" << info->OrderNo << "],"
			<< "[ClientOrderNo=" << info->ClientOrderNo << "],"
			<< "[OrderLocalNo=" << info->OrderLocalNo << "],"
			<< "[OrderSystemNo=" << info->OrderSystemNo << "],"
			<< "[OrderExchangeSystemNo=" << info->OrderExchangeSystemNo << "],"
			<< "[OrderParentNo=" << info->OrderParentNo << "],"
			<< "[OrderParentSystemNo=" << info->OrderParentSystemNo << "],"
			<< "[TradeNo=" << info->TradeNo << "],"
			<< "[UpperNo=" << info->UpperNo << "],"
			<< "[UpperChannelNo=" << info->UpperChannelNo << "],"
			<< "[UpperSettleNo=" << info->UpperSettleNo << "],"
			<< "[UpperUserNo=" << info->UpperUserNo << "],"
			<< "[OrderInsertUserNo=" << info->OrderInsertUserNo << "],"
			<< "[OrderInsertTime=" << info->OrderInsertTime << "],"
			<< "[OrderCommandUserNo=" << info->OrderCommandUserNo << "],"
			<< "[OrderUpdateUserNo=" << info->OrderUpdateUserNo << "],"
			<< "[OrderUpdateTime=" << info->OrderUpdateTime << "],"
			<< "[OrderState=" << info->OrderState << "],"
			<< "[OrderMatchPrice=" << info->OrderMatchPrice << "],"
			<< "[OrderMatchPrice2=" << info->OrderMatchPrice2 << "],"
			<< "[OrderMatchQty=" << info->OrderMatchQty << "],"
			<< "[OrderMatchQty2=" << info->OrderMatchQty2 << "],"
			<< "[ErrorCode=" << info->ErrorCode << "],"
			<< "[ErrorText=" << info->ErrorText << "],"
			<< "[IsBackInput=" << info->IsBackInput << "],"
			<< "[IsDeleted=" << info->IsDeleted << "],"
			<< "[IsAddOne=" << info->IsAddOne << "],"
			<< "[OrderStreamID=" << info->OrderStreamID << "],"
			<< "[UpperStreamID=" << info->UpperStreamID << "],"
			<< "[ContractSize=" << info->ContractSize << "],"
			<< "[ContractSize2=" << info->ContractSize2 << "],"
			<< "[CommodityCurrencyGroup=" << info->CommodityCurrencyGroup << "],"
			<< "[CommodityCurrency=" << info->CommodityCurrency << "],"
			<< "[FeeMode=" << info->FeeMode << "],"
			<< "[FeeParam=" << info->FeeParam << "],"
			<< "[FeeCurrencyGroup=" << info->FeeCurrencyGroup << "],"
			<< "[FeeCurrency=" << info->FeeCurrency << "],"
			<< "[FeeMode2=" << info->FeeMode2 << "],"
			<< "[FeeParam2=" << info->FeeParam2 << "],"
			<< "[FeeCurrencyGroup2=" << info->FeeCurrencyGroup2 << "],"
			<< "[FeeCurrency2=" << info->FeeCurrency2 << "],"
			<< "[MarginMode=" << info->MarginMode << "],"
			<< "[MarginParam=" << info->MarginParam << "],"
			<< "[MarginMode2=" << info->MarginMode2 << "],"
			<< "[MarginParam2=" << info->MarginParam2 << "],"
			<< "[PreSettlePrice=" << info->PreSettlePrice << "],"
			<< "[PreSettlePrice2=" << info->PreSettlePrice2 << "],"
			<< "[OpenVol=" << info->OpenVol << "],"
			<< "[CoverVol=" << info->CoverVol << "],"
			<< "[OpenVol2=" << info->OpenVol2 << "],"
			<< "[CoverVol2=" << info->CoverVol2 << "],"
			<< "[FeeValue=" << info->FeeValue << "],"
			<< "[MarginValue=" << info->MarginValue << "],"
			<< "[TacticsType=" << info->TacticsType << "],"
			<< "[TriggerCondition=" << info->TriggerCondition << "],"
			<< "[TriggerPriceType=" << info->TriggerPriceType << "],"
			<< "[AddOneIsValid=" << info->AddOneIsValid << "],"
			<< "[OrderQty2=" << info->OrderQty2 << "],"
			<< "[HedgeFlag2=" << info->HedgeFlag2 << "],"
			<< "[MarketLevel=" << info->MarketLevel << "],"
			<< "[OrderDeleteByDisConnFlag=" << info->OrderDeleteByDisConnFlag << "]"
			<< endl;	
}


static void printTapAPIFillInfo(const TapAPIFillInfo *info)
{
	cout << "Details: "
		<< "[AccountNo=" << info->AccountNo << "],"
		<< "[ParentAccountNo=" << info->ParentAccountNo << "],"
		<< "[ExchangeNo=" << info->ExchangeNo << "],"
		<< "[CommodityType=" << info->CommodityType << "],"
		<< "[CommodityNo=" << info->CommodityNo << "],"
		<< "[ContractNo=" << info->ContractNo << "],"
		<< "[StrikePrice=" << info->StrikePrice << "],"
		<< "[CallOrPutFlag=" << info->CallOrPutFlag << "],"
		<< "[ExchangeNoRef=" << info->ExchangeNoRef << "],"
		<< "[CommodityTypeRef=" << info->CommodityTypeRef << "],"
		<< "[CommodityNoRef=" << info->CommodityNoRef << "],"
		<< "[ContractNoRef=" << info->ContractNoRef << "],"
		<< "[StrikePriceRef=" << info->StrikePriceRef << "],"
		<< "[CallOrPutFlagRef=" << info->CallOrPutFlagRef << "],"
		<< "[OrderExchangeNo=" << info->OrderExchangeNo << "],"
		<< "[OrderCommodityType=" << info->OrderCommodityType << "],"
		<< "[OrderCommodityNo=" << info->OrderCommodityNo << "],"
		<< "[OrderType=" << info->OrderType << "],"
		<< "[MatchSource=" << info->MatchSource << "],"
		<< "[TimeInForce=" << info->TimeInForce << "],"
		<< "[ExpireTime=" << info->ExpireTime << "],"
		<< "[IsRiskOrder=" << info->IsRiskOrder << "],"
		<< "[MatchSide=" << info->MatchSide << "],"
		<< "[PositionEffect=" << info->PositionEffect << "],"
		<< "[PositionEffectRef=" << info->PositionEffectRef << "],"
		<< "[HedgeFlag=" << info->HedgeFlag << "],"
		<< "[ServerFlag=" << info->ServerFlag << "],"
		<< "[OrderNo=" << info->OrderNo << "],"
		<< "[OrderLocalNo=" << info->OrderLocalNo << "],"
		<< "[MatchNo=" << info->MatchNo << "],"
		<< "[ExchangeMatchNo=" << info->ExchangeMatchNo << "],"
		<< "[MatchDateTime=" << info->MatchDateTime << "],"
		<< "[UpperMatchDateTime=" << info->UpperMatchDateTime << "],"
		<< "[UpperNo=" << info->UpperNo << "],"
		<< "[UpperChannelNo=" << info->UpperChannelNo << "],"
		<< "[UpperSettleNo=" << info->UpperSettleNo << "],"
		<< "[UpperUserNo=" << info->UpperUserNo << "],"
		<< "[TradeNo=" << info->TradeNo << "],"
		<< "[MatchPrice=" << info->MatchPrice << "],"
		<< "[MatchQty=" << info->MatchQty << "],"
		<< "[IsBackInput=" << info->IsBackInput << "],"
		<< "[IsDeleted=" << info->IsDeleted << "],"
		<< "[IsAddOne=" << info->IsAddOne << "],"
		<< "[MatchStreamID=" << info->MatchStreamID << "],"
		<< "[UpperStreamID=" << info->UpperStreamID << "],"
		<< "[OpenCloseMode=" << info->OpenCloseMode << "],"
		<< "[ContractSize=" << info->ContractSize << "],"
		<< "[CommodityCurrencyGroup=" << info->CommodityCurrencyGroup << "],"
		<< "[CommodityCurrency=" << info->CommodityCurrency << "],"
		<< "[FeeMode=" << info->FeeMode << "],"
		<< "[FeeParam=" << info->FeeParam << "],"
		<< "[FeeCurrencyGroup=" << info->FeeCurrencyGroup << "],"
		<< "[FeeCurrency=" << info->FeeCurrency << "],"
		<< "[PreSettlePrice=" << info->PreSettlePrice << "],"
		<< "[FeeValue=" << info->FeeValue << "],"
		<< "[IsManualFee=" << info->IsManualFee << "],"
		<< "[Turnover=" << info->Turnover << "],"
		<< "[PremiumIncome=" << info->PremiumIncome << "],"
		<< "[PremiumPay=" << info->PremiumPay << "],"
		<< "[OppoMatchNo=" << info->OppoMatchNo << "],"
		<< "[CloseProfit=" << info->CloseProfit << "],"
		<< "[UnExpProfit=" << info->UnExpProfit << "],"
		<< "[UpperMatchPrice=" << info->UpperMatchPrice << "],"
		<< "[QuotePrice=" << info->QuotePrice << "],"
		<< "[ClosePL=" << info->ClosePL << "],"
		 << endl;
}

static void printTapAPIPositionInfo(const TapAPIPositionInfo *info)
{
	cout << "Details: "
		<< "[AccountNo=" << info->AccountNo << "],"
		<< "[ParentAccountNo=" << info->ParentAccountNo << "],"
		<< "[ExchangeNo=" << info->ExchangeNo << "],"
		<< "[CommodityType=" << info->CommodityType << "],"
		<< "[CommodityNo=" << info->CommodityNo << "],"
		<< "[ContractNo=" << info->ContractNo << "],"
		<< "[StrikePrice=" << info->StrikePrice << "],"
		<< "[CallOrPutFlag=" << info->CallOrPutFlag << "],"
		<< "[ExchangeNoRef=" << info->ExchangeNoRef << "],"
		<< "[CommodityTypeRef=" << info->CommodityTypeRef << "],"
		<< "[CommodityNoRef=" << info->CommodityNoRef << "],"
		<< "[ContractNoRef=" << info->ContractNoRef << "],"
		<< "[StrikePriceRef=" << info->StrikePriceRef << "],"
		<< "[CallOrPutFlagRef=" << info->CallOrPutFlagRef << "],"
		<< "[OrderExchangeNo=" << info->OrderExchangeNo << "],"
		<< "[OrderCommodityType=" << info->OrderCommodityType << "],"
		<< "[OrderCommodityNo=" << info->OrderCommodityNo << "],"
		<< "[OrderType=" << info->OrderType << "],"
		<< "[MatchSource=" << info->MatchSource << "],"
		<< "[TimeInForce=" << info->TimeInForce << "],"
		<< "[ExpireTime=" << info->ExpireTime << "],"
		<< "[MatchSide=" << info->MatchSide << "],"
		<< "[HedgeFlag=" << info->HedgeFlag << "],"
		<< "[PositionNo=" << info->PositionNo << "],"
		<< "[ServerFlag=" << info->ServerFlag << "],"
		<< "[OrderNo=" << info->OrderNo << "],"
		<< "[MatchNo=" << info->MatchNo << "],"
		<< "[ExchangeMatchNo=" << info->ExchangeMatchNo << "],"
		<< "[MatchDate=" << info->MatchDate << "],"
		<< "[MatchTime=" << info->MatchTime << "],"
		<< "[UpperMatchTime=" << info->UpperMatchTime << "],"
		<< "[UpperNo=" << info->UpperNo << "],"
		<< "[UpperSettleNo=" << info->UpperSettleNo << "],"
		<< "[UpperUserNo=" << info->UpperUserNo << "],"
		<< "[TradeNo=" << info->TradeNo << "],"
		<< "[PositionPrice=" << info->PositionPrice << "],"
		<< "[PositionQty=" << info->PositionQty << "],"
		<< "[IsBackInput=" << info->IsBackInput << "],"
		<< "[IsAddOne=" << info->IsAddOne << "],"
		<< "[MatchStreamID=" << info->MatchStreamID << "],"
		<< "[PositionStreamId=" << info->PositionStreamId << "],"
		<< "[OpenCloseMode=" << info->OpenCloseMode << "],"
		<< "[ContractSize=" << info->ContractSize << "],"
		<< "[CommodityCurrencyGroup=" << info->CommodityCurrencyGroup << "],"
		<< "[CommodityCurrency=" << info->CommodityCurrency << "],"
		<< "[PreSettlePrice=" << info->PreSettlePrice << "],"
		<< "[SettlePrice=" << info->SettlePrice << "],"
		<< "[Turnover=" << info->Turnover << "],"
		<< "[AccountMarginMode=" << info->AccountMarginMode << "],"
		<< "[AccountMarginParam=" << info->AccountMarginParam << "],"
		<< "[UpperMarginMode=" << info->UpperMarginMode << "],"
		<< "[UpperMarginParam=" << info->UpperMarginParam << "],"
		<< "[AccountInitialMargin=" << info->AccountInitialMargin << "],"
		<< "[AccountMaintenanceMargin=" << info->AccountMaintenanceMargin << "],"
		<< "[UpperInitialMargin=" << info->UpperInitialMargin << "],"
		<< "[UpperMaintenanceMargin=" << info->UpperMaintenanceMargin << "],"
		<< "[PositionProfit=" << info->PositionProfit << "],"
		<< "[LMEPositionProfit=" << info->LMEPositionProfit << "],"
		<< "[OptionMarketValue=" << info->OptionMarketValue << "],"
		<< "[MatchCmbNo=" << info->MatchCmbNo << "],"
		<< "[IsHistory=" << info->IsHistory << "],"
		<< "[FloatingPL=" << info->FloatingPL << "]"
		 << endl;
}

static void printTapAPIFundData(const TapAPIFundData *info)
{
	cout << "Details: "
		<< "[AccountNo=" << info->AccountNo << "],"
		<< "[ParentAccountNo=" << info->ParentAccountNo << "],"
		<< "[CurrencyGroupNo=" << info->CurrencyGroupNo << "],"
		<< "[CurrencyNo=" << info->CurrencyNo << "],"
		<< "[TradeRate=" << info->TradeRate << "],"
		<< "[FutureAlg=" << info->FutureAlg << "],"
		<< "[OptionAlg=" << info->OptionAlg << "],"
		<< "[PreBalance=" << info->PreBalance << "],"
		<< "[PreUnExpProfit=" << info->PreUnExpProfit << "],"
		<< "[PreLMEPositionProfit=" << info->PreLMEPositionProfit << "],"
		<< "[PreEquity=" << info->PreEquity << "],"
		<< "[PreAvailable1=" << info->PreAvailable1 << "],"
		<< "[PreMarketEquity=" << info->PreMarketEquity << "],"
		<< "[CashInValue=" << info->CashInValue << "],"
		<< "[CashOutValue=" << info->CashOutValue << "],"
		<< "[CashAdjustValue=" << info->CashAdjustValue << "],"
		<< "[CashPledged=" << info->CashPledged << "],"
		<< "[FrozenFee=" << info->FrozenFee << "],"
		<< "[FrozenDeposit=" << info->FrozenDeposit << "],"
		<< "[AccountFee=" << info->AccountFee << "],"
		<< "[ExchangeFee=" << info->ExchangeFee << "],"
		<< "[AccountDeliveryFee=" << info->AccountDeliveryFee << "],"
		<< "[PremiumIncome=" << info->PremiumIncome << "],"
		<< "[PremiumPay=" << info->PremiumPay << "],"
		<< "[CloseProfit=" << info->CloseProfit << "],"
		<< "[DeliveryProfit=" << info->DeliveryProfit << "],"
		<< "[UnExpProfit=" << info->UnExpProfit << "],"
		<< "[ExpProfit=" << info->ExpProfit << "],"
		<< "[PositionProfit=" << info->PositionProfit << "],"
		<< "[LmePositionProfit=" << info->LmePositionProfit << "],"
		<< "[OptionMarketValue=" << info->OptionMarketValue << "],"
		<< "[AccountIntialMargin=" << info->AccountIntialMargin << "],"
		<< "[AccountMaintenanceMargin=" << info->AccountMaintenanceMargin << "],"
		<< "[UpperInitalMargin=" << info->UpperInitalMargin << "],"
		<< "[UpperMaintenanceMargin=" << info->UpperMaintenanceMargin << "],"
		<< "[Discount=" << info->Discount << "],"
		<< "[Balance=" << info->Balance << "],"
		<< "[Equity=" << info->Equity << "],"
		<< "[Available=" << info->Available << "],"
		<< "[CanDraw=" << info->CanDraw << "],"
		<< "[MarketEquity=" << info->MarketEquity << "],"
		<< "[OriginalCashInOut=" << info->OriginalCashInOut << "],"
		<< "[FloatingPL=" << info->FloatingPL << "],"
		<< "[FrozenRiskFundValue=" << info->FrozenRiskFundValue << "],"
		<< "[ClosePL=" << info->ClosePL << "],"
		<< "[NoCurrencyPledgeValue=" << info->NoCurrencyPledgeValue << "],"
		<< "[PrePledgeValue=" << info->PrePledgeValue << "],"
		<< "[PledgeIn=" << info->PledgeIn << "],"
		<< "[PledgeOut=" << info->PledgeOut << "],"
		<< "[PledgeValue=" << info->PledgeValue << "],"
		<< "[BorrowValue=" << info->BorrowValue << "],"
		<< "[SpecialAccountFrozenMargin=" << info->SpecialAccountFrozenMargin << "],"
		<< "[SpecialAccountMargin=" << info->SpecialAccountMargin << "],"
		<< "[SpecialAccountFrozenFee=" << info->SpecialAccountFrozenFee << "],"
		<< "[SpecialAccountFee=" << info->SpecialAccountFee << "],"
		<< "[SpecialFloatProfit=" << info->SpecialFloatProfit << "],"
		<< "[SpecialCloseProfit=" << info->SpecialCloseProfit << "],"
		<< "[SpecialFloatPL=" << info->SpecialFloatPL << "],"
		<< "[SpecialClosePL=" << info->SpecialClosePL << "]"
		<<endl;
}
static void printTapAPIExchangeInfo(const TapAPIExchangeInfo *info)
{
	cout << "Details: "
		<< "[ExchangeNo=" << info->ExchangeNo << "],"
		<< "[ExchangeName=" << info->ExchangeName << "]"
		<< endl;
}

static void printTapAPICommodityInfo(const TapAPICommodityInfo *info)
{
	cout << "Details: "
		<< "[ExchangeNo=" << info->ExchangeNo << "],"
		<< "[CommodityType=" << info->CommodityType << "],"
		<< "[CommodityNo=" << info->CommodityNo << "],"
		<< "[CommodityName=" << info->CommodityName << "],"
		<< "[CommodityEngName=" << info->CommodityEngName << "],"
		<< "[RelateExchangeNo=" << info->RelateExchangeNo << "],"
		<< "[RelateCommodityType=" << info->RelateCommodityType << "],"
		<< "[RelateCommodityNo=" << info->RelateCommodityNo << "],"
		<< "[RelateExchangeNo2=" << info->RelateExchangeNo2 << "],"
		<< "[RelateCommodityType2=" << info->RelateCommodityType2 << "],"
		<< "[RelateCommodityNo2=" << info->RelateCommodityNo2 << "],"
		<< "[TradeCurrency=" << info->TradeCurrency << "],"
		<< "[SettleCurrency=" << info->SettleCurrency << "],"
		<< "[ContractSize=" << info->ContractSize << "],"
		<< "[MarginCalculateMode=" << info->MarginCalculateMode << "],"
		<< "[OptionMarginCalculateMode=" << info->OptionMarginCalculateMode << "],"
		<< "[OpenCloseMode=" << info->OpenCloseMode << "],"
		<< "[StrikePriceTimes=" << info->StrikePriceTimes << "],"
		<< "[IsOnlyQuoteCommodity=" << info->IsOnlyQuoteCommodity << "],"
		<< "[CommodityTickSize=" << info->CommodityTickSize << "],"
		<< "[CommodityDenominator=" << info->CommodityDenominator << "],"
		<< "[CmbDirect=" << info->CmbDirect << "],"
		<< "[OnlyCanCloseDays=" << info->OnlyCanCloseDays << "],"
		<< "[DeliveryMode=" << info->DeliveryMode << "],"
		<< "[DeliveryDays=" << info->DeliveryDays << "],"
		<< "[AddOneTime=" << info->AddOneTime << "],"
		<< "[CommodityTimeZone=" << info->CommodityTimeZone << "],"
		<< endl;
}

static void printTapAPITradeContractInfo(const TapAPITradeContractInfo *info)
{
	cout << "Details: "
		<< "[ExchangeNo=" << info->ExchangeNo << "],"
		<< "[CommodityType=" << info->CommodityType << "],"
		<< "[CommodityNo=" << info->CommodityNo << "],"
		<< "[ContractNo1=" << info->ContractNo1 << "],"
		<< "[StrikePrice1=" << info->StrikePrice1 << "],"
		<< "[CallOrPutFlag1=" << info->CallOrPutFlag1 << "],"
		<< "[ContractNo2=" << info->ContractNo2 << "],"
		<< "[StrikePrice2=" << info->StrikePrice2 << "],"
		<< "[CallOrPutFlag2=" << info->CallOrPutFlag2 << "],"
		<< "[ContractType=" << info->ContractType << "],"
		<< "[QuoteUnderlyingContract=" << info->QuoteUnderlyingContract << "],"
		<< "[ContractName=" << info->ContractName << "],"
		<< "[ContractExpDate=" << info->ContractExpDate << "],"
		<< "[LastTradeDate=" << info->LastTradeDate << "],"
		<< "[FirstNoticeDate=" << info->FirstNoticeDate << "],"
		<< "[FutureContractNo=" << info->FutureContractNo << "],"
		<< endl;
}

static void printTapAPICloseInfo(const TapAPICloseInfo *info)
{
	cout << "Details: "
		<< "[AccountNo=" << info->AccountNo << "],"
		<< "[ParentAccountNo=" << info->ParentAccountNo << "],"
		<< "[ExchangeNo=" << info->ExchangeNo << "],"
		<< "[CommodityType=" << info->CommodityType << "],"
		<< "[CommodityNo=" << info->CommodityNo << "],"
		<< "[ContractNo=" << info->ContractNo << "],"
		<< "[StrikePrice=" << info->StrikePrice << "],"
		<< "[CallOrPutFlag=" << info->CallOrPutFlag << "],"
		<< "[OpenOrderExchangeNo=" << info->OpenOrderExchangeNo << "],"
		<< "[OpenOrderCommodityType=" << info->OpenOrderCommodityType << "],"
		<< "[OpenOrderCommodityNo=" << info->OpenOrderCommodityNo << "],"
		<< "[CloseOrderExchangeNo=" << info->CloseOrderExchangeNo << "],"
		<< "[CloseOrderCommodityType=" << info->CloseOrderCommodityType << "],"
		<< "[CloseOrderCommodityNo=" << info->CloseOrderCommodityNo << "],"
		<< "[OpenMatchSource=" << info->OpenMatchSource << "],"
		<< "[CloseMatchSource=" << info->CloseMatchSource << "],"
		<< "[CloseSide=" << info->CloseSide << "],"
		<< "[CloseQty=" << info->CloseQty << "],"
		<< "[OpenPrice=" << info->OpenPrice << "],"
		<< "[ClosePrice=" << info->ClosePrice << "],"
		<< "[OpenServerFlag=" << info->OpenServerFlag << "],"
		<< "[OpenOrderNo=" << info->OpenOrderNo << "],"
		<< "[OpenMatchNo=" << info->OpenMatchNo << "],"
		<< "[OpenExchangeMatchNo=" << info->OpenExchangeMatchNo << "],"
		<< "[OpenMatchDateTime=" << info->OpenMatchDateTime << "],"
		<< "[CloseServerFlag=" << info->CloseServerFlag << "],"
		<< "[CloseOrderNo=" << info->CloseOrderNo << "],"
		<< "[CloseMatchNo=" << info->CloseMatchNo << "],"
		<< "[CloseExchangeMatchNo=" << info->CloseExchangeMatchNo << "],"
		<< "[CloseMatchDateTime=" << info->CloseMatchDateTime << "],"
		<< "[CloseStreamId=" << info->CloseStreamId << "],"
		<< "[OpenCloseMode=" << info->OpenCloseMode << "],"
		<< "[ContractSize=" << info->ContractSize << "],"
		<< "[CommodityCurrencyGroup=" << info->CommodityCurrencyGroup << "],"
		<< "[CommodityCurrency=" << info->CommodityCurrency << "],"
		<< "[PreSettlePrice=" << info->PreSettlePrice << "],"
		<< "[PremiumIncome=" << info->PremiumIncome << "],"
		<< "[PremiumPay=" << info->PremiumPay << "],"
		<< "[CloseProfit=" << info->CloseProfit << "],"
		<< "[UnExpProfit=" << info->UnExpProfit << "],"
		<< "[ClosePL=" << info->ClosePL << "]"
		<< endl;
}

static void printTapAPIPositionProfit(const TapAPIPositionProfit *info)
{
	cout << "Details: "
		<< "[PositionNo=" << info->PositionNo << "],"
		<< "[PositionStreamId=" << info->PositionStreamId << "],"
		<< "[PositionProfit=" << info->PositionProfit << "],"
		<< "[LMEPositionProfit=" << info->LMEPositionProfit << "],"
		<< "[OptionMarketValue=" << info->OptionMarketValue << "],"
		<< "[CalculatePrice=" << info->CalculatePrice << "],"
		<< "[FloatingPL=" << info->FloatingPL << "]"
		<< endl;
}

static void printTapAPIDeepQuoteInfo(const TapAPIDeepQuoteInfo *info)
{
	cout << "Details: "
		<< "[Side=" << info->Side << "],"
		<< "[Price=" << info->Price << "],"
		<< "[Qty=" << info->Qty << "]"
		<< endl;
}

static void printTapAPIExchangeStateInfo(const TapAPIExchangeStateInfo *info)
{
	cout << "Details: "
		<< "[UpperChannelNo=" << info->UpperChannelNo << "],"
		<< "[ExchangeNo=" << info->ExchangeNo << "],"
		<< "[CommodityType=" << info->CommodityType << "],"
		<< "[CommodityNo=" << info->CommodityNo << "],"
		<< "[ExchangeTime=" << info->ExchangeTime << "],"
		<< "[TradingState=" << info->TradingState << "]"
		<< endl;
}

static void printTapAPIReqQuoteNotice(const TapAPIReqQuoteNotice *info)
{
	cout << "Details: "
		<< "[ExchangeNo=" << info->ExchangeNo << "],"
		<< "[CommodityType=" << info->CommodityType << "],"
		<< "[CommodityNo=" << info->CommodityNo << "],"
		<< "[ContractNo=" << info->ContractNo << "],"
		<< "[StrikePrice=" << info->StrikePrice << "],"
		<< "[CallOrPutFlag=" << info->CallOrPutFlag << "],"
		<< "[InquiryNo=" << info->InquiryNo << "],"
		<< "[UpdateTime=" << info->UpdateTime << "],"
		<< endl;
}

static void printTapAPIUpperChannelInfo(const TapAPIUpperChannelInfo *info)
{
	cout << "Details: "
		<< "[UpperChannelNo=" << info->UpperChannelNo << "],"
		<< "[UpperChannelName=" << info->UpperChannelName << "],"
		<< "[UpperNo=" << info->UpperNo << "],"
		<< "[UpperUserNo=" << info->UpperUserNo << "]"
		<< endl;
}

static void printTapAPIAccountRentInfo(const TapAPIAccountRentInfo *info)
{
	cout << "Details: "
		<< "[AccountNo=" << info->AccountNo << "],"
		<< "[ExchangeNo=" << info->ExchangeNo << "],"
		<< "[CommodityType=" << info->CommodityType << "],"
		<< "[CommodityNo=" << info->CommodityNo << "],"
		<< "[ContractNo=" << info->ContractNo << "],"
		<< "[MatchSource=" << info->MatchSource << "],"
		<< "[CurrencyNo=" << info->CurrencyNo << "],"
		<< "[FeeMode=" << info->FeeMode << "],"
		<< "[OpenTurnover=" << info->OpenTurnover << "],"
		<< "[ClosedTurnover=" << info->ClosedTurnover << "],"
		<< "[CloseNewTurnover=" << info->CloseNewTurnover << "],"
		<< "[OpenVolume=" << info->OpenVolume << "],"
		<< "[ClosedVolume=" << info->ClosedVolume << "],"
		<< "[CloseNewVolume=" << info->CloseNewVolume << "],"
		<< "[MarginMode=" << info->MarginMode << "],"
		<< "[BuyTInitMargin=" << info->BuyTInitMargin << "],"
		<< "[SellTInitMargin=" << info->SellTInitMargin << "],"
		<< "[BuyBInitMargin=" << info->BuyBInitMargin << "],"
		<< "[SellBInitMargin=" << info->SellBInitMargin << "],"
		<< "[BuyLInitMargin=" << info->BuyLInitMargin << "],"
		<< "[SellLInitMargin=" << info->SellLInitMargin << "],"
		<< "[BuyMInitMargin=" << info->BuyMInitMargin << "],"
		<< "[SellMInitMargin=" << info->SellMInitMargin << "],"
		<< "[BuyTMaintMargin=" << info->BuyTMaintMargin << "],"
		<< "[SellTMaintMargin=" << info->SellTMaintMargin << "],"
		<< "[BuyBMaintMargin=" << info->BuyBMaintMargin << "],"
		<< "[SellBMaintMargin=" << info->SellBMaintMargin << "],"
		<< "[BuyLMaintMargin=" << info->BuyLMaintMargin << "],"
		<< "[SellLMaintMargin=" << info->SellLMaintMargin << "],"
		<< "[BuyMMaintMargin=" << info->BuyMMaintMargin << "],"
		<< "[SellMMaintMargin=" << info->SellMMaintMargin << "],"
		<< endl;
}

static void printTapAPIContract(const TapAPIContract* info)
{
	cout << "Details: "
		<< "[Commodity=" << info->Commodity.ExchangeNo<<"|"<<info->Commodity.CommodityNo<< "|" << info->Commodity.CommodityType << "],"
		<< "[ContractNo1=" << info->ContractNo1 << "],"
		<< "[StrikePrice1=" << info->StrikePrice1 << "],"
		<< "[CallOrPutFlag1=" << info->CallOrPutFlag1 << "],"
		<< "[ContractNo2=" << info->ContractNo2 << "],"
		<< "[StrikePrice2=" << info->StrikePrice2 << "],"
		<< "[CallOrPutFlag2=" << info->CallOrPutFlag2 << "]"
		<< endl;
}

#endif // TRADE_H
