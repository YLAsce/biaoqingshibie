#if !defined(AFX_EGTEMP_H__1774FD70_2CFE_4A0A_A34C_FEBB56F3AB28__INCLUDED_)
#define AFX_EGTEMP_H__1774FD70_2CFE_4A0A_A34C_FEBB56F3AB28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EGTemp.h : header file
//
#include "DIB.h"
/////////////////////////////////////////////////////////////////////////////
// CEGTemp dialog

class CEGTemp : public CDialog
{
// Construction
public:
	CDIB * m_pDIB;
	CEGTemp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEGTemp)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEGTemp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEGTemp)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EGTEMP_H__1774FD70_2CFE_4A0A_A34C_FEBB56F3AB28__INCLUDED_)
