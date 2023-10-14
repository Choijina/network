#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseLayer.h"
#include "pch.h"

class CNILayer
	: public CBaseLayer
{
private:
	pcap_t* m_pAdapter;
	char m_errbuf[PCAP_ERRBUF_SIZE];

public:
	CNILayer::CNILayer(char* pName)
		: CBaseLayer(pName)
	{
		m_pAdapter = pcap_open_live(pName, 65536, 1, 1000, m_errbuf);
		if (m_pAdapter == nullptr) {
			fprintf(stderr, "fail : %s\n", m_errbuf);
			exit(1);
		}
	}
	~CNILayer() {
		pcap_close(m_pAdapter);
	}

	BOOL GetSrcMACAddr(unsigned char* pAddr);
	BOOL Send(unsigned char* pFrame, int nlength);
};