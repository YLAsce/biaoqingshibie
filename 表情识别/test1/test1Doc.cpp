// test1Doc.cpp : implementation of the CTest1Doc class
//

#include "stdafx.h"
#include "test1.h"

#include "test1Doc.h"
#include "EGTemp.h"
#include "dlgTemp.h"
#include "dlgDetectFrame.h"
#include "dlgDisplayFrames.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest1Doc

IMPLEMENT_DYNCREATE(CTest1Doc, CDocument)

BEGIN_MESSAGE_MAP(CTest1Doc, CDocument)
	//{{AFX_MSG_MAP(CTest1Doc)
	ON_COMMAND(ID_MENUTWOVALUE, OnMenutwovalue)
	ON_COMMAND(ID_TEMP_INIT, OnTempInit)
	ON_COMMAND(ID_TEMP_RECOG, OnTempRecog)
	ON_COMMAND(ID_PRENORMAL1, OnPrenormal1)
	ON_COMMAND(ID_DETECT_KEYFRAME, OnDetectKeyframe)
	ON_COMMAND(ID_DETECT_DIS, OnDetectDis)
	ON_COMMAND(ID_TEST_KEYPOINT, OnTestKeypoint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest1Doc construction/destruction

CTest1Doc::CTest1Doc()
{
	// TODO: add one-time construction code here
		m_refColorBKG=0x00808080;
	CTest1App *myApp=(CTest1App*)AfxGetApp();
	if(!myApp->m_fTmpInit)
		myApp->OnInitTemps();
	m_pexpStrategy=&(myApp->m_expStrategy);//��ʼ��Gabor�˲���
	m_K=myApp->m_K;
	m_EGTemp=myApp->m_EGTemp;
	m_fTmpInit=myApp->m_fTmpInit;
		int i;
		for(i=0;i<TEMP_NUM;i++)
					m_temp[i]=NULL;
//m_fTmpInit=TRUE;
	//	m_K=13;//13����,��ǰ��5
	//	m_K=1;//1����,��ѡ����С����Ϊʶ����
		///
//		m_EGTemp=new CEGraph();//ģ�������һ��Ԫ�ز������ݣ�Ŀ����Ϊ�˸��������
}

CTest1Doc::~CTest1Doc()
{
	if(m_pDIB!=NULL)
		delete m_pDIB;
	int i;
	for(i=0;i<TEMP_NUM;i++)
	{
		if(m_temp[i]!=NULL)
		  delete[] m_temp[i];
	}
//	m_expStrategy.EGraph=NULL;
}

BOOL CTest1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTest1Doc serialization

void CTest1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTest1Doc diagnostics

#ifdef _DEBUG
void CTest1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTest1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTest1Doc commands

BOOL CTest1Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	printf("%s", lpszPathName);
	// TODO: Add your specialized creation code here
	BeginWaitCursor();
	m_pDIB=new CDIB(lpszPathName);
	EndWaitCursor();
	m_hDIB=m_pDIB->GetHDIB();
	if(m_hDIB==NULL) 
	{
		MessageBox(NULL,"��ͼ���ļ�����",NULL,MB_OK);
		delete m_pDIB;
		m_pDIB=NULL;
		return FALSE;
	}
	SetPathName(lpszPathName);
	SetModifiedFlag(FALSE);
	return TRUE;
}

CDIB* CTest1Doc::GetDIB() const
{
	return m_pDIB;
}

void CTest1Doc::SetSubRect(CRect &_rect)
{
	CDIB* _pDIB=new CDIB(m_pDIB,_rect.left,_rect.top,_rect.right,_rect.bottom);
	if(_pDIB->GetHDIB()==NULL)
	{
		MessageBox(NULL,"�ָ���ͼ�����",NULL,MB_OK);
		delete _pDIB;
		return;
	}
	delete m_pDIB;
	m_pDIB=_pDIB;
	m_hDIB=m_pDIB->GetHDIB();
	UpdateAllViews(NULL);
}

BOOL CTest1Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
//	MessageBox(NULL,"Hello",NULL,MB_OK)	;
	BeginWaitCursor();
	if(!m_pDIB->SaveDIB(lpszPathName))
	{
		MessageBox(NULL,"�����ļ����ִ���",NULL,MB_OK);
		EndWaitCursor();
		return FALSE;
	}
	return TRUE;
//һ��Ҫ������ĵ��û��ຯ�������ע�͵�������д�����ļ��У��м�!!
//	return CDocument::OnSaveDocument(lpszPathName);
}

void CTest1Doc::OnMenutwovalue() 
{
	// TODO: Add your command handler code here
	int i,j;
	CSize _size;
	int _thredhold=64;
	LPSTR _lpbi;
	int _withbytes;
	unsigned char* _image;
	_lpbi=(LPSTR)::GlobalLock((HGLOBAL)m_hDIB);
	_image=(unsigned char*)m_pDIB->FindDIBBits(_lpbi);
	_size=m_pDIB->GetDIBSize();
	_withbytes=WIDTHBYTES(_size.cx*8);
	for(i=0;i<_size.cy;i++)
		for(j=0;j<_size.cx;j++)
		{
			*(_image+i*_withbytes+j)=(*(_image+i*_withbytes+j)<64)?0:255;
		}
		::GlobalUnlock((HGLOBAL)m_hDIB);
		this->UpdateAllViews(NULL);
}

void CTest1Doc::OnTempInit() 
{
	if(!m_fTmpInit)
	{
		MessageBox(NULL,"��ʼ����ģ�����!",NULL,MB_OK);
		return;
	}
	

/*	CDlgTemp tempDlg;
	tempDlg.m_pDIB=m_pDIB;
	tempDlg.m_pStrategy=&m_expStrategy;
	tempDlg.DoModal();
	CEGTemp temp_EG;
	temp_EG.m_pDIB=m_pDIB;
	temp_EG.DoModal();

/
//	if(temp_EG.DoModal()==IDOK)
//		MessageBox(NULL,"��ʼ���ɹ�","OK",MB_OK);
//	else
//		MessageBox(NULL,"FAIL",NULL,MB_OK);
	//m_expStrategy�ĳ�ʼ��������Doc�Ĺ��캯���н��У����ﲻ��Ҫ
//	m_expStrategy.Initialize();
///�������汻ע�͵Ĳ���
//ģ�屣���ھ���·����E:\expressiondb\EGM_templates
//5�ֱ���(angry,sadness,surprise/fear,disgust,smile),����surprise��fear�������֣��ʷ���һ��
//����һ�����Ա���neutrality
	enum expressionKind fileKind[6]={angry,sadness,surprise,disgust,smile,neutrality};
    CString filePath="E:\\expressiondb\\EGM_templates\\";
	CString fileName[TEMP_NUM]={
			"angry1.bmp","sadness1.bmp","surprise1.bmp","disgust1.bmp","smile1.bmp","neutrality1.bmp",
				"angry2.bmp","sadness2.bmp","surprise2.bmp","disgust2.bmp","smile2.bmp","neutrality2.bmp",
				"angry3.bmp","sadness3.bmp","surprise3.bmp","disgust3.bmp","smile3.bmp","neutrality3.bmp"
		  // "sad_lefteye.bmp","sad_righteye.bmp","sad_mouth.bmp"
	};
	CString str_tmp;
	CDIB *tempDIB;
	CEGraph *tmpEGraph,*pEG;
	int i;
//MessageBox(NULL,filePath+fileName[0],"success",MB_OK);
	BeginWaitCursor();
	for(i=0;i<TEMP_NUM;i++)
	{
		str_tmp=filePath+fileName[i];
		tempDIB=new CDIB(str_tmp.GetBuffer(str_tmp.GetLength()));
		if(tempDIB==NULL)
		{
			MessageBox(NULL,"��ʼ��ģ��ʧ�ܣ�",NULL,MB_OK);
			break;
		}
		//important:���������㷨(init_tempExpr),���쵯��ͼ
		//����ͼ������CEGraph::m_pvGraphָ��������
		tmpEGraph=new CEGraph();
		if(!(tmpEGraph->init_tempExpr(tempDIB,m_pexpStrategy)))
		{//����ģ�嵯��ͼʧ��
			MessageBox(NULL,"����ģ�嵯��ͼʧ�ܣ�tmpEGraph->init_tempExpr",NULL,MB_OK);
			break;
		}
		//����ģ�嵯��ͼ�ı�������
		tmpEGraph->m_kind=fileKind[i%6];
		//����ģ�嵯��ͼ���������ĩβ
		pEG=m_EGTemp;
		while(pEG->m_pNext!=NULL)
			pEG=pEG->m_pNext;
		pEG->m_pNext=tmpEGraph;
		delete tempDIB;//ɾ��ģ��ͼ���´�ѭ��ʱ���ڵ�������ͼ��
	}
	EndWaitCursor();
	m_fTmpInit=TRUE;
//	filePath+=fileName;
	MessageBox(NULL,"��ʼ��ģ��ɹ�","OK",MB_OK);
	
	// TODO: Add your command handler code here
	//ģ�屣���ھ���·����E:\expressiondb\templetes
	/*CString filePath="E:\\expressiondb\\templetes\\";
	CString fileName[TEMP_NUM]={
		   "ang_lefteye.bmp","ang_righteye.bmp","ang_mouth.bmp",
		   "dis_lefteye.bmp","dis_righteye.bmp","dis_mouth.bmp",
		   "neu_lefteye.bmp","neu_righteye.bmp","neu_mouth.bmp",
		   "sad_lefteye.bmp","sad_righteye.bmp","sad_mouth.bmp",
		   "smi_lefteye.bmp","smi_righteye.bmp","smi_mouth.bmp",
		   "sur_lefteye.bmp","sur_righteye.bmp","sur_mouth.bmp"
		  // "sad_lefteye.bmp","sad_righteye.bmp","sad_mouth.bmp"
	};
	CString str_tmp;
	CDIB *tempDIB;
	int i;
MessageBox(NULL,filePath+fileName[0],"success",MB_OK);
	BeginWaitCursor();
	for(i=0;i<TEMP_NUM;i++)
	{
		str_tmp=filePath+fileName[i];
		tempDIB=new CDIB(str_tmp.GetBuffer(str_tmp.GetLength()));
		if(tempDIB==NULL)
		{
			MessageBox(NULL,"��ʼ��ģ��ʧ�ܣ�",NULL,MB_OK);
			break;
		}
		m_expStrategy.GaborTF(tempDIB,0,0,tempDIB->GetDIBSize().cx,tempDIB->GetDIBSize().cy);
		m_temp[i]=m_expStrategy.EGraph;
		m_tempSize[i].cx=m_expStrategy.grids_x;
		m_tempSize[i].cy=m_expStrategy.grids_y;
		delete tempDIB;
	}
	EndWaitCursor();
	m_expStrategy.EGraph=NULL;
	m_fTmpInit=TRUE;
//	filePath+=fileName;
	MessageBox(NULL,"��ʼ��ģ��ɹ�","OK",MB_OK);
	*/
}

void CTest1Doc::OnTempRecog() 
{
//	CTest1App *myApp=(CTest1App*)AfxGetApp();

	// TODO: Add your command handler code here
	if(!m_fTmpInit)
	{
		MessageBox(NULL,"û�г�ʼ��ģ��","OK",MB_OK);
		return;
	}
	CDlgResult dlgResult;
//	if(m_expStrategy.EGraph==NULL)
//	{
//		MessageBox(NULL,"��Ե�ǰͼ�����Gabor�任��Ȼ���ٽ���ģ��ƥ��","OK",MB_OK);
//		return;	
//	}
 // enum expressionKind fileKind[6]={angry,sadness,surprise,disgust,smile,neutrality};
 SYSTEMTIME starttime, endtime;
 ::GetSystemTime(&starttime);
///�����ʶ�����ͼ��ĵ���ͼ,����testEG
	CEGraph *testEG, *pEG;
	testEG=new CEGraph();
	if(!(testEG->init_testExpr(m_pDIB,m_pexpStrategy)))
	{
		MessageBox(NULL,"���챻�����ĵ���ͼʧ�ܣ�","OK",MB_OK);
		return;
	}
////////////////�����ִ�������Ĳ���
	int i;//ѭ������
	FLOAT tmpDis;
	FLOAT *f_result=new FLOAT[m_K];//������С��m_K������
	int *i_kinds=new int[m_K];//�����Ӧ�ĺ�ѡ��
	int i_result[6]={0,0,0,0,0,0};//����ÿ�ֵĵ�Ʊ��
//	FLOAT f_result[6]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};//����ÿ�ֵĵ÷�
	FLOAT f_minDis[6]={650000.0f,650000.0f,650000.0f,650000.0f,650000.0f,650000.0f};//����ÿ�ֵ���С����
//	FLOAT f_minDis[6]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};//����ÿ�ֵ���С����
	int i_max_num;//���Ʊ��
	int i_max_kind,i_flag;//��Ѻ�ѡ��
	CString _result[6]={//����ʶ����
		"angry","sadness","surprise","disgust","smile","fear"
	};
	int currentNum;//��¼��ǰ�ܵ�Ʊ��������ֵ����m_Kʱ������ĳ�౻��̭��tmpKind��¼��������̭�����
	for(i=0;i<m_K;i++)//��ʼ��ǰm_K����С����
	{
		f_result[i]=650000.0f;
	}
	currentNum=0;
	pEG=m_EGTemp->m_pNext;
	while(pEG!=NULL)
	{
		tmpDis=testEG->CalEnergy(pEG);
		if(currentNum<m_K)
		{//��Ʊ������m_K,���þ��μ��뵽f_result�У����޸Ķ�Ӧ��i_kinds
			int tmp_i;//�µĽ�����뽫���뵽tmp_i+1��
			int tmp_j;
			for(tmp_i=currentNum-1;tmp_i>=0;tmp_i--)
			{
				if(tmpDis>f_result[tmp_i])
					break;
			}
			for(tmp_j=currentNum;tmp_j>tmp_i+1;tmp_j--)
			{
				f_result[tmp_j]=f_result[tmp_j-1];
				i_kinds[tmp_j]=i_kinds[tmp_j-1];
			}
			f_result[tmp_j]=tmpDis;
			i_kinds[tmp_j]=pEG->m_kind;
			currentNum++;
		}
		else if(tmpDis < f_result[m_K-1])
		{//��ǰ��Ʊ���պ�Ϊm_K,�����������ʱ����Ҫ��̭ĳ�����
			int tmp_i;//�µĽ�����뽫���뵽tmp_i+1��
			int tmp_j;
			for(tmp_i=m_K-1;tmp_i>=0;tmp_i--)
			{
				if(tmpDis>f_result[tmp_i])
					break;
			}
			for(tmp_j=m_K-1;tmp_j>tmp_i+1;tmp_j--)
			{
				f_result[tmp_j]=f_result[tmp_j-1];
				i_kinds[tmp_j]=i_kinds[tmp_j-1];
			}
			f_result[tmp_j]=tmpDis;
			i_kinds[tmp_j]=pEG->m_kind;
		}
		pEG=pEG->m_pNext;
	}
  //m_K����ʶ��
/*********************************�㷨0****************
	for(i=0;i<m_K;i++)
	{
		i_result[i_kinds[i]]++;
		if(f_result[i]<f_minDis[i_kinds[i]])
			f_minDis[i_kinds[i]]=f_result[i];
	}
	i_max_num=-1;
	for(i=0;i<6;i++)
	{
		if(i_max_num<i_result[i])
		{
			i_max_num=i_result[i];
			i_max_kind=i;
		}
		else if((i_max_num==i_result[i])&&(f_minDis[i]<f_minDis[i_max_kind]))
			i_max_kind=i;
	}
*************************************************/
///////////************************�㷨1***************************
	int i_weight[13]={80,68,57,47,38,30,23,17,12,8,5,3,2};//ֻ������m_K=13�����
	for(i=0;i<m_K;i++)
	{
		i_result[i_kinds[i]]+=i_weight[i];
	}
	i_max_num=-1;
	for(i=0;i<6;i++)
	{
		if(i_max_num<i_result[i])
		{
			i_max_num=i_result[i];
			i_max_kind=i;
		}
		else if((i_max_num==i_result[i])&&(f_minDis[i]<f_minDis[i_max_kind]))
			i_max_kind=i;
	}
///////////********************************************************
	i_flag=i_max_kind;

	 ::GetSystemTime(&endtime);
	 WORD period=1000*(endtime.wSecond-starttime.wSecond)+endtime.wMilliseconds-starttime.wMilliseconds;
	CString str_period;
	str_period.Format("%d ����!",period);
	dlgResult.m_time=str_period;
	dlgResult.m_result=_result[i_flag];
	for(i=0;i<m_K;i++)
	{
		str_period.Format(": %f",f_result[i]);
		dlgResult.m_dises[i]=_result[i_kinds[i]]+str_period;
	}
	dlgResult.DoModal();
	delete [] f_result;
	delete [] i_kinds;
/////////////////////////////////
/*
	//////////ƥ�䣬ʶ��:���õ���ͼƥ���㷨��K����ʶ��(K=5)
//	FLOAT *minDis;
//	int *minDisSub;
	int i;
    enum expressionKind tmpKind;
	int currentNum;//��¼��ǰ�ܵ�Ʊ��������ֵ����m_Kʱ������ĳ�౻��̭��tmpKind��¼��������̭�����
	CString _result[6]={//����ʶ����
		"angry","sadness","surprise","disgust","smile","neutrality"
	};
//	for(i=0;i<6;i++)
//	{
//		MessageBox(NULL,_result[fileKind[i]],NULL,MB_OK);
//	}
	int i_result[6]={0,0,0,0,0,0};//��¼ÿ�����ĵ�Ʊ
	FLOAT f_maxDis[6]={-650000.0f,-650000.0f,-650000.0f,-650000.0f,-650000.0f,-650000.0f};//��¼ÿ������Ӧ����С����
	FLOAT f_minDis[6]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};//��¼ÿ������Ӧ���������
	FLOAT maxDis=-650000.0f;
	FLOAT minDis=0.0f;
	int i_max;//����Ʊ��
	int i_flag;//��¼����ʶ����
	FLOAT tmpDis;
//	i_max=-1;
//	i_flag=-1;
//	minDis=new FLOAT[m_K];
//	minDisSub=new int[m_K];
//	for(i=0;i<m_K;i++)
//	{
//		minDis[i]=650000.0f;
//		minDisSub[i]=-1;
//	}
	currentNum=0;
	pEG=m_EGTemp->m_pNext;
	while(pEG!=NULL)
	{//��ģ�嵯��ͼ�����е�ÿһ������ͼ�Ƚ���С����
		tmpDis=testEG->CalEnergy(pEG);
		if(currentNum<m_K)
		{//��Ʊ������m_K,����ǰ������i_result��f_minDis��
			i_result[pEG->m_kind]++;
			if(tmpDis<f_minDis[pEG->m_kind])
			{
				f_minDis[pEG->m_kind]=tmpDis;
			}
			if(tmpDis > f_maxDis[pEG->m_kind])
			{
				f_maxDis[pEG->m_kind]=tmpDis;
			}
			if(maxDis < tmpDis)
			{
				maxDis=tmpDis;
				tmpKind=pEG->m_kind;
			}
			currentNum++;
		}
		else if(tmpDis < maxDis)
		{//��ǰ��Ʊ���պ�Ϊm_K,�����������ʱ����Ҫ��̭ĳ����𣬼������������Ʊ����1
			i_result[tmpKind]--;//����ط������⣬��Ϊ�Ѹú�ѡ��Ʊ����һ�����������û�иĵ�����һ�������������
			i_result[pEG->m_kind]++;
			if(tmpDis<f_minDis[pEG->m_kind])
			{
				f_minDis[pEG->m_kind]=tmpDis;
			}
			if(tmpDis>f_maxDis[pEG->m_kind])
			{
				f_maxDis[pEG->m_kind]=tmpDis;				
			}
			//maxDis=0.0f;
			maxDis=-650000.0f;
			for(i=0;i<6;i++)
			{//���¼����������������������������maxDis��tmpKind
				if(maxDis < f_maxDis[i])
				{
					maxDis=f_maxDis[i];
					tmpKind=(enum expressionKind)i;
				}
			}
		}
		pEG=pEG->m_pNext;
	}


	//K���ڣ�ͳ�Ƶ�Ʊ���ģ����������ͬ�������ѡ����С������Ϊ���
	i_max=0;
	i_flag=-1;
	for(i=0;i<6;i++)
	{
		if(i_max < i_result[i])
		{
			i_max=i_result[i];
			i_flag=i;
		}
		else if(i_max==i_result[i])
		{
			if(f_minDis[i_flag] > f_minDis[i])
			{
				i_flag=i;
			}
		}
	}
*/
//	 ::GetSystemTime(&endtime);
//	 WORD period=1000*(endtime.wSecond-starttime.wSecond)+endtime.wMilliseconds-starttime.wMilliseconds;
//	CString str_period;
//	str_period.Format("������ʱ�䣺%d ����!",period);
//	MessageBox(NULL,str_period,"INFO",MB_OK);
	 /*	for(i=0;i<6;i++)
	{
		if(i_max<i_result[i])
		{
			i_max=i_result[i];
			//i_flag=i;
		}
	}
	for(i=0;i<m_K;i++)
	{
		if(i_max==i_result[minDisSub[i]])
			i_flag=minDisSub[i];
	}*/
//	if(i_flag==-1)
//		MessageBox(NULL,"ʶ���е�����","ʶ����",MB_OK);
//	else
//		MessageBox(NULL,_result[i_flag],"ʶ����",MB_OK);
}

void CTest1Doc::OnCloseDocument() 
{
/*	// TODO: Add your specialized code here and/or call the base class
	if(m_pDIB!=NULL)
		delete m_pDIB;
	int i;
	for(i=0;i<TEMP_NUM;i++)
	{
		if(m_temp[i]!=NULL)
		  delete m_temp[i];
	}	*/
	CDocument::OnCloseDocument();
}

void CTest1Doc::insertMinDis(FLOAT *minDis, int *minDisSub, int *currentNum, int i_result[], FLOAT tmpDis, int i)
{
	int m,n;
	if(*currentNum==0)
	{
		*currentNum+=1;
		minDis[0]=tmpDis;
		i_result[i]++;
		return;
	}
	m=0;
	while(m<*currentNum)
	{
		if(minDis[m]>tmpDis)
		{
			if(*currentNum==m_K)
			{
				i_result[minDisSub[*currentNum-1]]--;
			}
			for(n=*currentNum;n>m;n--)
			{
				minDis[n]=minDis[n-1];
				minDisSub[n]=minDisSub[n-1];
			}
			minDis[m]=tmpDis;
			minDisSub[m]=i;
			i_result[i]++;
			break;
		}
	    m++;
	}
	if(*currentNum<m_K)
		(*currentNum)++;
}

void CTest1Doc::OnPrenormal1() 
{
	// TODO: Add your command handler code here
	m_pDIB->ScaleNormal(CSize(90,100));
	this->UpdateAllViews(NULL);
}

void CTest1Doc::OnDetectKeyframe() 
{
	// TODO: Add your command handler code here
	 SYSTEMTIME starttime, endtime;

	CString filePath="D:\\expressiondb\\detectkeyframe\\";
	CString fileName[11]={
			"neutrality.bmp","frame1.bmp","frame2.bmp","frame3.bmp","frame4.bmp","frame5.bmp",
				"frame6.bmp","frame7.bmp","frame8.bmp","frame9.bmp","frame10.bmp"};
	CString str_tmp;
	CDIB *tempDIB;
	CEGraph *tmpEGraph,*NeuEG;
	int i;
	FLOAT f_dis[10]={65000.0f,65000.0f,65000.0f,65000.0f,
		65000.0f,65000.0f,65000.0f,65000.0f,65000.0f,65000.0f};//�������Ա�����������������С����
//MessageBox(NULL,filePath+fileName[0],"success",MB_OK);
	BeginWaitCursor();
	str_tmp=filePath+fileName[0];
	tempDIB=new CDIB(str_tmp.GetBuffer(str_tmp.GetLength()));
	if(tempDIB==NULL)
	{
		MessageBox(NULL,"�����Ա���ͼʧ�ܣ�",NULL,MB_OK);
		EndWaitCursor();
		return;
	}
	NeuEG=new CEGraph();
	if(!(NeuEG->init_testExpr(tempDIB,m_pexpStrategy)))
	{//����ģ�嵯��ͼʧ��
		MessageBox(NULL,"�������Ե���ͼʧ�ܣ�NeuEG->init_testExpr",NULL,MB_OK);
		delete tempDIB;
		EndWaitCursor();
		return;
	}
	delete tempDIB;
///////////////////////////////////////////////
BOOL b_time;
b_time=TRUE;
	for(i=1;i<11;i++)
	{
		str_tmp=filePath+fileName[i];
		tempDIB=new CDIB(str_tmp.GetBuffer(str_tmp.GetLength()));
		if(tempDIB==NULL)
		{
			MessageBox(NULL,"��ʼ��ģ��ʧ�ܣ�",NULL,MB_OK);
			break;
		}
if(b_time)
{::GetSystemTime(&starttime);}
		tmpEGraph=new CEGraph();
		if(!(tmpEGraph->init_testExpr(tempDIB,m_pexpStrategy)))
		{//����ģ�嵯��ͼʧ��
			MessageBox(NULL,"����ģ�嵯��ͼʧ�ܣ�tmpEGraph->init_tempExpr",NULL,MB_OK);
			delete tempDIB;
			break;
		}
		f_dis[i-1]=NeuEG->Cal_ModuleDis(tmpEGraph);
if(b_time)
{::GetSystemTime(&endtime); b_time=FALSE;}
		delete tempDIB;//ɾ��ģ��ͼ���´�ѭ��ʱ���ڵ�������ͼ��
		delete tmpEGraph;
	}
	delete NeuEG;
	int i_max;
	FLOAT f_max=0.0f;
	for(i=0;i<10;i++)
	{
		if(f_max<f_dis[i])
		{
			f_max=f_dis[i];
			i_max=i+1;
		}
	}
/////////////////////////////////
	WORD period=1000*(endtime.wSecond-starttime.wSecond)+endtime.wMilliseconds-starttime.wMilliseconds;
	CString str_period;
	str_period.Format("���ؼ��滨��%d ����!",10*period);
	EndWaitCursor();	
	MessageBox(NULL,str_period,NULL,MB_OK);
	CDlgDetectFrame dlgFrame;
	dlgFrame.m_key=i_max;
	for(i=0;i<10;i++)
		dlgFrame.m_dis[i]=f_dis[i];
	dlgFrame.DoModal();
}

void CTest1Doc::OnDetectDis() 
{
	// TODO: Add your command handler code here
	CDlgDisplayFrames dlgDisplay;
	dlgDisplay.m_path="D:\\expressiondb\\detectkeyframe\\";
	dlgDisplay.DoModal();	
}

void CTest1Doc::OnTestKeypoint() 
{
	// TODO: Add your command handler code here
	CDlgTemp tempDlg;
	tempDlg.m_pDIB=m_pDIB;
	tempDlg.m_pStrategy=m_pexpStrategy;
	tempDlg.DoModal();
}
