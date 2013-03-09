// PE Guarder ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder Server.h"
#include "PE Guarder ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPEGuarderServerDlg �Ի���




CPEGuarderServerDlg::CPEGuarderServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPEGuarderServerDlg::IDD, pParent)
	, m_FilePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPEGuarderServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILEPATH, m_FilePath);
}

BEGIN_MESSAGE_MAP(CPEGuarderServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SELECTFILE, &CPEGuarderServerDlg::OnBnClickedSelectfile)
	ON_EN_CHANGE(IDC_FILEPATH, &CPEGuarderServerDlg::OnEnChangeFilepath)
	ON_BN_CLICKED(IDC_STARTUPDATE, &CPEGuarderServerDlg::OnBnClickedStartupdate)
	ON_MESSAGE(UM_UpdateState, OnUpdateState)
END_MESSAGE_MAP()


// CPEGuarderServerDlg ��Ϣ�������

BOOL CPEGuarderServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CHAR hostName[128];  // ����������   
	gethostname(hostName, 128);  // ���������  
	hostent* pHost = gethostbyname(hostName);  // ��������ṹ  
	CString ip = inet_ntoa(*((in_addr*)pHost->h_addr));  // ��ñ���IP
	SetDlgItemText(IDC_IP, ip);  // ��ʾ����IP

	m_brush.CreateSolidBrush(RGB(255,255,255));  // ������ɫ��ˢ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPEGuarderServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPEGuarderServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CPEGuarderServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �ı�Ի���Ϳؼ�����ɫ
//
HBRUSH CPEGuarderServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
	if(nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(RGB(255,255,255));  // ���ÿؼ�����ɫ����ɫ��
		return m_brush;  // �����Զ���Ļ�ˢ���
	}
	return hbr;  // ����Ļ�����ϵͳĬ�ϵĻ�ˢ���
}


// ѡ������ļ���ť�¼�
//
void CPEGuarderServerDlg::OnBnClickedSelectfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// �������ļ��Ի������
	CFileDialog fileDialog(TRUE);
	// ���ѡ��ȡ����ťʱ
	if(fileDialog.DoModal() != IDOK)
	{
		return;
	}

	m_FilePath = fileDialog.GetPathName();  // �õ��ļ�·��

	UpdateData(FALSE);  // ͬ���Ի���
}


// �ļ�·����䶯�¼�
//
void CPEGuarderServerDlg::OnEnChangeFilepath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);  // ͬ���Ի���
}


// ��ʼ���°�ť�¼�
//
void CPEGuarderServerDlg::OnBnClickedStartupdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UINT port = GetDlgItemInt(IDC_PORT);  // �õ��˿ں�

	// ������
	if(m_FilePath.Trim() == "")
	{
		MessageBox("·������Ϊ�պͿ��ַ���");
		return;
	}
	if(port < 1 || port > 65535)
	{
		MessageBox("�˿ڲ�����Ч�ķ�Χ�ڣ�");
		return;
	}

	// ����ļ�·��������Ч��
	CFileFind fileFind;
	if(!fileFind.FindFile(m_FilePath))
	{
		MessageBox("������Ч���ļ�·����");
		fileFind.Close();  // �ر��ļ����ң��ͷ���Դ
		return;
	}
	fileFind.Close();  // �ر��ļ����ң��ͷ���Դ

	WIN32_FIND_DATA findData;  // �ļ���Ϣ�ṹ
	::FindClose(::FindFirstFile(m_FilePath, &findData));  // �ҵ��ļ�������Ϣ���������ṹ

	PUpdateDBThreadParam pParam = new UpdateDBThreadParam();  // �����̲߳����ṹ

	strcpy_s(pParam->streamFileInfo.cFileName, findData.cFileName);  // �ļ���
	pParam->streamFileInfo.dwFileSize = findData.nFileSizeLow;  // �ļ���С

	pParam->strFilePath = m_FilePath;  // �ļ�·��
	pParam->uiPort = port;  // �˿�
	pParam->hWnd = m_hWnd;  // ���ھ��
	
	GetDlgItem(IDC_STARTUPDATE)->EnableWindow(FALSE);  // ���ÿ�ʼ���°�ť

	m_pUpdateThread = AfxBeginThread(UpdateDBThread, (LPVOID)pParam);  // ��ʼ�����߳�
}


// ���²������߳�
//
UINT CPEGuarderServerDlg::UpdateDBThread(LPVOID pParam)
{
	// ��������
	SOCKET_STREAM_FILE_INFO streamFileInfo = ((PUpdateDBThreadParam)pParam)->streamFileInfo;
	CString filePath = ((PUpdateDBThreadParam)pParam)->strFilePath;
	UINT port = ((PUpdateDBThreadParam)pParam)->uiPort;
	HWND hWnd = ((PUpdateDBThreadParam)pParam)->hWnd;
	delete pParam;

	CSocket sockServ;  // �������׽���
	sockServ.Create(port);  // �˿�����
	sockServ.Listen();  // ��ʼ����

	CSocket sockRecv;  // �����׽���	
	sockServ.Accept(sockRecv);  // �󶨽����׽��ֺͷ������׽���

	// �ȷ�һ��֪ͨ��Ϣ���ͻ��ˣ���֪Ӧ�ÿ��ٶ��Ŀռ��������ļ�
	sockRecv.Send(&streamFileInfo, sizeof(SOCKET_STREAM_FILE_INFO));  

	// ���ļ���ֻ���Ͷ�����
	CFile file;
	BOOL bOpen = file.Open(filePath, CFile::modeRead | CFile::typeBinary);  

	if(bOpen == TRUE)
	{
		DWORD dwRead = 0;  // �Ѿ���ȡ��������
		DWORD dwReal = 0;  // ÿ��������ȡ��������

		// ��ȡ�����ļ����ݲ��ֶ�(1KB)����
		while(dwRead < streamFileInfo.dwFileSize)
		{
			LPBYTE pSegment = new BYTE[1024];  // ����1KB�Ŀռ�
			dwReal = file.Read(pSegment, 1024);  // ���ļ�1KB��С��1KB�����ݷ��������ռ䣬����ʵ��ֵ
			sockRecv.Send(pSegment, dwReal);  // ���ʹ˿ռ��е�����
			dwRead += dwReal;  // �Ѷ���������
			delete pSegment;  // ��տռ�
		}

		file.Close();  // �ļ�����ر�
		sockRecv.Close();  // �����׽��ֹر�
		sockServ.Close();  // �������׽��ֹر�
		::SendMessage(hWnd, UM_UpdateState, 1, NULL);  // ���³ɹ�
	}
	else
	{
		sockRecv.Close();  // �����׽��ֹر�
		sockServ.Close();  // �������׽��ֹر�
		::SendMessage(hWnd, UM_UpdateState, 0, NULL);  // ����ʧ��
	}

	return 0;
}


// ����״̬��Ϣ
//
LRESULT CPEGuarderServerDlg::OnUpdateState(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_STARTUPDATE)->EnableWindow(TRUE);  // ���ÿ�ʼ���°�ť
	
	if(wParam == 1)
	{
		MessageBox("���³ɹ���");
	}
	else
	{
		MessageBox("����ʧ�ܣ�");
	}

	return 0;
}