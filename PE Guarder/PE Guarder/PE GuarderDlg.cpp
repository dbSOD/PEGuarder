// PE GuarderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder.h"
#include "PE GuarderDlg.h"
#include "SystemController.h"
#include "Skin.h"

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


// CPEGuarderDlg �Ի���




CPEGuarderDlg::CPEGuarderDlg(CWnd* pParent /*=NULL*/)
	: CDialogSK(CPEGuarderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPEGuarderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSK::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_MyTabCtrl);
}

BEGIN_MESSAGE_MAP(CPEGuarderDlg, CDialogSK)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MIN, &CPEGuarderDlg::OnBnClickedMin)
	ON_BN_CLICKED(IDC_TRAY, &CPEGuarderDlg::OnBnClickedTray)
	ON_COMMAND(ID_FILE_PEGUARDER, &CPEGuarderDlg::OnFilePeguarder)
	ON_COMMAND(ID_FILE_EXIT, &CPEGuarderDlg::OnFileExit)
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_BN_CLICKED(IDC_SKIN, &CPEGuarderDlg::OnBnClickedSkin)
END_MESSAGE_MAP()


// CPEGuarderDlg ��Ϣ�������

BOOL CPEGuarderDlg::OnInitDialog()
{
	CDialogSK::OnInitDialog();

	// ����Բ�ǶԻ���
	CRect dialogRect; 
	GetClientRect(&dialogRect); 
	CRgn rgn; 
	rgn.CreateRoundRectRgn(0,0,dialogRect.Width(),dialogRect.Height(),20,20); 
	SetWindowRgn(rgn,TRUE); 

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

	CString iniFileName;  // ini�ļ�·������
	GetModuleFileName(NULL, iniFileName.GetBuffer(MAX_PATH), MAX_PATH);  // ��õ�ǰӦ�ó���·��
	iniFileName.ReleaseBuffer();  // һ��Ҫ�ͷţ������޷�ƴ��
	iniFileName = iniFileName.Left(iniFileName.ReverseFind('\\'));  // ȥ����ǰӦ�ó�����
	iniFileName = iniFileName + "\\bin\\set.ini";  // ƴ�ӳ�ini�ļ�·��  
	m_iniFile.SetIniFileName(iniFileName);  // ����ini�ļ�·��

	CString skinPath;  // Ƥ��·��
	m_iniFile.ReadIni("SET", "SKIN", skinPath);  // ��ȡini�ļ��е�Ƥ��·��

	// ����ļ�·��������Ч�ģ�������Ĭ��Ƥ��
	CFileFind fileFind;
	if(!fileFind.FindFile(skinPath))
	{
		skinPath = iniFileName;
		skinPath = skinPath.Left(skinPath.ReverseFind('\\'));  // ȥ�������ļ���
		skinPath = skinPath + "\\bk1.bmp";
		SetBitmap(skinPath);  // ����Ĭ�ϱ���
	}
	else
	{
		SetBitmap(skinPath);  // ���ñ���
	}
	fileFind.Close();  // �ر��ļ����ң��ͷ���Դ

	EnableEasyMove();  // �����κ�λ�ö����ƶ��Ի���
	SetStyle(LO_RESIZE);  // ���öԻ�����Ӧλͼ
	SetTransparentColor(RGB(0, 255, 0));  // ������ɫ��Ϊ͸��ɫ

	// �Զ���ѡ����������ǩ��
	m_MyTabCtrl.InsertItem(0, "PE �ļ�������");
	m_MyTabCtrl.InsertItem(1, "PE ���������");
	m_MyTabCtrl.InsertItem(2, "��   ��");

	// ������������ģʽ���Ի���
	CAnalyser* m_A = new CAnalyser();
	m_MyTabCtrl.m_pAnalyser = m_A;
	m_A->Create(IDD_ANALYSER, &m_MyTabCtrl);

	// �����������ģʽ���Ի���
	CDetector* m_D = new CDetector();
	m_MyTabCtrl.m_pDetector = m_D;
	m_D->Create(IDD_DETECTOR, &m_MyTabCtrl);

	// �������߷�ģʽ���Ի���
	CTool* m_T = new CTool();
	m_MyTabCtrl.m_pTool = m_T;
	m_T->Create(IDD_TOOL, &m_MyTabCtrl);

	// ���ó�ʼ�ͻ�����ǩ����
	CRect tabRect;
	m_MyTabCtrl.GetClientRect(tabRect);
	tabRect.DeflateRect(1,20,2,2);
	m_D->ShowWindow(SW_HIDE);
	m_T->ShowWindow(SW_HIDE);
	m_A->MoveWindow(tabRect);
	m_A->ShowWindow(SW_SHOW);

	if(!CSystemController::SetReg("*\\shell\\PE Guarder\\Command"))
	{
		MessageBox("ע������ô���", "��ʾ", MB_OK);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPEGuarderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogSK::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPEGuarderDlg::OnPaint()
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
		CDialogSK::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CPEGuarderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ��С����Ϣ
//
void CPEGuarderDlg::OnBnClickedMin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(0, 0));  // ������С����Ϣ
}


// "��С������"��ť
//
void CPEGuarderDlg::OnBnClickedTray()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_TrayIcon.Create(this,WM_ICON_NOTIFY,"PE Guarder����������",m_hIcon,IDR_MENU);  // ����
	ShowWindow(SW_HIDE);  // ���ش���
}


// �˵�"PE Guarder"
//
void CPEGuarderDlg::OnFilePeguarder()
{
	// TODO: �ڴ���������������

	m_TrayIcon.RemoveIcon();
	ShowWindow(SW_SHOW);
}


// �˵�" �˳�"
//
void CPEGuarderDlg::OnFileExit()
{
	// TODO: �ڴ���������������

	m_TrayIcon.RemoveIcon();
	OnCancel();
}


// ������Ϣ
//
LRESULT CPEGuarderDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	return m_TrayIcon.OnTrayNotification(wParam,lParam);
}


// "����"��ť
//
void CPEGuarderDlg::OnBnClickedSkin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��Ƥ���Ի���
	CSkin skin;
	skin.DoModal();
}


// ����Ƥ��
//
void CPEGuarderDlg::SetSkin(CString skinPath)
{
	SetBitmap(skinPath);  // ����Ƥ��(λͼ)

	// д��ini�ļ�Ƥ��·��
	m_iniFile.WriteIni("SET", "SKIN", skinPath);
}