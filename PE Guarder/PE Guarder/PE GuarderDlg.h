// PE GuarderDlg.h : ͷ�ļ�
//

#pragma once

#include "CDialogSK.h"  // ����Ƥ���Ի���ͷ�ļ�
#include "afxcmn.h"
#include "MyTabCtrl.h"  // �����Զ���ѡ�ͷ�ļ�
#include "TrayIcon.h"  // ��������ͷ�ļ�
#include "IniFile.h"  // �����ʼ������ͷ�ļ�

#define WM_ICON_NOTIFY WM_USER+1  // �Զ���������Ϣ


// CPEGuarderDlg �Ի���
class CPEGuarderDlg : public CDialogSK
{
// ����
public:
	CPEGuarderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PEGUARDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CMyTabCtrl m_MyTabCtrl;  // �Զ���ѡ��ؼ��ı���
	CTrayIcon m_TrayIcon;  // ���̱���
	CIniFile m_iniFile;  // ��ʼ�������ļ�����

// ʵ��
protected:
	HICON m_hIcon;
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedMin();  // ��С����Ϣ
public:
	afx_msg void OnBnClickedTray();  // "��С������"��ť
public:
	afx_msg void OnFilePeguarder();  // �˵�"PE Guarder"
public:
	afx_msg void OnFileExit();  // �˵�" �˳�"
public:
	LRESULT OnTrayNotification(WPARAM wParam,LPARAM lParam);  // ������Ϣ
public:
	afx_msg void OnBnClickedSkin();  // "����"��ť
public:
	void SetSkin(CString skinPath);  // ����Ƥ��
};
