#pragma once

#include "XmlFile.h"  // ����xml������


// CSignatureAdder �Ի���

class CSignatureAdder : public CDialog
{
	DECLARE_DYNAMIC(CSignatureAdder)

public:
	CSignatureAdder(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSignatureAdder();

// �Ի�������
	enum { IDD = IDD_ADDSIGNATURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();  // �Ի����ʼ������
public:
	// �ı�Ի���Ϳؼ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnBnClickedSave();  // ���水ť�¼�
public:
	afx_msg void OnEnChangeSignature1();  // ������1�䶯�¼�
public:
	afx_msg void OnEnChangeSignature2();  // ������2�䶯�¼�
public:
	afx_msg void OnEnChangeSignature3();  // ������3�䶯�¼�
public:
	afx_msg void OnEnChangeSignature4();  // ������4�䶯�¼�
public:
	afx_msg void OnBnClickedFormat();  // �ο���ʽ��ť�¼�

public:
	CString m_Sign1;  //������1����
	CString m_Sign2;  //������2����
	CString m_Sign3;  //������3����
	CString m_Sign4;  //������4����
	CXmlFile m_XmlFile;  // xml�ļ�����
private:
	CBrush m_brush;  // �Զ��廭ˢ
};
