#pragma once

enum BAV_OBJ_TYPE {BO_PHY_FILE, BO_MEM_FILE};  // ɨ���������
enum BAV_SIGN_LOGIC_OPERATION {BL_EQUAL, BL_NOT_EQUAL};  // �߼���������

// ɨ�������࣬����ɨ�財��ʱ��Ҫ�õ��ĶԸ��ֲ����������������
// �������麯���������Ĺ�����Ҫ�����������Ķ����н���ʵ�֡�
class CScanObject
{
public:
	CScanObject(void);
	~CScanObject(void);

	BAV_OBJ_TYPE GetObjType();  // ���ɨ���������

	/*----- ���麯�����޺����� --------*/
	virtual BAV_OBJ_TYPE GetObjectType() = 0;  // ���ɨ���������
	virtual LPCSTR GetObjectName() = 0;  // ���ɨ���������
	virtual BOOL SetObjectName(CString* pstrName) = 0;  // ����ɨ���������
	virtual DWORD GetObjectSize() = 0;  // ���ɨ������С
	virtual BOOL Open() = 0;  // ��ɨ�����
	virtual BOOL Close() = 0;  // �ر�ɨ�����
	virtual BOOL IsOpened() = 0;  // �ж�ɨ������Ƿ��Ѵ�
	// �Ƚ�ɨ�������������
	virtual BOOL Compare(IN INT nOffset, IN INT nSize, IN LPBYTE pSignature, IN BAV_SIGN_LOGIC_OPERATION eLogicOp = BL_EQUAL) = 0;
	// �Ƚ�ɨ�������������
	virtual BOOL Compare(IN LPBYTE pData, IN INT nSize, IN LPBYTE pSignature, IN BAV_SIGN_LOGIC_OPERATION eLogicOp = BL_EQUAL) = 0;
	
protected:
	BAV_OBJ_TYPE m_eObjType;  // ɨ����� 
};
