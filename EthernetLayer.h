// EthernetLayer.h: interface for the CEthernetLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ETHERNETLAYER_H__7857C9C2_B459_4DC8_B9B3_4E6C8B587B29__INCLUDED_)
#define AFX_ETHERNETLAYER_H__7857C9C2_B459_4DC8_B9B3_4E6C8B587B29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseLayer.h"
#include "pch.h"

class CEthernetLayer
	: public CBaseLayer
{
private:
	inline void		ResetFrame();

public:
	BOOL			Receive(unsigned char* ppayload);
	BOOL			Send(unsigned char* ppayload, int nlength);
	unsigned char* GetDestinAddress();
	unsigned char* GetSourceAddress();

	CEthernetLayer(char* pName);
	virtual ~CEthernetLayer();

	typedef struct _ETHERNET_ADDR
	{
		union {
			struct { unsigned char e0, e1, e2, e3, e4, e5; } s_un_byte;
			unsigned char s_ether_addr[6];
		} S_un;
#define addr0 S_un.s_un_byte.e0
#define addr1 S_un.s_un_byte.e1
#define addr2 S_un.s_un_byte.e2
#define addr3 S_un.s_un_byte.e3
#define addr4 S_un.s_un_byte.e4
#define addr5 S_un.s_un_byte.e5
#define addr S_un.s_ether_addr
	} ETHERNET_ADDR, * LPETHERNET_ADDR;

	typedef struct _ETHERNET
	{
		ETHERNET_ADDR enet_desaddr; // 상대방 주소
		ETHERNET_ADDR enet_srcaddr; // 자기 주소
		unsigned short enet_type; // frame data type
		unsigned char enet_data[ETHER_MAX_DATA_SIZE];
	} ETHERNET, * LPETHERNET;


protected:
	ETHERNET	m_sFrame	;
};

#endif // !defined(AFX_ETHERNETLAYER_H__7857C9C2_B459_4DC8_B9B3_4E6C8B587B29__INCLUDED_)
