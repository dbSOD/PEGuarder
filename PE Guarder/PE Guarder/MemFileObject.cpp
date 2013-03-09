#include "StdAfx.h"
#include "MemFileObject.h"


// ���캯��
//
CMemFileObject::CMemFileObject(void)
{
	m_eObjType = BO_MEM_FILE;  // ɨ���������Ϊ�ڴ��ļ�
	m_hMapFile	= NULL;  // ��ʼ���ڴ��ļ����
	m_pFile = NULL;  // �ڴ�ָ���ʼ��
}


// ���ƹ��캯��
//
CMemFileObject::CMemFileObject(CMemFileObject& cMemFileObj)
{
	m_eObjType = BO_MEM_FILE;  // ɨ���������Ϊ�ڴ��ļ�
	m_hFile = INVALID_HANDLE_VALUE;  // ��ʼ���ļ����
	m_dwObjSize = cMemFileObj.m_dwObjSize;  // �����ļ���С
	m_strObjName = cMemFileObj.m_strObjName;  // �����ļ�����
	m_hMapFile	= NULL;  // ��ʼ���ڴ��ļ����
	m_pFile = NULL;  // �ڴ�ָ���ʼ��
}


// ��������
//
CMemFileObject::~CMemFileObject(void)
{
	if(m_pFile != NULL)
	{
		Close();  // �ر��ڴ��ļ�
	}
}


// �����ڴ�ָ��
//
LPBYTE CMemFileObject::GetBuffer()
{
	return m_pFile;
}


// ���ڴ��ļ�
//
BOOL CMemFileObject::Open()
{
	// ����CFileObject��Open����
	if(CFileObject::Open() == FALSE)
	{
		return FALSE;
	}

	// ����һ���µ��ļ�ӳ�����(���ļ�ӳ�䵽һ�����̵ĺ���)
	m_hMapFile = ::CreateFileMapping(m_hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if(m_hMapFile == NULL)
	{
		Close();
		return FALSE;
	}

	// ������ͼ�����ļ�ӳ�䵽��ǰ�����ڴ������ַ�ռ䣬����ֵ���������ַ
	m_pFile = (LPBYTE)(::MapViewOfFile(m_hMapFile, FILE_MAP_READ, 0, 0, 0));
	if(m_pFile == NULL)
	{
		Close();
		return FALSE;
	}

	return TRUE;
}


// �ر��ڴ��ļ�
//
BOOL CMemFileObject::Close()
{
	// ȡ���ļ�ӳ��
	if(m_pFile != NULL)
	{
		::UnmapViewOfFile(m_pFile);
		m_pFile = NULL;
	}

	// �ر�ӳ�����
	if(m_hMapFile != NULL)
	{
		::CloseHandle(m_hMapFile);
		m_hMapFile = NULL;
	}

	// ����CFileObject��Close����
	return CFileObject::Close();
}


// �ж��ڴ��ļ��Ƿ��Ѵ�
//
BOOL CMemFileObject::IsOpened()
{
	if(m_pFile != NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


// �Ƚ��ڴ��ļ���������
//
BOOL CMemFileObject::Compare(IN INT nOffset, IN INT nSize, IN LPBYTE pSignature, IN BAV_SIGN_LOGIC_OPERATION eLogicOp)
{
	return Compare(m_pFile+nOffset, nSize, pSignature, eLogicOp);
}


// �Ƚ��ڴ��ļ���������
//
BOOL CMemFileObject::Compare(IN LPBYTE pData, IN INT nSize, IN LPBYTE pSignature, IN BAV_SIGN_LOGIC_OPERATION eLogicOp)
{
	// �ж��ڴ��ļ��Ƿ��Ѵ�
	if(IsOpened() == FALSE)
	{
		return FALSE;
	}

	// ������λ�ó����ļ���Χ
	if(pData < m_pFile || pData > (m_pFile + m_dwObjSize))
	{
		return FALSE;
	}

	// �Ƚ��ڴ�����pData��pSignature��ǰnSize���ֽ�
	int nRes = memcmp(pData, pSignature, nSize);

	switch(eLogicOp)
	{
	case BL_EQUAL:
		return nRes == 0;
	case BL_NOT_EQUAL:
		return nRes != 0;
	default:
		return FALSE;
	}
}