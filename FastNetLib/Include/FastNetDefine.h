#ifndef _FAST_NET_DEFINE_H__
#define _FAST_NET_DEFINE_H__
//#include "ISocket.h"


namespace fastnet
{
	class ISocket;

	enum EM_FAST_NET_EVENT_TYPE
	{
		EFNET_CONNECT,  //�յ�����
		EFNET_DISCONNECT, //�յ��Ͽ�����
		EFNET_RECV_DATA   //�յ�����
	} ;

	struct CFastNetEvent
	{
		EM_FAST_NET_EVENT_TYPE eventType;
		ISocket *pSocket;
	};

	class IFastNetEventListen
	{
	public:

		virtual void NotifyEvent(CFastNetEvent *pEvent) = 0;
	};

}

#endif/*_FAST_NET_DEFINE_H__*/
