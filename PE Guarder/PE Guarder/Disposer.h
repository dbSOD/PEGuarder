#pragma once

// ������
class CDisposer
{
public:
	CDisposer(void);
	~CDisposer(void);

	BOOL Delete(IN LPCSTR pszPathName);  // ɾ��
	BOOL Isolate(IN LPCSTR pszPathName);  // ����  
	BOOL Ignore(IN LPCSTR pszPathName);  // ����
};
