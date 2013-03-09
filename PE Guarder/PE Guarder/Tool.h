#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTool �Ի���

class CTool : public CDialog
{
	DECLARE_DYNAMIC(CTool)

public:
	CTool(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTool();

// �Ի�������
	enum { IDD = IDD_TOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

public:
	CString m_FilePath;  // �ļ�·��
	DWORD m_FileSize;  // �ļ���С
	CButton m_Shatter;  // ���鰴ť����
	CProgressCtrl m_ShatterProgress;  // �������ؼ�����

private:
	CBrush m_brush;  // �Զ��廭ˢ

public:
	virtual BOOL OnInitDialog();  // �Ի����ʼ������
public:
	// �ı�Ի���Ϳؼ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnBnClickedBrowse();  // �����ť��Ϣ
public:
	afx_msg void OnEnChangeFilepath();  // ·���ı���䶯��Ϣ
public:
	afx_msg void OnBnClickedDelete();  // ɾ����ť��Ϣ
public:
	afx_msg void OnBnClickedShatter();  // ���鰴ť��Ϣ
public:
	void GetFileSize();  // ���ָ���ļ���С
};

DWORD WINAPI MyShatterThread(LPVOID lpParameter);  // �Զ����̺߳���