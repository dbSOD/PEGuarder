#include "StdAfx.h"
#include "Disposer.h"

CDisposer::CDisposer(void)
{
}

CDisposer::~CDisposer(void)
{
}


// ɾ��
//
BOOL CDisposer::Delete(LPCSTR pszPathName)
{
	if(::DeleteFile(pszPathName) == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


// ����
//
BOOL CDisposer::Isolate(LPCSTR pszPathName)
{
	return FALSE;
}


// ����
//
BOOL CDisposer::Ignore(LPCSTR pszPathName)
{
	return FALSE;
}