#pragma once

#include "SignatureAdder.h"
#include "DBUpdate.h"

// CSet �Ի���

class CSet : public CDialog
{
	DECLARE_DYNAMIC(CSet)

public:
	CSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSet();

// �Ի�������
	enum { IDD = IDD_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();  // �Ի����ʼ������
public:
	// �ı�Ի���Ϳؼ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnBnClickedAddsignature();  // ��������밴ť�¼�
public:
	afx_msg void OnBnClickedDbupdate();  // ��������°�ť�¼�

public:
	CSignatureAdder* m_pSignatureAdder;  // ���������Ի������
	CDBUpdate* m_pDBUpdate;  // ��������¶Ի������
private:
	CBrush m_brush;  // �Զ��廭ˢ
};
