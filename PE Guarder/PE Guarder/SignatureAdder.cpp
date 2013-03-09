// SignatureAdder.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder.h"
#include "SignatureAdder.h"


// CSignatureAdder �Ի���

IMPLEMENT_DYNAMIC(CSignatureAdder, CDialog)

CSignatureAdder::CSignatureAdder(CWnd* pParent /*=NULL*/)
	: CDialog(CSignatureAdder::IDD, pParent)
	, m_Sign1(_T(""))
	, m_Sign2(_T(""))
	, m_Sign3(_T(""))
	, m_Sign4(_T(""))
{

}

CSignatureAdder::~CSignatureAdder()
{
}

void CSignatureAdder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SIGNATURE1, m_Sign1);
	DDX_Text(pDX, IDC_SIGNATURE2, m_Sign2);
	DDX_Text(pDX, IDC_SIGNATURE3, m_Sign3);
	DDX_Text(pDX, IDC_SIGNATURE4, m_Sign4);
}


BEGIN_MESSAGE_MAP(CSignatureAdder, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SAVE, &CSignatureAdder::OnBnClickedSave)
	ON_EN_CHANGE(IDC_SIGNATURE1, &CSignatureAdder::OnEnChangeSignature1)
	ON_EN_CHANGE(IDC_SIGNATURE2, &CSignatureAdder::OnEnChangeSignature2)
	ON_EN_CHANGE(IDC_SIGNATURE3, &CSignatureAdder::OnEnChangeSignature3)
	ON_EN_CHANGE(IDC_SIGNATURE4, &CSignatureAdder::OnEnChangeSignature4)
	ON_BN_CLICKED(IDC_FORMAT, &CSignatureAdder::OnBnClickedFormat)
END_MESSAGE_MAP()


// CSignatureAdder ��Ϣ�������


// �Ի����ʼ������
//
BOOL CSignatureAdder::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString xmlFileName;  // xml�ļ�·������
	GetModuleFileName(NULL, xmlFileName.GetBuffer(MAX_PATH), MAX_PATH);  // ��õ�ǰӦ�ó���·��
	xmlFileName.ReleaseBuffer();  // һ��Ҫ�ͷţ������޷�ƴ��
	xmlFileName = xmlFileName.Left(xmlFileName.ReverseFind('\\'));  // ȥ����ǰӦ�ó�����
	xmlFileName = xmlFileName + "\\bin\\DB.xml";  // ƴ�ӳ�xml�ļ�·��

	m_XmlFile.SetXmlFileName(xmlFileName);  // ����xml�ļ�·��

	m_brush.CreateSolidBrush(RGB(255,255,255));  // ������ɫ��ˢ

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


// �ı�Ի���Ϳؼ�����ɫ
//
HBRUSH CSignatureAdder::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;

	if(nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(RGB(255,255,255));  // ���ÿؼ�����ɫ����ɫ��
		return m_brush;  // �����Զ���Ļ�ˢ���
	}
	return hbr;  // ����Ļ�����ϵͳĬ�ϵĻ�ˢ���
}


// ���水ť�¼�
//
void CSignatureAdder::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��������ʽ
	if(m_Sign1.Trim() == "" && m_Sign2.Trim() == "" && m_Sign3.Trim()== "" && m_Sign4.Trim()== "")
	{
		MessageBox("�������ȫΪ�ջ���ַ���");

		// �����ԭ
		m_Sign1.Empty();
		m_Sign2.Empty();
		m_Sign3.Empty();
		m_Sign4.Empty();
		UpdateData(FALSE);
		
		return;
	}

	// ��xml�м��벡������
	if(m_XmlFile.AppendForPE(m_Sign1.Trim(), m_Sign2.Trim(), m_Sign3.Trim(), m_Sign4.Trim()) == TRUE)
	{
		MessageBox("����ɹ���");
	}
	else
	{
		MessageBox("����ʧ�ܣ�");
	}

	// �����ԭ
	m_Sign1.Empty();
	m_Sign2.Empty();
	m_Sign3.Empty();
	m_Sign4.Empty();
	UpdateData(FALSE);
}


// ������1�䶯�¼�
//
void CSignatureAdder::OnEnChangeSignature1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
}


// ������2�䶯�¼�
//
void CSignatureAdder::OnEnChangeSignature2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
}


// ������3�䶯�¼�
//
void CSignatureAdder::OnEnChangeSignature3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
}


// ������4�䶯�¼�
//
void CSignatureAdder::OnEnChangeSignature4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
}


// �ο���ʽ��ť�¼�
//
void CSignatureAdder::OnBnClickedFormat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	MessageBox("���磺BS_STRUCT_OFFSET, 1, -1, 1, BL_NOT_EQUAL, 0x00,");
}
