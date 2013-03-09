// DBUpdate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder.h"
#include "DBUpdate.h"

BOOL gThreadController;  // �߳̿����ߣ�ȫ�ֱ���


// CDBUpdate �Ի���

IMPLEMENT_DYNAMIC(CDBUpdate, CDialog)

CDBUpdate::CDBUpdate(CWnd* pParent /*=NULL*/)
	: CDialog(CDBUpdate::IDD, pParent)
{
}

CDBUpdate::~CDBUpdate()
{
	gThreadController = TRUE;  // �������ã���ȫ�����߳�
}

void CDBUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDBUpdate, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_STARTUPDATE, &CDBUpdate::OnBnClickedStartupdate)
	ON_MESSAGE(UM_UpdateState, OnUpdateState)
	ON_BN_CLICKED(IDC_STOPUPDATE, &CDBUpdate::OnBnClickedStopupdate)
END_MESSAGE_MAP()


// CDBUpdate ��Ϣ�������


// �Ի����ʼ������
//
BOOL CDBUpdate::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_brush.CreateSolidBrush(RGB(255,255,255));  // ������ɫ��ˢ

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


// �ı�Ի���Ϳؼ�����ɫ
//
HBRUSH CDBUpdate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


// ��ʼ���°�ť�¼�
//
void CDBUpdate::OnBnClickedStartupdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString savePath;  // �ļ�����·������
	GetModuleFileName(NULL, savePath.GetBuffer(MAX_PATH), MAX_PATH);  // ��õ�ǰӦ�ó���·��
	savePath.ReleaseBuffer();  // �ͷŻ���
	savePath = savePath.Left(savePath.ReverseFind('\\'));  // ȥ����ǰӦ�ó�����
	savePath = savePath + "\\bin\\";  // ƴ�ӳɱ���Ŀ¼ 

	CString ip;
	GetDlgItemText(IDC_IP, ip);  // �õ�������IP��ַ
	UINT port = GetDlgItemInt(IDC_PORT);  // �õ��������˿ں�

	PUpdateDBThreadParam pParam = new UpdateDBThreadParam;  // �����̲߳����ṹ
	pParam->strIP = ip;  // IP
	pParam->uiPort = port;  // �˿�
	pParam->hWnd = m_hWnd;  // ���ھ��
	pParam->strSavePath = savePath;  // ����·��

	GetDlgItem(IDC_STARTUPDATE)->EnableWindow(FALSE);  // ���ÿ�ʼ���°�ť

	gThreadController = FALSE;  // ����������
	m_pUpdateThread = AfxBeginThread(UpdateDBThread, (LPVOID)pParam);  // ��ʼ�����߳�
}


// ֹͣ���°�ť�¼�
//
void CDBUpdate::OnBnClickedStopupdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	gThreadController = TRUE;  // ��������

	GetDlgItem(IDC_STARTUPDATE)->EnableWindow(TRUE);  // ���ÿ�ʼ���°�ť
}


// ���²������߳�
//
UINT CDBUpdate::UpdateDBThread(LPVOID pParam)
{
	// ��������
	CString ip = ((PUpdateDBThreadParam)pParam)->strIP;
	UINT port = ((PUpdateDBThreadParam)pParam)->uiPort;
	HWND hWnd = ((PUpdateDBThreadParam)pParam)->hWnd;
	CString savePath = ((PUpdateDBThreadParam)pParam)->strSavePath;
	delete pParam;

	CSocket sockClient;  // �ͻ����׽���
	sockClient.Create();  // �˿��ɳ���ָ��
	
	// ���ӵ�ָ���׽���
	if(sockClient.Connect(ip, port) == FALSE)
	{
		::SendMessage(hWnd, UM_UpdateState, 0, NULL);  //  ����ʧ��
		sockClient.Close();  // �ͻ����׽��ֹر�
		return 0;
	}

	SOCKET_STREAM_FILE_INFO streamFileInfo;  // ���ļ���Ϣ�ṹ
	sockClient.Receive(&streamFileInfo, sizeof(SOCKET_STREAM_FILE_INFO));  // ���շ���������������

	savePath = savePath + streamFileInfo.cFileName;  // ��������·��

	// �����ļ�
	CFile file(savePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	DWORD dwRead = 0;  // �Ѿ���ȡ��������
	DWORD dwReal = 0;  // ÿ��������ȡ��������

	// ���������ļ����ݲ��ֶ�(1KB)д���ļ�
	while(dwRead < streamFileInfo.dwFileSize)
	{
		// ����з��յ�����֪ͨ
		if(gThreadController == TRUE)
		{
			file.Close();  // �ļ�����ر�
			sockClient.Close();  // �ͻ����׽��ֹر�
			return 0;
		}
		LPBYTE pSegment = new BYTE[1024];  // ����1KB�Ŀռ�
		dwReal = sockClient.Receive(pSegment, 1024);  // ���ļ�1KB��С��1KB�����ݷ��������ռ䣬����ʵ��ֵ
		file.Write(pSegment, dwReal);  // ����д���ļ� 
		dwRead += dwReal;  // �Ѷ���������
		delete pSegment;  // ��տռ�
	}

	file.Close();  // �ļ�����ر�
	sockClient.Close();  // �ͻ����׽��ֹر�

	::SendMessage(hWnd, UM_UpdateState, 1, NULL);  // ���³ɹ�

	return 0;
}


// ����״̬��Ϣ
//
LRESULT CDBUpdate::OnUpdateState(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_STARTUPDATE)->EnableWindow(TRUE);  // ���ÿ�ʼ���°�ť

	if(wParam == 1)
	{
		MessageBox("���³ɹ���");
	}
	else
	{
		MessageBox("���ӷ�����ʧ�ܣ����Ժ����ԣ�");
	}

	return 0;
}

