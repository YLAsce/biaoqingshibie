#if !defined(AFX_DLGDETECTFRAME_H__33461B87_712E_48F1_9D80_B6AE28DBCD88__INCLUDED_)
#define AFX_DLGDETECTFRAME_H__33461B87_712E_48F1_9D80_B6AE28DBCD88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDetectFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDetectFrame dialog

class CDlgDetectFrame : public CDialog
{
// Construction
public:
	CDlgDetectFrame(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDetectFrame)
	enum { IDD = IDD_DIALOG4 };
	int		m_key;
	float m_dis[10];
	/*float	m_dis9;
	float	m_dis10;
	float	m_dis1;
	float	m_dis2;
	float	m_dis3;
	float	m_dis4;
	float	m_dis5;
	float	m_dis6;
	float	m_dis7;
	float	m_dis8;*/
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDetectFrame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDetectFrame)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDETECTFRAME_H__33461B87_712E_48F1_9D80_B6AE28DBCD88__INCLUDED_)
