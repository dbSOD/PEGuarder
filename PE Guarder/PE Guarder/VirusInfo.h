#pragma once

// ���ݲ���ID��ȡ���������Ϣ
class CVirusInfo
{
public:
	CVirusInfo(void);
	~CVirusInfo(void);

	static LPCSTR GetNameByID(DWORD dwVID);  // ���ݲ���ID��ȡ������
};
