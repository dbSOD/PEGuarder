#pragma once

// �����������������������ͷ�ļ�
#include "Analyser.h"
#include "Detector.h"
#include "Tool.h"

// CMyTabCtrl
// �����Լ���ѡ��ؼ�
class CMyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl)

public:
	CMyTabCtrl();
	virtual ~CMyTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	// ���������������������ָ��
	CAnalyser* m_pAnalyser;
	CDetector* m_pDetector;
	CTool* m_pTool;

public:
	// ѡ�ѡ���л���Ϣ
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


