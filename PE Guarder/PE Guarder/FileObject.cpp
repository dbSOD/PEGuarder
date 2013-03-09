#include "StdAfx.h"
#include "FileObject.h"


// ���캯��
//
CFileObject::CFileObject(void)
{
	m_eObjType = BO_PHY_FILE;  // ɨ���������Ϊ�����ļ�
	m_hFile = INVALID_HANDLE_VALUE;  // ��ʼ���ļ����
	m_dwObjSize = 0;  // ��ʼ���ļ���С
}


// ���ƹ��캯��
//
CFileObject::CFileObject(CFileObject& cFileObj)
{
	m_eObjType = BO_PHY_FILE;  // ɨ���������Ϊ�����ļ�
	m_hFile = INVALID_HANDLE_VALUE;  // ��ʼ���ļ����
	m_dwObjSize = cFileObj.m_dwObjSize;  // �����ļ���С
	m_strObjName = cFileObj.m_strObjName;  // �����ļ�����
}


// ��������
//
CFileObject::~CFileObject(void)
{
	if(m_hFile != INVALID_HANDLE_VALUE)
	{
		Close();  // �ر�ɨ���ļ�
	}
}


// ���ɨ���ļ�����
//
BAV_OBJ_TYPE CFileObject::GetObjectType()
{
	return m_eObjType;
}


// ���ɨ���ļ�����
//
LPCSTR CFileObject::GetObjectName()
{
	return (LPCSTR)m_strObjName;
}


// ����ɨ���ļ�����
//
BOOL CFileObject::SetObjectName(CString* pstrName)
{
	if(pstrName == NULL)
	{
		return FALSE;
	}

	m_strObjName = *pstrName;  // ��ֵ�ļ���
	
	return TRUE;
}


// ���ɨ���ļ���С
//
DWORD CFileObject::GetObjectSize()
{
	return m_dwObjSize;
}


// ��ɨ���ļ�
//
BOOL CFileObject::Open()
{
	// ���ļ��������ļ����
	m_hFile = ::CreateFile(m_strObjName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(m_hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	// ����ļ���С����λΪbytes
	m_dwObjSize = GetFileSize(m_hFile, NULL);														
	
	return TRUE; 
}


// �ر�ɨ���ļ�
//
BOOL CFileObject::Close()
{
	// �ر��ļ����
	if(::CloseHandle(m_hFile) == TRUE)
	{
		m_hFile = INVALID_HANDLE_VALUE;  
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


// �ж�ɨ���ļ��Ƿ��Ѵ�
//
BOOL CFileObject::IsOpened()
{
	if(m_hFile != INVALID_HANDLE_VALUE)
	{
		return TRUE;  // ��ʾ�Ѵ�
	}
	else
	{
		return FALSE;  // ��ʾδ��
	}
}


// �Ƚ�ɨ���ļ���������
//
BOOL CFileObject::Compare(IN INT nOffset, IN INT nSize, IN LPBYTE pSignature, IN BAV_SIGN_LOGIC_OPERATION eLogicOp)
{
	// �ж�ɨ���ļ��Ƿ��Ѵ�
	if(IsOpened() == FALSE)
	{
		return FALSE;
	}

	// ������λ�ó����ļ���С
	if((nOffset+nSize) > (INT)m_dwObjSize)
	{
		return FALSE;
	}

	// �����ļ�ָ��λ��
	if(::SetFilePointer(m_hFile, nOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		return FALSE;
	}

	BYTE buf[MAX_SIGNATURE_LEN];
	DWORD dwReadBytes;

	// ���ļ�ָ����ָλ�ÿ�ʼ��ȡ�ļ�
	if(::ReadFile(m_hFile, buf, nSize, &dwReadBytes, NULL) && nSize == dwReadBytes)
	{
		// �Ƚ��ڴ�����buf��pSignature��ǰnSize���ֽ�
		int nRes = memcmp(buf, pSignature, nSize);  
	
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
	else
	{
		return FALSE;
	}
}


// �Ƚ�ɨ���ļ���������
//
BOOL CFileObject::Compare(IN LPBYTE pData, IN INT nSize, IN LPBYTE pSignature, IN BAV_SIGN_LOGIC_OPERATION eLogicOp)
{
	// CFileObject��֧�ִ˷���
	return FALSE;
}