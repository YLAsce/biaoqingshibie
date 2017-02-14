// DlgResult.cpp : implementation file
//

#include "stdafx.h"
#include "test1.h"
#include "DlgResult.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgResult dialog


CDlgResult::CDlgResult(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgResult::IDD, pParent)
{
	int i;
	//{{AFX_DATA_INIT(CDlgResult)
	m_result = _T("");
	m_time = _T("");
	for(i=0;i<14;i++)
		m_dises[i]=_T("");
/*	m_dis1 = _T("");
	m_dis2 = _T("");
	m_dis3 = _T("");
	m_dis4 = _T("");
	m_dis5 = _T("");
	m_dis6 = _T("");
	m_dis7 = _T("");
	m_dis8 = _T("");
	m_dis9 = _T("");
	m_dis10 = _T("");
	m_dis11 = _T("");
	m_dis12 = _T("");
	m_dis13 = _T("");
	m_dis14 = _T("");
*/
	//}}AFX_DATA_INIT
}


void CDlgResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgResult)
	DDX_Text(pDX, IDC_EDIT1, m_result);
	DDX_Text(pDX, IDC_EDIT2, m_time);
	DDX_Text(pDX, IDC_EDIT3, m_dises[0]);
	DDX_Text(pDX, IDC_EDIT4, m_dises[1]);
	DDX_Text(pDX, IDC_EDIT5, m_dises[2]);
	DDX_Text(pDX, IDC_EDIT6, m_dises[3]);
	DDX_Text(pDX, IDC_EDIT7, m_dises[4]);
	DDX_Text(pDX, IDC_EDIT8, m_dises[5]);
	DDX_Text(pDX, IDC_EDIT9, m_dises[6]);
	DDX_Text(pDX, IDC_EDIT10, m_dises[7]);
	DDX_Text(pDX, IDC_EDIT11, m_dises[8]);
	DDX_Text(pDX, IDC_EDIT12, m_dises[9]);
	DDX_Text(pDX, IDC_EDIT13, m_dises[10]);
	DDX_Text(pDX, IDC_EDIT14, m_dises[11]);
	DDX_Text(pDX, IDC_EDIT15, m_dises[12]);
	DDX_Text(pDX, IDC_EDIT16, m_dises[13]);
/*	DDX_Text(pDX, IDC_EDIT3, m_dis1);
	DDX_Text(pDX, IDC_EDIT4, m_dis2);
	DDX_Text(pDX, IDC_EDIT5, m_dis3);
	DDX_Text(pDX, IDC_EDIT6, m_dis4);
	DDX_Text(pDX, IDC_EDIT7, m_dis5);
	DDX_Text(pDX, IDC_EDIT8, m_dis6);
	DDX_Text(pDX, IDC_EDIT9, m_dis7);
	DDX_Text(pDX, IDC_EDIT10, m_dis8);
	DDX_Text(pDX, IDC_EDIT11, m_dis9);
	DDX_Text(pDX, IDC_EDIT12, m_dis10);
	DDX_Text(pDX, IDC_EDIT13, m_dis11);
	DDX_Text(pDX, IDC_EDIT14, m_dis12);
	DDX_Text(pDX, IDC_EDIT15, m_dis13);
	DDX_Text(pDX, IDC_EDIT16, m_dis14);
*/
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgResult, CDialog)
	//{{AFX_MSG_MAP(CDlgResult)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgResult message handlers
