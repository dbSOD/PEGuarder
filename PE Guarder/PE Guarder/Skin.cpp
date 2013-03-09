// Skin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder.h"
#include "Skin.h"
#include "PE GuarderDlg.h"

// CSkin �Ի���

IMPLEMENT_DYNAMIC(CSkin, CDialog)

CSkin::CSkin(CWnd* pParent /*=NULL*/)
	: CDialog(CSkin::IDD, pParent)
{

}

CSkin::~CSkin()
{
}

void CSkin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SKINBLACK, m_SkinBlack);
	DDX_Control(pDX, IDC_SKINBLUE, m_SkinBlue);
	DDX_Control(pDX, IDC_SKINORANGE, m_SkinOrange);
}


BEGIN_MESSAGE_MAP(CSkin, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SKINBLACK, &CSkin::OnBnClickedSkinblack)
	ON_BN_CLICKED(IDC_SKINBLUE, &CSkin::OnBnClickedSkinblue)
	ON_BN_CLICKED(IDC_SKINORANGE, &CSkin::OnBnClickedSkinorange)
END_MESSAGE_MAP()


// CSkin ��Ϣ�������


// �Ի����ʼ������
//
BOOL CSkin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ��ť���λͼ
	if(m_SkinBlack.GetBitmap() == NULL)
	{
		m_SkinBlack.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SKINBLACK)));
	}

	// ��ť���λͼ
	if(m_SkinBlue.GetBitmap() == NULL)
	{
		m_SkinBlue.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SKINBLUE)));
	}

	// ��ť���λͼ
	if(m_SkinOrange.GetBitmap() == NULL)
	{
		m_SkinOrange.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SKINORANGE)));
	}

	m_brush.CreateSolidBrush(RGB(255,255,255));  // ������ɫ��ˢ

	GetModuleFileName(NULL, m_skinPath.GetBuffer(MAX_PATH), MAX_PATH);  // ��õ�ǰӦ�ó���·��
	m_skinPath.ReleaseBuffer();  // һ��Ҫ�ͷţ������޷�ƴ��
	m_skinPath = m_skinPath.Left(m_skinPath.ReverseFind('\\'));  // ȥ����ǰӦ�ó�����
	m_skinPath = m_skinPath + "\\bin\\";  // Ƥ��Ŀ¼����  

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


// �ı�Ի���Ϳؼ�����ɫ
//
HBRUSH CSkin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


// ��ɫƤ����ť�¼�
//
void CSkin::OnBnClickedSkinblack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	m_skinPath += "bk1.bmp";  // Ƥ��Ŀ¼
	((CPEGuarderDlg*)GetParent())->SetSkin(m_skinPath);  // ����Ƥ��
	
	OnCancel();  // ȡ���Ի���
}


// ��ɫƤ����ť�¼�
//
void CSkin::OnBnClickedSkinblue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_skinPath += "bk2.bmp";  // Ƥ��Ŀ¼
	((CPEGuarderDlg*)GetParent())->SetSkin(m_skinPath);  // ����Ƥ��
	
	OnCancel();  // ȡ���Ի���
}


// ��ɫƤ����ť�¼�
//
void CSkin::OnBnClickedSkinorange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_skinPath += "bk3.bmp";  // Ƥ��Ŀ¼
	((CPEGuarderDlg*)GetParent())->SetSkin(m_skinPath);  // ����Ƥ��
	
	OnCancel();  // ȡ���Ի���
}
