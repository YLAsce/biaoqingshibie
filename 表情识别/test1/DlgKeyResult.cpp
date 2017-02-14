// DlgKeyResult.cpp : implementation file
//

#include "stdafx.h"
#include "test1.h"
#include "DlgKeyResult.h"

#include "DIB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyResult dialog


CDlgKeyResult::CDlgKeyResult(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyResult::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyResult)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bPaint = FALSE ; //Don't draw line graph
}


void CDlgKeyResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyResult)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyResult, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyResult)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyResult message handlers

void CDlgKeyResult::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (!m_bPaint) {
		AfxMessageBox("Refused to draw line graph");
		return;
	}
	//Draw line graph constructed by distances
	FLOAT minDis, maxDis, scrop, aveDis; //The minmum , maximum and average distance
	int xLine, yLine; //x point and y point
	CString str_lab; //label
	int max_index;//the Max image Index
	minDis = 65000.0f;
	maxDis = 0.0f;
	max_index = 0;//the image indexed 0
	aveDis = 0.0f;
	int i; //iterative factor
	for (i = 0; i < 40; i ++) {
		aveDis += m_fDis[i];
		minDis = (minDis > m_fDis[i]) ? m_fDis[i] : minDis;
		//maxDis = (maxDis < m_fDis[i]) ? m_fDis[i] : maxDis;
		if (maxDis < m_fDis[i]) {
			maxDis = m_fDis[i];
			max_index = i;
		}
	}
	scrop = maxDis - minDis;
	aveDis = aveDis / 40;
	
	CPen newPen(PS_SOLID,1,RGB(255,0,0));
	CPen bluePen(PS_SOLID,2,RGB(0,0,255));
	CPen *oldPen;
	CBrush *oldBrush;
	oldPen = (CPen*)dc.SelectObject(&newPen);
	//oldBrush=(CBrush*)dc.SelectStockObject(NULL_BRUSH); //Null Brush
	oldBrush=(CBrush*)dc.SelectStockObject(WHITE_BRUSH); //white brush
	////X axe: the length is 450
	dc.MoveTo(30, 130); //The original point: O(0,0)
	dc.LineTo(480, 130);
	//Y axe: the length is 120
	dc.MoveTo(30, 130);
	dc.LineTo(30, 10);
	//Draw arrow of X
	dc.MoveTo(480, 130);
	dc.LineTo(463, 120);
	dc.MoveTo(480, 130);
	dc.LineTo(463, 140);
	//draw arrow of Y
	dc.MoveTo(30, 10);
	dc.LineTo(20, 27);
	dc.MoveTo(30, 10);
	dc.LineTo(40, 27);
	//draw the label of y
	str_lab.Format("%4.2f", minDis);
	dc.TextOut(0, 120, str_lab);
	str_lab.Format("%4.2f", maxDis);
	dc.TextOut(0, 10, str_lab);
	//draw the label of X
	for (i = 0; i <= 40; i += 5){
		str_lab.Format("%d", i);
		dc.TextOut(30 + 10 * i, 140, str_lab);
		dc.MoveTo(30 + 10 * i, 135);
		dc.LineTo(30 + 10 * i, 125);
	}
	//Draw Minimum distance
	int yy;
	yy = 130 - (1.15 * aveDis - minDis) / scrop * 100;
	dc.MoveTo(30, yy);
	dc.LineTo(460, yy);
	//Draw every distance
	dc.SelectObject(&bluePen);
	dc.MoveTo(30, 130);
	for (i = 0; i< 40; i ++){
		xLine = 30 + (i+1) * 10;
		yLine = 130 - (m_fDis[i] - minDis) / scrop * 100;
		dc.LineTo(xLine, yLine);
	}

	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);

	///draw the neutral image and maximum image
	if (m_path.IsEmpty()) {
		AfxMessageBox("Can not find the directory of images");
		return;
	}
	CDIB *pNeutralImg = NULL;
	CDIB *pMaxImg = NULL;
	CString tmpStr;
	CRect rect;
	tmpStr = m_path + "neutral.bmp";
	pNeutralImg = new CDIB(tmpStr.GetBuffer(tmpStr.GetLength()));
	if (pNeutralImg == NULL) {
		AfxMessageBox("Error in paint neutral image");
		return;
	}
	rect.top = 180;
	rect.bottom = 180 + 100;
	rect.left = 35;
	rect.right = 35 + 90;
	pNeutralImg->PaintDIB(dc.m_hDC, &rect);
	delete pNeutralImg;
	str_lab.Format("suprise%d.bmp", max_index + 1);
	tmpStr = m_path + str_lab;
	pMaxImg = new CDIB(tmpStr.GetBuffer(tmpStr.GetLength()));
	if (pMaxImg == NULL) {
		AfxMessageBox("Error in paint Maximum image");
		return;
	}
	rect.top = 180;
	rect.bottom = 180 + 100;
	rect.left = 145;
	rect.right = 145 + 90;
	pMaxImg->PaintDIB(dc.m_hDC, &rect);
	delete pMaxImg;
	
	// Do not call CDialog::OnPaint() for painting messages
}
