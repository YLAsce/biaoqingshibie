// DlgDetectFrame.cpp : implementation file
//

#include "stdafx.h"
#include "test1.h"
#include "DlgDetectFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDetectFrame dialog


CDlgDetectFrame::CDlgDetectFrame(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDetectFrame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDetectFrame)
	m_key = 0;
	int i=0;
	for(i=0;i<10;i++)
		m_dis[i]=0.0f;
	/*m_dis9 = 0.0f;
	m_dis10 = 0.0f;
	m_dis1 = 0.0f;
	m_dis2 = 0.0f;
	m_dis3 = 0.0f;
	m_dis4 = 0.0f;
	m_dis5 = 0.0f;
	m_dis6 = 0.0f;
	m_dis7 = 0.0f;
	m_dis8 = 0.0f;*/
	//}}AFX_DATA_INIT
}


void CDlgDetectFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDetectFrame)
	DDX_Text(pDX, IDC_EDIT1, m_key);
	DDX_Text(pDX, IDC_EDIT10, m_dis[8]);
	DDX_Text(pDX, IDC_EDIT11, m_dis[9]);
	DDX_Text(pDX, IDC_EDIT2, m_dis[0]);
	DDX_Text(pDX, IDC_EDIT3, m_dis[1]);
	DDX_Text(pDX, IDC_EDIT4, m_dis[2]);
	DDX_Text(pDX, IDC_EDIT5, m_dis[3]);
	DDX_Text(pDX, IDC_EDIT6, m_dis[4]);
	DDX_Text(pDX, IDC_EDIT7, m_dis[5]);
	DDX_Text(pDX, IDC_EDIT8, m_dis[6]);
	DDX_Text(pDX, IDC_EDIT9, m_dis[7]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDetectFrame, CDialog)
	//{{AFX_MSG_MAP(CDlgDetectFrame)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDetectFrame message handlers
