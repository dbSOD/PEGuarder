// MyTabCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder.h"
#include "MyTabCtrl.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl()
{
	// ָ���ʼ��
	m_pAnalyser = NULL;
	m_pDetector = NULL;
	m_pTool = NULL;
}

CMyTabCtrl::~CMyTabCtrl()
{
	// ���ָ����ָ�ڴ浥Ԫ
	delete m_pAnalyser;
	delete m_pDetector;
	delete m_pTool;
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTabCtrl::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTabCtrl ��Ϣ�������



void CMyTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// �����Զ���ѡ��л�ʱ�ͻ�����������
	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(1,20,2,2);

	// ������ã���ѡ���
	int cursel=this->GetCurSel();
	switch(cursel)
	{
	case 0:
		{
		m_pDetector->ShowWindow(SW_HIDE);
		m_pTool->ShowWindow(SW_HIDE);
		m_pAnalyser->MoveWindow(rect);
		m_pAnalyser->ShowWindow(SW_SHOW);
		break;
		}
	case 1:
		{
		m_pAnalyser->ShowWindow(SW_HIDE);
		m_pTool->ShowWindow(SW_HIDE);
		m_pDetector->MoveWindow(rect);
		m_pDetector->ShowWindow(SW_SHOW);
		break;
		}
	case 2:
		{
		m_pAnalyser->ShowWindow(SW_HIDE);
		m_pDetector->ShowWindow(SW_HIDE);
		m_pTool->MoveWindow(rect);
		m_pTool->ShowWindow(SW_SHOW);
		break;
		}
	}
	*pResult = 0;
}
