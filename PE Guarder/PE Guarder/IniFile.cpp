#include "StdAfx.h"
#include "IniFile.h"

CIniFile::CIniFile(void)
{
}

CIniFile::~CIniFile(void)
{
}


// ���ini�ļ�·��
//
CString CIniFile::GetIniFileName()
{
	return m_IniFileName;
}


// ����ini�ļ�·��
//
void CIniFile::SetIniFileName(CString iniFileName)
{
	m_IniFileName = iniFileName;
}


// ��ȡini�ļ����ֵ
//
void CIniFile::ReadIni(CString strSection, CString strItem, CString& strValue)
{
	GetPrivateProfileString(strSection, strItem, NULL, strValue.GetBuffer(MAX_PATH), MAX_PATH, m_IniFileName); 
}


// д��ini�ļ����ֵ
//
void CIniFile::WriteIni(CString strSection, CString strItem, CString strValue)
{
	WritePrivateProfileString(strSection, strItem, strValue, m_IniFileName); 
}