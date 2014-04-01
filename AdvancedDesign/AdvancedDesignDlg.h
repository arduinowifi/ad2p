
// AdvancedDesignDlg.h : ��� ����
//
#include "CommThread.h"	
#pragma once


// CAdvancedDesignDlg ��ȭ ����
class CAdvancedDesignDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CAdvancedDesignDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADVANCEDDESIGN_DIALOG };
	
	int m_iSendDataType;
	int m_iReceiveDataType;
	int m_iStopBit;
	int m_iSerialPort;
	int m_iParity;
	int m_iDataBit;
	int m_iBaudRate;
	CString m_strControl;
	CString m_strSend;
	CString m_strReceive;

	CEdit m_EditReceive;
	CEdit m_EditSend;
	CEdit m_EditControl;

	CComboBox m_cStopBit;
	CComboBox m_cSerialPort;
	CComboBox m_cSendDataType;
	CComboBox m_cReceiveDataType;
	CComboBox m_cParity;
	CComboBox m_cDataBit;
	CComboBox m_cBaudRate;

	CString m_strMyIP;
	CString m_strOtherIP;
	CIPAddressCtrl m_IPAddress;
	CListBox m_listChat;
	int m_nChatMode;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;
	
public:

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonSend();
	afx_msg void OnClickedRadioServer();
	afx_msg void OnRadioClient();
	void ReceiveData(CString strReceive);
	void Accept(CString strSock);
		
	afx_msg long OnCommunication(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnPortOpen();
	afx_msg void OnSendData();
	afx_msg void OnReceiveDataClear();
	afx_msg void OnSendDataClear();
	afx_msg void OnPortClose();
	afx_msg void OnControlboxclear();
	afx_msg void OnSelchangeBaudRate();
	afx_msg void OnSelchangeSerialPort();
	afx_msg void OnSelchangeDataBit();
	afx_msg void OnSelchangeStopBit();
	afx_msg void OnSelchangeParity();
	afx_msg void OnSelchangeSendDataType();
	afx_msg void OnSelchangeReceiveDataType();
	DECLARE_MESSAGE_MAP()
public:

	CCommThread m_ComuPort;

private:
	int m_iSize;
	int m_iCount;
	int nMakeHexData(); //���� ������ Ÿ���� hex�� ��� hex�����ͷ� ���� ����
	int nMakeAsciiData();//���� ������ Ÿ���� ascii�� ��� ascii�����ͷ� ���� ����
	BYTE byCode2AsciiValue(char cData);// ���ڸ� hex������ ���� 0~F ������ �״�� �� �ܿ� ���ڴ� 0���� 
	CString byIndexComPort(int xPort);// ��Ʈ�̸� �ޱ� 
	DWORD byIndexBaud(int xBaud);// ���۷� �ޱ�
	BYTE byIndexData(int xData);//������ ��Ʈ �ޱ�
	BYTE byIndexStop(int xStop);// �����Ʈ �ޱ� 
	BYTE byIndexParity(int xParity);// �縮Ƽ �ޱ�

public:
	char buff[255];
	bool isTCPon;
};
