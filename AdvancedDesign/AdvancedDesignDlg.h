
// AdvancedDesignDlg.h : 헤더 파일
//
#include "CommThread.h"	
#pragma once


// CAdvancedDesignDlg 대화 상자
class CAdvancedDesignDlg : public CDialogEx
{
// 생성입니다.
public:
	CAdvancedDesignDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	
public:

	// 생성된 메시지 맵 함수
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
	int nMakeHexData(); //보낼 데이터 타입이 hex일 경우 hex데이터로 만들어서 전송
	int nMakeAsciiData();//보낼 데이터 타입이 ascii일 경우 ascii데이터로 만들어서 전송
	BYTE byCode2AsciiValue(char cData);// 문자를 hex값으로 변경 0~F 까지는 그대로 그 외에 글자는 0으로 
	CString byIndexComPort(int xPort);// 포트이름 받기 
	DWORD byIndexBaud(int xBaud);// 전송률 받기
	BYTE byIndexData(int xData);//데이터 비트 받기
	BYTE byIndexStop(int xStop);// 스톱비트 받기 
	BYTE byIndexParity(int xParity);// 펠리티 받기

public:
	char buff[255];
	bool isTCPon;
};
