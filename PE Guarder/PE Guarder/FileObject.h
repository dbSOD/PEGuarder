#pragma once
#include "ScanObject.h"

// ������CScanObject����ʵ��CScanObject�ж�����麯�������������ļ�����ز�����
class CFileObject : public CScanObject
{
public:
	CFileObject(void);  // ���캯��
	CFileObject(CFileObject& cFileObj);  // ���ƹ��캯��
	~CFileObject(void);  // ��������

	BAV_OBJ_TYPE GetObjectType();  // ���ɨ���ļ�����
	LPCSTR GetObjectName();  // ���ɨ���ļ�����
	BOOL SetObjectName(CString* pstrName);  // ����ɨ���ļ�����
	DWORD GetObjectSize();  // ���ɨ���ļ���С
	BOOL Open();  // ��ɨ���ļ�
	BOOL Close();  // �ر�ɨ���ļ�
	BOOL IsOpened();  // �ж�ɨ���ļ��Ƿ��Ѵ�
	// �Ƚ�ɨ���ļ���������
	BOOL Compare(IN INT nOffset, IN INT nSize, IN LPBYTE pSignature, IN BAV_SIGN_LOGIC_OPERATION eLogicOp = BL_EQUAL);
	// �Ƚ�ɨ���ļ���������
	BOOL Compare(IN LPBYTE pData, IN INT nSize, IN LPBYTE pSignature, IN BAV_SIGN_LOGIC_OPERATION eLogicOp = BL_EQUAL);

public:
	CString m_strObjName;  // ɨ���ļ�����

protected:
	HANDLE	m_hFile;  // ɨ���ļ����
	DWORD	m_dwObjSize;  // ɨ���ļ���С
};
