#pragma once
// ChatAppLayer.h: interface for the CChatAppLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATAPPLAYER_H__E78615DE_0F23_41A9_B814_34E2B3697EF2__INCLUDED_)
#define AFX_CHATAPPLAYER_H__E78615DE_0F23_41A9_B814_34E2B3697EF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseLayer.h"
#include "pch.h"
class CChatAppLayer
	: public CBaseLayer
{
private:
	inline void		ResetHeader();
	BOOL DoFragmentation(unsigned char* ppayload, int nlength);
	CObject* mp_Dlg;

public:
	BOOL			Receive(unsigned char* ppayload);
	BOOL			Send(unsigned char* ppayload, int nlength);
	unsigned int	GetDestinAddress();
	unsigned int	GetSourceAddress();
	void			SetDestinAddress(unsigned int dst_addr);
	void			SetSourceAddress(unsigned int src_addr);

	CChatAppLayer(char* pName);
	virtual ~CChatAppLayer();

	typedef struct _CHAT_APP
	{
		unsigned short	capp_totlen; // total length of message 2bytes
		unsigned char	capp_type;	// type of message 1byte
		unsigned char	capp_unused;	// unsed 1byte
		unsigned char	capp_data[MAX_APP_DATA];	//data up to 1496bytes
	} CHAT_APP, *LPCHAT_APP;


protected:
	_CHAT_APP		m_sPacket;

	enum {
		DATA_TYPE_CONT = 0x01,
		DATA_TYPE_END = 0x02
	};
};

#endif // !defined(AFX_CHATAPPLAYER_H__E78615DE_0F23_41A9_B814_34E2B3697EF2__INCLUDED_)








