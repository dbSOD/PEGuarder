#pragma once

class CSystemController
{
public:
	CSystemController(void);
public:
	~CSystemController(void);
public:
	static void RebootSystem();  // ����ϵͳ��������װ���������͵�ϵͳ
public:
	static BOOL RebootNTx86();  // ר�����NTϵͳ����������
public:
	static BOOL SetReg(LPCSTR lpSubKey);  // ע������ú���
public:
	static BOOL FileAttributesOperation(CString filePath);  // �����ļ�����
};
