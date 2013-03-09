#include "StdAfx.h"
#include "ShellOperator.h"

CShellOperator::CShellOperator(void)
{
}

CShellOperator::~CShellOperator(void)
{
}


// �ϲ�����PIDL��ͨ�����ڽ����ļ��е�ȫPIDL���������ļ����ļ��ж����
// ���PIDL�ϲ����Ӷ��õ��ļ��������ļ��е�ȫPIDL
//
LPITEMIDLIST CShellOperator::ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
	UINT cb1 = 0;
	if (pidl1 != NULL)
	{
		cb1 = GetSize(pidl1) - sizeof(pidl1->mkid.cb);  // pidl1��ռ�ֽ��������������벿��
	}

	UINT cb2 = GetSize(pidl2);  // pidl2��ռ�ֽ���

	LPITEMIDLIST pidlNew = CreatePidl(cb1 + cb2);  //����һ���µ�PIDL
	if (pidlNew != NULL)
	{
		if (pidl1 != NULL)
		{
			memcpy(pidlNew, pidl1, cb1);  // ��pidl1��ָ�ڴ�������cb1���ֽڵ�pidlNew��ָ�ڴ�����
		}

		// ��pidl2��ָ�ڴ�������cb2���ֽڵ�pidlNew+cb1��ָ�ڴ�����
		memcpy(((LPSTR)pidlNew) + cb1, pidl2, cb2);
	}

	return pidlNew;
}


// ���ĳ��PIDLʹ�õ��ֽ���
//
UINT CShellOperator::GetSize(LPCITEMIDLIST pidl)
{
	UINT cbTotal = 0;  // �������ֽ���

	if (pidl != NULL)
	{
		cbTotal += sizeof(pidl->mkid.cb);  // һ��unsigned short���ͱ����ĳ��ȣ����Ǳ���Ҫ�ӵ�

		while (pidl->mkid.cb > 0)
		{
			cbTotal += pidl->mkid.cb;  // ÿһ��item��ռ�ֽ���  

			// �õ�һ��PIDL��ָ����һ��item ID��ָ��
			LPSTR pb = (LPSTR)pidl;
			pb += pidl->mkid.cb;  // �ڴ������������
			pidl = (LPITEMIDLIST)pb;
		}
	}

	return cbTotal;
}


// ����һ���µ�PIDL
//
LPITEMIDLIST CShellOperator::CreatePidl(UINT cbSize)
{
	LPITEMIDLIST pidl = NULL;

	LPMALLOC pMalloc;
	SHGetMalloc(&pMalloc);  // ȡ��IMalloc�ӿ� 
	
	if(pMalloc != NULL)
	{
		pidl = (LPITEMIDLIST)pMalloc->Alloc(cbSize);  // �����ڴ�

		if (pidl != NULL)
		{
			memset(pidl, 0, cbSize);  // �ڴ�����
		}

		pMalloc->Release();  // �ͷ�IMalloc�ӿ�
	}

	return pidl;  
}


// ��ȿ���һ��PIDL
//
LPITEMIDLIST CShellOperator::CopyItemID(LPMALLOC pMalloc, LPCITEMIDLIST pidl)
{
	if(pMalloc == NULL || pidl == NULL)
	{
		return NULL;
	}

	LPITEMIDLIST pidlTemp = NULL;
	pidlTemp=(LPITEMIDLIST)pMalloc->Alloc(pidl->mkid.cb+sizeof(pidl->mkid.cb));  // �����ڴ�
	// ��pidl�ڴ�����ݸ��Ƶ�pidlTempλ��
	CopyMemory((PVOID)pidlTemp, (CONST VOID *)pidl, pidl->mkid.cb+sizeof(pidl->mkid.cb));

	return pidlTemp;
}