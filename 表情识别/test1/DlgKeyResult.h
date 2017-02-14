#if !defined(AFX_DLGKEYRESULT_H__55D460BE_B14D_4C4B_B121_391D78E8B01C__INCLUDED_)
#define AFX_DLGKEYRESULT_H__55D460BE_B14D_4C4B_B121_391D78E8B01C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyResult.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyResult dialog

class CDlgKeyResult : public CDialog
{
// Construction
public:
	CDlgKeyResult(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgKeyResult)
	enum { IDD = IDD_DIALOG6 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	FLOAT m_fDis[40];  // The 40 distances.
	BOOL m_bPaint;  //whether draw line graph or not
	CString m_path; //The directory of images

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgKeyResult)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgKeyResult)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGKEYRESULT_H__55D460BE_B14D_4C4B_B121_391D78E8B01C__INCLUDED_)
