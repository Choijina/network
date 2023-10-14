// BaseLayer.cpp: implementation of the CBaseLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ipc2023.h"
#include "BaseLayer.h"
#include "pch.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;	//디버그에서 어느 소스파일이 잘못되었는 지 알게해주는 code
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseLayer::CBaseLayer(char* pName)
	: m_nUpperLayerCount(0),
	mp_UnderLayer(NULL)
{
	m_pLayerName = pName;
}

CBaseLayer::~CBaseLayer()
{

}

void CBaseLayer::SetUnderUpperLayer(CBaseLayer* pUULayer)
{
	if (!pUULayer) // if the pointer is null, 
	{
#ifdef _DEBUG
		TRACE("[CBaseLayer::SetUnderUpperLayer] The variable , 'pUULayer' is NULL");
#endif
		return;
	}

	// ���ڷ� ���� ������ ���� ������ Under�� ����
	//231004 Modify
	this->SetUnderLayer(pUULayer);
	// ���� ������ ���ڷ� ���� ������ Upper�� ���´�.
	pUULayer->SetUpperLayer(this);
}

void CBaseLayer::SetUpperUnderLayer(CBaseLayer* pUULayer)
{
	if (!pUULayer) // if the pointer is null, 
	{
#ifdef _DEBUG
		TRACE("[CBaseLayer::SetUpperUnderLayer] The variable , 'pUULayer' is NULL");
#endif
		return;
	}



	this->SetUpperLayer(pUULayer);

	pUULayer->SetUnderLayer(this);

}

void CBaseLayer::SetUpperLayer(CBaseLayer* pUpperLayer)
{
	if (!pUpperLayer) // if the pointer is null, 
	{
#ifdef _DEBUG
		TRACE("[CBaseLayer::SetUpperLayer] The variable , 'pUpperLayer' is NULL");
#endif
		return;
	}

	// UpperLayer ���� ����
	//231004 Modify
	this->mp_aUpperLayer[m_nUpperLayerCount++] = pUpperLayer;
	for (int i = 0; i < m_nUpperLayerCount; i++) 
		printf("%s ", mp_aUpperLayer[i]->m_pLayerName);
}

void CBaseLayer::SetUnderLayer(CBaseLayer* pUnderLayer)
{
	if (!pUnderLayer) // if the pointer is null, 
	{
#ifdef _DEBUG
		TRACE("[CBaseLayer::SetUnderLayer] The variable , 'pUnderLayer' is NULL\n");
#endif
		return;
	}

	// UnderLayer assignment..
	this->mp_UnderLayer = pUnderLayer;
	printf("%s ", this->mp_UnderLayer->m_pLayerName);
}

CBaseLayer* CBaseLayer::GetUpperLayer(int nindex)
{
	if (nindex < 0 ||
		nindex > m_nUpperLayerCount ||
		m_nUpperLayerCount < 0)
	{
#ifdef _DEBUG
		TRACE("[CBaseLayer::GetUpperLayer] There is no UpperLayer in Array..\n");
#endif 
		return NULL;
	}

	return mp_aUpperLayer[nindex];
}

CBaseLayer* CBaseLayer::GetUnderLayer()
{
	if (!mp_UnderLayer)
	{
#ifdef _DEBUG
		TRACE("[CBaseLayer::GetUnderLayer] There is not a UnerLayer..\n");
#endif 
		return NULL;
	}

	return mp_UnderLayer;
}

char* CBaseLayer::GetLayerName()
{
	return m_pLayerName;
}

