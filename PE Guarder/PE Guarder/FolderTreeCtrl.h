#pragma once

#include "shlwapi.h"


// IDB_BMP_STATE״̬: 0->��ѡ��ť 1->û��ѡ�� 2->����ѡ�� 3->ȫ��ѡ��
enum CheckState{        
	NoCheckBox,  // ��ѡ���
	UnChecked,  // û��ѡ��
	PartChecked,  // ����ѡ��
	AllChecked  // ȫ��ѡ��
};

// �ýṹ���ڱ���һ���������Ϣ
typedef struct _TV_ItemData     
{
	LPITEMIDLIST lpi;  // ���PIDL
	LPITEMIDLIST lpifq;  // ȫPIDL
	LPSHELLFOLDER lpsfParent;  // ���ļ��е�IShellFolderָ��
}TVItemData, *LPTVItemData;


// CFolderTreeCtrl
// �����Լ����ļ�����
class CFolderTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CFolderTreeCtrl)

public:
	CFolderTreeCtrl();
	virtual ~CFolderTreeCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL DisplayTree();  // ��ʾ���νṹĿ¼
	void GetSelectedPath(CStringList& listSelectedPath);  // ȡ�ñ�ѡ���·��

private:
	// ��hParent�������nFolderָ���������ļ���
	HTREEITEM InsertSpecialFolder(int nFolder, HTREEITEM hParent);  

	void GetFileName(LPSHELLFOLDER psf, LPITEMIDLIST pidl, CString& fileName);  // ��ȡpidl��Ӧ�ļ��е���ʾ��
	int GetSmallIcon(LPITEMIDLIST pidl);  // ��ȡpidl��Ӧ�ļ���Сͼ��
	int GetSelectedIcon(LPITEMIDLIST pidl);  // ��ȡpidl��Ӧ�ļ��б�ѡ��ʱ��ͼ��

	void FillTreeCtrl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpifq, HTREEITEM hParent);  // �����

	// ��ITEMIDLISTת��Ϊ�ĵ�ϵͳ·��
	void GetPathFromIDList(HTREEITEM hNewItem, LPCITEMIDLIST pidlNew, CString fileName);  

	// ��ѡ��(ȡ��)ĳһ��ʱ,�Զ�ѡ��(ȡ��)��������(��)��(�ݹ�ʵ��)
	void SetChildItemState(HTREEITEM hItem, UINT uState);  
	// ��ѡ��(ȡ��)ĳһ��ʱ, �޸������и���״̬(�ݹ�ʵ��)
	void SetParentItemState(HTREEITEM hItem, UINT uState);  

	// ��ȡhItem����"ȫ��ѡ��"���ļ��е�·��,��listSelectedPath����(�ݹ�ʵ��)
	void GetSelectedPath(HTREEITEM hItem, CStringList& listSelectedPath);  

	// ���������������еĻص�����
	static int CALLBACK TreeViewCompareProc(LPARAM lparam1, LPARAM lparam2, LPARAM lparamSort);

private:
	CImageList m_ImgState;  // ѡ���ͼ�����
	HTREEITEM m_hDesktop;  // ��������
	CMap<HTREEITEM, HTREEITEM, CString, CString> m_mapFolderPath;  // ���<key=HTREEITEM, value=�ļ�·��>
	HTREEITEM m_hMyComputer;  // "�ҵĵ���"�ڵ�Ҫ���⴦��,��ΪSHGetPathFromIDList��ȡ·��Ϊ��

public:	
	// �������������CheckBox��"+"��ʱ,�赥������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	// ���չ������
	afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);
};


