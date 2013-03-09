#pragma once
#include "foldertreectrl.h"
#include "afxcmn.h"
#include "Engine.h"

#define UM_DisplayState WM_USER+2  // ��ʾɨ��״̬����Ϣ


// ɨ���̲߳����ṹ
typedef struct _ScanThreadParam
{
	HWND hWnd;  // ���ھ��
	CStringList *pListDir;  // �ַ����б�ָ��
}ScanThreadParam, *LPScanThreadParam;


// ɨ����Ϣ
typedef struct _ScanMessage
{
	CString fileName;  // �ļ���(����·��)
	BOOL bDisposed;  // ����ɹ����
}ScanMessage, *LPScanMessage;


// CDetector �Ի���

class CDetector : public CDialog
{
	DECLARE_DYNAMIC(CDetector)

public:
	CDetector(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDetector();

// �Ի�������
	enum { IDD = IDD_DETECTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

public:
	CFolderTreeCtrl m_FolderTreeCtrl;  // �ļ���������
	CListCtrl m_ListCtrl2;  // �б�����
	int m_FileNum;  // ɨ���ļ���
	int m_VirusNum;  // ���ֲ�����
	CString m_Time;  // ��ʾʱ��
	CString m_FileName;  // ��ʾ����ɨ���ļ�����
	DWORD m_Seconds;  // ɨ��ʱ������
	CWinThread* m_pThreadScan;  // ɨ���߳� 

private:
	CBrush m_brush;  // �Զ��廭ˢ

public:
	virtual BOOL OnInitDialog();  // �Ի����ʼ������
public:
	// �ı�Ի���Ϳؼ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	void ThreadScanBegin();  // ��ʼɨ���߳�
public:	
	void ThreadScanExit();  // ��ֹɨ���߳�
public:	
	void ThreadScanSuspend();  // ����ɨ���߳�
public:	
	void ThreadScanResume();  // ��������ɨ���߳�
public:
	static UINT ScanThread(LPVOID pParam);  // ɨ���ļ��̺߳���
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);  // ��ʱ������
public:
	afx_msg void OnBnClickedBeginandexit();  // "��ʼ\ֹͣ"��ť
public:
	afx_msg void OnBnClickedSuspendandresume();  // "����\����"��ť
public:
	// ������ʾ��ǰɨ�赽���ļ���Ϣ
	afx_msg LRESULT OnDisplayState(WPARAM wParam, LPARAM lParam);  
public:
	afx_msg void OnBnClickedSet();  // "����"��ť
};
