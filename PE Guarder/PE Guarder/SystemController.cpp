#include "StdAfx.h"
#include "SystemController.h"

CSystemController::CSystemController(void)
{
}

CSystemController::~CSystemController(void)
{
}


// ����ϵͳ��������װ���������͵�ϵͳ
//
void CSystemController::RebootSystem()
{
	// �жϵ�ǰʹ�õĲ���ϵͳ
	DWORD dwVersion = GetVersion();

	if (dwVersion < 0x80000000)  // Windows NT/2000/XP
	{ 
		if(!RebootNTx86())
		{
			::MessageBox(NULL, "�޷���������Ȩ�ޣ�" ,"��ʾ" ,MB_OK);
			return;
		}
	}
	else  // Windows 9x/ME
	{ 
		ExitWindowsEx(EWX_REBOOT, 0);  
	}
}


// ר�����NTϵͳ����������
//
BOOL CSystemController::RebootNTx86()
{
	HANDLE hToken = 0;  // ���ƾ��
	TOKEN_PRIVILEGES tp;  // ����Ȩ��

	// �õ����̵����ƾ��
	if (!::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		::MessageBox(NULL, "�޷���������Ȩ�ޣ�" ,"��ʾ" ,MB_OK);
		return FALSE;
	}
	else
	{
		// ��ѯ���̵�Ȩ��
		if (!::LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid))
		{
			::MessageBox(NULL, "�޷���������Ȩ�ޣ�" ,"��ʾ" ,MB_OK);
			return FALSE;
		}
		else
		{
			// ������������Ȩ
			tp.PrivilegeCount = 1;
			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

			// ֪ͨWindows NT�޸ı����̵�Ȩ��      
			if(!::AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
			{
				::MessageBox(NULL, "�޷���������Ȩ�ޣ�" ,"��ʾ" ,MB_OK);
				return FALSE;
			}
			else
			{
				// ����ϵͳ
				ExitWindowsEx(EWX_REBOOT, 0);
			}
		}
		CloseHandle(hToken);
		return TRUE;
	}
}


// ע������ú���
//
BOOL CSystemController::SetReg(LPCSTR lpSubKey)
{
	char path[MAX_PATH]={0};  // �����ļ�·��
	GetModuleFileName(NULL,path,MAX_PATH);  // ���ļ�·�����浽path������
	strcat_s(path," %1");  // ע������в�������ʾ����Ĳ�������

	HKEY hKey;  // ע������
	// ��ע���ָ�������´���һ������
	RegCreateKey(HKEY_CLASSES_ROOT, lpSubKey, &hKey);
	// ����ע���ָ�����ֵ
	LONG res = RegSetValueEx(hKey, NULL, 0, REG_SZ, (CONST BYTE *)path, (DWORD)strlen(path));

	// ע����������
	if (res != ERROR_SUCCESS)
	{
		return 0;
	}

	return 1;
}


// �����ļ�����
//
BOOL CSystemController::FileAttributesOperation(CString filePath)
{
	// 1.����ļ�����
	DWORD attr = ::GetFileAttributes(filePath);
	
	// 2.�����ļ�����
	if(attr != INVALID_FILE_ATTRIBUTES)  // �ļ����Ի�óɹ�
	{
		// �ļ�������ֻ��
		if(attr & FILE_ATTRIBUTE_READONLY)  
		{
			// �����ļ�����Ϊ��ͨ
			if(!::SetFileAttributes(filePath,FILE_ATTRIBUTE_NORMAL))  
			{
				return FALSE;
			}
		}
	}
	else  // ����ļ�����ʧ��
	{
		return FALSE;
	}

	return TRUE;
}