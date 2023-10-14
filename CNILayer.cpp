//practice : From Host1 To BroadCast Packet transfer


#define ETHERNET_ADDR_LEN 6
#include "CNILayer.h"

BOOL CNILayer::GetSrcMACAddr(unsigned char* pAddr) {
	LPADAPTER adapter = NULL;
	PPACKET_OID_DATA OidData;
	
	OidData = (PPACKET_OID_DATA)malloc(sizeof(PACKET_OID_DATA));
	if (!OidData) return FALSE;

	OidData->Oid = OID_802_3_CURRENT_ADDRESS; // OID for Mac addr
	OidData->Length = 6;

	adapter = PacketOpenAdapter((char*)m_pAdapter);
	if (!adapter) {
		free(OidData);
		return FALSE;
	}

	BOOL result = PacketRequest(adapter, FALSE, OidData);
	if (!result) {
		PacketCloseAdapter(adapter);
		free(OidData);
		return FALSE;
	}

	memcpy(pAddr, OidData->Data, 6);

	PacketCloseAdapter(adapter);
	free(OidData);
	return TRUE;
}