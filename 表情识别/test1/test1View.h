// test1View.h : interface of the CTest1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST1VIEW_H__57F27AA1_303B_4779_9136_97A991660A7D__INCLUDED_)
#define AFX_TEST1VIEW_H__57F27AA1_303B_4779_9136_97A991660A7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CYeahDlg;

class CTest1View : public CScrollView
{
protected: // create from serialization only
	CTest1View();
	DECLARE_DYNCREATE(CTest1View)

private:
	CYeahDlg* m_pDlgYeah; //用于显示我的视频的窗口
	BOOL m_bYeahDis; //是否显示视频窗口
// Attributes
public:
	CTest1Doc* GetDocument();

// Operations
public:
	BOOL m_bYeahDetect; //control whether detect the key frame of yeah
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTest1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	int m_drawKinds;//绘图种类(1-图像,2-图像中的数据,3-Gabor变换结果)
	BOOL m_flagSub;
	BOOL m_flagMove;
	CRect m_subRect;
	//{{AFX_MSG(CTest1View)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnImageSub1();
	afx_msg void OnImageSub2();
	afx_msg void OnUpdateImageSub1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImageSub2(CCmdUI* pCmdUI);
	afx_msg void OnImageData();
	afx_msg void OnGabortf();
	afx_msg void OnGaborSave();
	afx_msg void OnGabortf2();
	afx_msg void OnYeahFrames();
	afx_msg void OnYeahDetect();
	afx_msg void OnUpdateYeahDetect(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnGoodBye(WPARAM wParam,LPARAM lParam);//用户自定义消息函数，隐藏窗口
	afx_msg LRESULT OnDetYeahKey(WPARAM wParam,LPARAM lParam);//user's message function to detect key frame
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in test1View.cpp
inline CTest1Doc* CTest1View::GetDocument()
   { return (CTest1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST1VIEW_H__57F27AA1_303B_4779_9136_97A991660A7D__INCLUDED_)
