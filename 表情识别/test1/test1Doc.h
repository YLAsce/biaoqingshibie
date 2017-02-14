// test1Doc.h : interface of the CTest1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST1DOC_H__F9BDC5A3_0DBB_4B21_A663_CB8D888EC2EC__INCLUDED_)
#define AFX_TEST1DOC_H__F9BDC5A3_0DBB_4B21_A663_CB8D888EC2EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "test1.h"

//5�ֱ���(angry,sadness,surprise/fear,disgust,smile),����surprise��fear�������֣��ʷ���һ��
//����һ�����Ա���neutrality
//��6�֣�ÿ��3����׼����ģ�壬��һ��18��
//#define TEMP_NUM 18

class CTest1Doc : public CDocument
{
private:
	void insertMinDis(FLOAT *minDis,int *minDisSub,int *currentNum,int i_result[6],FLOAT tmpDis,int i);
	CDIB* m_pDIB;
	HDIB m_hDIB;
	FLOAT *m_temp[TEMP_NUM];// ��������ƥ���ģ�壬��Щģ��������Gabor�任
	CSize m_tempSize[TEMP_NUM];//������Ӧģ��Ĵ�С(���Ϳ�)
	int m_K;//k����
	///
	CEGraph *m_EGTemp;//����ģ������ģ�������һ��Ԫ�ز������ݣ�Ŀ����Ϊ�˸��������

protected: // create from serialization only
	CTest1Doc();
	DECLARE_DYNCREATE(CTest1Doc)

// Attributes
public:
	COLORREF 	m_refColorBKG;
	CExpStrategy *m_pexpStrategy;
	BOOL m_fTmpInit;//���ڱ��ģ���Ƿ����
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
