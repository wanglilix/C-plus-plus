// MyThreadDlg.h : ͷ�ļ�
//

#pragma once

void Threadfunc();
// CMyThreadDlg �Ի���
class CMyThreadDlg : public CDialog
{
// ����
public:
	CMyThreadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYTHREAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	HANDLE hThread;
	DWORD ThreadID;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickeddsd();
	afx_msg void OnBnClickedBtnStop();
};
