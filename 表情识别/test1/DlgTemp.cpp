// DlgTemp.cpp : implementation file
//

#include "stdafx.h"
#include "test1.h"
#include "DlgTemp.h"
#include "EGraph.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTemp dialog


CDlgTemp::CDlgTemp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTemp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTemp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pDIB=NULL;
	m_pStrategy=NULL;
}


void CDlgTemp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTemp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTemp, CDialog)
	//{{AFX_MSG_MAP(CDlgTemp)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTemp message handlers

/**
** 接受原始的DIB图像，并利用该图像构造一个新的DIB图像
** 然后进行Gabor变换，变换后的向量取模
** 将模映射到0~255之间，并显示出来
** 参考CExpStrategy::GaborTF(), DIB::DIB()
*/
void CDlgTemp::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if((m_pDIB==NULL)||(m_pStrategy==NULL))
		return;
	/*CDIB *tmpDIB=new CDIB(m_pDIB,0,0,m_pDIB->GetDIBSize().cx,m_pDIB->GetDIBSize().cy);
	if(tmpDIB==NULL)
	{
		MessageBox("Failed to construct a DIB");
		return;
	}*/
	CEGraph *tmpEGraph=NULL;
		tmpEGraph=new CEGraph();
		if(!(tmpEGraph->init_testExpr(m_pDIB,m_pStrategy)))
		{//构造模板弹性图失败
			MessageBox("构造模板弹性图失败：tmpEGraph->init_tempExpr");
			return;
		}
		/////////
//	FLOAT *EGraph=new FLOAT[360];
//	int i,j;
//	for(i=0;i<20;i++)
//		for(j=0;j<18;j++)
//			EGraph[i*18+j]=tmpEGraph->m_module[i*18+j];
	////////
//	FLOAT *EGraph=NULL;
//	EGraph=m_pStrategy->GaborTF(m_pDIB,0,0,0,0,FALSE);
	int EGcx,EGcy;
	EGcx=18;
	EGcy=20;
	//EGcx=m_pDIB->GetDIBSize().cx/5;
	//EGcy=m_pDIB->GetDIBSize().cy/5;
//	CDIB *tmpDIB=new CDIB(m_pDIB,EGraph,CSize(EGcx,EGcy),FALSE);
	CDIB *tmpDIB=new CDIB(m_pDIB,tmpEGraph->m_module,CSize(EGcx,EGcy),FALSE);
	CRect rectImg;
	rectImg.top=20;
	rectImg.left=20;
	rectImg.right=EGcx*5+20;
	rectImg.bottom=EGcy*5+20;
	tmpDIB->PaintDIB(dc.m_hDC,&rectImg);
///////////标记关键点
	tmpEGraph->DetectKeyPoints();
	CPen newPen(PS_SOLID,1,RGB(255,0,0));
	CPen *oldPen;
	CBrush *oldBrush;
	oldPen=(CPen*)dc.SelectObject(&newPen);
	oldBrush=(CBrush*)dc.SelectStockObject(NULL_BRUSH);
	int i,left,top;

/*	for(i=0;i<KEY_NUM;i++)
	{
		left=tmpEGraph->m_keyPoints[i].x*5;
		top=tmpEGraph->m_keyPoints[i].y*5;
		dc.Rectangle(left+20,top+20,left+25,top+25);
	}
	CRect rect;//(2,3,15,8)
	rect.left=20+2*5;
	rect.top=20+2*5;
	rect.right=20+16*5;
	rect.bottom=20+7*5;
	dc.Rectangle(&rect);
/////////////////////////////

	//	CRect rect;(5,12,13,18)
	rect.left=20+5*5;
	rect.top=20+12*5;
	rect.right=20+13*5;
	rect.bottom=20+18*5;
	dc.Rectangle(&rect);
*/////////////////////////
	CPoint key_points[24]={CPoint(3,2),CPoint(6,2),CPoint(2,4),CPoint(7,4),CPoint(4,5),
		CPoint(11,2),CPoint(13,2),CPoint(10,4),CPoint(14,4),CPoint(13,5),
		CPoint(6,1),CPoint(9,1),CPoint(5,13),CPoint(8,13),CPoint(11,13),
		CPoint(4,14),CPoint(12,14),CPoint(6,16),CPoint(8,16),CPoint(11,16),
		CPoint(6,10),CPoint(5,11),CPoint(10,10),CPoint(11,11)};
	for(i=0;i<24;i++)
	{
		left=key_points[i].x*5;
		top=key_points[i].y*5;
		dc.Rectangle(left+20,top+20,left+25,top+25);
	}	
	dc.SelectObject(oldBrush);
	dc.SelectObject(oldPen);
////////////////////
	delete tmpDIB;
//	delete [] EGraph;
//	if(tmpEGraph!=NULL)
//		delete [] tmpEGraph;
}

void CDlgTemp::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgTemp::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgTemp::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnMouseMove(nFlags, point);
}
