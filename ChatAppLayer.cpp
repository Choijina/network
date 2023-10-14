// ChatAppLayer.cpp: implementation of the CChatAppLayer class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "pch.h"
#include "ChatAppLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChatAppLayer::CChatAppLayer(char* pName)
	: CBaseLayer(pName),
	mp_Dlg(NULL)
{
	ResetHeader();
}

CChatAppLayer::~CChatAppLayer()
{

}

void CChatAppLayer::ResetHeader()
{
	m_sPacket.capp_totlen = 0;
	m_sPacket.capp_type = 0x00;
	m_sPacket.capp_unused = 0x00;
	memset(m_sPacket.capp_data, 0, APP_DATA_SIZE);
}

BOOL CChatAppLayer::Send(unsigned char* ppayload, int nlength)
{
	if (nlength < MAX_APP_DATA) {
		m_sPacket.capp_totlen = (unsigned short)nlength;
		memcpy(m_sPacket.capp_data, ppayload, nlength);
		BOOL bSuccess = FALSE;

		bSuccess = mp_UnderLayer->Send((unsigned char*)&m_sPacket, sizeof(m_sPacket));
		return bSuccess;
	}
	else
		return DoFragmentation(ppayload, nlength);
}
BOOL CChatAppLayer::DoFragmentation(unsigned char* ppayload, int nlength) 
/* Returns whether it is framented or not
	@param1 - User Message
	@param2 - sizeof(ppayload)
	@return - BOOL
*/
{
	int remaining_length = nlength;
	int sent_length = 0;
	int total_framents = (nlength / MAX_APP_DATA) + 1;

	m_sPacket.capp_totlen = (unsigned short)nlength; //수신 대비

	while ((int)m_sPacket.capp_type < total_framents) { // type의 최대는 255일텐데 255 * 1496이상의 data만 안 받으면 됨, 예외 처리 필요x
		int current_send_length = (remaining_length > MAX_APP_DATA) ? MAX_APP_DATA : remaining_length;

		m_sPacket.capp_totlen = (unsigned short)current_send_length;
		memcpy(m_sPacket.capp_data, ppayload + sent_length, current_send_length);
		

		BOOL bSuccess = FALSE;

		bSuccess = mp_UnderLayer->Send((unsigned char*)&m_sPacket, sizeof(m_sPacket));
		return bSuccess;

		sent_length += current_send_length;
		remaining_length -= current_send_length;

		m_sPacket.capp_type++;
	}
	return TRUE;
}

BOOL CChatAppLayer::Receive(unsigned char* ppayload)
{
	CHAT_APP app_hdr = (CHAT_APP)ppayload;

	if (app_hdr->app_dstaddr == m_sPacket.app_srcaddr ||
		(app_hdr->app_srcaddr != m_sPacket.app_srcaddr &&
			app_hdr->app_dstaddr == (unsigned int)0xff))
	{
		unsigned char GetBuff[APP_DATA_SIZE]; 

		memset(GetBuff, 0, sizeof(GetBuff));  

		memcpy(GetBuff, app_hdr->app_data, app_hdr->app_length > APP_DATA_SIZE ? APP_DATA_SIZE : app_hdr->app_length);

		CString Msg;

		if (app_hdr->app_dstaddr == (unsigned int)0xff)
			Msg.Format(_T("[%d:BROADCAST] %s"), app_hdr->app_srcaddr, (char*)GetBuff);
		else
			Msg.Format(_T("[%d:%d] %s"), app_hdr->app_srcaddr, app_hdr->app_dstaddr, (char*)GetBuff);

		mp_aUpperLayer[0]->Receive((unsigned char*)(LPCTSTR)Msg);
		return TRUE;
	}
	else
		return FALSE;
}


