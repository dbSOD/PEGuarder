#include "StdAfx.h"
#include "VirusDB.h"
#include "ParsePE.h"
#include "XmlFile.h"

CVirusDB::CVirusDB(void)
{

}

CVirusDB::~CVirusDB(void)
{
}


// ���ز�����
//
BOOL CVirusDB::Load()
{
	//PVRECORD pVRecord;  // ���ڴ�Ų�������ÿ��������¼������

	/////*------------------- eicar virus ------------------------*/

	//pVRecord = new VRECORD;  // �½�������¼
	//if(pVRecord == NULL)
	//{
	//	return FALSE;
	//}

	//pVRecord->dwVirusID = 1;  // ָ��������ID���
	//pVRecord->dwSignCount = 3;  // ���������Ķ�����Ҳ���Ƕ��ڸò���ȡ�˶��ٶ�������

	//VSIGNATURE aVSign1[3]=
	//{
	//	// ���ļ�ƫ�ƣ�������ʼ��ַ0����������32������32���ֽ��Ǿ�������ֵ
	//	{
	//		BS_PHY_FILE, 0, 0, 32, BL_EQUAL, 
	//		0x58, 0x35, 0x4F, 0x21, 0x50, 0x25, 0x40, 0x41, 0x50, 0x5B, 0x34, 0x5C, 0x50, 0x5A, 0x58, 0x35, 
	//		0x34, 0x28, 0x50, 0x5E, 0x29, 0x37, 0x43, 0x43, 0x29, 0x37, 0x7D, 0x24, 0x45, 0x49, 0x43, 0x41, 
	//	},
	//	// ���ļ�ƫ�ƣ�������ʼ��ַ32����������32������32���ֽ��Ǿ�������ֵ
	//	{
	//		BS_PHY_FILE, 0, 32, 32, BL_EQUAL,
	//		0x52, 0x2D, 0x53, 0x54, 0x41, 0x4E, 0x44, 0x41, 0x52, 0x44, 0x2D, 0x41, 0x4E, 0x54, 0x49, 0x56, 
	//		0x49, 0x52, 0x55, 0x53, 0x2D, 0x54, 0x45, 0x53, 0x54, 0x2D, 0x46, 0x49, 0x4C, 0x45, 0x21, 0x24, 
	//	},
	//	// ���ļ�ƫ�ƣ�������ʼ��ַ64����������4������4���ֽ��Ǿ�������ֵ
	//	{
	//		BS_PHY_FILE, 0, 64, 4, BL_EQUAL,
	//		0x48, 0x2B, 0x48, 0x2A, 
	//	},
	//};

	//// ���ÿ�������������
	//for(DWORD i=0; i<pVRecord->dwSignCount; i++)
	//{
	//	PVSIGNATURE	pSign = new VSIGNATURE;
	//	*pSign = aVSign1[i];
	//	pVRecord->pVSign[i] = pSign;
	//}

	//// ���б������м���˲�����¼
	//m_listVRecords.push_back(pVRecord);


	/////*--------------- notepad.exe as a fake virus -----------------------*/

	//pVRecord = new VRECORD;  // �½�������¼
	//if(pVRecord == NULL)
	//{
	//	return FALSE;
	//}

	//pVRecord->dwVirusID = 2;  // ָ��������ID���
	//pVRecord->dwSignCount = 4;  // ���������Ķ�����Ҳ���Ƕ��ڸò���ȡ�˶��ٶ�������

	//VSIGNATURE aVSign2[4]=
	//{
	//	// ���ļ�ƫ�ƣ�������ʼ��ַ256����������32������32���ֽ��Ǿ�������ֵ
	//	{
	//		BS_PHY_FILE, 0, 256, 32, BL_EQUAL,
	//		0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9D, 0x73, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	//		0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 
	//	},
	//	// ���ļ�ƫ�ƣ�������ʼ��ַ1952����������32������32���ֽ��Ǿ�������ֵ
	//	{
	//		BS_PHY_FILE, 0, 1952, 32, BL_EQUAL,
	//		0x4E, 0x00, 0x70, 0x00, 0x45, 0x00, 0x6E, 0x00, 0x63, 0x00, 0x6F, 0x00, 0x64, 0x00, 0x69, 0x00, 
	//		0x6E, 0x00, 0x67, 0x00, 0x44, 0x00, 0x69, 0x00, 0x61, 0x00, 0x6C, 0x00, 0x6F, 0x00, 0x67, 0x00, 
	//	},
	//	// ���ļ�ƫ�ƣ�������ʼ��ַ31776����������32������32���ֽ��Ǿ�������ֵ
	//	{
	//		BS_PHY_FILE, 0, 31776, 32, BL_EQUAL,
	//		0x4E, 0x00, 0x6F, 0x00, 0x74, 0x00, 0x65, 0x00, 0x70, 0x00, 0x61, 0x00, 0x64, 0x00, 0x00, 0x00, 
	//		0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
	//	},
	//	// ���ļ�ƫ�ƣ�������ʼ��ַ65168����������32������32���ֽ��Ǿ�������ֵ
	//	{
	//		BS_PHY_FILE, 0, 65184, 32, BL_EQUAL,
	//		0x6E, 0x00, 0x74, 0x00, 0x65, 0x00, 0x72, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x6C, 0x00, 0x4E, 0x00, 
	//		0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x00, 0x00, 0x4E, 0x00, 0x6F, 0x00, 0x74, 0x00, 0x65, 0x00, 
	//	}
	//};

	//// ���ÿ�������������
	//for(DWORD i=0; i<pVRecord->dwSignCount; i++)
	//{
	//	PVSIGNATURE	pSign = new VSIGNATURE;
	//	*pSign = aVSign2[i];
	//	pVRecord->pVSign[i] = pSign;
	//}

	//// ���б������м���˲�����¼
	//m_listVRecords.push_back(pVRecord);


	/////*---------------------- CIH virus -----------------------*/

	//pVRecord = new VRECORD;  // �½�������¼
	//if(pVRecord == NULL)
	//{
	//	return FALSE;
	//}

	//pVRecord->dwVirusID = 3;  // ָ��������ID���
	//pVRecord->dwSignCount = 3;  // ���������Ķ�����Ҳ���Ƕ��ڸò���ȡ�˶��ٶ�������

	//VSIGNATURE aVSign3[3]=
	//{
	//	// ��BS_SUB_NT_HEADERS�ο���ƫ�ƣ�������ʼ��ַ-1����������1������1���ֽ��Ǿ�������ֵ
	//	{
	//		BS_STRUCT_OFFSET, 1, -1, 1, BL_NOT_EQUAL, 
	//		0x00,
	//	},
	//	// ��BS_SUB_ENTRY_POINT�ο���ƫ�ƣ�������ʼ��ַ0����������32������32���ֽ��Ǿ�������ֵ
	//	{
	//		BS_STRUCT_OFFSET, 2, 0, 32, BL_EQUAL, 
	//		0x55, 0x8D, 0x44, 0x24, 0xF8, 0x33, 0xDB, 0x64, 0x87, 0x03, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5B, 
	//		0x8D, 0x4B, 0x42, 0x51, 0x50, 0x50, 0x0F, 0x01, 0x4C, 0x24, 0xFE, 0x5B, 0x83, 0xC3, 0x1C, 0xFA, 
	//	},
	//	// ��BS_SUB_ENTRY_POINT�ο���ƫ�ƣ�������ʼ��ַ137����������27������27���ֽ��Ǿ�������ֵ
	//	{
	//		BS_STRUCT_OFFSET, 2, 137, 27, BL_EQUAL, 
	//		0xCD, 0x20, 0x53, 0x00, 0x01, 0x00, 0x83, 0xC4, 0x20, 0x97, 0x8D, 0x46, 0x9D, 0xCF, 0x8D, 0x87, 
	//		0xF7, 0xFC, 0xFF, 0xFF, 0x50, 0xCD, 0x20, 0x67, 0x00, 0x40, 0x00, 
	//	},
	//};

	//// ���ÿ�������������
	//for(DWORD i=0; i<pVRecord->dwSignCount; i++)
	//{
	//	PVSIGNATURE	pSign = new VSIGNATURE;
	//	*pSign = aVSign3[i];
	//	pVRecord->pVSign[i] = pSign;
	//}

	//// ���б������м���˲�����¼
	//m_listVRecords.push_back(pVRecord);
   

   CString xmlFileName;  // xml�ļ�·������
	GetModuleFileName(NULL, xmlFileName.GetBuffer(MAX_PATH), MAX_PATH);  // ��õ�ǰӦ�ó���·��
	xmlFileName.ReleaseBuffer();  // һ��Ҫ�ͷţ������޷�ƴ��
	xmlFileName = xmlFileName.Left(xmlFileName.ReverseFind('\\'));  // ȥ����ǰӦ�ó�����
	xmlFileName = xmlFileName + "\\bin\\DB.xml";  // ƴ�ӳ�xml�ļ�·��

	CXmlFile xmlFile;
	xmlFile.SetXmlFileName(xmlFileName);  // ����xml�ļ�·��
	xmlFile.LoadForPE(&m_listVRecords);  // ���ز�����

	return TRUE;
}


// ж�ز�����
//
BOOL CVirusDB::Unload()
{
	list<PVRECORD>::iterator iter = m_listVRecords.begin();  // �б�����������ָ���б�ͷ

	// �����б�����
	while(iter != m_listVRecords.end())
	{
		PVRECORD pVRecord = *iter;  // �б������е�һ��������¼
		// ���ÿһ��������¼�������
		for(DWORD i=0; i<pVRecord->dwSignCount; i++)
		{
			delete pVRecord->pVSign[i];  // ɾ��ָ����ָ����
		}
		delete pVRecord;  // ɾ��ָ����ָ����

		iter++;  // ������ָ����һ���б�Ԫ��
	}

	return TRUE;
}


// ��ɨ������ڱ��������м�⣬���ز���ID��0
DWORD CVirusDB::Search(CScanObject* pScanObj)
{
	CParsePE parserPE;  // PE������
	parserPE.BasicParse((CMemFileObject*)pScanObj);  // �ж��Ƿ�PE�ļ�

	BOOL bVirus = FALSE;  // �ж��Ƿ񲡶���־
	list<PVRECORD>::iterator iter = m_listVRecords.begin();  // �б�����������ָ���б�ͷ
	// �����б�����
	while(iter != m_listVRecords.end())
	{
		PVRECORD pVRecord = *iter;  // �б������е�һ��������¼
		bVirus = FALSE;  // �����жϱ�ʶ

		// �ȶ�һ��������¼�е�ÿ��������
		for(DWORD i=0; i<pVRecord->dwSignCount; i++)
		{
			PVSIGNATURE pVSign = pVRecord->pVSign[i];  // ָ��һ��������

			// �жϴ˶������������
			switch(pVSign->eType)
			{
			// ������������Ϊ���ļ�ƫ��
			case BS_PHY_FILE:  
				bVirus = pScanObj->Compare(pVSign->nOffset, pVSign->nSize, pVSign->Signature, pVSign->eLogicOp);
				break;
			// ������������Ϊ��ĳ���ṹΪ�ο���ƫ��(Ŀǰֻ������PE�ļ�)
			case BS_STRUCT_OFFSET:  
				// �ж��Ƿ������ڴ��ļ�
				if(pScanObj->GetObjType() != BO_MEM_FILE)
				{
					bVirus = FALSE;
					break;  // �����˶�������
				}

				// ����PE�ļ�
				if(parserPE.GetFSPE().bPEFile == TRUE)
				{
					// �ж�������������
					switch(pVSign->dwSubType)
					{
					case BS_SUB_NT_HEADERS:  // ��BS_SUB_NT_HEADERS�ο���ƫ��
						bVirus = pScanObj->Compare(((LPBYTE)parserPE.GetFSPE().pNtHeaders)+pVSign->nOffset, 
							pVSign->nSize, pVSign->Signature, pVSign->eLogicOp);
						break;
					case BS_SUB_ENTRY_POINT:  // ��BS_SUB_ENTRY_POINT�ο���ƫ��
						bVirus = pScanObj->Compare(((LPBYTE)parserPE.GetFSPE().pEntryPoint)+pVSign->nOffset, 
							pVSign->nSize, pVSign->Signature, pVSign->eLogicOp);
						break;
					default:
						bVirus = FALSE;  // ���������������Ͳ���ȷ
					}
				}
				// ����PE�ļ�
				else
				{
					bVirus = FALSE;
					break;  // �����˶�������
				}
				break;
			default:
				bVirus = FALSE;  // �������������Ͳ���ȷ
			}

			// ��һ�������벻���Ͼ������˲�����¼
			if(bVirus == FALSE)	
			{
				break;  // ����forѭ��
			}
		}

		// ��ɨ�����ƥ��һ��������¼�е����������룬����Ϊ�Ǵ��ֲ���
		if(bVirus == TRUE)
		{
			return pVRecord->dwVirusID;  // ���ز���ID
		}
		else
		{
			iter++;  // ������ָ����һ���б�Ԫ��
		}
	}

	// ��δ�����������ΪPE�ļ������������ʽɨ��
	if(bVirus == FALSE && parserPE.GetFSPE().bPEFile == TRUE)
	{
		// ����δ֪��в
		if(parserPE.AdvancedParse() == TRUE)
		{
			return -2;  // ��ʾδ֪��в
		}
	}
	
	return 0;  // ��ʾ�޲���(���ٴ˲�������û����֮ƥ���������)
}