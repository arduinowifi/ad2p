
// AdvancedDesignDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "AdvancedDesign.h"
#include "AdvancedDesignDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HWND hCommWnd;


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAdvancedDesignDlg ��ȭ ����




CAdvancedDesignDlg::CAdvancedDesignDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdvancedDesignDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strMyIP = _T("");
	m_strOtherIP = _T("");
	m_nChatMode = 0;
	m_iParity = 0;
	m_strReceive = _T("");
	m_iBaudRate = 1;
	m_strControl = _T("");
	m_iDataBit = 3;
	m_iReceiveDataType = 0;
	m_strSend = _T("");
	m_iSendDataType = 0;
	m_iSerialPort = 0;
	m_iStopBit = 0;
	m_iSize = 0;
	m_iCount = 0;
	buff[0] = NULL;
	isTCPon = FALSE;
}

void CAdvancedDesignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CONTROL, m_strControl);
	DDX_Text(pDX, IDC_RECEIVE, m_strReceive);
	DDX_Text(pDX, IDC_SEND, m_strSend);
	DDX_CBIndex(pDX, IDC_BAUD_RATE, m_iBaudRate);
	DDX_CBIndex(pDX, IDC_DATA_BIT, m_iDataBit);
	DDX_CBIndex(pDX, IDC_PARITY, m_iParity);
	DDX_CBIndex(pDX, IDC_SERIAL_PORT, m_iSerialPort);
	DDX_CBIndex(pDX, IDC_STOP_BIT, m_iStopBit);
	DDX_CBIndex(pDX, IDC_RECEIVE_DATA_TYPE, m_iReceiveDataType);
	DDX_CBIndex(pDX, IDC_SEND_DATA_TYPE, m_iSendDataType);
	DDX_Control(pDX, IDC_BAUD_RATE, m_cBaudRate);
	DDX_Control(pDX, IDC_DATA_BIT, m_cDataBit);
	DDX_Control(pDX, IDC_PARITY, m_cParity);
	DDX_Control(pDX, IDC_RECEIVE_DATA_TYPE, m_cReceiveDataType);
	DDX_Control(pDX, IDC_SEND_DATA_TYPE, m_cSendDataType);
	DDX_Control(pDX, IDC_SERIAL_PORT, m_cSerialPort);
	DDX_Control(pDX, IDC_STOP_BIT, m_cStopBit);
	DDX_Control(pDX, IDC_CONTROL, m_EditControl);
	DDX_Control(pDX, IDC_SEND, m_EditSend);
	DDX_Control(pDX, IDC_RECEIVE, m_EditReceive);

	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_IPAddress);
	DDX_Control(pDX, IDC_LIST_CHAT, m_listChat);
	DDX_Radio(pDX, IDC_RADIO_SERVER, m_nChatMode);
}

BEGIN_MESSAGE_MAP(CAdvancedDesignDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_COMM_READ , OnCommunication) //�߰�
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CAdvancedDesignDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CAdvancedDesignDlg::OnClickedButtonSend)
	ON_BN_CLICKED(IDC_RADIO_SERVER, &CAdvancedDesignDlg::OnClickedRadioServer)
	ON_COMMAND(IDC_RADIO_CLIENT, &CAdvancedDesignDlg::OnRadioClient)


	ON_BN_CLICKED(IDC_CONTROLBOXCLEAR, &CAdvancedDesignDlg::OnControlboxclear)
	ON_BN_CLICKED(IDC_FILE_OPEN, &CAdvancedDesignDlg::OnFileOpen)
	ON_BN_CLICKED(IDC_FILE_SAVE, &CAdvancedDesignDlg::OnFileSave)
	ON_BN_CLICKED(IDC_PORT_CLOSE, &CAdvancedDesignDlg::OnPortClose)
	ON_BN_CLICKED(IDC_PORT_OPEN, &CAdvancedDesignDlg::OnPortOpen)
	ON_BN_CLICKED(IDC_RECEIVE_DATA_CLEAR, &CAdvancedDesignDlg::OnReceiveDataClear)
	ON_BN_CLICKED(IDC_SEND_DATA, &CAdvancedDesignDlg::OnSendData)
	ON_BN_CLICKED(IDC_SEND_DATA_CLEAR, &CAdvancedDesignDlg::OnSendDataClear)

	ON_CBN_SELCHANGE(IDC_BAUD_RATE, &CAdvancedDesignDlg::OnSelchangeBaudRate)
	ON_CBN_SELCHANGE(IDC_DATA_BIT, &CAdvancedDesignDlg::OnSelchangeDataBit)
	ON_CBN_SELCHANGE(IDC_PARITY, &CAdvancedDesignDlg::OnSelchangeParity)
	ON_CBN_SELCHANGE(IDC_RECEIVE_DATA_TYPE, &CAdvancedDesignDlg::OnSelchangeReceiveDataType)
	ON_CBN_SELCHANGE(IDC_SEND_DATA_TYPE, &CAdvancedDesignDlg::OnSelchangeSendDataType)
	ON_CBN_SELCHANGE(IDC_SERIAL_PORT, &CAdvancedDesignDlg::OnSelchangeSerialPort)
	ON_CBN_SELCHANGE(IDC_STOP_BIT, &CAdvancedDesignDlg::OnSelchangeStopBit)

END_MESSAGE_MAP()


// CAdvancedDesignDlg �޽��� ó����

BOOL CAdvancedDesignDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	hCommWnd = m_hWnd;

	//IP�ּ� ��������
	char name[255]; 
	PHOSTENT hostinfo;
	if ( gethostname(name, sizeof(name)) == 0)
	{
		if ((hostinfo = gethostbyname(name)) != NULL) 
		{
			m_strMyIP = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
		}
	}

	//��Ʈ�� �ʱ�ȭ
	m_IPAddress.SetWindowText(m_strMyIP);
	m_IPAddress.EnableWindow(FALSE);
	SetDlgItemText(IDC_BUTTON_CONNECT,_T("OPEN"));

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CAdvancedDesignDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAdvancedDesignDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CAdvancedDesignDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAdvancedDesignDlg::OnClickedRadioServer()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_IPAddress.SetWindowText(m_strMyIP);
	m_IPAddress.EnableWindow(FALSE);
	SetDlgItemText(IDC_BUTTON_CONNECT,_T("OPEN"));
}

void CAdvancedDesignDlg::OnRadioClient()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_IPAddress.SetWindowText(_T(""));
	m_IPAddress.EnableWindow(TRUE);
	SetDlgItemText(IDC_BUTTON_CONNECT,_T("CONNECT"));

}


void CAdvancedDesignDlg::OnClickedButtonConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	if (!m_nChatMode)
	{
		((CAdvancedDesignApp*)AfxGetApp())->InitServer();
		GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	}
	else
	{
		CString strIP;
		GetDlgItemText(IDC_IPADDRESS_SERVER, strIP);
		if (strIP != _T("0.0.0.0"))
		{
			GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
			((CAdvancedDesignApp*)AfxGetApp())->Connect(strIP);
			m_strOtherIP = strIP;
		}
		else
		{
			AfxMessageBox(_T("������ ������ IP�ּҸ� �Է��ϼ���"));
		}
	}
	isTCPon = TRUE;
}


void CAdvancedDesignDlg::OnClickedButtonSend()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strSend, strInsert;
	GetDlgItemText(IDC_EDIT_SEND, strSend);
	strInsert.Format(_T("[%s]:%s"), m_strMyIP, strSend);
	theApp.SendData(strSend);
	int sel = m_listChat.InsertString(-1, strInsert);
	m_listChat.SetCurSel(sel);
	SetDlgItemText(IDC_EDIT_SEND, _T(""));
}

void CAdvancedDesignDlg::ReceiveData(CString strReceive)
{
	CString strInsert;
	strInsert.Format(_T("[%s]:%s"), m_strOtherIP, strReceive);
	int sel = m_listChat.InsertString(-1, strInsert);
	m_listChat.SetCurSel(sel);
}


void CAdvancedDesignDlg::Accept(CString strSock)
{
	m_strOtherIP = strSock;
}

void CAdvancedDesignDlg::OnControlboxclear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_iSize =0;
	m_EditControl.SetSel(0,-1);
	m_EditControl.Clear();
	m_strControl.Empty();
}


void CAdvancedDesignDlg::OnFileOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//txt������ ��� SEND������ â�� ������ �� ����
	CString GetFileName;
	char *buf;
	CFile file;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST, "Text File(*.txt)|*txt", NULL);
	if(dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetFileName(),CFile::modeRead, NULL);
		DWORD len = file.GetLength();				
		buf = new char[len];
		memset(buf,0,len);
		file.Read(buf, len);
		SetDlgItemText(IDC_SEND,buf);
		delete [] buf;
		file.Close();
	}
}


void CAdvancedDesignDlg::OnFileSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//���� ������ ������ txt���Ϸ� ���� 
	UpdateData(TRUE);
	CFileException ex;
	CFile file;
	CString name;
	CFileDialog dlg(FALSE,NULL,NULL,OFN_FILEMUSTEXIST, "Text File (*.*)|*", NULL);
	if(dlg.DoModal() == IDOK)
	{
		name = dlg.GetFileName();
		name.MakeLower();
		if(name.Right(4) != "" )
		{
			name += "";
		}
		file.Open(name, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary, &ex);
		file.Write(m_strReceive,m_strReceive.GetLength());
		file.Close();
	}
}


void CAdvancedDesignDlg::OnPortClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString PortName;
	if(m_ComuPort.m_bConnected == TRUE)
	{	
		m_ComuPort.ClosePort();
		PortName.Format("CLOSE PORT: %s \r\n",byIndexComPort(m_iSerialPort));
		m_EditControl.SetSel(-1,0);
		m_EditControl.ReplaceSel(PortName);
	}
	else
	{
		PortName.Format("%s Port not yet open \r\n",byIndexComPort(m_iSerialPort));
		m_EditControl.SetSel(-1,0);
		m_EditControl.ReplaceSel(PortName);

	}
}


void CAdvancedDesignDlg::OnPortOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString PortName;
	PortName.Format("OPEN PORT: %s\r\n",byIndexComPort(m_iSerialPort));
	if(m_ComuPort.m_bConnected == FALSE)//��Ʈ�� ���� ���� ��쿡�� ��Ʈ�� ���� ����
	{
		if(m_ComuPort.OpenPort(byIndexComPort(m_iSerialPort), byIndexBaud(m_iBaudRate), byIndexData(m_iDataBit), byIndexStop(m_iStopBit), byIndexParity(m_iParity)) ==TRUE)
		{
			m_EditControl.SetSel(-1,0);
			m_EditControl.ReplaceSel(PortName);
		}
	}
	else
	{
		AfxMessageBox("Already Port open");
	}
}

void CAdvancedDesignDlg::OnSelchangeSerialPort()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString change,str;
	m_iSerialPort = m_cSerialPort.GetCurSel();
	m_cSerialPort.GetLBText(m_iSerialPort,str);
	change.Format("ComPort change: %s \r\n",str);
	m_EditControl.SetSel(-1,0);
	m_EditControl.ReplaceSel(change);

}

void CAdvancedDesignDlg::OnSelchangeBaudRate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString change,str;
	m_iBaudRate = m_cBaudRate.GetCurSel();
	if(m_ComuPort.m_bConnected == TRUE)
	{
		m_ComuPort.ClosePort();
		m_ComuPort.OpenPort(byIndexComPort(m_iSerialPort), byIndexBaud(m_iBaudRate), byIndexData(m_iDataBit), byIndexStop(m_iStopBit), byIndexParity(m_iParity));
	}
	m_cBaudRate.GetLBText(m_iBaudRate,str);
	change.Format("BaudRate change: %s \r\n",str);
	m_EditControl.SetSel(-1,0);
	m_EditControl.ReplaceSel(change);
}

void CAdvancedDesignDlg::OnSelchangeDataBit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString change,str;
	m_iDataBit = m_cDataBit.GetCurSel();
	if(m_ComuPort.m_bConnected == TRUE)
	{
		m_ComuPort.ClosePort();
		m_ComuPort.OpenPort(byIndexComPort(m_iSerialPort), byIndexBaud(m_iBaudRate), byIndexData(m_iDataBit), byIndexStop(m_iStopBit), byIndexParity(m_iParity));
	}
	m_cDataBit.GetLBText(m_iDataBit,str);
	change.Format("DataBit change: %s \r\n",str);
	m_EditControl.SetSel(-1,0);
	m_EditControl.ReplaceSel(change);


}


void CAdvancedDesignDlg::OnSelchangeStopBit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString change, str;
	m_iStopBit= m_cStopBit.GetCurSel();
	if(m_ComuPort.m_bConnected == TRUE)
	{
		m_ComuPort.ClosePort();
		m_ComuPort.OpenPort(byIndexComPort(m_iSerialPort), byIndexBaud(m_iBaudRate), byIndexData(m_iDataBit), byIndexStop(m_iStopBit), byIndexParity(m_iParity));
	}
	m_cStopBit.GetLBText(m_iStopBit,str);
	change.Format("StopBit change: %s \r\n",str);
	m_EditControl.SetSel(-1,0);
	m_EditControl.ReplaceSel(change);
}

void CAdvancedDesignDlg::OnSelchangeParity()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString change,str;
	m_iParity = m_cParity.GetCurSel();
	if(m_ComuPort.m_bConnected == TRUE)
	{
		m_ComuPort.ClosePort();
		m_ComuPort.OpenPort(byIndexComPort(m_iSerialPort), byIndexBaud(m_iBaudRate), byIndexData(m_iDataBit), byIndexStop(m_iStopBit), byIndexParity(m_iParity));
	}
	m_cParity.GetLBText(m_iParity,str);
	change.Format("Parity change: %s \r\n",str);
	m_EditControl.SetSel(-1,0);
	m_EditControl.ReplaceSel(change);

}


void CAdvancedDesignDlg::OnSelchangeSendDataType()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString change, data;
	m_cSendDataType.GetLBText(m_iSendDataType,data);
	change.Format("Send Data Type change: %s \r\n",data);
	m_EditControl.SetSel(-1,0);
	m_EditControl.ReplaceSel(change);
}

void CAdvancedDesignDlg::OnSelchangeReceiveDataType()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString change,data;
	m_cReceiveDataType.GetLBText(m_iReceiveDataType,data);
	change.Format("Receive Data Type change: %s \r\n",data);
	m_EditControl.SetSel(-1,0);
	m_EditControl.ReplaceSel(change);

}



CString CAdvancedDesignDlg::byIndexComPort(int xPort)
{
	CString PortName;
	switch(xPort)
	{
		case 0:		PortName = "COM1"; 			break;
			
		case 1:		PortName = "COM2";			break;

		case 2:		PortName = "COM3"; 			break;
		
		case 3:		PortName = "COM4";			break;
			
		case 4:		PortName = "\\\\.\\COM5"; 	break;
			
		case 5:		PortName = "\\\\.\\COM6";	break;
			
		case 6:		PortName = "\\\\.\\COM7"; 	break;
			
		case 7:		PortName = "\\\\.\\COM8";	break;
		
		case 8:		PortName = "\\\\.\\COM9"; 	break;
			
		case 9:		PortName = "\\\\.\\COM10";	break;
	}


	
	return PortName;
}

DWORD CAdvancedDesignDlg::byIndexBaud(int xBaud)
{
	DWORD dwBaud;
	switch(xBaud)
	{
		case 0:		dwBaud = CBR_4800;		break;
			
		case 1:		dwBaud = CBR_9600;		break;
	
		case 2:		dwBaud = CBR_14400;		break;
	
		case 3:		dwBaud = CBR_19200;		break;
	
		case 4:		dwBaud = CBR_38400;		break;
	
		case 5:		dwBaud = CBR_56000;		break;
	
		case 6:		dwBaud = CBR_57600;		break;
	
		case 7:		dwBaud = CBR_115200;	break;
	}

	return dwBaud;
}

BYTE CAdvancedDesignDlg::byIndexData(int xData)
{
	BYTE byData;
	switch(xData)
	{
		case 0 :	byData = 5;			break;
	
		case 1 :	byData = 6;			break;
		
		case 2 :	byData = 7;			break;
		
		case 3 :	byData = 8;			break;
	}
	return byData;
}

BYTE CAdvancedDesignDlg::byIndexStop(int xStop)
{
	BYTE byStop;
	if(xStop == 0)
	{
		byStop = ONESTOPBIT;
	}
	else
	{
		byStop = TWOSTOPBITS;
	}
	return byStop;
}
BYTE CAdvancedDesignDlg::byIndexParity(int xParity)
{
	BYTE byParity;
	switch(xParity)
	{
	case 0 :	byParity = NOPARITY;	break;
	
	case 1 :	byParity = ODDPARITY;	break;
	
	case 2 :	byParity = EVENPARITY;	break;
	}

	return byParity;
}

BYTE CAdvancedDesignDlg::byCode2AsciiValue(char cData)
{
	//�� �Լ��� char���ڸ� hex������ ������ �ִ� �Լ� �Դϴ�.
	BYTE byAsciiValue;
	if( ( '0' <= cData ) && ( cData <='9' ) )
	{
		byAsciiValue = cData - '0';
	}
	else if( ( 'A' <= cData ) && ( cData <= 'F' ) )
	{
		byAsciiValue = (cData - 'A') + 10;
	}
	else if( ( 'a' <= cData ) && ( cData <= 'f' ) )
	{
		byAsciiValue = (cData - 'a') + 10;
	}
	else
	{
		byAsciiValue = 0;
	}
	return byAsciiValue;
}

void CAdvancedDesignDlg::OnSendData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	int iSize;
	char sSize[128];
	if(m_iSendDataType == 0) //������  �����Ͱ� ascii or hex�� ���� 
	{
		iSize = nMakeHexData(); //�����͸�  hex�� ���� ���
	}
	else
	{
		iSize = nMakeAsciiData();// �����͸� ascii�� ���� ��� 
	}
	wsprintf(sSize,"Send %d Characters \r\n",iSize);
	m_EditControl.SetSel(-1,0);
	m_EditControl.ReplaceSel(sSize);//����â�� ���� ������ ������ ������

}

int CAdvancedDesignDlg::nMakeHexData()
{
	int bufPos = 0;
	int datasize,bufsize, i,j;
	BYTE *Send_buff, byHigh, byLow;
	CString byGetData = m_strSend; //��Ʈ�� �ɹ� ������ �޴´�.
	byGetData.Replace(" ","");// ���� ���ֱ� 
	byGetData.Replace("\r\n","");//���� ���ֱ�
	datasize = byGetData.GetLength(); // ������ ���� ���ڿ� ���� ��� 

	// ���� ���̸� %2�� ���� ���� 0�� �ƴϸ� Ȧ�� �̱� ������ ������ ���ڸ� ó�� ����� ��
	if(datasize %2 == 0)
	{
		bufsize = datasize;
	}
	else
	{
		bufsize = datasize -1; 
	}

	Send_buff = new BYTE[bufsize];

	for( i = 0; i < bufsize ; i+=2)
	{
		byHigh = byCode2AsciiValue(byGetData[i]);
		byLow  = byCode2AsciiValue(byGetData[i+1]);
		Send_buff[bufPos++] = (byHigh <<4) | byLow;

	}
	//������ ���ڰ� 1�ڸ��� �϶� ó�� �ϱ� ����  ��) 1 -> 01
	if(datasize %2 !=0)
	{	
		Send_buff[bufPos++] = byCode2AsciiValue(byGetData[datasize-1]);
	}

	int etc = bufPos % 8;
	//��Ʈ�� �����͸� 8���� ���� ����
	//�������� ���̰� 8�� ����� �ƴϸ� ������ �����ʹ� ���� ������
	for(j =0; j < bufPos-etc; j+= 8)//8�� ��� ����
	{
		m_ComuPort.WriteComm(&Send_buff[j], 8) ;
	}
	if(etc != 0)//������ ������ ����
	{
		m_ComuPort.WriteComm(&Send_buff[bufPos -etc], etc) ;// ��Ʈ�� ������ ���� 
	}

	delete [] Send_buff;
	return bufPos;

}

int CAdvancedDesignDlg::nMakeAsciiData()
{

	int nSize = m_strSend.GetLength();
	int bufPos = 0;
	BYTE *Send_buff;
	Send_buff = new BYTE[nSize];
	for(int i = 0; i < nSize; i++)//ASCII ������ �̱� ������ ���Ϳ� �״�� ����
	{
		Send_buff[bufPos++] = m_strSend[i];
	}
	int etc = bufPos % 8;
	//��Ʈ�� �����͸� 8���� ���� ����
	//�������� ���̰� 8�� ����� �ƴϸ� ������ �����ʹ� ���� ������
	for(int j =0; j < bufPos-etc; j+= 8)
	{
		m_ComuPort.WriteComm(&Send_buff[j], 8) ;
	}
	if(etc != 0)//������ ������ ����
	{
		m_ComuPort.WriteComm(&Send_buff[bufPos -etc], etc) ;
	}
	delete [] Send_buff;
	return nSize;

}

long CAdvancedDesignDlg::OnCommunication(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);//�޴� ������ Ÿ���� �˱� ����
	CString str = "";
	CString result;
	char size[128];
	BYTE aByte; //�����͸� ������ ���� 
	int iSize =  (m_ComuPort.m_QueueRead).GetSize(); //��Ʈ�� ���� ������ ����
	//SetCommState�� ������ ���� ������ ���� 8���� ����
	m_iSize += iSize;	//���� �������� �� ������ ����â�� �����ֱ� ���� 
	wsprintf(size,"Receive %d characters\r\n",m_iSize);
	if(iSize != 0)//���� ������ 0�� �ƴϸ� ȭ�鿡 ���� ������ ����â��  ���
	{
		m_EditControl.SetSel(-1,0);
		m_EditControl.ReplaceSel(size);
	}

	for(int i  = 0 ; i < iSize; i++)//���� ���� ��ŭ �����͸� �о� �� ȭ�鿡 ������
	{
		(m_ComuPort.m_QueueRead).GetByte(&aByte);//ť���� ������ �Ѱ��� �о��
		switch(m_iReceiveDataType)//�޴� ������ Ÿ���� ASCII or HEX �ΰ��� ���� ������ �޴� ���� �ٸ���
		{
		case 0: //�����Ͱ� HEX�̸�
			str.Format("%02X ", aByte);	
			m_iCount++;//������ ���� ����
			if((m_iCount % 16) == 0) //16���� ������ �� �ٲ�
			{
				str += _T("\r\n");
			}
			/*else if((m_iCount % 8) ==0)//8���� ������ TAB�� �־ ������ ���� 
			{
			str += _T("\t");
			}*/
			result += str;
			break;
		case 1://�����Ͱ� ASCII�̸�
			str.Format("%c", aByte);
			result+= str;
			strcpy(buff, result);
			break;
		}
	}	
	m_EditReceive.SetSel(-1,0);
	m_EditReceive.ReplaceSel(result);//ȭ�鿡 ���� ������ ������

	// TCP ���� ����
	if(isTCPon)
	{
		CString strSend, strInsert;
		strSend = result;
		strInsert.Format(_T("[%s]:%s"), m_strMyIP, strSend);
		theApp.SendData(strSend);
		int sel = m_listChat.InsertString(-1, strInsert);
		m_listChat.SetCurSel(sel);
		SetDlgItemText(IDC_EDIT_SEND, _T(""));
	}

	return 1;
}

void CAdvancedDesignDlg::OnReceiveDataClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//�̷����� ���� �ּ��� ���� �ʿ䰡 ������?
	m_iCount =0;
	m_EditReceive.SetSel(0, -1);
	m_EditReceive.Clear();
	m_strReceive.Empty();
}

void CAdvancedDesignDlg::OnSendDataClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_EditSend.SetSel(0,-1);
	m_EditSend.Clear();
	m_strSend.Empty();
	m_EditSend.SetFocus();	
}





