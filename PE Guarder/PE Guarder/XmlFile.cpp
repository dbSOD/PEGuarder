#include "StdAfx.h"
#include "XmlFile.h"



CXmlFile::CXmlFile(void)
{
}

CXmlFile::~CXmlFile(void)
{
}


// ���xml�ļ�·��
//
CString CXmlFile::GetXmlFileName()
{
	return m_XmlFileName;
}


// ����xml�ļ�·��
//
void CXmlFile::SetXmlFileName(CString xmlFileName)
{
	m_XmlFileName = xmlFileName;
}


// �õ�ָ���������ֵ
//
CString CXmlFile::GetValue(CString nodeName)
{
	CString nodeValue;  // ����������ֵ
	CoInitialize(NULL);  // ��ʼ��com

	// �����ĵ�����
	MSXML2::IXMLDOMDocumentPtr pDoc;  
	HRESULT hr = pDoc.CreateInstance(__uuidof(DOMDocument30));
	if(hr < 0)
	{     
		return NULL;
	}   
	pDoc->load((const _variant_t)m_XmlFileName);  // ����ָ��xml
	
	MSXML2::IXMLDOMElementPtr pRoot=pDoc->GetdocumentElement();  // �õ������ָ��
	MSXML2::IXMLDOMElementPtr pTarget=pRoot->selectSingleNode((_bstr_t)nodeName);  // �õ�Ŀ����ָ��        
	nodeValue = _com_util::ConvertBSTRToString(pTarget->text);  // �õ�Ŀ����ֵ  
	
	pTarget.Release();  // Ŀ�����ͷ�
	pRoot.Release();  // ������ͷ�
	pDoc.Release();  // �ĵ������ͷ�

	CoUninitialize();  // ����com

	return nodeValue;
}


// �޸�ָ���ڵ�ֵ
//
BOOL CXmlFile::SetValue(CString nodeName, CString nodeValue)
{
	CoInitialize(NULL);  // ��ʼ��com

	// �����ĵ�����
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(DOMDocument30));
	if(hr < 0)
	{     
		return FALSE;
	}   
	pDoc->load((const _variant_t)m_XmlFileName);  // ����ָ��xml

	MSXML2::IXMLDOMElementPtr pRoot = pDoc->GetdocumentElement();  // �õ������ָ��            
	MSXML2::IXMLDOMElementPtr pTarget = pRoot->selectSingleNode((_bstr_t)nodeName);  // �õ�Ŀ����ָ��
	pTarget->Puttext((_bstr_t)nodeValue);  // ����Ŀ����ֵ
	pDoc->save((const _variant_t)m_XmlFileName);  // ����

	pTarget.Release();  // Ŀ�����ͷ�
	pRoot.Release();  // ������ͷ�
	pDoc.Release();  // �ĵ������ͷ�

	CoUninitialize();  // ����com

	return TRUE;
}


// ��ӽ��ͽ��ֵ
//
BOOL CXmlFile::AppendForPE(CString sign1, CString sign2, CString sign3, CString sign4)
{
	LONG num = atol(GetValue("num"));  // �����������в�����
	num++;  // ����������

	// ������ת�����ַ���
	CString strNum;
	strNum.Format("%ld",num);

	SetValue("num", strNum);  // �޸�xml�ļ��в�����

	CoInitialize(NULL);  // ��ʼ��com

	// �����ĵ�����
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(DOMDocument30));
	if(hr < 0)
	{     
		return FALSE;
	}   
	pDoc->load((const _variant_t)m_XmlFileName);  // ����ָ��xml

	MSXML2::IXMLDOMElementPtr pRoot = pDoc->GetdocumentElement();  // �õ������ָ��

	// �ӽ��
	MSXML2::IXMLDOMElementPtr pChild = pDoc->createElement("virus");
	pRoot->appendChild(pChild);

	/* -------------- ���ӽ�� ------------ */
	// ID
	MSXML2::IXMLDOMElementPtr pGrandChild = pDoc->createElement("ID");
	pGrandChild->Puttext((_bstr_t)strNum);
	pChild->appendChild(pGrandChild);

	/*---------- Signature ------------*/
	if(sign1.IsEmpty() == false)
	{
		pGrandChild = pDoc->createElement("sign");
		pGrandChild->Puttext((_bstr_t)sign1);
		pChild->appendChild(pGrandChild);
	}

	if(sign2.IsEmpty() == false)
	{
		pGrandChild = pDoc->createElement("sign");
		pGrandChild->Puttext((_bstr_t)sign2);
		pChild->appendChild(pGrandChild);
	}

	if(sign3.IsEmpty() == false)
	{
		pGrandChild = pDoc->createElement("sign");
		pGrandChild->Puttext((_bstr_t)sign3);
		pChild->appendChild(pGrandChild);
	}

	if(sign4.IsEmpty() == false)
	{
		pGrandChild = pDoc->createElement("sign");
		pGrandChild->Puttext((_bstr_t)sign4);
		pChild->appendChild(pGrandChild);
	}

	pDoc->save((const _variant_t)m_XmlFileName);  // ����

	pGrandChild.Release();  // ���ӽ���ͷ�
	pChild.Release();  // ���ӽ���ͷ�
	pRoot.Release();  // ������ͷ�
	pDoc.Release();  // �ĵ������ͷ�

	CoUninitialize();  // ����com

	return TRUE;
}


// ���ز�����
//
BOOL CXmlFile::LoadForPE(list<PVRECORD>* pList)
{
	CoInitialize(NULL);  // ��ʼ��com

	// �����ĵ�����
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(DOMDocument30));
	if(hr < 0)
	{     
		return FALSE;
	}   
	pDoc->load((const _variant_t)m_XmlFileName);  // ����ָ��xml

	MSXML2::IXMLDOMElementPtr pRoot = pDoc->GetdocumentElement();  // �õ������ָ��
	MSXML2::IXMLDOMNodeListPtr pVirusList = pRoot->selectNodes("virus");  // �õ�virus���ָ���б�
	PVRECORD pVRecord;  // ������¼

	// �������в�����¼
	for(long i=0; i<pVirusList->Getlength(); i++)
	{
		MSXML2::IXMLDOMNodePtr pID = pVirusList->Getitem(i)->selectSingleNode("ID");  // ID���
		pVRecord = new VRECORD;  // �½�������¼
		pVRecord->dwVirusID = atol(_com_util::ConvertBSTRToString(pID->text));  // ����ID
		MSXML2::IXMLDOMNodeListPtr pSignList = pVirusList->Getitem(i)->selectNodes("sign");  // �õ�sign���ָ���б�
		pVRecord->dwSignCount = pSignList->Getlength();  // һ����¼�����������

		for(DWORD i=0; i<pVRecord->dwSignCount; i++)
		{
			// �ַ���ת������
			pVRecord->pVSign[i] = StrToSign(_com_util::ConvertBSTRToString(pSignList->Getitem(i)->text));
		}

		pList->push_back(pVRecord);  // ���벡����¼ 

		pSignList.Release();  // ���ָ���б��ͷ�
		pID.Release();  // ID����ͷ�
	}

	pVirusList.Release();  // ���ָ���б��ͷ�
	pRoot.Release();  // ������ͷ�
	pDoc.Release();  // �ĵ������ͷ�

	CoUninitialize();  // ����com

	return TRUE;
}


// �ַ���ת������
//
PVSIGNATURE CXmlFile::StrToSign(CString str)
{
	PVSIGNATURE pVSignature = new VSIGNATURE;

	/*------------------- eType -------------------*/
	CString type = str.Left(str.Find(",")).Trim();
	if(type == "BS_PHY_FILE")
	{
		pVSignature->eType = BS_PHY_FILE;
	}
	else if(type == "BS_STRUCT_OFFSET")
	{
		pVSignature->eType = BS_STRUCT_OFFSET;
	}

	str.Delete(0,str.Find(",")+1);  // �ַ�����ȥ����������ո�Ͷ��� 

	/*----------------- dwSubType -----------------*/
	pVSignature->dwSubType = atol(str.Left(str.Find(",")).Trim());
	
	str.Delete(0,str.Find(",")+1);  // �ַ�����ȥ����������ո�Ͷ���

	/*------------------- nOffset -------------------*/
	pVSignature->nOffset = atoi(str.Left(str.Find(",")).Trim());
	
	str.Delete(0,str.Find(",")+1);  // �ַ�����ȥ����������ո�Ͷ���

	/*-------------------- nSize --------------------*/
	pVSignature->nSize = atoi(str.Left(str.Find(",")).Trim());
	
	str.Delete(0,str.Find(",")+1);  // �ַ�����ȥ����������ո�Ͷ���

	/*------------------ eLogicOp -------------------*/
	CString op = str.Left(str.Find(",")).Trim();
	if(op == "BL_EQUAL")
	{
		pVSignature->eLogicOp = BL_EQUAL;
	}
	else if(op == "BL_NOT_EQUAL")
	{
		pVSignature->eLogicOp = BL_NOT_EQUAL;
	}

	str.Delete(0,str.Find(",")+1);  // �ַ�����ȥ����������ո�Ͷ���

	/*------------------ Signature -------------------*/
	str.Trim();  // �������(������������)

	CString strByte;  // һ���ֽ�(�ַ���)  
	int iTemp;  // ���ɱ���
	for(int i=0; i<pVSignature->nSize; i++)
	{
		strByte = str.Left(str.Find(",")).Trim();
		sscanf_s(strByte, "%x", &iTemp);  // ��strByte�е�ֵ��16���Ƶĸ�ʽ���ͣ�����iTemp��
		pVSignature->Signature[i] = (BYTE)iTemp;
		str.Delete(0,str.Find(",")+1);  // �ַ�����ȥ����������ո�Ͷ���
	}


	return pVSignature;
}