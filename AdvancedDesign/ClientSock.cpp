// ClientSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AdvancedDesign.h"
#include "ClientSock.h"


// CClientSock

CClientSock::CClientSock()
{
}

CClientSock::~CClientSock()
{
}


// CClientSock ��� �Լ�


void CClientSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CAdvancedDesignApp*)AfxGetApp())->CloseChild();

	CAsyncSocket::OnClose(nErrorCode);
}


void CClientSock::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CAdvancedDesignApp*)AfxGetApp())->ReceiveData();

	CAsyncSocket::OnReceive(nErrorCode);

}
