// PE Guarder Server.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPEGuarderServerApp:
// �йش����ʵ�֣������ PE Guarder Server.cpp
//

class CPEGuarderServerApp : public CWinApp
{
public:
	CPEGuarderServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPEGuarderServerApp theApp;