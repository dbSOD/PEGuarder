#pragma once
#include "FileObject.h"

// ������CScanObject����ʵ��CScanObject�ж�����麯���������ڴ��ļ��������ز�����
class CMemFileObject : public CFileObject
{
public:
	CMemFileObject(void);  // ���캯��
	CMemFileObject(CMemFileObject& cMemFileObj);  // ���ƹ��캯��
	~CMemFileObject(void);  // ��������

	LPBYTE GetBuffer();  // �����ڴ�ָ��
	BOOL Open();  // ���ڴ��ļ�
	BOOL Close();  // �ر��ڴ��ļ�
	BOOL IsOpened();  // �ж��ڴ��ļ��Ƿ��Ѵ�
	// �Ƚ��ڴ��ļ���������
	BOOL Compare(IN INT nOffset, IN INT nSize, IN LPBYTE pSignature, IN BAV_SIGN_LOGIC_OPERATION eLogicOp = BL_EQUAL);
	// �Ƚ��ڴ��ļ���������
	BOOL Compare(IN LPBYTE pData, IN INT nSize, IN LPBYTE pSignature, IN BAV_SIGN_LOGIC_OPERATION eLogicOp = BL_EQUAL);
	
protected:
	HANDLE	m_hMapFile;  // �ڴ��ļ����
	LPBYTE	m_pFile;  // �ڴ�ָ��(ָ��ӳ��)
};
