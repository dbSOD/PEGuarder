#pragma once

class CShellOperator
{
public:
	CShellOperator(void);
public:
	~CShellOperator(void);
public:
	// �ϲ�����PIDL��ͨ�����ڽ����ļ��е�ȫPIDL���������ļ�����
	// ���ж�������PIDL�ϲ����Ӷ��õ��ļ��������ļ��е�ȫPIDL 
	static LPITEMIDLIST ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);  
public:
	static UINT GetSize(LPCITEMIDLIST pidl);  // ���ĳ��PIDLʹ�õ��ֽ���
public:
	static LPITEMIDLIST CreatePidl(UINT cbSize);  // ����һ���µ�PIDL
public:
	static LPITEMIDLIST CopyItemID(LPMALLOC lpMalloc, LPCITEMIDLIST lpi);  // ��ȿ���һ��PIDL
};
