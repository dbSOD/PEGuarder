#pragma once
#include "ScanObject.h"

// ����������
enum BAV_SIGN_TYPE {BS_PHY_FILE/*���ļ�ƫ��*/, BS_STRUCT_OFFSET/*��ĳ���ṹ�Ĳο���ƫ��*/};
/* BAV_SIGN_TYPE.dwType == BS_PHY_FILE
    dwSubType:0
	BAV_SIGN_TYPE.dwType == BS_STRUCT_OFFSET
    dwSubType:                                               */
#define BS_SUB_NT_HEADERS 1  // ��NTͷΪ�ο���
#define BS_SUB_ENTRY_POINT 2  // ����ڵ�Ϊ�ο���   


// ���ڴ�ŵ�һ�����룬�ܶ�����������һ��������¼��Ҳ����һ��VRECORD
typedef struct tagVSIGNATURE {
	BAV_SIGN_TYPE eType;  // �������������������
	DWORD dwSubType;  // ����ǰһ������ݶ�����������  
	INT nOffset;  // �洢���������ƫ����
	INT nSize;  // �洢������ĳ���
	BAV_SIGN_LOGIC_OPERATION eLogicOp;  // �߼�����
	BYTE	Signature[MAX_SIGNATURE_LEN];  // ��������봮
} VSIGNATURE, *PVSIGNATURE;


// ���ڴ�Ų�������ÿ��������¼������
typedef struct tagVRECORD {
	DWORD dwVirusID;  // ָ��������ID���
	DWORD dwSignCount;  // ���������Ķ�����Ҳ���Ƕ��ڸò���ȡ�˶��ٶ�������
	PVSIGNATURE pVSign[8];  // ���ÿ�������������
} VRECORD, *PVRECORD;


// ʵ�ֲ�����ļ��غ�ж�ز�������Ҫ��¶��Search()������
// ���ڽ�ɨ������ڱ��������м�⡣����ɨ��������Compare()��������������ƥ�䡣
class CVirusDB
{
public:
	CVirusDB(void);
	~CVirusDB(void);

	BOOL Load();  // ���ز����� 
	BOOL Unload();  // ж�ز�����
	// ��ɨ������ڱ��������м�⣬���ز���ID��0
	DWORD Search(IN CScanObject* pScanObj);

public:
	list<PVRECORD> m_listVRecords;  // �б�������������Ŷ��������¼
};
