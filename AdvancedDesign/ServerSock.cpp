// ServerSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "AdvancedDesign.h"
#include "ServerSock.h"


// CServerSock

CServerSock::CServerSock()
{
}

CServerSock::~CServerSock()
{
}


// CServerSock ��� �Լ�


void CServerSock::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CAdvancedDesignApp*)AfxGetApp())->Accept();

	CAsyncSocket::OnAccept(nErrorCode);
}
