#if !defined(AFX_DLGRESULT_H__5F99FA18_F9EA_4EFF_81BF_D7E53D90296C__INCLUDED_)
#define AFX_DLGRESULT_H__5F99FA18_F9EA_4EFF_81BF_D7E53D90296C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgResult.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgResult dialog

class CDlgResult : public CDialog
{
// Construction
public:
	CDlgResult(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgResult)
	enum { IDD = IDD_DIALOG2 };
	CString	m_result;
	CString	m_time;
	CString m_dises[14];
/*	CString	m_dis1;
	CString	m_dis2;
	CString	m_dis3;
	CString	m_dis4;
	CString	m_dis5;
	CString	m_dis6;
	CString	m_dis7;
	CString	m_dis8;
	CString	m_dis9;
	CString	m_dis10;
	CString	m_dis11;
	CString	m_dis12;
	CString	m_dis13;
	CString	m_dis14;
*/
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgResult)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgResult)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRESULT_H__5F99FA18_F9EA_4EFF_81BF_D7E53D90296C__INCLUDED_)
