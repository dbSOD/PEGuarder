#include "StdAfx.h"
#include "Engine.h"
#include "MemFileObject.h"


// ���캯��
//
CEngine::CEngine(void)
{
	m_pVDB = NULL;  // ָ�򲡶����ָ�� 

	// ɨ���¼��ʼ��
	m_ScanRecord.dwVirusID = 0;
	m_ScanRecord.pScanObject= NULL;
}


// ��������
//
CEngine::~CEngine(void)
{
	m_pVDB = NULL;  // ָ�򲡶����ָ��
	Release();  // �ͷ�ɨ���¼
}


// ����ָ��������
//
BOOL CEngine::Load(IN CVirusDB* pVDB)
{
	if(pVDB == NULL)
	{
		return FALSE;
	}
	m_pVDB = pVDB;  

	return TRUE;
}


// �ͷ�ɨ���¼
//
void CEngine::Release()
{
	m_ScanRecord.dwVirusID = 0;
	m_ScanRecord.pScanObject= NULL;
}


// ���ɨ���¼
//
SCAN_RECORD CEngine::GetScanRecord()
{
	return m_ScanRecord;
}


// ɨ��
//
void CEngine::Scan(LPCSTR pszPathName)
{
	Release();  // ���ǰ��ɨ���¼

	CMemFileObject memFileObj;  // �ڴ�ӳ���ļ�����
	memFileObj.m_strObjName = pszPathName;  // ɨ���ļ�����
	if(memFileObj.Open() == FALSE)
	{
		return;
	}

	// ��ɨ������ڱ��������м�⣬���ز���ID��0
	DWORD dwVID = m_pVDB->Search(&memFileObj);
	// ���ֲ���
	if(dwVID != 0)
	{
		CFileObject* pScanObj = new CFileObject(memFileObj);  // ���°�װɨ�����

		m_ScanRecord.dwVirusID = dwVID;  // ����ID
		m_ScanRecord.pScanObject = pScanObj;  // ɨ�����ָ��
	}

	memFileObj.Close();  // �رն���
}


// ������
//
BOOL CEngine::Dispose(LPCSTR pszPathName)
{
	// Ŀǰֻ��ɾ������
	if(m_disposer.Delete(pszPathName) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

