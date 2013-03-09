// Tool.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder.h"
#include "Tool.h"
#include "SystemController.h"

// CTool �Ի���

IMPLEMENT_DYNAMIC(CTool, CDialog)

CTool::CTool(CWnd* pParent /*=NULL*/)
	: CDialog(CTool::IDD, pParent)
	, m_FilePath(_T(""))
{

}

CTool::~CTool()
{
}

void CTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILEPATH, m_FilePath);
	DDX_Control(pDX, IDC_SHATTER, m_Shatter);
	DDX_Control(pDX, IDC_SHATTERPROGRESS, m_ShatterProgress);
}


BEGIN_MESSAGE_MAP(CTool, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BROWSE, &CTool::OnBnClickedBrowse)
	ON_EN_CHANGE(IDC_FILEPATH, &CTool::OnEnChangeFilepath)
	ON_BN_CLICKED(IDC_DELETE, &CTool::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_SHATTER, &CTool::OnBnClickedShatter)
END_MESSAGE_MAP()


// CTool ��Ϣ�������


// �Ի����ʼ������
//
BOOL CTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_brush.CreateSolidBrush(RGB(255,255,255));  // ������ɫ��ˢ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


// �ı�Ի���Ϳؼ�����ɫ
//
HBRUSH CTool::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


// �����ť��Ϣ
//
void CTool::OnBnClickedBrowse()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_ShatterProgress.SetPos(0);  // ���ý�����
	SetDlgItemText(IDC_STATICDIGITAL,"");  // ����˵���ı����ʼ��

	// �������ļ��Ի������
	CFileDialog fileDialog(TRUE,NULL,NULL,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY,"All File(*.*)|*.*||",this);
	// ����ģʽ���Ի�����������ȡ������ť��
	// �򲻼���ִ�к�������
	if (fileDialog.DoModal() != IDOK)
	{
		return;
	}

	m_FilePath = fileDialog.GetPathName();  // ����ļ�·��
	
	// �ļ�·���ؼ���ʾ��ǰ�ļ�·��
	UpdateData(FALSE);
	// ����ļ���С
	GetFileSize();
}


// ·���ı���䶯��Ϣ
//
void CTool::OnEnChangeFilepath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	// ���ı��༭������ݸ�ֵ��·������
	UpdateData(TRUE);
	GetFileSize();  // ����ļ���С

	m_ShatterProgress.SetPos(0);  // ���ý�����
	// ����˵���ı�������
	SetDlgItemText(IDC_STATICDIGITAL,"");  
}


// ɾ����ť��Ϣ
//
void CTool::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ����ļ�·��������Ч�ģ�������Ӧ
	CFileFind fileFind;
	if(!fileFind.FindFile(m_FilePath))
	{
		MessageBox("������Ч���ļ�·����", "��ʾ", MB_OK);
		fileFind.Close();  // �ر��ļ����ң��ͷ���Դ
		return;
	}
	fileFind.Close();  // �ر��ļ����ң��ͷ���Դ

	// �����ļ�����(ȡ��ֻ������)
	if(!CSystemController::FileAttributesOperation(m_FilePath))
	{
		MessageBox("�ļ���������ʧ�ܣ�", "��ʾ", MB_OK);
		return;
	}

	// ����ϵͳ��ɾ���ļ�
	if(::MoveFileEx(m_FilePath,NULL,MOVEFILE_DELAY_UNTIL_REBOOT))
	{
		// ������ʾ��
		if (MessageBox("Ҫ���ɾ�����������������ԣ��Ƿ�����������", "��ʾ", MB_YESNO) == IDNO)
		{
			MessageBox("���Ժ���������!", "��ʾ", MB_OK);
		}
		else  // ����ϵͳ
		{
			CSystemController::RebootSystem();
		}
	}
	else
	{
		MessageBox("ɾ���ļ�ʧ��", "��ʾ", MB_OK);
	}
}


// ���鰴ť��Ϣ
//
void CTool::OnBnClickedShatter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ����ļ�·��������Ч�ģ�������Ӧ
	CFileFind fileFind;
	if(!fileFind.FindFile(m_FilePath))
	{
		MessageBox("������Ч���ļ�·����", "��ʾ", MB_OK);
		fileFind.Close();  // �ر��ļ����ң��ͷ���Դ
		return;
	}
	fileFind.Close();  // �ر��ļ����ң��ͷ���Դ

	// �����ļ�����(ȡ��ֻ������)
	if(!CSystemController::FileAttributesOperation(m_FilePath))
	{
		MessageBox("�ļ���������ʧ�ܣ�", "��ʾ", MB_OK);
		return;
	}

	::EnableWindow(m_Shatter, FALSE);  // ���鰴ť���ɫ�Ҳ�����

	// �����̣߳������ؾ��
	HANDLE hThread = CreateThread(NULL, 0, MyShatterThread, this, 0, NULL);
	// ����̴߳���ʧ���򷵻�
	if(hThread == NULL)
	{
		MessageBox("�̴߳�������","��ʾ",MB_OK);
		return;
	}
}


// ���ָ���ļ���С
//
void CTool::GetFileSize()
{
	// ��ָ���ļ���������Ӧ���
	HANDLE hHandle = ::CreateFile(m_FilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
	// ͨ�����صľ���õ��ļ���С
	if(hHandle == INVALID_HANDLE_VALUE)
	{
		m_FileSize = 0;	 
	}
	else
	{
		m_FileSize = ::GetFileSize(hHandle, NULL); 
	}
	CloseHandle(hHandle);  // �رվ�� 
}


// �Զ����̺߳���
//
DWORD WINAPI MyShatterThread(LPVOID lpParameter)
{
	CTool *pTool = (CTool *)lpParameter;  // ��������ת��

	FILE *pWrite;  // �ļ�дָ��
	// �Զ����ƿ�д��ʽ���ļ�,�Ƚ��򿪵��ļ�������գ�
	// ������д����
	fopen_s(&pWrite, pTool->m_FilePath, "wb");
	// �����ļ�ָ��λ��Ϊ�ļ�ͷ
	fseek(pWrite, 0, SEEK_SET);

	// ����ļ�ָ�봴��ʧ�ܣ��򷵻�0
	if(pWrite == NULL)
	{
		return 0;
	}

	DWORD cout = pTool->m_FileSize/100;  // �̣������ļ�ÿ�ٷ�֮һ�Ĵ�С
	DWORD mod = pTool->m_FileSize%100;  // ����
	// ���ý������ؼ��ķ�Χ
	pTool->m_ShatterProgress.SetRange(0,100);
	DWORD ByteWritten=0;  // ��¼���޸ĵ��ֽ���
	CString strProgress;  // ������ʾ���ȵ��ַ���

	// ��ʾ����
	for (DWORD j=1;j<=100;j++)
	{
		for (DWORD k=1;k<=cout;k++)
		{
			// д��0
			fputc(0,pWrite);
			// ��¼���޸ĵ��ֽ���
			ByteWritten++;
		}
		// ��������ʾ����
		pTool->m_ShatterProgress.SetPos(j);
		strProgress.Format("%d%s",j,"%");
		// �����ı�����ʾ����
		pTool->SetDlgItemText(IDC_STATICDIGITAL,strProgress);
	}

	// �������µ��ֽ�
	for (DWORD y=1;y<=mod;y++)
	{
		// д��0
		fputc(0,pWrite);
		// ��¼���޸ĵ��ֽ���
		ByteWritten++;
	}

	fclose(pWrite);  // �ر��ļ�дָ��

	if (ByteWritten == pTool->m_FileSize) 
	{
		// ʹ�ܷ��鰴ť���ָ�����
		::EnableWindow(pTool->m_Shatter,TRUE);
	}

	return 1;
}