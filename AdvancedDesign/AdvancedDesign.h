
// AdvancedDesign.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


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
};

extern CAdvancedDesignApp theApp;