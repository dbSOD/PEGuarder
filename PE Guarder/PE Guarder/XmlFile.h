#pragma once

#include "VirusDB.h"
#import <msxml3.dll>
using namespace MSXML2;

// ��Ų����������xml�ļ���
class CXmlFile
{
public:
	CXmlFile(void);
	~CXmlFile(void);

	CString GetXmlFileName();  // ���xml�ļ�·��
	void SetXmlFileName(CString xmlFileName);  // ����xml�ļ�·��
	CString GetValue(CString nodeName);  // �õ�ָ���������ֵ
	BOOL SetValue(CString nodeName, CString nodeValue);  // �޸�ָ���ڵ�ֵ
	BOOL AppendForPE(CString sign1, CString sign2, CString sign3, CString sign4);  // ��ӽ��ͽ��ֵ
	BOOL LoadForPE(list<PVRECORD>* pList);  // ���ز�����
	PVSIGNATURE StrToSign(CString str);  // �ַ���ת������

private:
	CString m_XmlFileName;  // xml�ļ�·��
};
