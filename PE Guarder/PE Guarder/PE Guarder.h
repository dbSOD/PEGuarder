// PE Guarder.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPEGuarderApp:
// �йش����ʵ�֣������ PE Guarder.cpp
//

class CPEGuarderApp : public CWinApp
{
public:
	CPEGuarderApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPEGuarderApp theApp;