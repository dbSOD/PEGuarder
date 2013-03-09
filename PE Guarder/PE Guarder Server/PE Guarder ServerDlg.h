// PE Guarder ServerDlg.h : ͷ�ļ�
//

#pragma once

#define UM_UpdateState WM_USER+1  // ����״̬��Ϣ


// ��ʽ�ļ���Ϣ�ṹ
typedef struct _SOCKET_STREAM_FILE_INFO {
	CHAR cFileName[MAX_PATH];  // �ļ���           
	DWORD dwFileSize;  // �ļ���С            
} SOCKET_STREAM_FILE_INFO, *PSOCKET_STREAM_FILE_INFO;


// �����̲߳����ṹ
typedef struct _UpdateDBThreadParam {
	SOCKET_STREAM_FILE_INFO streamFileInfo;  // ��ʽ�ļ���Ϣ
	CString strFilePath;  // �ļ�·��
	UINT uiPort;  // �˿�
	HWND hWnd;  // ���ھ��
} UpdateDBThreadParam, *PUpdateDBThreadParam;


// CPEGuarderServerDlg �Ի���
class CPEGuarderServerDlg : public CDialog
{
// ����
public:
	CPEGuarderServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PEGUARDERSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	// �ı�Ի���Ϳؼ�����ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnBnClickedSelectfile();  // ѡ������ļ���ť�¼�
public:
	afx_msg void OnEnChangeFilepath();  // �ļ�·����䶯�¼�
public:
	afx_msg void OnBnClickedStartupdate();  // ��ʼ���°�ť�¼�
public:
	static UINT UpdateDBThread(LPVOID pParam);  // ���²������߳�
public:
	afx_msg LRESULT OnUpdateState(WPARAM wParam, LPARAM lParam);  // ����״̬��Ϣ  

private:
	CString m_FilePath;  // �����ļ�·��
	CWinThread* m_pUpdateThread;  // �����߳�
	CBrush m_brush;  // �Զ��廭ˢ
};
