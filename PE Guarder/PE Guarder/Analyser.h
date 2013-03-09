#pragma once
#include "afxcmn.h"


// CAnalyser �Ի���

class CAnalyser : public CDialog
{
	DECLARE_DYNAMIC(CAnalyser)

public:
	CAnalyser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAnalyser();

// �Ի�������
	enum { IDD = IDD_ANALYSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_ListCtrl1;  // �б�����
	IMAGE_DOS_HEADER dosHeader;  // DOSͷ�ṹ
	IMAGE_NT_HEADERS ntHeader;    // PEͷ�ṹ
	DWORD len;  // ��¼�ļ�����
	BYTE *ptr;   // ���������ļ�
	BOOL bValid;   // �ж�PE�ļ��ı�ʶ

private:
	CBrush m_brush;  // �Զ��廭ˢ

public:
	virtual BOOL OnInitDialog();  // �Ի����ʼ������
public:
	// �ı�Ի�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);  
public:
	afx_msg void OnBnClickedLoadpe();  // ��������ļ��Ƿ�ΪPE�ļ�
public:
	afx_msg void OnBnClickedDosheader();  // ��DOSͷ
public:
	afx_msg void OnBnClickedPeheader();  // ��PEͷ(ntHeader)
public:
	afx_msg void OnBnClickedSectiontable();  // �����
public:
	afx_msg void OnBnClickedDatadirectory();  // ������Ŀ¼

};
