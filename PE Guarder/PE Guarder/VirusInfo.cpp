#include "StdAfx.h"
#include "VirusInfo.h"

CVirusInfo::CVirusInfo(void)
{
}

CVirusInfo::~CVirusInfo(void)
{
}


// ���ݲ���ID��ȡ������
//
LPCSTR CVirusInfo::GetNameByID(DWORD dwVID)
{
	LPCSTR pVName = NULL;

	switch(dwVID)
	{
	case 1:
		pVName = "Dos.Eicar";
		break;
	case 2:
		pVName = "NotVirus.Win32.Notepad.xp";
		break;
	case 3:
		pVName = "Win32.CIH.12";
		break;
	default:
		pVName = "�����ļ����Զ����ļ�";
	}

	return pVName;
}