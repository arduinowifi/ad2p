
// AdvancedDesign.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "ServerSock.h"
#include "ClientSock.h"


// CAdvancedDesignApp:
// �� Ŭ������ ������ ���ؼ��� AdvancedDesign.cpp�� �����Ͻʽÿ�.
//

class CAdvancedDesignApp : public CWinApp
{
public:
	CAdvancedDesignApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	void InitServer(void);
	CServerSock* m_pServer;
	CClientSock* m_pClient;
	void Accept(void);
	void Connect(CString strIP);
	void ReceiveData(void);
	void SendData(CString strData);
	void CloseChild(void);
	void CleanUp(void);
};

extern CAdvancedDesignApp theApp;