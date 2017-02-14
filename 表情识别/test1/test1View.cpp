// test1View.cpp : implementation of the CTest1View class
//

#include "stdafx.h"
#include "test1.h"

#include "YeahDlg.h"
#include "test1Doc.h"
#include "test1View.h"

#include "DlgKeyResult.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest1View

IMPLEMENT_DYNCREATE(CTest1View, CScrollView)

BEGIN_MESSAGE_MAP(CTest1View, CScrollView)
	//{{AFX_MSG_MAP(CTest1View)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_IMAGE_SUB1, OnImageSub1)
	ON_COMMAND(ID_IMAGE_SUB2, OnImageSub2)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_SUB1, OnUpdateImageSub1)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_SUB2, OnUpdateImageSub2)
	ON_COMMAND(ID_IMAGE_DATA, OnImageData)
	ON_COMMAND(ID_GABORTF, OnGabortf)
	ON_COMMAND(ID_GABOR_SAVE, OnGaborSave)
	ON_COMMAND(ID_GABORTF2, OnGabortf2)
	ON_COMMAND(ID_YEAH_FRAMES, OnYeahFrames)
	ON_COMMAND(ID_YEAH_DETECT, OnYeahDetect)
	ON_UPDATE_COMMAND_UI(ID_YEAH_DETECT, OnUpdateYeahDetect)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)

	ON_MESSAGE(WM_GOODBYE, OnGoodBye)
	ON_MESSAGE(WM_DETYEAHKEY, OnDetYeahKey)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest1View construction/destruction

CTest1View::CTest1View():m_flagSub(FALSE),m_flagMove(FALSE),m_subRect(0,0,0,0)
{
	// TODO: add construction code here
	m_drawKinds=1;//绘图种类(1-图像,2-图像中的数据,3-Gabor变换结果)

}

CTest1View::~CTest1View()
{
	//销毁我的视频窗口
	delete m_pDlgYeah;
}

BOOL CTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	////初始化我的我的视频帧窗口
	m_pDlgYeah = new CYeahDlg(this);
	m_bYeahDis = FALSE;
	m_bYeahDetect =FALSE; //Can not detect key frame of yeah

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTest1View drawing

void CTest1View::OnDraw(CDC* pDC)
{
	CTest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(pDoc->GetDIB()==NULL)
	{
		MessageBox("图像文件不存在！绘制无法完成！");
		return;
	}
	//////////////绘图
	CRect rcDest;
	CSize sizeSRC;
	CSize _size;
	int w,h;
	int widthBytes;
	CString str;
	CDIB* pDIB;
	LPSTR lpbi;
	LPSTR image;
switch(m_drawKinds)
{
case 1:
	BeginWaitCursor();
		//CRect rcDest; //图像的目标绘图区
	//	CSize 
			sizeSRC=pDoc->GetDIB()->GetDIBSize();
		if(pDC->IsPrinting())//打印
		{
			int cxPage=pDC->GetDeviceCaps(HORZRES);
			int cyPage=pDC->GetDeviceCaps(VERTRES);
			int cxInch=pDC->GetDeviceCaps(LOGPIXELSX);
			int cyInch=pDC->GetDeviceCaps(LOGPIXELSY);
			rcDest.left=rcDest.top=0;
			rcDest.bottom=(int)(((double)sizeSRC.cy*cxPage*cyInch)/((double)sizeSRC.cx*cxInch));
			rcDest.right=cxPage;
			int temp=cyPage-(rcDest.bottom-rcDest.top);
			rcDest.bottom+=temp/2;
			rcDest.top+=temp/2;
		}
		else
		{
			rcDest.top=rcDest.left=0;
			rcDest.right=sizeSRC.cx;
			rcDest.bottom=sizeSRC.cy;
		}
		if(!pDoc->GetDIB()->PaintDIB(pDC->m_hDC,&rcDest))
			MessageBox("绘图出现错误");
	EndWaitCursor();
	break;//end of case 1
case 2://打印出图像数据
	//CSize _size;
	//int w,h;
	//CString str;
	//CDIB*
	pDIB=GetDocument()->GetDIB();
	_size=pDIB->GetDIBSize();
	lpbi=(LPSTR)::GlobalLock((HGLOBAL)pDIB->GetHDIB());
	image=pDIB->FindDIBBits(lpbi);
	widthBytes=WIDTHBYTES(_size.cx*8);
	for(h=0;h<_size.cy;h++)
		for(w=0;w<_size.cx;w++)
		{
			str.Empty();
			str.Format("%d",(unsigned char)image[(_size.cy-1-h)*widthBytes+w]);
			pDC->TextOut(w*25,h*20,str);
		}
		::GlobalUnlock((HGLOBAL)pDIB->GetHDIB());
	break;
case 3://draw Gabor TF result
	GetDocument()->m_pexpStrategy->Draw(pDC);
	break;
case 4:
	rcDest.top=rcDest.left=0;
	rcDest.bottom=pDoc->m_pexpStrategy->m_pDIB->GetDIBSize().cy;
	rcDest.right=pDoc->m_pexpStrategy->m_pDIB->GetDIBSize().cx;
	GetDocument()->m_pexpStrategy->m_pDIB->PaintDIB(pDC->m_hDC,&rcDest);
	break;
default:
	break;
}
}

void CTest1View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CTest1View printing

BOOL CTest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTest1View diagnostics

#ifdef _DEBUG
void CTest1View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTest1View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTest1Doc* CTest1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTest1Doc)));
	return (CTest1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTest1View message handlers

BOOL CTest1View::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush brush(GetDocument()->m_refColorBKG);
	CBrush* pOldBrush=pDC->SelectObject(&brush);
	CRect rectClip;
	pDC->GetClipBox(&rectClip);
	pDC->PatBlt(rectClip.left,rectClip.top,rectClip.Width(),rectClip.Height(),PATCOPY);
	pDC->SelectObject(pOldBrush);	
	return TRUE;	
///	return CScrollView::OnEraseBkgnd(pDC);
}


void CTest1View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_flagSub)
	{
		m_flagMove=FALSE;
		m_subRect.right=point.x;
		m_subRect.bottom=point.y;
	}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CTest1View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_flagSub&&m_flagMove)
	{
		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		CPen newPen,*oldPen;
		CBrush *oldBrush;
		newPen.CreatePen(PS_SOLID,1,RGB(255,0,0));
		oldPen=dc.SelectObject(&newPen);
		oldBrush=(CBrush*)dc.SelectStockObject(NULL_BRUSH);
		dc.Rectangle(&m_subRect);
		m_subRect.right=point.x;
		m_subRect.bottom=point.y;
		dc.Rectangle(&m_subRect);
		dc.SelectObject(oldPen);
		dc.SelectObject(oldBrush);
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CTest1View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_flagSub)
	{
		m_flagMove=TRUE;
		m_subRect.left=point.x;
		m_subRect.top=point.y;
		m_subRect.right=point.x;
		m_subRect.bottom=point.y;
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CTest1View::OnImageSub1() 
{
	// TODO: Add your command handler code here
	m_flagSub=TRUE;
	
}

void CTest1View::OnImageSub2() 
{
	// TODO: Add your command handler code here
	m_flagSub=FALSE;
	GetDocument()->SetSubRect(m_subRect);
	
}

void CTest1View::OnUpdateImageSub1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_flagSub)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable();
}

void CTest1View::OnUpdateImageSub2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!m_flagSub)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable();	
}

void CTest1View::OnImageData() 
{
	// TODO: Add your command handler code here
	m_drawKinds=2;
	this->Invalidate();
	
}

void CTest1View::OnGabortf() 
{
	if(!GetDocument()->m_fTmpInit)
	{
		MessageBox("请先初始化模板");
		return;
	}
	// TODO: Add your command handler code here
	CDIB *pDIB=GetDocument()->GetDIB();
	GetDocument()->m_pexpStrategy->GaborTF(pDIB,0,0,pDIB->GetDIBSize().cx,pDIB->GetDIBSize().cy,TRUE);
	m_drawKinds=3;
	//m_drawKinds=4;
	this->Invalidate();
}

void CTest1View::OnGaborSave() 
{
	// TODO: Add your command handler code here
	if(GetDocument()->m_pexpStrategy->m_pDIB==NULL)
		return;
	CFileDialog dialog(FALSE);
	CString fileName;
	if(dialog.DoModal()==IDOK)
	{
		fileName=dialog.GetPathName();
		MessageBox(fileName);
		GetDocument()->m_pexpStrategy->m_pDIB->SaveDIB(fileName.GetBuffer(fileName.GetLength()));
	}
}

void CTest1View::OnGabortf2() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	if(!GetDocument()->m_fTmpInit)
	{
		MessageBox("请先初始化模板");
		return;
	}
	CDIB *pDIB=GetDocument()->GetDIB();
	GetDocument()->m_pexpStrategy->GaborTF(pDIB,0,0,pDIB->GetDIBSize().cx,pDIB->GetDIBSize().cy,TRUE);
	//m_drawKinds=3;
	m_drawKinds=4;
	this->Invalidate();	
}

void CTest1View::OnYeahFrames() 
{
	// TODO: Add your command handler code here
	m_bYeahDis = !m_bYeahDis;
	m_bYeahDetect = TRUE; //Can detect the key frame of yeah
	m_pDlgYeah->m_path = "D:\\expressiondb\\videoframes\\256\\surprise\\";
	if(m_bYeahDis){
		m_pDlgYeah->MyCreate();
	}
	else {
		m_pDlgYeah->DestroyWindow();
	}
	
}

LRESULT CTest1View::OnGoodBye(WPARAM wParam,LPARAM lParam)
{
	m_pDlgYeah->DestroyWindow();
	m_bYeahDis = FALSE;
	return 0L;
}

/*
 *	关键帧检测，调用对话框输出欧氏距离的变化曲线，并检测关键帧
 */
void CTest1View::OnYeahDetect() 
{
	// TODO: Add your command handler code here
	if (m_pDlgYeah == NULL) {
		AfxMessageBox("The keyFrames Dialog is NULL");
		return;
	}
	CDlgKeyResult dlgResult;
	int i;
	for (i = 0; i < 40 ; i ++){
		dlgResult.m_fDis[i] = m_pDlgYeah->m_fDis[i];
	}
	dlgResult.m_bPaint = TRUE;
	dlgResult.m_path = "D:\\expressiondb\\videoframes\\256\\surprise\\";
	dlgResult.DoModal();	
}

void CTest1View::OnUpdateYeahDetect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bYeahDetect);
}

LRESULT CTest1View::OnDetYeahKey(WPARAM wParam,LPARAM lParam)
{
	OnYeahDetect();
	return 0L;
}
