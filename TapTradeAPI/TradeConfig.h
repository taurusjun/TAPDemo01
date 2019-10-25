#ifndef TRADE_CONFIG_H
#define TRADE_CONFIG_H

//交易IP地址与端口
#define DEFAULT_IP		("123.161.206.213")
#define DEFAULT_PORT	(6060)

//授权码
// #define DEFAULT_AUTHCODE	("67EA896065459BECDFDB924B29CB7DF1946CED\
// 32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC5211AF9FEE\
// 541DDE41BCBAB68D525B0D111A0884D847D57163FF7F329FA574E7946CED32E26C1E\
// AC946CED32E26C1EAC733827B0CE853869ABD9B8F170E14F8847D3EA0BF4E191F5D9\
// 7B3DFE4CCB1F01842DD2B3EA2F4B20CAD19B8347719B7E20EA1FA7A3D1BFEFF22290\
// F4B5C43E6C520ED5A40EC1D50ACDF342F46A92CCF87AEE6D73542C42EC17818349C7\
// DEDAB0E4DB16977714F873D505029E27B3D57EB92D5BEDA0A710197EB67F94BB1892\
// B30F58A3F211D9C3B3839BE2D73FD08DD776B9188654853DDA57675EBB7D6FBBFC")

#define DEFAULT_AUTHCODE	("Demo_TestCollect")
//用户名密码
#define DEFAULT_USERNAME	("Q48753284")
#define DEFAULT_PASSWORD	("335236")

//下单
#define DEFAULT_ACCOUNT_NO		(DEFAULT_USERNAME)

///------------- 日盘 9:00~15:00 -------------
#define DEFAULT_EXCHANGE_NO		("CFFEX")
#define DEFAULT_COMMODITY_TYPE	(TAPI_COMMODITY_TYPE_FUTURES)
#define DEFAULT_COMMODITY_NO	("IF")
#define DEFAULT_CONTRACT_NO		("1911")
///-------------------------------

///------------- 夜盘 21:00~1:00 -------------
// #define DEFAULT_EXCHANGE_NO		("ZCE")
// #define DEFAULT_COMMODITY_TYPE	(TAPI_COMMODITY_TYPE_FUTURES)
// #define DEFAULT_COMMODITY_NO	("CF")
// #define DEFAULT_CONTRACT_NO		("001")
///-------------------------------

#define DEFAULT_ORDER_TYPE		(TAPI_ORDER_TYPE_MARKET)
#define DEFAULT_ORDER_SIDE		(TAPI_SIDE_BUY)
#define DEFAULT_ORDER_SIDE_SELL		(TAPI_SIDE_SELL)
#define DEFAULT_POSITION_EFFECT	(TAPI_PositionEffect_OPEN)
#define DEFAULT_POSITION_EFFECT_COVER	(TAPI_PositionEffect_COVER)
#define DEFAULT_ORDER_PRICE		(0)
#define DEFAULT_ORDER_QTY		(1)	

#endif // TRADE_CONFIG_H
