// DlgDisplayFrames.cpp : implementation file
//

#include "stdafx.h"
#include "test1.h"
#include "DlgDisplayFrames.h"
#include "dib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDisplayFrames dialog


CDlgDisplayFrames::CDlgDisplayFrames(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDisplayFrames::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDisplayFrames)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDisplayFrames::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDisplayFrames)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDisplayFrames, CDialog)
	//{{AFX_MSG_MAP(CDlgDisplayFrames)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDisplayFrames message handlers

void CDlgDisplayFrames::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CString fileName[11]={
			"neutrality.bmp","frame1.bmp","frame2.bmp","frame3.bmp","frame4.bmp","frame5.bmp",
				"frame6.bmp","frame7.bmp","frame8.bmp","frame9.bmp","frame10.bmp"};
	if(m_path.IsEmpty())
	{
		MessageBox("找不文件路径");
	}
	CString str_tmp;
	CDIB *tmpDIB;
	CRect rectImg;
	int i;
	str_tmp=m_path+fileName[0];
	tmpDIB=new CDIB(str_tmp.GetBuffer(str_tmp.GetLength()));
	if(tmpDIB==NULL)
	{
		MessageBox("读中性表情图失败！",NULL,MB_OK);
		return;
	}
	rectImg.top=10; rectImg.left=10; rectImg.right=10+90; rectImg.bottom=10+100;
	tmpDIB->PaintDIB(dc.m_hDC,&rectImg);
	delete tmpDIB;
	for(i=1;i<=5;i++)
	{
		str_tmp=m_path+fileName[i];
		tmpDIB=new CDIB(str_tmp.GetBuffer(str_tmp.GetLength()));
		if(tmpDIB==NULL)
		{
			MessageBox("读表情帧失败！","INFO",MB_OK);
			return;
		}		
		rectImg.top=120; rectImg.left=10+(i-1)*100; rectImg.right=10+(i-1)*100+90; rectImg.bottom=120+100;
		tmpDIB->PaintDIB(dc.m_hDC,&rectImg);
		delete tmpDIB;
	}
	for(i=6;i<=10;i++)
	{
		str_tmp=m_path+fileName[i];
		tmpDIB=new CDIB(str_tmp.GetBuffer(str_tmp.GetLength()));
		if(tmpDIB==NULL)
		{
			MessageBox("读表情帧失败！","INFO",MB_OK);
			return;
		}		
		rectImg.top=230; rectImg.left=10+(i-6)*100; rectImg.right=10+(i-6)*100+90; rectImg.bottom=230+100;
		tmpDIB->PaintDIB(dc.m_hDC,&rectImg);
		delete tmpDIB;
	}
}
