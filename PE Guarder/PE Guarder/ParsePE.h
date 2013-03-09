#pragma once
#include "MemFileObject.h"

#define MAX_SECTIONS 64  // ������
#define MAX_IMPORTS 64  // ��������


// ���ڴ洢PE�ṹ����Ҫ��Ϣ
typedef struct tagFSPE
{
	BOOL bPEFile;  // �ж��Ƿ���ЧPE�ļ�
	PIMAGE_DOS_HEADER pDosHeader;  // ָ��DOSͷ��ָ��
	PIMAGE_NT_HEADERS pNtHeaders;  // ָ��NTͷ��ָ��
	PIMAGE_FILE_HEADER pFileHeader;  // ָ���ļ�ͷ��ָ��
	PIMAGE_OPTIONAL_HEADER pOptionalHeader;  // ָ���ѡͷ��ָ��
	LPBYTE pEntryPoint;  // ָ�������ڵ��ָ��  
	INT nSectionCount;  // ����
	PIMAGE_SECTION_HEADER aSectionHeaders[MAX_SECTIONS];  // ��ָ������
	INT nImportCount;  // �������
	PIMAGE_IMPORT_DESCRIPTOR aImportDescriptors[MAX_IMPORTS];  // �����ָ������
}FSPE, *PFSPE;


// ���ݴ����CMemFileObject ���������ʵ�ֶ�PE�ļ���ȷ���Լ�PE ��ʽ�ķ���
class CParsePE
{
public:
	CParsePE(void);  // ���캯��
	~CParsePE(void);  // ��������

	BOOL BasicParse(IN CMemFileObject* pScanObj);  // ��һ���ڴ���ִ�ж����PE�ṹ���з���
	BOOL AdvancedParse();  // ��PE�ļ���������ʽɨ��
	BOOL StructureParse();  // ��PE�ļ��ṹ���з������ж��쳣
	BOOL ImportTableParse();  // ���������з���(�鿴����õ�API)
	DWORD Rva2Offset(DWORD rva);  // ������������ַ(rva)����ƫ�Ƶ�ַ(offset)
	FSPE GetFSPE();  // �õ�PE��Ϣ

protected:
	FSPE m_PE;  // PE��Ϣ�ṹ
};
