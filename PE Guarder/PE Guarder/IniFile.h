#pragma once

// ��ʼ���ļ��࣬��ʼ���ļ�(set.ini)�洢��Ƥ����Ϣ��
class CIniFile
{
public:
	CIniFile(void);
	~CIniFile(void);

	CString GetIniFileName();  // ���ini�ļ�·��
	void SetIniFileName(CString iniFileName);  // ����ini�ļ�·��
	void ReadIni(CString strSection, CString strItem, CString& strValue);  // ��ȡini�ļ����ֵ
	void WriteIni(CString strSection, CString strItem, CString strValue);  // д��ini�ļ����ֵ
	
private:
	CString m_IniFileName;  // ini�ļ�·��
};
