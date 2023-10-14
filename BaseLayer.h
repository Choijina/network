#pragma once
// BaseLayer.h: interface for the CBaseLayer class.
//
//////////////////////////////////////////////////////////////////////
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <pcap.h>
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <Packet32.h>
#pragma comment(lib,"packet.lib")


#include "pch.h"
#include"stdafx.h"

#if !defined(AFX_BASELAYER_H__041C5A07_23A9_4CBC_970B_8743460A7DA9__INCLUDED_) //Header guard
#define AFX_BASELAYER_H__041C5A07_23A9_4CBC_970B_8743460A7DA9__INCLUDED_

#if _MSC_VER > 1000 // 오래된 컴파일러 아니면
#pragma once // 헤더파일 중복방지
#endif // _MSC_VER > 1000

class CBaseLayer
{
public:
		char* GetLayerName();

		CBaseLayer* GetUnderLayer();
		CBaseLayer* GetUpperLayer(int nindex);
		void			SetUnderUpperLayer(CBaseLayer* pUULayer = NULL); // p접두사는 pointer UU는 upperupper
		void			SetUpperUnderLayer(CBaseLayer* pUULayer = NULL);
		void			SetUnderLayer(CBaseLayer* pUnderLayer = NULL);
		void			SetUpperLayer(CBaseLayer* pUpperLayer = NULL);

		CBaseLayer(char* pName = NULL);
		virtual ~CBaseLayer();

	// param : unsigned char*	- the data of the upperlayer
	//         int				- the length of data
	virtual	BOOL	Send(unsigned char*, int) { return FALSE; }
	// param : unsigned char*	- the data of the underlayer
	virtual	BOOL	Receive(unsigned char* ppayload) { return FALSE; }
	virtual	BOOL	Receive() { return FALSE; }

protected:
	char* m_pLayerName;			//m is member var naming
	CBaseLayer* mp_UnderLayer;							// UnderLayer pointer
	CBaseLayer* mp_aUpperLayer[MAX_LAYER_NUMBER];		// UpperLayer pointer
	int				m_nUpperLayerCount;						// UpperLayer Count
};

#endif // !defined(AFX_BASELAYER_H__041C5A07_23A9_4CBC_970B_8743460A7DA9__INCLUDED_)
