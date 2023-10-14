// EthernetLayer.cpp: implementation of the CEthernetLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pch.h"
#include "EthernetLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEthernetLayer::CEthernetLayer(char* pName)
	: CBaseLayer(pName)
{
	ResetFrame();
}

CEthernetLayer::~CEthernetLayer()
{
}

void CEthernetLayer::ResetFrame()
{
	memset(m_sFrame.enet_desaddr.addr, 0, 6);	//공용체의 특징 
	memset(m_sFrame.enet_srcaddr.addr, 0, 6);
	memset(m_sFrame.enet_data, ETHER_MAX_DATA_SIZE, 6);	
	m_sFrame.enet_type = 0x2080; //만약 ChatAppLayer에게 주는 것이 아닌 FileAppLayer에게 준다면 0x2090으로 초기화
}

unsigned char* CEthernetLayer::GetSourceAddress()
{
	return m_sHeader.enet_srcaddr;
}

unsigned char* CEthernetLayer::GetDestinAddress()
{
	return m_sHeader.enet_dstaddr;
}


BOOL CEthernetLayer::Send(unsigned char* ppayload, int nlength)
{
	memcpy(m_sFrame.enet_data, ppayload, nlength);

	BOOL bSuccess = FALSE;
	bSuccess = mp_UnderLayer->Send((unsigned char*)&m_sFrame,sizeof(m_sFrame));
	return bSuccess;
}

BOOL CEthernetLayer::Receive(unsigned char* ppayload)
{
	PETHERNET_HEADER pFrame = (PETHERNET_HEADER)ppayload;

	BOOL bSuccess = FALSE;

	bSuccess = mp_aUpperLayer[0]->Receive((unsigned char*)pFrame->enet_data);

	return bSuccess;
}
