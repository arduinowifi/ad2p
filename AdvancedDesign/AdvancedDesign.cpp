
// AdvancedDesign.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "AdvancedDesign.h"
#include "AdvancedDesignDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdvancedDesignApp

BEGIN_MESSAGE_MAP(CAdvancedDesignApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAdvancedDesignApp ����

CAdvancedDesignApp::CAdvancedDesignApp()
	: m_pServer(NULL)
	, m_pClient(NULL)
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CAdvancedDesignApp ��ü�Դϴ�.

CAdvancedDesignApp theApp;


// CAdvancedDesignApp �ʱ�ȭ

BOOL CAdvancedDesignApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CAdvancedDesignDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}




void CAdvancedDesignApp::InitServer(void)
{
	 m_pServer = new CServerSock;
     m_pServer->Create(7777);
     m_pServer->Listen();	
}


void CAdvancedDesignApp::Accept(void)
{
	if (m_pClient == NULL)
	{
		m_pClient = new CClientSock;
		m_pServer->Accept(*m_pClient);
		CString strSock;
		UINT nPort;
		m_pClient->GetPeerName(strSock,nPort);
		((CAdvancedDesignDlg*)m_pMainWnd)->Accept(strSock);
	}	
}


void CAdvancedDesignApp::Connect(CString strIP)
{
	m_pClient = new CClientSock;
	m_pClient->Create();
	m_pClient->Connect(strIP, 7777);
}



void CAdvancedDesignApp::ReceiveData(void)
{
	char temp[MAX_PATH];
	m_pClient->Receive(temp, sizeof(temp));
	((CAdvancedDesignDlg*)m_pMainWnd)->ReceiveData(temp);
}


void CAdvancedDesignApp::SendData(CString strData)
{
	if (m_pClient)
	{
		m_pClient->Send((LPCTSTR)strData, sizeof(TCHAR)*(strData.GetLength()+1));
	}
}


void CAdvancedDesignApp::CloseChild(void)
{
	AfxMessageBox(_T("���� ���� ����"));
	delete m_pClient;
	m_pClient = NULL;
}


void CAdvancedDesignApp::CleanUp(void)
{
	if(m_pServer)
		delete m_pServer;

	if(m_pClient)
		delete m_pClient;


}
