// test1Doc.h : interface of the CTest1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST1DOC_H__F9BDC5A3_0DBB_4B21_A663_CB8D888EC2EC__INCLUDED_)
#define AFX_TEST1DOC_H__F9BDC5A3_0DBB_4B21_A663_CB8D888EC2EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "test1.h"

//5种表情(angry,sadness,surprise/fear,disgust,smile),其中surprise和fear难以区分，故放在一起
//另外一种中性表情neutrality
//共6种，每种3个标准表情模板，故一共18个
//#define TEMP_NUM 18

class CTest1Doc : public CDocument
{
private:
	void insertMinDis(FLOAT *minDis,int *minDisSub,int *currentNum,int i_result[6],FLOAT tmpDis,int i);
	CDIB* m_pDIB;
	HDIB m_hDIB;
	FLOAT *m_temp[TEMP_NUM];// 保存用于匹配的模板，这些模板已做了Gabor变换
	CSize m_tempSize[TEMP_NUM];//保存相应模板的大小(长和宽)
	int m_K;//k近邻
	///
	CEGraph *m_EGTemp;//表情模板链表，模板链表的一个元素不存数据，目的是为了更方便操作

protected: // create from serialization only
	CTest1Doc();
	DECLARE_DYNCREATE(CTest1Doc)

// Attributes
public:
	COLORREF 	m_refColorBKG;
	CExpStrategy *m_pexpStrategy;
	BOOL m_fTmpInit;//用于标记模板是否加载
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetSubRect(CRect& _rect);
	CDIB* GetDIB() const;
	virtual ~CTest1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTest1Doc)
	afx_msg void OnMenutwovalue();
	afx_msg void OnTempInit();
	afx_msg void OnTempRecog();
	afx_msg void OnPrenormal1();
	afx_msg void OnDetectKeyframe();
	afx_msg void OnDetectDis();
	afx_msg void OnTestKeypoint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST1DOC_H__F9BDC5A3_0DBB_4B21_A663_CB8D888EC2EC__INCLUDED_)
