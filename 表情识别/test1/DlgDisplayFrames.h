#if !defined(AFX_DLGDISPLAYFRAMES_H__535F1FCF_9B1A_4446_9D73_C60A8F8D761C__INCLUDED_)
#define AFX_DLGDISPLAYFRAMES_H__535F1FCF_9B1A_4446_9D73_C60A8F8D761C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDisplayFrames.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDisplayFrames dialog

class CDlgDisplayFrames : public CDialog
{
// Construction
public:
	CDlgDisplayFrames(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDisplayFrames)
	enum { IDD = IDD_DIALOG5 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDisplayFrames)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	public:
	CString m_path;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDisplayFrames)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDISPLAYFRAMES_H__535F1FCF_9B1A_4446_9D73_C60A8F8D761C__INCLUDED_)
