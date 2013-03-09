// FolderTreeCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PE Guarder.h"
#include "FolderTreeCtrl.h"
#include "ShellOperator.h"  // �����pidl�Ĳ���ͷ�ļ�

// CFolderTreeCtrl

IMPLEMENT_DYNAMIC(CFolderTreeCtrl, CTreeCtrl)

CFolderTreeCtrl::CFolderTreeCtrl()
{

}

CFolderTreeCtrl::~CFolderTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CFolderTreeCtrl, CTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, &CFolderTreeCtrl::OnTvnItemexpanded)
END_MESSAGE_MAP()



// CFolderTreeCtrl ��Ϣ�������


// �������������CheckBox��"+"��ʱ,�赥������
//
void CFolderTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	UINT uFlags;
	HTREEITEM hItem = HitTest(point, &uFlags);  // ��ȡ���λ�ò�������Ӧ�����

	if(uFlags & TVHT_ONITEMSTATEICON )  // �������ѡ�����
	{            
		UINT uState = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12;  // ��ȡ���״̬
		
		if(uState == PartChecked)  // ������Ϊ����ѡ��״̬,����Ϊȫ��ѡ��
		{
			uState = AllChecked;
		}
		else if(uState == UnChecked)  // ������Ϊδѡ��״̬,����Ϊȫ��ѡ��
		{
			uState = AllChecked;
		}
		else if(uState == AllChecked)  // ������Ϊȫ��ѡ��״̬,����Ϊδѡ��
		{
			uState = UnChecked;
		}

		SetItemState(hItem, INDEXTOSTATEIMAGEMASK(uState), TVIS_STATEIMAGEMASK);  // ���ý��״̬
		SetChildItemState(hItem, uState);  // ���������ӽ��״̬
		SetParentItemState(hItem, uState);  //  �������и����״̬
	}
	else if(uFlags & TVHT_ONITEMBUTTON)  // �����������������İ�ť"+"��  
	{                                       
		// �����Ȳ���һ��,չ������ɾ��
		HTREEITEM hTempItem = InsertItem("*.*", hItem);
		CTreeCtrl::OnLButtonDown(nFlags, point);
		DeleteItem(hTempItem);
	}
	else
	{
		CTreeCtrl::OnLButtonDown(nFlags, point);  // ϵͳ�Զ����
	}
}


// ���չ������
//
void CFolderTreeCtrl::OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ����չ����,���ٴ���
	if(pNMTreeView->itemNew.state & TVIS_EXPANDEDONCE)   
	{
		return;
	}

	LPTVItemData pItemData = (LPTVItemData)pNMTreeView->itemNew.lParam;
	if(pItemData != NULL)
	{
		LPSHELLFOLDER psfNew;
		// ��ȡ��ǰIShellFolder�ӿڵ�lpi��ָ��IShellFolder�ӿڣ�psfNew���ռ������Ľӿ�ָ��
		pItemData->lpsfParent->BindToObject(pItemData->lpi, 0, IID_IShellFolder, (LPVOID*)&psfNew);
		// �����
		FillTreeCtrl(psfNew, pItemData->lpifq, pNMTreeView->itemNew.hItem);

		// ��������Ŀ�Ľṹ
		TVSORTCB tvSortCB;
		tvSortCB.hParent = pNMTreeView->itemNew.hItem;
		tvSortCB.lpfnCompare = TreeViewCompareProc;
		tvSortCB.lParam  = NULL;
		
		// ʹ����Ӧ�ó������������TreeViewCompareProc����������
		SortChildrenCB(&tvSortCB); 
	}

	*pResult = 0;
}


// ��ʾ���νṹĿ¼
//
BOOL CFolderTreeCtrl::DisplayTree()
{
	// ��ȡϵͳСͼ����
	SHFILEINFO shFileInfo;
	HIMAGELIST hSysSmallImgList = (HIMAGELIST)SHGetFileInfo("c:\\", 0, &shFileInfo, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	// ��ϵͳСͼ�����󶨵�TreeCtrl ��
	if(hSysSmallImgList != NULL)
	{
		::SendMessage(m_hWnd, TVM_SETIMAGELIST, (WPARAM) TVSIL_NORMAL, (LPARAM) hSysSmallImgList);
	}
	else
	{
		return FALSE;
	} 

	// ѡ���ͼ������
	m_ImgState.Create(IDB_BMP_STATE, 13, 0, RGB(255,255,255));
	SetImageList(&m_ImgState, TVSIL_STATE);

	// ����"����"��Ϊ�������
	m_hDesktop = InsertSpecialFolder(CSIDL_DESKTOP, TVI_ROOT);
	// ������������ѡ���
	SetItemState(m_hDesktop, INDEXTOSTATEIMAGEMASK(NoCheckBox), TVIS_STATEIMAGEMASK);

	// ����һ�������ļ��е�IShellFolder�ӿ�
	LPSHELLFOLDER psfDesktop;
	SHGetDesktopFolder(&psfDesktop);

	// �����
	FillTreeCtrl(psfDesktop, NULL, m_hDesktop);

	// �ͷŽӿ�
	psfDesktop->Release();

	// չ��������
	Expand(m_hDesktop, TVE_EXPAND);

	// չ���ҵĵ��ԣ�Ϊ����չ��,�����Ȳ���һ��,չ������ɾ��
	HTREEITEM hTemp = InsertItem("*", m_hMyComputer);
	Expand(m_hMyComputer, TVE_EXPAND);
	DeleteItem(hTemp);

	return TRUE;
}


// ��hParent�������nFolderָ���������ļ���
//
HTREEITEM CFolderTreeCtrl::InsertSpecialFolder(int nFolder, HTREEITEM hParent)
{
	// �õ�"����"�Ĵ���"ȫ·��"
	LPITEMIDLIST pidl;             
	SHGetSpecialFolderLocation(m_hWnd, nFolder, &pidl);

	// ����һ��"����"�ļ��е�IShellFolder�ӿ�
	LPSHELLFOLDER psfDesktop;
	SHGetDesktopFolder(&psfDesktop);  

	// ��ȡpidl��Ӧ�ļ��е���ʾ��
	CString fileName;
	GetFileName(psfDesktop, pidl, fileName);

	// �ͷŽӿ�
	psfDesktop->Release();

	// ���в���ָ����
	HTREEITEM hItem = InsertItem(fileName, GetSmallIcon(pidl), GetSelectedIcon(pidl), hParent); 

	return hItem;
}


// ��ȡpidl��Ӧ�ļ��е���ʾ��
//
void CFolderTreeCtrl::GetFileName(LPSHELLFOLDER psf, LPITEMIDLIST pidl, CString& fileName)
{
	// �����ʾ��
	STRRET strRet;  // �����洢IShellFolder�ӿڵķ������ص���ʾ��
	psf->GetDisplayNameOf(pidl, SHGDN_NORMAL, &strRet);  // ����ʾ������STRRET�ṹ

	// ��STRRET�ṹ�ڵ���ʾ������
	LPSTR str;
	StrRetToStr(&strRet, pidl, &str);  // ��ʾ����STRRET�ṹ���ݵ�str
	fileName = str;  // ��ʾ������fileName

	CoTaskMemFree(str);  // �ͷ���Դ  
}


// ��ȡpidl��Ӧ�ļ���Сͼ��
//
int CFolderTreeCtrl::GetSmallIcon(LPITEMIDLIST pidl)
{
	SHFILEINFO shFileInfo;
	SHGetFileInfo((LPCTSTR)pidl, 0, &shFileInfo, sizeof(SHFILEINFO), SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	
	return shFileInfo.iIcon;  // ����ͼ���ϵͳ������  
}


// ��ȡpidl��Ӧ�ļ��б�ѡ��ʱ��ͼ��
//
int CFolderTreeCtrl::GetSelectedIcon(LPITEMIDLIST pidl)
{
	SHFILEINFO shFileInfo;
	SHGetFileInfo((LPCTSTR)pidl, 0, &shFileInfo, sizeof(SHFILEINFO), SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_OPENICON);
	
	return shFileInfo.iIcon;  // ����ͼ���ϵͳ������        
}


// �����
//
void CFolderTreeCtrl::FillTreeCtrl(LPSHELLFOLDER psf, LPITEMIDLIST pidl, HTREEITEM hParent)
{
	LPMALLOC pMalloc;
	SHGetMalloc(&pMalloc);  // ȡ��IMalloc�ӿ�   
	
	LPENUMIDLIST peidl;  // IEnumIDList�ӿ�ָ��
	// ��ָ���ļ���Ϊ����ö���ļ�(��)(���������ļ�(��))������Ĭ����֪ͨ��Ϣ
	HRESULT hr = psf->EnumObjects(NULL, SHCONTF_FOLDERS | SHCONTF_INCLUDEHIDDEN | SHCONTF_STORAGE, &peidl);  
	// ����մ������
	if(FAILED(hr))
	{
		return;
	}

	LPITEMIDLIST pItem;  // �����psf�����PIDL
	ULONG ulFetched; 
	ULONG ulAttrs;
	
	// ����IEnumIDList�ӿڶ����Next���������������ÿ���Ӷ�������PIDL
	while(peidl->Next(1, &pItem, &ulFetched) == NOERROR)
	{
		ulAttrs = SFGAO_FOLDER | SFGAO_HASSUBFOLDER;  // �ļ����������ļ���
		psf->GetAttributesOf(1, (const ITEMIDLIST**)&pItem, &ulAttrs);  // ��ö�������

		if(ulAttrs & SFGAO_FOLDER)  // ���ļ��� 
		{
			TVITEM tvItem;  // �������ͻ���չ���һ��������ͼ����Ŀ���й���Ϣ
			tvItem.mask = TVIF_TEXT | TVIF_STATE | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;  // ָ��TVITEM��Ч��Ա

			if(ulAttrs & SFGAO_HASSUBFOLDER)  // �����ļ���
			{
				// ��ʾ"+"
				tvItem.mask = tvItem.mask | TVIF_CHILDREN;  
			}

			// �����ӽ���븸���״̬һ��
			UINT uState = GetItemState(hParent, TVIS_STATEIMAGEMASK) >> 12;  // �õ������״̬
			tvItem.state = INDEXTOSTATEIMAGEMASK(uState);  // �����ӽ��״̬
			tvItem.stateMask = TVIS_STATEIMAGEMASK;  // �����ӽ��״̬  

			// ��ȡpItem��Ӧ�ļ��е���ʾ��
			CString fileName;
			GetFileName(psf, pItem, fileName);

			// ����ʾ"�������"��"�����ھ�"��"����վ"
			if(fileName == "�������" || fileName == "�����ھ�" || fileName == "����վ")           
			{
				continue;
			}

			// �ϲ�����PIDL�����"ȫ·��"
			LPITEMIDLIST pidlNew = CShellOperator::ConcatPidls(pidl, pItem);

			tvItem.pszText = fileName.GetBuffer(MAX_PATH);  // ���ָ����ʾ����������ָ��
			tvItem.iImage = GetSmallIcon(pidlNew);  // ��ȡpidlNew��Ӧ�ļ���Сͼ��
			tvItem.iSelectedImage = GetSelectedIcon(pidlNew);  // ��ȡpidlNew��Ӧ�ļ��б�ѡ��ʱ��ͼ��

			LPTVItemData pItemData = (LPTVItemData)pMalloc->Alloc(sizeof(TVItemData));  // �����ڴ�
			pItemData->lpi = CShellOperator::CopyItemID(pMalloc, pItem);  // ���PIDL
			pItemData->lpifq = pidlNew;  // ȫPIDL
			pItemData->lpsfParent = psf;  // ���ļ��е�IShellFolderָ��

			tvItem.lParam = (LPARAM)pItemData;

			TVINSERTSTRUCT tvInsertStruct;  // ���������������ӿؼ���ʹ�õ���Ϣ
			tvInsertStruct.item = tvItem;  // ��Ҫ��ӵ���Ŀ
			tvInsertStruct.hParent = hParent;  // �����
			tvInsertStruct.hInsertAfter = TVI_LAST;  // ���뵽���λ��

			HTREEITEM hNewItem = InsertItem(&tvInsertStruct);  // ��������

			GetPathFromIDList(hNewItem, pidlNew, fileName);  // ��ITEMIDLISTת��Ϊ�ĵ�ϵͳ·��
		}
	}

	pMalloc->Free(pItem);  // �ͷű�ʶ���б�
	pMalloc->Release();  // �ͷ�IMalloc�ӿ�
}


// ��ITEMIDLISTת��Ϊ�ĵ�ϵͳ·��
//
void CFolderTreeCtrl::GetPathFromIDList(HTREEITEM hNewItem, LPCITEMIDLIST pidl, CString fileName)
{
	CHAR folderPath[MAX_PATH];
	if(SHGetPathFromIDList(pidl, folderPath))
	{
		CString path;
		path.Format("%s", folderPath);
		m_mapFolderPath[hNewItem] = path;
	}

	// "�ҵĵ���"Ҫ���⴦����ΪSHGetPathFromIDList�ó���·��Ϊ��
	if(fileName == "�ҵĵ���")     
	{                                 
		m_hMyComputer = hNewItem; 
	}
}


// ��ѡ��(ȡ��)ĳһ��ʱ,�Զ�ѡ��(ȡ��)��������(��)��(�ݹ�ʵ��)
// 
void CFolderTreeCtrl::SetChildItemState(HTREEITEM hItem, UINT uState)
{
	hItem = GetChildItem(hItem);  // ��ȡ��hItemָ�����������

	// ͬ�����
	while(hItem != NULL)
	{
		SetItemState(hItem, INDEXTOSTATEIMAGEMASK(uState), TVIS_STATEIMAGEMASK);  // ����hItemָ�������״̬
		SetChildItemState(hItem, uState);  // �ݹ�
		hItem = GetNextSiblingItem(hItem);  // ��ȡ��һ���ֵ���
	}
}


// ��ѡ��(ȡ��)ĳһ��ʱ, �޸������и���״̬(�ݹ�ʵ��)
// (1).  �ӽ��Ϊ"����ѡ��",�򸸽��ҲΪ"����ѡ��"
// (2.1).�ӽ��Ϊ"û��ѡ��",�����ֵܽ����"ȫ��ѡ��"��"����ѡ��",�򸸽��Ϊ"����ѡ��"
// (2.2).�ӽ��Ϊ"û��ѡ��",�����ֵܽ�㶼"û��ѡ��",�򸸽��Ϊ"û��ѡ��"
// (3.1).�ӽ��Ϊ"ȫ��ѡ��",�����ֵܽ����"û��ѡ��"��"����ѡ��",�򸸽��Ϊ"����ѡ��"
// (3.2).�ӽ��Ϊ"ȫ��ѡ��",�����ֵܽ�㶼"ȫ��ѡ��",�򸸽��Ϊ"ȫ��ѡ��"
//
void CFolderTreeCtrl::SetParentItemState(HTREEITEM hItem, UINT uState)
{
	// "����"��㲻��ʾѡ���
	if(hItem == m_hDesktop)                   
	{
		SetItemState(m_hDesktop, INDEXTOSTATEIMAGEMASK(NoCheckBox), TVIS_STATEIMAGEMASK);
		return;
	}

	UINT parentState;
	HTREEITEM hParent = GetParentItem(hItem);  // ��ø������
	if(hParent == NULL)  // �޸����
	{
		return;
	}

	if(uState == PartChecked)  // (1)�ӽ��Ϊ"����ѡ��",�򸸽��ҲΪ"����ѡ��"
	{
		parentState = PartChecked;  
	}

	// (2)�ӽ��Ϊ"û��ѡ��"ʱ
	if(uState == UnChecked)
	{
		HTREEITEM hSiblingItem = GetChildItem(hParent);  // ��õ�һ���ӽ����

		UINT uSiblingState;
		// ͬ�����
		while(hSiblingItem != NULL)
		{
			uSiblingState = GetItemState(hSiblingItem, TVIS_STATEIMAGEMASK) >> 12;  // ��ý��״̬
			// (2.1)�ӽ��Ϊ"û��ѡ��",�����ֵܽ����"ȫ��ѡ��"��"����ѡ��",�򸸽��Ϊ"����ѡ��"	
			if(uSiblingState != UnChecked)           
			{
				parentState = PartChecked;
				break;
			}
			hSiblingItem = GetNextSiblingItem(hSiblingItem);  // ����ֵܽ��
		}

		// (2.2)�ӽ��Ϊ"û��ѡ��",�����ֵܽ�㶼"û��ѡ��",�򸸽��Ϊ"û��ѡ��"
		if(uSiblingState == UnChecked)                   
		{
			parentState = UnChecked;
		}
	}

	// (3)�ӽ��Ϊ"ȫ��ѡ��"ʱ
	if(uState == AllChecked)
	{
		HTREEITEM hSiblingItem = GetChildItem(hParent);  // ��õ�һ���ӽ����

		UINT uSiblingState;
		// ͬ�����
		while(hSiblingItem != NULL)
		{
			uSiblingState = GetItemState(hSiblingItem, TVIS_STATEIMAGEMASK) >> 12;  // ��ý��״̬
			// (3.1)�ӽ��Ϊ"ȫ��ѡ��",�����ֵܽ����"û��ѡ��"��"����ѡ��",�򸸽��Ϊ"����ѡ��"
			if(uSiblingState != AllChecked)
			{
				parentState = PartChecked;      
				break;
			}
			hSiblingItem = GetNextSiblingItem(hSiblingItem);  // ����ֵܽ��
		}

		// (3.2)�ӽ��Ϊ"ȫ��ѡ��",�����ֵܽ�㶼"ȫ��ѡ��",�򸸽��Ϊ"ȫ��ѡ��"
		if(uSiblingState == AllChecked)
		{
			parentState = AllChecked;               
		}
	}

	// ���ø����ѡ���״̬
	SetItemState(hParent, INDEXTOSTATEIMAGEMASK(parentState), TVIS_STATEIMAGEMASK);

	// �ݹ�
	SetParentItemState(hParent, parentState);
}


// ȡ�ñ�ѡ���·��
// �ⲿ�ӿں���������Ҫ������GetSelectedPath(HTREEITEM hItem, CStringArray& listSelectedPath)ʵ��
//  
void CFolderTreeCtrl::GetSelectedPath(CStringList& listSelectedPath)
{
	listSelectedPath.RemoveAll();  // ����ַ����б�
	HTREEITEM hStartItem = GetChildItem(m_hDesktop);  // ���"����"�ĵ�һ���ӽ����
	GetSelectedPath(hStartItem, listSelectedPath);  // ����ʵ�ֹ��ܵĺ���
}


// ��ȡhItem����"ȫ��ѡ��"���ļ��е�·��,��listSelectedPath����(�ݹ�ʵ��)
// (1.1).��Ϊ"ȫ��ѡ��"�Ҳ�Ϊ"�ҵĵ���",����m_mapFolderPath[hItem]����·��
// (1.2).��Ϊ"ȫ��ѡ��"��Ϊ"�ҵĵ���",����SHGetPathFromIDList���ص�·��Ϊ��,���Ա����ֶ����"�ҵĵ���"�������ļ���
// (2).  ��Ϊ"����ѡ��",������Ŀ¼�½��в���
// (3).  �����ֵ�,�������ֵ���
//
void CFolderTreeCtrl::GetSelectedPath(HTREEITEM hItem, CStringList& listSelectedPath)
{
	UINT uState = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12;  // ��ý��״̬      
       
	// (1)."ȫ��ѡ��"ʱ
	if(uState == AllChecked)
	{
		// (1.1).��Ϊ"ȫ��ѡ��"�Ҳ�Ϊ"�ҵĵ���",����m_mapFolderPath[hItem]����·��
		if(hItem != m_hMyComputer)      
		{
			listSelectedPath.AddTail(m_mapFolderPath[hItem]);  // ���б�β�����Ԫ��(·��)
		}
		// (1.2).��Ϊ"ȫ��ѡ��"��Ϊ"�ҵĵ���",����SHGetPathFromIDList���ص�·��Ϊ��,
		// ���Ա����ֶ����"�ҵĵ���"�������ļ���
		else                            
		{
			HTREEITEM hRootDir = GetChildItem(m_hMyComputer);  // ���"�ҵĵ���"��һ���ӽ����
			// ͬ�����
			while(hRootDir != NULL)
			{
				listSelectedPath.AddTail(m_mapFolderPath[hRootDir]);  // ���б�β�����Ԫ��(·��)
				hRootDir = GetNextSiblingItem(hRootDir);  // ����ֵܽ����
			}
		}
	}
        
	// (2).��Ϊ"����ѡ��",������Ŀ¼�½��в���
	if(uState == PartChecked)               
	{
		HTREEITEM hChild = GetChildItem(hItem);  // ��õ�һ���ӽ����
		GetSelectedPath(hChild, listSelectedPath);  // �ݹ�
	} 

	// (3).�����ֵ�,�������ֵ���
	HTREEITEM hSibling = GetNextSiblingItem(hItem);  // ����ֵܽ����
	if(hSibling != NULL)                            
	{
		GetSelectedPath(hSibling, listSelectedPath);  // �ݹ�
	}
}


// ���������������еĻص�����
//
int CALLBACK CFolderTreeCtrl::TreeViewCompareProc(LPARAM lparam1, LPARAM lparam2, LPARAM lparamSort)
{
	LPTVItemData lptvid1=(LPTVItemData)lparam1;
	LPTVItemData lptvid2=(LPTVItemData)lparam2;
	if(lptvid1 == NULL || lptvid2 == NULL)
	{
		return 0;  // ���ߵ�λ�ȼ�
	}
        
	HRESULT hr = lptvid1->lpsfParent->CompareIDs(0,lptvid1->lpi,lptvid2->lpi);  // �Ƚ��������˳��˳��

	// �������0����������˳��ȼ�
	// �������0������ǰ���ں��ߺ���
	// ���С��0������ǰ���ں���ǰ�� 
	return (short)HRESULT_CODE((hr));  
}