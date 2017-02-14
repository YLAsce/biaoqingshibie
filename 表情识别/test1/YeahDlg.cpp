// YeahDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test1.h"
#include "YeahDlg.h"

#include "DIB.h"
#include "test1Doc.h"
#include "test1View.h"
#include "EGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYeahDlg dialog


CYeahDlg::CYeahDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYeahDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYeahDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pView = NULL;
}


void CYeahDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYeahDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CYeahDlg, CDialog)
	//{{AFX_MSG_MAP(CYeahDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYeahDlg message handlers

int CYeahDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CYeahDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CString fileName[40] = {  //要显示图像帧的文件名
			"suprise1.bmp", "suprise2.bmp", "suprise3.bmp","suprise4.bmp",
			"suprise5.bmp", "suprise6.bmp", "suprise7.bmp", "suprise8.bmp", "suprise9.bmp",
			"suprise10.bmp", "suprise11.bmp", "suprise12.bmp", "suprise13.bmp", "suprise14.bmp",
			"suprise15.bmp", "suprise16.bmp", "suprise17.bmp", "suprise18.bmp", "suprise19.bmp",
			"suprise20.bmp", "suprise21.bmp", "suprise22.bmp", "suprise23.bmp", "suprise24.bmp",
			"suprise25.bmp", "suprise26.bmp", "suprise27.bmp", "suprise28.bmp", "suprise29.bmp",
			"suprise30.bmp", "suprise31.bmp", "suprise32.bmp", "suprise33.bmp", "suprise34.bmp",
			"suprise35.bmp", "suprise36.bmp", "suprise37.bmp", "suprise38.bmp", "suprise39.bmp",
			"suprise40.bmp"
			};	
	// TODO: Add your message handler code here

	////显示图像每行8幅，共5行
	if (m_path.IsEmpty()) {
		AfxMessageBox("Failed to access image directory!");
		return;
	}

	//construct neutral Dib image and its Elastic Graph
	CDIB neutralDib(m_path + "neutral.bmp");
	CEGraph neutralEG;
	CTest1Doc *pDoc = ((CTest1View*)m_pView)->GetDocument();
	if(!neutralEG.init_testExpr(&neutralDib, pDoc->m_pexpStrategy)){
		AfxMessageBox("Failed to construct Egraph");
		return;
	}
	
	//construct every test Dib image and its EG and then 
	//calucalate the distance between neutral EG and test EG
	CString str_tmp; //图像文件名
	CDIB* m_pTmpDib;// 指向临时图像的指针
	CEGraph *m_pTestEG; //the EG of test Dib accord to m_pTmpDib
	int i, j; // iterative factors
	CRect imageRect; //The rect of Dib image to be drawn
	BOOL flag;//Decting first
	m_pTmpDib = NULL;
	m_pTestEG = NULL;
	flag = FALSE;
	if (m_bFistDect) {
		flag = TRUE;
		m_bFistDect = FALSE;
	}
	
///////////////begin of for
	for (i = 0; i < 5; i ++)
		for(j = 0; j < 8; j ++){
			str_tmp = m_path + fileName[i * 8 +j];
			m_pTmpDib = new CDIB(str_tmp.GetBuffer(str_tmp.GetLength()));
			if (m_pTmpDib == NULL) {
				AfxMessageBox("Failed to construct DIB image");
				break;
			}
			imageRect.top = i * 110; 
			imageRect.bottom = imageRect.top + 100;
			imageRect.left = j * 95;
			imageRect.right = imageRect.left + 90;
			m_pTmpDib->PaintDIB(dc.m_hDC, &imageRect);

	//////////////// Construct its EG and calculate the distance
		if ( flag)
		{
			m_pTestEG = new CEGraph;
			if(!m_pTestEG->init_testExpr(m_pTmpDib, pDoc->m_pexpStrategy)){
				AfxMessageBox("Fail to construct test Elastic Graph");
				delete m_pTmpDib;
				delete m_pTestEG;
				return;
			}
			m_fDis[i * 8 +j] = neutralEG.Cal_ModuleDis(m_pTestEG);
			delete m_pTestEG;
			m_pTestEG = NULL;
		}
	 /////////////////////////////////////////////////////////

			delete m_pTmpDib;
			m_pTmpDib = NULL;
		}
///////////end of for	

	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CYeahDlg::MyCreate()
{
	return CDialog::Create(CYeahDlg::IDD);
}

CYeahDlg::CYeahDlg(CView* pParent)
{
	m_pView = pParent;
	int i;
	for (i = 0 ;i < 40 ; i++) {
		m_fDis[i] = 65000.0f;
	}
	m_bFistDect = TRUE;
}

void CYeahDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(m_pView != NULL){
		//UpdateDate(TRUE);
		m_pView->PostMessage(WM_GOODBYE, IDCANCEL);
	}
	else{
		CDialog::OnCancel();
	}
	
//	CDialog::OnCancel();
}

void CYeahDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (m_pView != NULL) {
		UpdateData(TRUE);
		m_pView->PostMessage(WM_DETYEAHKEY, IDOK);
	}
	else {
		CDialog::OnOK();
	}
	
//	CDialog::OnOK();
}
