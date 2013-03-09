// Set.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder.h"
#include "Set.h"


// CSet �Ի���

IMPLEMENT_DYNAMIC(CSet, CDialog)

CSet::CSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSet::IDD, pParent)
{

}

CSet::~CSet()
{
	// ɾ��ָ����ָ����
	delete m_pSignatureAdder;
	delete m_pDBUpdate;
}

void CSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSet, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ADDSIGNATURE, &CSet::OnBnClickedAddsignature)
	ON_BN_CLICKED(IDC_DBUPDATE, &CSet::OnBnClickedDbupdate)
END_MESSAGE_MAP()


// CSet ��Ϣ�������


// �Ի����ʼ������
//
BOOL CSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ������ģ̬���������Ի���
	m_pSignatureAdder = new CSignatureAdder();
	m_pSignatureAdder->Create(IDD_ADDSIGNATURE, this);

	// ������ģ̬��������¶Ի���
	m_pDBUpdate = new CDBUpdate();
	m_pDBUpdate->Create(IDD_DBUPDATE, this);

	m_pSignatureAdder->ShowWindow(SW_SHOW);  // ��ʾ���������Ի���
	m_pDBUpdate->ShowWindow(SW_HIDE);  // ���ز�������¶Ի���

	m_brush.CreateSolidBrush(RGB(255,255,255));  // ������ɫ��ˢ

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


// �ı�Ի���Ϳؼ�����ɫ
//
HBRUSH CSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


// ��������밴ť�¼�
//
void CSet::OnBnClickedAddsignature()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_pSignatureAdder->ShowWindow(SW_SHOW);  // ��ʾ���������Ի���
	m_pDBUpdate->ShowWindow(SW_HIDE);  // ���ز�������¶Ի���
}


// ��������°�ť�¼�
//
void CSet::OnBnClickedDbupdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_pDBUpdate->ShowWindow(SW_SHOW);  // ��ʾ��������¶Ի���
	m_pSignatureAdder->ShowWindow(SW_HIDE);  // �������������Ի���
}
