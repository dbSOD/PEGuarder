#pragma once

#define UM_UpdateState WM_USER+3  // ����״̬��Ϣ


// ��ʽ�ļ���Ϣ�ṹ
typedef struct _SOCKET_STREAM_FILE_INFO {
	CHAR cFileName[MAX_PATH];  // �ļ���           
	DWORD dwFileSize;  // �ļ���С            
} SOCKET_STREAM_FILE_INFO, *PSOCKET_STREAM_FILE_INFO;


// �����̲߳����ṹ
typedef struct _UpdateDBThreadParam {
	CString strIP;  // IP
	UINT uiPort;  // �˿�
	HWND hWnd;  // ���ھ��
	CString strSavePath;  // ����·��
} UpdateDBThreadParam, *PUpdateDBThreadParam;


// CDBUpdate �Ի���

class CDBUpdate : public CDialog
{
	DECLARE_DYNAMIC(CDBUpdate)

public:
	CDBUpdate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDBUpdate();

// �Ի�������
	enum { IDD = IDD_DBUPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();  // �Ի����ʼ������
public:
	// �ı�Ի���Ϳؼ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnBnClickedStartupdate();  // ��ʼ���°�ť�¼�
public:
	afx_msg void OnBnClickedStopupdate();  // ֹͣ���°�ť�¼�
public:
	static UINT UpdateDBThread(LPVOID pParam);  // ���²������߳�
public:
	afx_msg LRESULT OnUpdateState(WPARAM wParam, LPARAM lParam);  // ����״̬��Ϣ  

private:
	CWinThread* m_pUpdateThread;  // �����߳�
	CBrush m_brush;  // �Զ��廭ˢ	
};


