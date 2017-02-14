#if !defined(AFX_DLGTEMP_H__3C2ADA13_DC6E_4DB2_8DDD_18B57AA06B95__INCLUDED_)
#define AFX_DLGTEMP_H__3C2ADA13_DC6E_4DB2_8DDD_18B57AA06B95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTemp.h : header file
//
#include "dib.h"
#include "ExpStrategy.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgTemp dialog

class CDlgTemp : public CDialog
{
// Construction
public:
	CDlgTemp(CWnd* pParent = NULL);   // standard constructor
	CDIB *m_pDIB;
	CExpStrategy *m_pStrategy;
// Dialog Data
	//{{AFX_DATA(CDlgTemp)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTemp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTemp)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEMP_H__3C2ADA13_DC6E_4DB2_8DDD_18B57AA06B95__INCLUDED_)
