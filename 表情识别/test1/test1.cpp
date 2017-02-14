// test1.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "test1.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "test1Doc.h"
#include "test1View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest1App

BEGIN_MESSAGE_MAP(CTest1App, CWinApp)
	//{{AFX_MSG_MAP(CTest1App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_INIT_TEMPS, OnInitTemps)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest1App construction

//构造函数做两件事:初始化Gabor小波函数以及初始化表情模板(加载)
CTest1App::CTest1App()
{
	m_expStrategy.Initialize();//初始化Gabor滤波器
		m_fTmpInit=FALSE;
		m_K=13;//13近邻,以前是5
	//	m_K=1;//1近邻,即选择最小能量为识别结果
		///
		m_EGTemp=new CEGraph();//模板链表的一个元素不存数据，目的是为了更方便操作
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTest1App object

CTest1App theApp;

/////////////////////////////////////////////////////////////////////////////
// CTest1App initialization

BOOL CTest1App::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_TEST1TYPE,
		RUNTIME_CLASS(CTest1Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CTest1View));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	cmdInfo.m_nShellCommand=CCommandLineInfo::FileNothing;
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();


// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CTest1App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTest1App message handlers


void CTest1App::OnInitTemps() 
{
	// TODO: Add your command handler code here
	if(m_fTmpInit)
		return;

	enum expressionKind fileKind[6]={angry,sadness,surprise,disgust,smile,fear};
    CString filePath="D:\\expressiondb\\temp_2_norm\\";
	CString subPath[6]={"angry\\","sadness\\","surprise\\","disgust\\","smile\\","fear\\"};

	CString str_tmp1,str_tmp2;
	CDIB *tempDIB;
	CEGraph *tmpEGraph,*pEG;
	int i;
//MessageBox(NULL,filePath+fileName[0],"success",MB_OK);
	BeginWaitCursor();
	for(i=0;i<TEMP_NUM;i++)
	{
		str_tmp1.Format("%d.bmp",i%8+1);
		str_tmp2=filePath+subPath[i/8]+str_tmp1;
		tempDIB=new CDIB(str_tmp2.GetBuffer(str_tmp2.GetLength()));
		if(tempDIB==NULL)
		{
			MessageBox(NULL,"初始化模板失败！",NULL,MB_OK);
			break;
		}
		//important:调用主体算法(init_tempExpr),构造弹性图
		//弹性图保存在CEGraph::m_pvGraph指针数组中
		tmpEGraph=new CEGraph();
		if(!(tmpEGraph->init_tempExpr(tempDIB,&m_expStrategy)))
		{//构造模板弹性图失败
			MessageBox(NULL,"构造模板弹性图失败：tmpEGraph->init_tempExpr",NULL,MB_OK);
			break;
		}
		//赋予模板弹性图的表情类型
		tmpEGraph->m_kind=fileKind[i/8];
		//将该模板弹性图放入链表的末尾
		pEG=m_EGTemp;
		while(pEG->m_pNext!=NULL)
			pEG=pEG->m_pNext;
		pEG->m_pNext=tmpEGraph;
		delete tempDIB;//删除模板图像，下次循环时便于调入下张图像
	}
	EndWaitCursor();
	m_fTmpInit=TRUE;
//	filePath+=fileName;
	MessageBox(NULL,"初始化模板成功","OK",MB_OK);	
}

void CTest1App::OnFinalRelease() 
{
	// TODO: Add your specialized code here and/or call the base class
	CEGraph *pGraph1, *pGraph2;
	pGraph1=pGraph2=m_EGTemp;
	while(pGraph1->m_pNext!=NULL)
	{
		pGraph2=pGraph1->m_pNext;
		delete pGraph1;
		pGraph1=pGraph2;
	}
	delete pGraph1;
	
	CWinApp::OnFinalRelease();
}
