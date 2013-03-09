#include "StdAfx.h"
#include "ParsePE.h"

// ���캯��
//
CParsePE::CParsePE(void)
{
	m_PE.bPEFile = FALSE;
	m_PE.pDosHeader = NULL;
	m_PE.pNtHeaders = NULL;
	m_PE.pFileHeader = NULL;
	m_PE.pOptionalHeader = NULL;
	m_PE.pEntryPoint = NULL;
	m_PE.nSectionCount = 0;
	m_PE.nImportCount = 0;
}


// ��������
//
CParsePE::~CParsePE(void)
{
	m_PE.bPEFile = FALSE;
	m_PE.pDosHeader = NULL;
	m_PE.pNtHeaders = NULL;
	m_PE.pFileHeader = NULL;
	m_PE.pOptionalHeader = NULL;
	m_PE.pEntryPoint = NULL;
	m_PE.nSectionCount = 0;
	m_PE.nImportCount = 0;
}


// ��һ���ڴ���ִ�ж����PE�ṹ���з���
//
BOOL CParsePE::BasicParse(CMemFileObject* pScanObj)
{
	// �ж��ڴ��ļ��Ƿ��Ѵ�
	if(pScanObj->IsOpened() == FALSE)
	{
		return FALSE;
	}

	DWORD dwObjSize = pScanObj->GetObjectSize();  // ɨ������С

	// �ų�����
	if(dwObjSize < sizeof(PIMAGE_DOS_HEADER))	
	{
		m_PE.bPEFile = FALSE;
		return FALSE;
	}

	m_PE.pDosHeader	= (PIMAGE_DOS_HEADER)pScanObj->GetBuffer();  // �����ڴ�ָ��

	// ���"MZ"��־
	if(m_PE.pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		m_PE.bPEFile = FALSE;
		return FALSE;  // ����PE�ļ�
	}

	// �ų�����(dosx.exe)
	if((DWORD)m_PE.pDosHeader->e_lfanew > dwObjSize)
	{
		m_PE.bPEFile = FALSE;
		return FALSE;
	}

	// ��ַ+ƫ����=NTͷλ��
	m_PE.pNtHeaders	= (PIMAGE_NT_HEADERS)
		(pScanObj->GetBuffer() + m_PE.pDosHeader->e_lfanew);

	// ���"PE"��־
	if(m_PE.pNtHeaders->Signature != IMAGE_NT_SIGNATURE)
	{
		m_PE.bPEFile = FALSE;
		return FALSE;  // ����PE�ļ�
	}
	else
	{
		m_PE.bPEFile = TRUE;  // ��PE�ļ�
	}

	m_PE.pFileHeader = &(m_PE.pNtHeaders->FileHeader);  // �ļ�ͷָ��ȡֵ
	m_PE.pOptionalHeader = &(m_PE.pNtHeaders->OptionalHeader);  // ��ѡͷָ��ȡֵ

	// �õ�ָ�������ڵ��ָ��
	m_PE.pEntryPoint = pScanObj->GetBuffer() +  // �ڴ��ļ�ӳ���ַ(��ַ)
		m_PE.pOptionalHeader->AddressOfEntryPoint;  // �������RVA��ַ
	// �ų�����
	if(m_PE.pEntryPoint > (dwObjSize + pScanObj->GetBuffer()))
	{
		return FALSE;
	}

	// �õ�����е�һ���ָ��
	PIMAGE_SECTION_HEADER	pSectionHeader = (PIMAGE_SECTION_HEADER)((LPBYTE)m_PE.pNtHeaders + sizeof(IMAGE_NT_HEADERS));

	m_PE.nSectionCount = m_PE.pFileHeader->NumberOfSections;  // �õ�����
	// ����ָ������
	for(int i=0; i<m_PE.nSectionCount; i++)
	{
		m_PE.aSectionHeaders[i] = pSectionHeader;
		pSectionHeader++;
	}

	// �ж��Ƿ��е����
	if(m_PE.pOptionalHeader->DataDirectory[1].VirtualAddress == 0)
	{
		m_PE.nImportCount = 0;  // �������
	}
	else
	{
		// �õ���һ�������
		PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(pScanObj->GetBuffer() +  // �ڴ��ļ�ӳ���ַ(��ַ) 
			Rva2Offset(m_PE.pOptionalHeader->DataDirectory[1].VirtualAddress));  // �����rvaתoffset

		int j =0;
		// ��䵼���ָ������
		for(j=0; pImportDescriptor->Characteristics!=0; j++,pImportDescriptor++)
		{
			m_PE.aImportDescriptors[j] = pImportDescriptor;
		}
		m_PE.nImportCount = j;  // �������
	}

	return TRUE;
}


// ��PE�ļ���������ʽɨ��
//
BOOL CParsePE::AdvancedParse()
{
	// �ӽṹ�͵���������Ƕȷ���PE�ļ�
	if(m_PE.nImportCount != 0 && StructureParse() == TRUE)
	{
		if(ImportTableParse() == TRUE)
		{
			return TRUE;  // �����϶�Ϊδ֪����
		}
		else
		{
			return FALSE;  // �����϶�Ϊ��δ֪����
		}
	}
	else
	{
		return FALSE;  // �����϶�Ϊ��δ֪����
	}
}


// ��PE�ļ��ṹ���з������ж��쳣
//
BOOL CParsePE::StructureParse()
{
	FLOAT unVirus = 0;  // δ֪�������ۼ�ֵ
	FLOAT criteriaValue = 90;  // �ӽṹ�쳣�ж��Ƿ�δ֪�����Ľ���
	FLOAT addOfEryPotValue = 40;  // AddressOfEntryPointȨֵ
	FLOAT checkSumValue = 20;  // CheckSumȨֵ
	FLOAT sectionValue = 40;  // SizeOfRawData��PointerToRawDataȨֵ

	/*------------- Optional Header --------------*/

	// AddressOfEntryPoint
	if(m_PE.pOptionalHeader->AddressOfEntryPoint < m_PE.aSectionHeaders[0]->VirtualAddress)
	{
		unVirus += addOfEryPotValue;
	}

	// CheckSum
	if(m_PE.pOptionalHeader->CheckSum == 0)
	{
		unVirus += checkSumValue;
	}

	/*------------- Section Table ----------------*/

	// �������
	for(int i=0; i<m_PE.nSectionCount; i++)
	{
		// SizeOfRawData��PointerToRawData
		if(m_PE.aSectionHeaders[i]->SizeOfRawData == 0 && m_PE.aSectionHeaders[i]->PointerToRawData == 0)
		{
			unVirus += sectionValue/m_PE.nSectionCount;
		}
	}

	// δ֪�������ۼ�ֵ������������Ϊ�ṹ�쳣������ṹ����
	if(unVirus >= criteriaValue)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


// ���������з���(�鿴����õ�API)
//
BOOL CParsePE::ImportTableParse()
{
	PIMAGE_THUNK_DATA pThunkData;
	LPBYTE pMapping = (LPBYTE)m_PE.pDosHeader;  // ӳ���ַ
	CString dllName;  // dll��
	CString funName;  // dll�еĺ�����
	list<CString> listFunName;  // ���dll�к��������б�

	// ��������������õ�����dll��
	for(int i=0; i<m_PE.nImportCount; i++)
	{
		dllName = pMapping + Rva2Offset(m_PE.aImportDescriptors[i]->Name);  // dll��

		// ��OriginalFirstThunk��ֵΪ0��ϵͳ����FirstThunk��ֵ�ҵ�ָ�������ĵ�ַ��
		if(m_PE.aImportDescriptors[i]->OriginalFirstThunk == 0)
		{
			pThunkData = (PIMAGE_THUNK_DATA)(pMapping + Rva2Offset(m_PE.aImportDescriptors[i]->FirstThunk));
		}
		else
		{
			pThunkData = (PIMAGE_THUNK_DATA)(pMapping + Rva2Offset(m_PE.aImportDescriptors[i]->OriginalFirstThunk));
		}
		
		// ����IMAGE_THUNK_DATA���飬�õ���dll�еĺ�����
		while(pThunkData->u1.Ordinal != 0)
		{
			// ���pThunkData->u1.Ordinal����߶���λΪ1����ô�����������������
			if(pThunkData->u1.Ordinal & IMAGE_ORDINAL_FLAG32)
			{
				funName.Format("%x",pThunkData->u1.Ordinal & 0x0FFFF);
				listFunName.push_back(funName);
			}
			// ���Ԫ��ֵ����߶���λΪ0���Ϳɽ���ֵ��ΪRVAת��IMAGE_IMPORT_BY_NAME�ṹ
			else
			{
				funName = pMapping + Rva2Offset(pThunkData->u1.Ordinal)+2;  // ��2����Ϊ��Hint
				listFunName.push_back(funName);
			}

			pThunkData++;
		}
	}

	BOOL bFindFirstFile = FALSE;  // �ж�FindFirstFile(A)�����Ƿ�ʹ��
	BOOL bFindNextFile = FALSE;  // �ж�FindNextFile(A)�����Ƿ�ʹ��
	list<CString>::iterator iter = listFunName.begin();  // �б�����������ָ���б�ͷ
	// �����б�����
	while(iter != listFunName.end())
	{
		// �ж�FindFirstFile(A)�����Ƿ�ʹ��
		if(*iter == "FindFirstFile" || *iter == "FindFirstFileA")
		{
			bFindFirstFile = TRUE;
			if(bFindNextFile == TRUE)
			{
				break;  // ����whileѭ��
			}
		}

		// �ж�FindNextFile(A)�����Ƿ�ʹ��
		if(*iter == "FindNextFile" || *iter == "FindNextFileA")
		{
			bFindNextFile = TRUE;
			if(bFindFirstFile == TRUE)
			{
				break;  // ����whileѭ��
			}
		}

		iter++;  // ������ָ����һ���б�Ԫ��
	}
	listFunName.clear();  // ����б�Ԫ��

	// ��FindFirstFile(A)������FindNextFile(A)������ʹ�ã���ӵ����Ƕ���Ϊ��δ֪������������
	if(bFindFirstFile == TRUE && bFindNextFile == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


// ������������ַ(rva)����ƫ�Ƶ�ַ(offset)
//
DWORD CParsePE::Rva2Offset(DWORD rva)
{
	// Ĭ�ϵ�һ���ַ��ͣ�rva�������κο���
	if(rva<m_PE.aSectionHeaders[0]->VirtualAddress && rva>=0)
	{
		return rva;
	}

	// rva����ĳһ����
	for(int i=0; i<m_PE.nSectionCount; i++)
	{
		if(m_PE.aSectionHeaders[i]->VirtualAddress <= rva &&
			rva < m_PE.aSectionHeaders[i]->VirtualAddress + m_PE.aSectionHeaders[i]->SizeOfRawData)
		{
			return m_PE.aSectionHeaders[i]->PointerToRawData + rva - m_PE.aSectionHeaders[i]->VirtualAddress;
		}
	}

	return 0;
}


// �õ�PE��Ϣ
//
FSPE CParsePE::GetFSPE()
{
	return m_PE;
}