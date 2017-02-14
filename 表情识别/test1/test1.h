// test1.h : main header file for the TEST1 application
//

#if !defined(AFX_TEST1_H__42330636_0F94_42D4_892B_B4D672283AE9__INCLUDED_)
#define AFX_TEST1_H__42330636_0F94_42D4_892B_B4D672283AE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest1App:
// See test1.cpp for the implementation of this class
//
#include "dib.h"
#include "ExpStrategy.h"
#include "EGraph.h"
#include "dlgResult.h"

//共6种，每种8个标准表情模板，故一共48个
#define TEMP_NUM 48
class CTest1App : public CWinApp
{
public:
	int m_K;//k近邻
	///
	CEGraph *m_EGTemp;//表情模板链表，模板链表的一个元素不存数据，目的是为了更方便操作
	BOOL m_fTmpInit;//用于标记模板是否加载
	CExpStrategy m_expStrategy;

public:
	CTest1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest1App)
	public:
	virtual BOOL InitInstance();
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTest1App)
	afx_msg void OnAppAbout();
	afx_msg void OnInitTemps();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST1_H__42330636_0F94_42D4_892B_B4D672283AE9__INCLUDED_)
