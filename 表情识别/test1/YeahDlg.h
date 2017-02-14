#if !defined(AFX_YEAHDLG_H__C84DBC35_3BF1_41D6_906B_96C449AD6C3C__INCLUDED_)
#define AFX_YEAHDLG_H__C84DBC35_3BF1_41D6_906B_96C449AD6C3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YeahDlg.h : header file
//

#define WM_GOODBYE WM_USER + 5  //用户自定义消息，隐藏窗口
#define WM_DETYEAHKEY WM_USER + 6 //user's message to diplay detect key frame dialog

/////////////////////////////////////////////////////////////////////////////
// CYeahDlg dialog

class CYeahDlg : public CDialog
{
// Construction
public:
	CYeahDlg(CWnd* pParent = NULL);   // standard constructor
	CYeahDlg(CView* pParent);   // standard constructor
	BOOL MyCreate();
	CView* m_pView; //指向父窗口指针
	CString m_path; //要显示的图像帧的目录
	FLOAT m_fDis[40]; //Distances between neutral EG and test EG
	BOOL m_bFistDect; //True if perform detecting key frame first



// Dialog Data
	//{{AFX_DATA(CYeahDlg)
	enum { IDD = IDD_YEAHDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYeahDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CYeahDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YEAHDLG_H__C84DBC35_3BF1_41D6_906B_96C449AD6C3C__INCLUDED_)
