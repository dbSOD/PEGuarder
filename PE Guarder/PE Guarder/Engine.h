#pragma once
#include "VirusDB.h"
#include "Disposer.h"

// ɨ���¼�ṹ
typedef struct tagScanRecord
{
	DWORD dwVirusID;  // ����ID 
	CScanObject*	pScanObject;  // ɨ�����ָ��
}SCAN_RECORD, *PSCAN_RECORD;


// �����࣬ʵ��ɱ�������̵Ŀ��ơ���������ɱ����CScanObject��
// ���ò��������CVirusDB����⣬���������¼������
class CEngine
{
public:
	CEngine(void);  // ���캯��
	~CEngine(void);  // ��������

	BOOL Load(IN CVirusDB* pVDB);  // ����ָ��������
	void Release();  // �ͷ�ɨ���¼
	SCAN_RECORD GetScanRecord();  // ���ɨ���¼ 
	void Scan(IN LPCSTR pszPathName);  // ɨ��
	BOOL Dispose(IN LPCSTR pszPathName);  // ������

protected:
	CVirusDB *m_pVDB;  // ָ�򲡶����ָ��  
	SCAN_RECORD m_ScanRecord;  // һ��ɨ���¼
	CDisposer m_disposer;  // ������
};
