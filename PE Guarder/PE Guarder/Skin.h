#pragma once
#include "afxwin.h"


// CSkin �Ի���

class CSkin : public CDialog
{
	DECLARE_DYNAMIC(CSkin)

public:
	CSkin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSkin();

// �Ի�������
	enum { IDD = IDD_SKIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();  // �Ի����ʼ������
public:
	// �ı�Ի���Ϳؼ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnBnClickedSkinblack();  // ��ɫƤ����ť�¼�
public:
	afx_msg void OnBnClickedSkinblue();  // ��ɫƤ����ť�¼�
public:
	afx_msg void OnBnClickedSkinorange();  // ��ɫƤ����ť�¼�

public:
	CButton m_SkinBlack;  // ��ɫƤ����ť
	CButton m_SkinBlue;  // ��ɫƤ����ť
	CButton m_SkinOrange;  //��ɫƤ����ť
	CString m_skinPath;  // Ƥ���ļ�·��

private:
	CBrush m_brush;  // �Զ��廭ˢ
};
