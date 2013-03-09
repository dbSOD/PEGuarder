// Detector.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder.h"
#include "Detector.h"
#include "VirusInfo.h"
#include "Set.h"

// CDetector �Ի���

IMPLEMENT_DYNAMIC(CDetector, CDialog)

CDetector::CDetector(CWnd* pParent /*=NULL*/)
	: CDialog(CDetector::IDD, pParent)
	, m_FileNum(0)
	, m_VirusNum(0)
	, m_Time(_T(""))
	, m_FileName(_T(""))
{
	m_Seconds = 0;  //  ���ݳ�ʼ��
}

CDetector::~CDetector()
{
	
}

void CDetector::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_FolderTreeCtrl);
	DDX_Text(pDX, IDC_FILENUM, m_FileNum);
	DDX_Text(pDX, IDC_VIRUSNUM, m_VirusNum);
	DDX_Text(pDX, IDC_TIME, m_Time);
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl2);
}


BEGIN_MESSAGE_MAP(CDetector, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BeginAndExit, &CDetector::OnBnClickedBeginandexit)
	ON_BN_CLICKED(IDC_SuspendAndResume, &CDetector::OnBnClickedSuspendandresume)
	ON_MESSAGE(UM_DisplayState, OnDisplayState)
	ON_BN_CLICKED(IDC_SET, &CDetector::OnBnClickedSet)
END_MESSAGE_MAP()


// CDetector ��Ϣ�������


// �Ի����ʼ������
//
BOOL CDetector::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_FolderTreeCtrl.DisplayTree();  // ��ʾ�ļ�����
	GetDlgItem(IDC_SuspendAndResume)->EnableWindow(FALSE);  // ����"��ͣ/�ָ�"��ť

	// �б�����������
	m_ListCtrl2.InsertColumn(0,"�ļ���",LVCFMT_LEFT,200);
	m_ListCtrl2.InsertColumn(1,"��в����",LVCFMT_LEFT,90);
	m_ListCtrl2.InsertColumn(2,"״̬",LVCFMT_LEFT,75);

	m_brush.CreateSolidBrush(RGB(255,255,255));  // ������ɫ��ˢ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


// �ı�Ի���Ϳؼ�����ɫ
//
HBRUSH CDetector::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


// ��ʱ������
//
void CDetector::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_Seconds++;  // ����һ��

	CString hours;
	hours.Format("%d",(m_Seconds/3600));
	if(hours.GetLength() == 1)
	{
		hours.Insert(0, "0");  // ��ʾΪ��λ
	}

	CString minutes;
	minutes.Format("%d", ((m_Seconds%3600)/60));
	if(minutes.GetLength() == 1)
	{
		minutes.Insert(0, "0");  // ��ʾΪ��λ
	}

	CString seconds;
	seconds.Format("%d", (m_Seconds%60));
	if(seconds.GetLength() == 1)
	{
		seconds.Insert(0, "0");  // ��ʾΪ��λ
	}

	// ��ʾʱ���ʽ����
	m_Time = hours + "Сʱ" + minutes + "��" + seconds + "��";

	UpdateData(FALSE);  // ����Ա������ʾ����Ӧ�Ĵ�����

	CDialog::OnTimer(nIDEvent);
}


// "��ʼ\ֹͣ"��ť
//
void CDetector::OnBnClickedBeginandexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString buttonText;
	GetDlgItemText(IDC_BeginAndExit, buttonText);  // ��ð�ť���ı�����  
	if(buttonText == "��ʼɨ��")
	{
		ThreadScanBegin();  // ��ʼɨ���߳�
	}
	else                    
	{
		ThreadScanExit();  // ֹͣɨ���߳�
	}
}


// "����\����"��ť
//
void CDetector::OnBnClickedSuspendandresume()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString buttonText;
	GetDlgItemText(IDC_SuspendAndResume, buttonText);  // ��ð�ť���ı�����
	if(buttonText == "��ͣɨ��")
	{
		ThreadScanSuspend();  // ��ͣɨ���߳�
	}
	else  
	{
		ThreadScanResume();  // �ָ�ɨ���߳�
	}   
}


// ������ʾ��ǰɨ�赽���ļ���Ϣ
// 
LRESULT CDetector::OnDisplayState(WPARAM wParam, LPARAM lParam)
{
	PCHAR szScanCode = (PCHAR)wParam;
	int nCode = atoi(szScanCode);  // �ַ���תΪ����
	if(nCode == -1)  // ɨ�����            
	{
		SetDlgItemText(IDC_BeginAndExit, "��ʼɨ��");  // ��ť��ʾΪ��ʼɨ��       
		GetDlgItem(IDC_TREE)->EnableWindow(TRUE);  // ����TreeCtrl
		GetDlgItem(IDC_SuspendAndResume)->EnableWindow(FALSE);  // ����"��ͣ/�ָ�"��ť
		KillTimer(1);  // �رռ�ʱ��
		MessageBox("ɨ�����!!!", "��ʾ", MB_OK);
	}
	else 
	{
		LPScanMessage pScanMessage = (LPScanMessage)lParam;
		m_FileName = pScanMessage->fileName;  // �ļ���(����·��)

		m_FileNum++;  // ɨ���ļ����ݼ�
		
		if(nCode > 0)  // ���ֲ���
		{
			m_VirusNum++;  // ����������
			
			// �б��
			m_ListCtrl2.InsertItem(0, "");  // ����һ��
			m_ListCtrl2.SetItemText(0, 0, m_FileName);  // �ļ���
			m_ListCtrl2.SetItemText(0, 1, CVirusInfo::GetNameByID(nCode));  // ��в����
			// ����ɹ����
			if(pScanMessage->bDisposed == TRUE)
			{
				m_ListCtrl2.SetItemText(0, 2, "����ɹ�");  // ״̬
			}
			else
			{
				m_ListCtrl2.SetItemText(0, 2, "����ʧ��");  // ״̬
			}
		}
		else if(nCode == -2)  // ��ʾδ֪��в
		{
			// �б��
			m_ListCtrl2.InsertItem(0, "");  // ����һ��
			m_ListCtrl2.SetItemText(0, 0, m_FileName);  // �ļ���
			m_ListCtrl2.SetItemText(0, 1, CVirusInfo::GetNameByID(nCode));  // ��в����
			m_ListCtrl2.SetItemText(0, 2, "δ����");  // ״̬
		}

		UpdateData(FALSE);  // ��ʾ��������
		delete pScanMessage;  // ���ָ����ָ����
	}

	delete szScanCode;  // ���ָ����ָ����
	return 0;
}


// ��ʼɨ���߳�
//
void CDetector::ThreadScanBegin()
{
	// ȡ�ñ�ѡ���·��
	CStringList *pListDir = new CStringList();
	m_FolderTreeCtrl.GetSelectedPath(*pListDir); 

	// ����ַ����б���û���ļ��У�����
	if(pListDir->GetCount() == 0)
	{
		MessageBox("��ѡ��ɨ���ļ���!!!", "ɨ���ļ�������", MB_OK);
		return;
	}

	CString showPath = "";
	// �����ַ����б�
	POSITION pos = pListDir->GetHeadPosition();  // ��ȡ�ַ����б��ͷԪ��  
	while(pos != NULL)
	{
		showPath += pListDir->GetNext(pos);
		showPath += "\n";
	}

	// ����ȷ�Ͽ�"ȷ��"������"ȡ��"����
	if (MessageBox(showPath, "ɨ��·��", MB_OKCANCEL) == IDCANCEL)
	{
		return;
	}

	// ���ݳ�ʼ��
	m_FileNum = 0;
	m_VirusNum = 0;
	m_Seconds = 0;
	m_Time = "";
	m_ListCtrl2.DeleteAllItems();

	UpdateData(FALSE);  // ����Ա������ʾ����Ӧ�Ĵ�����
	SetTimer(1, 1000, NULL);  // ��ʱ�������

	SetDlgItemText(IDC_BeginAndExit, "ֹͣɨ��");  //��ʼɨ�谴ť��ֹͣɨ��
	GetDlgItem(IDC_TREE)->EnableWindow(FALSE);  // ����TreeCtrl
	GetDlgItem(IDC_SuspendAndResume)->EnableWindow(TRUE);  // ����"��ͣ/�ָ�"��ť

	LPScanThreadParam pParam = new ScanThreadParam();  // ɨ���̲߳����ṹ
	pParam->hWnd = m_hWnd;  // ָ�������ھ��
	pParam->pListDir = pListDir;  // ָ���ַ����б�ָ��
	m_pThreadScan = AfxBeginThread(ScanThread, (LPVOID)pParam);  // ���������߳�  
}


// ��ֹɨ���߳�
//
void CDetector::ThreadScanExit()
{
	if(m_pThreadScan != NULL)
	{
		ThreadScanSuspend();  // �ȹ���ɨ���߳�

		if(MessageBox("ɨ����δ���,ȷ��ֹͣ��?", "ֹͣɨ��", MB_OKCANCEL) == IDOK)
		{
			DWORD dwExitCode;                       
			GetExitCodeThread(m_pThreadScan->m_hThread, &dwExitCode);  // �õ��߳̽�����
			TerminateThread(m_pThreadScan->m_hThread, dwExitCode);  // ��ֹ�߳�
			CloseHandle(m_pThreadScan->m_hThread);  // ɾ���߳� 

			SetDlgItemText(IDC_BeginAndExit, "��ʼɨ��");  // ֹͣɨ�谴ť�俪ʼɨ��
			SetDlgItemText(IDC_SuspendAndResume, "��ͣɨ��");  //  "��ͣ\�ָ�"��ť��ʾ��ͣɨ��
			GetDlgItem(IDC_SuspendAndResume)->EnableWindow(FALSE);  // ʹ"��ͣ\�ָ�"��ť���ɰ�
			GetDlgItem(IDC_TREE)->EnableWindow(TRUE);  // ʹ�����ؼ�
			return;
		}
		else
		{
			ThreadScanResume();  // ��������ɨ���߳�
		}
	}
}


// ����ɨ���߳�
//
void CDetector::ThreadScanSuspend()
{
	m_pThreadScan->SuspendThread();  // ����ɨ���߳�
	SetDlgItemText(IDC_SuspendAndResume, "�ָ�ɨ��");  //  "��ͣ\�ָ�"��ť��ʾ�ָ�ɨ��
	KillTimer(1);  // ֹͣ��ʱ��
}


// ��������ɨ���߳�
//
void CDetector::ThreadScanResume()
{ 
	m_pThreadScan->ResumeThread();  // ��������ɨ���߳�

	SetDlgItemText(IDC_SuspendAndResume, "��ͣɨ��");  //  "��ͣ\�ָ�"��ť��ʾ��ͣɨ��
	SetTimer(1, 1000, NULL);  // ������ʱ��
}


// ɨ���ļ��̺߳���
//
UINT CDetector::ScanThread(LPVOID pParam)
{
	// ���������
	CVirusDB VDB;
	VDB.Load();

	// ��������װ�ز�����
	CEngine engine;
	engine.Load(&VDB);

	BOOL bDisposed;  // �жϲ����Ƿ񱻴���ɹ�

	HWND hWnd = ((LPScanThreadParam)pParam)->hWnd;  // ���ھ��
	CStringList *pListDir = ((LPScanThreadParam)pParam)->pListDir;  // �ַ����б�ָ��
	delete pParam;  // ɾ����ָ����ָ����

	while(pListDir->GetCount() > 0)  // �ַ����б�Ϊ��             
	{
		POSITION pos = pListDir->GetHeadPosition();  // �ӵ�һ����㿪ʼ����
		CString& fileName = pListDir->GetAt(pos);  // ����ַ����б���ָ��λ�õ�ֵ

		// ���ó�x:\xx\*.*��ʽ
		if(fileName[fileName.GetLength()-1] != '\\')
		{
			fileName += "\\";
		}
		fileName += "*.*";

		WIN32_FIND_DATA findFileData;  // �˽ṹ���ڱ�ʾ�ҵ����ļ���Ŀ¼�������������Ϣ
		HANDLE hFindFile = ::FindFirstFile(fileName, &findFileData);  // ���ҵ�һ��Ŀ¼���ļ�����ȡ���Ҿ��
		if(hFindFile != INVALID_HANDLE_VALUE)  // �жϲ��Ҿ����Ч��
		{
			do  // ͬ����� 
			{
				// ������ '.' \ '..' (��ʾ��ǰĿ¼\�ϲ�Ŀ¼)��cFileName��������·��
				if(findFileData.cFileName[0] == '.')
				{
					continue;
				}

				// ��ΪĿ¼,������б�ǰ��
				if(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					CString dirName;  
					dirName.Format("%s", findFileData.cFileName);  // ��ʽ��Ŀ¼��
					dirName.Insert(0, fileName.Left(fileName.GetLength()-3));  // ƴ������·��

					pListDir->InsertAfter(pos, dirName);  // Ŀ¼�����б�
				}
				// ��Ϊ�ļ�����������в�������
				else  
				{
					CString filePath;  
					filePath.Format("%s", findFileData.cFileName);  // ��ʽ���ļ���
					filePath.Insert(0, fileName.Left(fileName.GetLength()-3));  // ƴ������·�� 
					PCHAR szScanCode = new CHAR[32];

					engine.Scan(filePath);  // ɨ��һ���ļ�
					int VID = engine.GetScanRecord().dwVirusID;  // ���ع�������ļ��ļ�¼
					
					// ���ֲ������ʹ���
					if(VID > 0)
					{
						if(engine.Dispose(filePath) == TRUE)
						{
							bDisposed = TRUE;  // ����ɹ�
						}
						else
						{
							bDisposed = FALSE;  // ����ʧ��
						}
					}
					else
					{
						bDisposed = TRUE;  // ���ǲ�����Ĭ�ϴ���ɹ�
					}

					// ɨ����Ϣ
					LPScanMessage pScanMessage = new ScanMessage;  
					pScanMessage->fileName = filePath;  // �ļ���(����·��)
					pScanMessage->bDisposed = bDisposed;  // ����ɹ����

					// wParamΪ0����ʾû�в�����wParam>0����ʾ�в�����Ϊ����ID��wParam=-2����ʾ����δ֪��в��
					_itoa_s(VID, szScanCode, 32, 10);  // ����ת��Ϊ�ַ��� 
					::SendMessage(hWnd, UM_DisplayState, (WPARAM)szScanCode, (LPARAM)pScanMessage);  // ������ʾ��Ϣ
				}
			}while(::FindNextFile(hFindFile, &findFileData));
		}

		::FindClose(hFindFile);  // �ر�FindFirstFile�������������
		pListDir->RemoveHead();  // ��Ŀ¼�������,ɾ��
	}

	pListDir->RemoveAll();  // ����ַ����б�
	delete pListDir;  // ɾ���ַ����б����

	engine.Release();  // �ͷ�ɨ���¼
	VDB.Unload();  // ж�ز�����

	PCHAR szScanCode = new CHAR[32];   // ֪ͨ���߳̽���ɨ��
	_itoa_s(-1, szScanCode, 32, 10);  // wParamΪ-1, ��ʾɨ�����������ת��Ϊ�ַ���
	::SendMessage(hWnd, UM_DisplayState, (WPARAM)szScanCode, NULL);  // ������ʾ��Ϣ�����ɨ��

	return 0;
}


// "����"��ť
//
void CDetector::OnBnClickedSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ����ģ̬�Ի���
	CSet set;
	set.DoModal();  
}
