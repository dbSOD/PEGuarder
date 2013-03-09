// Analyser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder.h"
#include "Analyser.h"


// CAnalyser �Ի���

IMPLEMENT_DYNAMIC(CAnalyser, CDialog)

CAnalyser::CAnalyser(CWnd* pParent /*=NULL*/)
	: CDialog(CAnalyser::IDD, pParent)
{

}

CAnalyser::~CAnalyser()
{
}

void CAnalyser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl1);
}


BEGIN_MESSAGE_MAP(CAnalyser, CDialog)
	ON_BN_CLICKED(IDC_LOADPE, &CAnalyser::OnBnClickedLoadpe)
	ON_BN_CLICKED(IDC_DOSHEADER, &CAnalyser::OnBnClickedDosheader)
	ON_BN_CLICKED(IDC_PEHEADER, &CAnalyser::OnBnClickedPeheader)
	ON_BN_CLICKED(IDC_SECTIONTABLE, &CAnalyser::OnBnClickedSectiontable)
	ON_BN_CLICKED(IDC_DATADIRECTORY, &CAnalyser::OnBnClickedDatadirectory)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAnalyser ��Ϣ�������


// �Ի����ʼ������
//
BOOL CAnalyser::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	len = 0;
	ptr = NULL;
	bValid = FALSE;

	// �б�����������
	m_ListCtrl1.InsertColumn(0,"����",LVCFMT_LEFT,110);
	m_ListCtrl1.InsertColumn(1,"ֵ",LVCFMT_LEFT,90);
	m_ListCtrl1.InsertColumn(2,"˵��",LVCFMT_LEFT,150);

	m_brush.CreateSolidBrush(RGB(255,255,255));  // �Ի�����ɫ��Ϊ��ɫ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


// �ı�Ի�����ɫ
//
HBRUSH CAnalyser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
	return m_brush;
}


// ��������ļ��Ƿ�ΪPE�ļ�
//
void CAnalyser::OnBnClickedLoadpe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//m_ListCtrl1.DeleteAllItems();  // ����б�������

	// �������ļ��Ի������
	CFileDialog fileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"All File(*.*)|*.*||",this);
	if(fileDialog.DoModal() != IDOK)
	{
   		return;
	}

	// �����ļ����������ļ����
	HANDLE hFile = ::CreateFile(fileDialog.GetFileName(),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	// ��鷵�ص��ļ�����Ƿ���Ч
	if(hFile == INVALID_HANDLE_VALUE)         
	{
		MessageBox("��Ч�ļ�",NULL,MB_OK);
		return;
	}

	// ���ݷ��ص��ļ�����õ��ļ��Ĵ�С
	len = GetFileSize(hFile,NULL);
	// �����ļ���С�����ڴ�ռ�
	ptr = new BYTE[len];
	if(!ptr){
		MessageBox("�ڴ治��",NULL,MB_OK);
		return;
	}
	// ��ȡȫ���ļ�����ptr��ָ�ڴ�ռ���
	::ReadFile(hFile,ptr,len,&len,NULL);


	// ��ptr��ָ��dosHeader��С�����ݷ���dosHeader��ַ����
	memmove(&dosHeader,ptr,sizeof(dosHeader));

	// ͨ��ͷ�����ֽ��Ƿ�Ϊ"MZ"�����DOSͷ�Ƿ���Ч
	if(dosHeader.e_magic == IMAGE_DOS_SIGNATURE)
	{
		// �ƶ��ļ�ָ�뵽PE�ļ�ͷ��PE�ļ���־��
		::SetFilePointer(hFile,dosHeader.e_lfanew,NULL,FILE_BEGIN);
		// �����ļ������ȡntHeader���ֵ�ntHeader��ַ����
		::ReadFile(hFile,&ntHeader,sizeof(ntHeader),&len,NULL);

		// ���PE�ļ�ͷ(NTӳ��ͷ)��PE�ļ���־�Ƿ�Ϊ"PE00"
		if(ntHeader.Signature == IMAGE_NT_SIGNATURE)
		{
			bValid = TRUE;   // TRUE������PE�ļ�
		}
		else
		{
			bValid = FALSE;  // FALSE������PE�ļ�
		}

	}
	else
	{
		bValid = FALSE;  // FALSE������PE�ļ�
	}

	// ͨ������Ƿ�ΪPE�ļ��������ж�����
	if(bValid)
	{
		MessageBox("��PE�ļ�",NULL,MB_OK);
	}
	else
	{
		MessageBox("����PE�ļ�",NULL,MB_OK);
	}

	::CloseHandle(hFile);  // �ر��ļ����
	m_ListCtrl1.DeleteAllItems();  // ����б�������

	return;
}


// ��DOSͷ
//
void CAnalyser::OnBnClickedDosheader()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// �����������δ�򿪹��κ��ļ�����ptrΪNULL���Ӷ��޷���ȡ�ļ�����
	// ���������ļ�����PE�ļ�
	if(ptr == NULL || bValid == FALSE)
	{
	   return;
	}

	m_ListCtrl1.DeleteAllItems();  // ����б�������
	// ��ptr��ָ��dosHeader��С�����ݷ���dosHeader��ַ����
	memmove(&dosHeader,ptr,sizeof(dosHeader));

	CString dosHeaderInf;  // �洢dosHeader��Ϣ

	/*--------��ʮ��������ʾDOSͷ���йؽṹ��Ϣ--------*/

	m_ListCtrl1.InsertItem(0,"");
	dosHeaderInf.Format("%xh",dosHeader.e_ss);
	m_ListCtrl1.SetItemText(0,0,"e_ss");
	m_ListCtrl1.SetItemText(0,1,dosHeaderInf);

	m_ListCtrl1.InsertItem(1,"");
	dosHeaderInf.Format("%xh",dosHeader.e_sp);
	m_ListCtrl1.SetItemText(1,0,"e_sp");
	m_ListCtrl1.SetItemText(1,1,dosHeaderInf);

	m_ListCtrl1.InsertItem(2,"");
	dosHeaderInf.Format("%xh",dosHeader.e_ip);
	m_ListCtrl1.SetItemText(2,0,"e_ip");
	m_ListCtrl1.SetItemText(2,1,dosHeaderInf);

	m_ListCtrl1.InsertItem(3,"");
	dosHeaderInf.Format("%xh",dosHeader.e_cs);
	m_ListCtrl1.SetItemText(3,0,"e_cs");
	m_ListCtrl1.SetItemText(3,1,dosHeaderInf);

	m_ListCtrl1.InsertItem(4,"");
	dosHeaderInf.Format("%xh",dosHeader.e_lfanew);
	m_ListCtrl1.SetItemText(4,0,"e_lfanew");
	m_ListCtrl1.SetItemText(4,1,dosHeaderInf);
	m_ListCtrl1.SetItemText(4,2,"ָ��PE�ļ�ͷ��ʼλ��");
}


// ��PEͷ(ntHeader)
//
void CAnalyser::OnBnClickedPeheader()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// �����������δ�򿪹��κ��ļ�����ptrΪNULL���Ӷ��޷���ȡ�ļ�����
	// ���������ļ�����PE�ļ�
	if(ptr == NULL || bValid == FALSE)
	{
	   return;
	}

	m_ListCtrl1.DeleteAllItems();  // ����б�������
	// ��ntHeader���ַ���ntHeader������ַ����
	memmove(&ntHeader,ptr+dosHeader.e_lfanew,sizeof(ntHeader));

	CString ntHeaderInf;  // �洢ntHeader��Ϣ

	/*------------------Fileͷ����---------------------*/

	// ����
	m_ListCtrl1.InsertItem(0,"");
	ntHeaderInf.Format("%xh",ntHeader.FileHeader.NumberOfSections);
	m_ListCtrl1.SetItemText(0,0,"NumberOfSections");
	m_ListCtrl1.SetItemText(0,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(0,2,"����");

	// �ļ�������ʱ������(��1970��1��1��00��00��00�������)
	m_ListCtrl1.InsertItem(1,"");
	ntHeaderInf.Format("%xh",ntHeader.FileHeader.TimeDateStamp);
	m_ListCtrl1.SetItemText(1,0,"TimeDateStamp");
	m_ListCtrl1.SetItemText(1,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(1,2,"�ļ�������ʱ������(��1970��1��1��00��00��00�������)");

	// ��ѡͷ��С(��ֵe0h)
	m_ListCtrl1.InsertItem(2,"");
	ntHeaderInf.Format("%xh",ntHeader.FileHeader.SizeOfOptionalHeader);
	m_ListCtrl1.SetItemText(2,0,"SizeOfOptionalHeader");
	m_ListCtrl1.SetItemText(2,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(2,2,"��ѡͷ��С(��ֵe0h)");


	// �ļ���Ϣ��־����dll��exe
	m_ListCtrl1.InsertItem(3,"");
	ntHeaderInf.Format("%xh",ntHeader.FileHeader.Characteristics);
	m_ListCtrl1.SetItemText(3,0,"Characteristics");
	m_ListCtrl1.SetItemText(3,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(3,2,"�ļ���Ϣ��־����dll��exe");


	/*------------------NT��ѡͷ����----------------*/

	// ��־��(��ֵ10bh)
	m_ListCtrl1.InsertItem(4,"");
	ntHeaderInf.Format("%xh",ntHeader.OptionalHeader.Magic);
	m_ListCtrl1.SetItemText(4,0,"Magic");
	m_ListCtrl1.SetItemText(4,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(4,2,"��־��(��ֵ10bh)");

	// �������RVA��ַ
	m_ListCtrl1.InsertItem(5,"");
	ntHeaderInf.Format("%xh",ntHeader.OptionalHeader.AddressOfEntryPoint);
	m_ListCtrl1.SetItemText(5,0,"AddressOfEntryPoint");
	m_ListCtrl1.SetItemText(5,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(5,2,"�������RVA��ַ");


	// �������ʼRVA
	m_ListCtrl1.InsertItem(6,"");
	ntHeaderInf.Format("%xh",ntHeader.OptionalHeader.BaseOfCode);
	m_ListCtrl1.SetItemText(6,0,"BaseOfCode");
	m_ListCtrl1.SetItemText(6,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(6,2,"�������ʼRVA");

	// ���ݿ���ʼRVA
	m_ListCtrl1.InsertItem(7,"");
	ntHeaderInf.Format("%xh",ntHeader.OptionalHeader.BaseOfData);
	m_ListCtrl1.SetItemText(7,0,"BaseOfData");
	m_ListCtrl1.SetItemText(7,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(7,2,"���ݿ���ʼRVA");

	// ��ַ
	m_ListCtrl1.InsertItem(8,"");
	ntHeaderInf.Format("%xh",ntHeader.OptionalHeader.ImageBase);
	m_ListCtrl1.SetItemText(8,0,"ImageBase");
	m_ListCtrl1.SetItemText(8,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(8,2,"��ַ");

	// ӳ���С
	m_ListCtrl1.InsertItem(9,"");
	ntHeaderInf.Format("%xh",ntHeader.OptionalHeader.SizeOfImage);
	m_ListCtrl1.SetItemText(9,0,"SizeOfImage");
	m_ListCtrl1.SetItemText(9,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(9,2,"ӳ���С");

	// ��ǰͷ����С
	m_ListCtrl1.InsertItem(10,"");
	ntHeaderInf.Format("%xh",ntHeader.OptionalHeader.SizeOfHeaders);
	m_ListCtrl1.SetItemText(10,0,"SizeOfHeaders");
	m_ListCtrl1.SetItemText(10,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(10,2,"��ǰͷ����С");

	// У���
	m_ListCtrl1.InsertItem(11,"");
	ntHeaderInf.Format("%xh",ntHeader.OptionalHeader.CheckSum);
	m_ListCtrl1.SetItemText(11,0,"CheckSum");
	m_ListCtrl1.SetItemText(11,1,ntHeaderInf);
	m_ListCtrl1.SetItemText(11,2,"У���");
}


// �����
//
void CAnalyser::OnBnClickedSectiontable()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// �����������δ�򿪹��κ��ļ�����ptrΪNULL���Ӷ��޷���ȡ�ļ�����
	// ���������ļ�����PE�ļ�
	if(ptr == NULL || bValid == FALSE)
	{
	   return;
	}

	m_ListCtrl1.DeleteAllItems();  // ����б�������
	// ��dosHeader���ַ���dosHeader������ַ����
	memmove(&dosHeader,ptr,sizeof(dosHeader));
	// ��ntHeader���ַ���ntHeader������ַ����
	memmove(&ntHeader,ptr+dosHeader.e_lfanew,sizeof(ntHeader));
	
	CString sectionHeaderInf;  // �洢sectionHeader��Ϣ
	IMAGE_SECTION_HEADER sectionHeader;  // ��ͷ�ṹ
	DWORD num = ntHeader.FileHeader.NumberOfSections;  // ����

	// ������п����Ҫ����
	for(DWORD i = 0;i < num;i ++)
	{
		// ��ÿһ������������Ƶ�sectionHeader������ַ����
		memmove(&sectionHeader,ptr+dosHeader.e_lfanew+sizeof(ntHeader)+i*sizeof(sectionHeader),sizeof(sectionHeader));
   
		// ����
		m_ListCtrl1.InsertItem(0+7*i,"");
		sectionHeaderInf.Format("%s",sectionHeader.Name);
		m_ListCtrl1.SetItemText(0+7*i,0,"Name");
		m_ListCtrl1.SetItemText(0+7*i,1,sectionHeaderInf);
		m_ListCtrl1.SetItemText(0+7*i,2,"����");

		// �ڴ��п��С
		m_ListCtrl1.InsertItem(1+7*i,"");
		sectionHeaderInf.Format("%xh",sectionHeader.Misc.VirtualSize);
		m_ListCtrl1.SetItemText(1+7*i,0,"VirtualSize");
		m_ListCtrl1.SetItemText(1+7*i,1,sectionHeaderInf);
		m_ListCtrl1.SetItemText(1+7*i,2,"�ڴ��п��С");

		// �ڴ��п�RVAֵ
		m_ListCtrl1.InsertItem(2+7*i,"");
		sectionHeaderInf.Format("%xh",sectionHeader.VirtualAddress);
		m_ListCtrl1.SetItemText(2+7*i,0,"VirtualAddress");
		m_ListCtrl1.SetItemText(2+7*i,1,sectionHeaderInf);
		m_ListCtrl1.SetItemText(2+7*i,2,"�ڴ��п�RVAֵ");

		// �ļ��п��С
		m_ListCtrl1.InsertItem(3+7*i,"");
		sectionHeaderInf.Format("%xh",sectionHeader.SizeOfRawData);
		m_ListCtrl1.SetItemText(3+7*i,0,"SizeOfRawData");
		m_ListCtrl1.SetItemText(3+7*i,1,sectionHeaderInf);
		m_ListCtrl1.SetItemText(3+7*i,2,"�ļ��п��С");

		// �ļ��п�ƫ��
		m_ListCtrl1.InsertItem(4+7*i,"");
		sectionHeaderInf.Format("%xh",sectionHeader.PointerToRawData);
		m_ListCtrl1.SetItemText(4+7*i,0,"PointerToRawData");
		m_ListCtrl1.SetItemText(4+7*i,1,sectionHeaderInf);
		m_ListCtrl1.SetItemText(4+7*i,2,"�ļ��п�ƫ��");

		// ������
		m_ListCtrl1.InsertItem(5+7*i,"");
		sectionHeaderInf.Format("%xh",sectionHeader.Characteristics);
		m_ListCtrl1.SetItemText(5+7*i,0,"Characteristics");
		m_ListCtrl1.SetItemText(5+7*i,1,sectionHeaderInf);
		m_ListCtrl1.SetItemText(5+7*i,2,"������");

		// �ָ���
		m_ListCtrl1.InsertItem(6+7*i,"");
	}
}


// ������Ŀ¼
//
void CAnalyser::OnBnClickedDatadirectory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// �����������δ�򿪹��κ��ļ�����ptrΪNULL���Ӷ��޷���ȡ�ļ�����
	// ���������ļ�����PE�ļ�
	if(ptr == NULL || bValid == FALSE)
	{
	   return;
	}

	m_ListCtrl1.DeleteAllItems();  // ����б�������
	// ��dosHeader���ַ���dosHeader������ַ����
	memmove(&dosHeader,ptr,sizeof(dosHeader));
	// ��ntHeader���ַ���ntHeader������ַ����
	memmove(&ntHeader,ptr+dosHeader.e_lfanew,sizeof(ntHeader));

	CString dataDirectoryInf;  // �洢����Ŀ¼��Ϣ

	/*------------��ʮ��������ʾdataDirectory���йؽṹ��Ϣ--------------*/

	// ������RVAֵ����С
	m_ListCtrl1.InsertItem(0,"");
	dataDirectoryInf.Format("%xh",ntHeader.OptionalHeader.DataDirectory[0].VirtualAddress);
	m_ListCtrl1.SetItemText(0,0,"VirtualAddress");
	m_ListCtrl1.SetItemText(0,1,dataDirectoryInf);
	m_ListCtrl1.SetItemText(0,2,"������RVAֵ");

	// ������С
	m_ListCtrl1.InsertItem(1,"");
	dataDirectoryInf.Format("%xh",ntHeader.OptionalHeader.DataDirectory[0].Size);
	m_ListCtrl1.SetItemText(1,0,"Size");
	m_ListCtrl1.SetItemText(1,1,dataDirectoryInf);
	m_ListCtrl1.SetItemText(1,2,"������С");

	// �ָ���
	m_ListCtrl1.InsertItem(2,"");

	// ������RVAֵ����С
	m_ListCtrl1.InsertItem(3,"");
	dataDirectoryInf.Format("%xh",ntHeader.OptionalHeader.DataDirectory[1].VirtualAddress);
	m_ListCtrl1.SetItemText(3,0,"VirtualAddress");
	m_ListCtrl1.SetItemText(3,1,dataDirectoryInf);
	m_ListCtrl1.SetItemText(3,2,"������RVAֵ");

	// ������С
	m_ListCtrl1.InsertItem(4,"");
	dataDirectoryInf.Format("%xh",ntHeader.OptionalHeader.DataDirectory[1].Size);
	m_ListCtrl1.SetItemText(4,0,"Size");
	m_ListCtrl1.SetItemText(4,1,dataDirectoryInf);
	m_ListCtrl1.SetItemText(4,2,"������С");
}



