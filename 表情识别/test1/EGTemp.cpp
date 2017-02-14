// EGTemp.cpp : implementation file
//

#include "stdafx.h"
#include "test1.h"
#include "EGTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEGTemp dialog


CEGTemp::CEGTemp(CWnd* pParent /*=NULL*/)
	: CDialog(CEGTemp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEGTemp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pDIB=NULL;
}


void CEGTemp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEGTemp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEGTemp, CDialog)
	//{{AFX_MSG_MAP(CEGTemp)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEGTemp message handlers

void CEGTemp::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rectImg;
	rectImg.top=60;
	rectImg.left=40;
	rectImg.bottom=260;
	rectImg.right=220;
	int rectHeight,rectWidth;
	rectHeight=rectImg.bottom-rectImg.top;
	rectWidth=rectImg.right-rectImg.left;
	CPoint EG_pos[15];
	//eyes and eyebrows
	EG_pos[0]=CPoint(rectImg.left+(int)(rectWidth*0.12),rectImg.top+(int)(0.23*rectHeight));
	EG_pos[1]=CPoint(rectImg.left+(int)(rectWidth*0.3),rectImg.top+(int)(0.08*rectHeight));
	EG_pos[2]=CPoint(rectImg.left+(int)(rectWidth*0.35),rectImg.top+(int)(0.25*rectHeight));
	EG_pos[3]=CPoint(rectImg.left+(int)(rectWidth*0.5),rectImg.top+(int)(0.1*rectHeight));
	EG_pos[4]=CPoint(rectImg.left+(int)(rectWidth*0.65),rectImg.top+(int)(0.25*rectHeight));
	EG_pos[5]=CPoint(rectImg.left+(int)(rectWidth*0.7),rectImg.top+(int)(0.08*rectHeight));
	EG_pos[6]=CPoint(rectImg.left+(int)(rectWidth*0.9),rectImg.top+(int)(0.23*rectHeight));
//mouth
	EG_pos[7]=CPoint(rectImg.left+(int)(rectWidth*0.3),rectImg.top+(int)(0.7*rectHeight));
	EG_pos[8]=CPoint(rectImg.left+(int)(rectWidth*0.5),rectImg.top+(int)(0.7*rectHeight));
	EG_pos[9]=CPoint(rectImg.left+(int)(rectWidth*0.65),rectImg.top+(int)(0.7*rectHeight));
	EG_pos[10]=CPoint(rectImg.left+(int)(rectWidth*0.3),rectImg.top+(int)(0.85*rectHeight));
	EG_pos[11]=CPoint(rectImg.left+(int)(rectWidth*0.5),rectImg.top+(int)(0.85*rectHeight));
	EG_pos[12]=CPoint(rectImg.left+(int)(rectWidth*0.65),rectImg.top+(int)(0.85*rectHeight));
//mouth coners
	EG_pos[13]=CPoint(rectImg.left+(int)(rectWidth*0.25),rectImg.top+(int)(0.78*rectHeight));
	EG_pos[14]=CPoint(rectImg.left+(int)(rectWidth*0.7),rectImg.top+(int)(0.78*rectHeight));

	if(m_pDIB==NULL)
		return;
	else
		m_pDIB->PaintDIB(dc.m_hDC,&rectImg);
	//dc.SetROP2(R2_NOT);
	CPen newPen(PS_SOLID,1,RGB(255,0,0));
	CPen *oldPen;
	CBrush *oldBrush;
	oldPen=(CPen*)dc.SelectObject(&newPen);
	oldBrush=(CBrush*)dc.SelectStockObject(NULL_BRUSH);
	int i;
	CString str;
	for(i=0;i<15;i++)
	{
		dc.Rectangle(EG_pos[i].x-10,EG_pos[i].y-10,EG_pos[i].x+9,EG_pos[i].y+9);
		str.Format("%d",i);
		dc.TextOut(EG_pos[i].x,EG_pos[i].y,str);
	}
	dc.Rectangle(41,61,219,121);
	dc.Rectangle(91,190,171,250);
	dc.SelectObject(oldBrush);
	dc.SelectObject(oldPen);
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}
