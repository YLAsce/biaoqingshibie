// EGraph.cpp: implementation of the CEGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "test1.h"
#include "EGraph.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEGraph::CEGraph()
{
	m_dimension=0;
	m_pNext=NULL;
	int i;
	for(i=0;i<KEY_NUM;i++)
	{
		m_keyPoints[i].x=0;
		m_keyPoints[i].y=0;
	}
}

CEGraph::~CEGraph()
{//负责释放m_pvGraph中的各个向量
	int i;
	for(i=0;i<m_dimension;i++)
		delete [] m_pvGraph[i];
}

BOOL CEGraph::init_tempExpr(CDIB *pDIB, CExpStrategy *pExpStr)
{
////表情模板也和被测表情图一样，保存所有信息，即得到向量指针18×20个
////该部分代替下面被注释的部分
	if(m_dimension!=0)
		return FALSE;
	CSize sizeDIB=pDIB->GetDIBSize();
	if((sizeDIB.cx!=90)||(sizeDIB.cy!=100))
	{
		MessageBox(NULL,"请先将图像归一为90×100","Information",MB_OK);
		return FALSE;
	}
	int widthBytes=WIDTHBYTES(8*sizeDIB.cx);

	LPSTR lpbi;
	int i,j;
	BYTE *image;
	HDIB tmp_hDIB;
	tmp_hDIB=pDIB->GetHDIB();
	lpbi=(LPSTR)::GlobalLock((HGLOBAL)tmp_hDIB);
	image=(BYTE*)pDIB->FindDIBBits(lpbi);
	for(i=0;i<20;i++)//行
		for(j=0;j<18;j++)//列
		{//m_pvGraph的第0单元存储向量
			m_pvGraph[i*18+j]=pExpStr->GetGaborVector_5(image,j*5,100-i*5-5,widthBytes);
		}
		m_dimension=360;
/////////////////////
	::GlobalUnlock((HGLOBAL)tmp_hDIB);
////计算每个向量的模，并保存入m_module数组中
	for(i=0;i<360;i++)
	{
		m_module[i]=CalModule(m_pvGraph[i]);
	}
//////////////增加的语句：用于检测关键点，只要模板需要，而被测表情图像不需要
//	DetectKeyPoints();
	return TRUE;
///该函数用于创建标准模板表情图像(pDIB,大小90×100)的弹性图
 ///向量分布于眼角、眉毛、额角、嘴巴等共15处
/*
	if(m_dimension!=0)
		return FALSE;
	CSize sizeDIB=pDIB->GetDIBSize();
	if((sizeDIB.cx!=90)||(sizeDIB.cy!=100))
	{
		MessageBox(NULL,"请先将图像归一为90×100","Information",MB_OK);
		return FALSE;
	}
	int widthBytes=WIDTHBYTES(8*sizeDIB.cx);
	LPSTR lpbi;
	int i;
	//保存模板各个关键点的坐标,0单元不用
	//注意图像返过来保存
	int pos_x[16]={0,5,22,26,40,53,58,76,  22,40,53,22,40,53,17,58};
	int pos_y[16]={0,23,8,25,10,25,8,23,  70,70,70,85,85,85,78,78};
	for(i=1;i<16;i++)
		pos_y[i]=95-pos_y[i];
//	LPBITMAPINFO lpbmi;
	BYTE *image;
	HDIB tmp_hDIB;
	tmp_hDIB=pDIB->GetHDIB();
	lpbi=(LPSTR)::GlobalLock((HGLOBAL)tmp_hDIB);
	image=(BYTE*)pDIB->FindDIBBits(lpbi);

	for(i=1;i<=15;i++)
		m_pvGraph[i]=pExpStr->GetGaborVector_5(image,pos_x[i],pos_y[i],widthBytes);
	::GlobalUnlock((HGLOBAL)tmp_hDIB);
	m_dimension=15;
	return TRUE;
	*/
}


BOOL CEGraph::init_testExpr(CDIB *pDIB, CExpStrategy *pExpStr)
{///创建归一化后的被测表情图像(pDIB,90×100)的弹性图
 ///分别提取眼睛(图像的上半部分,90×30)和嘴巴(下半部分,40×30)的特征向量
	if(m_dimension!=0)
		return FALSE;
	CSize sizeDIB=pDIB->GetDIBSize();
	if((sizeDIB.cx!=90)||(sizeDIB.cy!=100))
	{
		MessageBox(NULL,"请先将图像归一为90×100","Information",MB_OK);
		return FALSE;
	}
	int widthBytes=WIDTHBYTES(8*sizeDIB.cx);
	LPSTR lpbi;
	int i,j;
	BYTE *image;
	HDIB tmp_hDIB;
	tmp_hDIB=pDIB->GetHDIB();
	lpbi=(LPSTR)::GlobalLock((HGLOBAL)tmp_hDIB);
	image=(BYTE*)pDIB->FindDIBBits(lpbi);
/////////////10*10:
/*	for(i=0;i<3;i++)//行
		for(j=0;j<9;j++)//列
		{//m_pvGraph的第0单元不存储向量
			m_pvGraph[i*9+j+1]=pExpStr->GetGaborVector(image,j*10,100-i*10-10,widthBytes);
		}
	for(i=0;i<3;i++)
		for(j=0;j<5;j++)
		{
			m_pvGraph[27+i*5+j+1]=pExpStr->GetGaborVector(image,20+j*10,35-i*10-10,widthBytes);
		}
	m_dimension=42;*/
///////////////5*5:
	for(i=0;i<20;i++)//行
		for(j=0;j<18;j++)//列
		{//m_pvGraph的第0单元存储向量
			m_pvGraph[i*18+j]=pExpStr->GetGaborVector_5(image,j*5,100-i*5-5,widthBytes);
		}
		m_dimension=360;
/////////////////////
	::GlobalUnlock((HGLOBAL)tmp_hDIB);
/////计算每个向量的模，并保存入m_module数组中
	for(i=0;i<360;i++)
	{
		m_module[i]=CalModule(m_pvGraph[i]);
	}
/*	for(i=0;i<20;i++)//行
		for(j=0;j<18;j++)//列
			m_module[i*18+j]=j;*/
	return TRUE;
}

/**
采用弹性匹配算法计算本弹性图(待测表情)与模板弹性图的最小能量
* 该算法是整体程序的主体之一
*/
FLOAT CEGraph::CalEnergy(CEGraph *tempEG)
{
////////*********************************算法0************************
//采用欧氏距离衡量两个图间的相似性
	if((tempEG==NULL)||(tempEG->m_dimension!=360))
	{
		MessageBox(NULL,"能量的参数必须是模板弹性图",NULL,MB_OK);
		return -1.0f;
	}
	int  i,j,m,n;
	FLOAT f_result, f_tmp;
	f_result=65000.0f;
	//模板可以在被测图上进行微小的整体偏移，取所有偏移中最小的值为最终结果
	for(i=-1;i<=1;i++)
		for(j=-1;j<=1;j++)
		{//******************************************
			f_tmp=0.0f;//累加
			///眼睛区域(14×5),权值为1.2
			for(n=2;n<7;n++)
				for(m=2;m<16;m++)///眼睛区域(14×5)
				{
					f_tmp+=1.2*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
				}		
			///嘴巴区域(8×6)，权值为1.5
				for(n=12;n<18;n++)
					for(m=5;m<13;m++)
					{
						f_tmp+=1.5*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
					}
			///脸颊(4点)，权值为0.9
			n=10; m=7;
				f_tmp+=0.9*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
			n=11; m=7;
				f_tmp+=0.9*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
			n=10; m=11;
				f_tmp+=0.9*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
			n=11; m=11;
				f_tmp+=0.9*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
		//	if(f_tmp>0) f_tmp*=-1.0f;
			f_tmp/=112.0f;//共112个点，故，取其均值
			if(f_result>f_tmp) f_result=f_tmp;
		}//*********************************************
		return f_result;
////******************************************************
/***********************************************算法1*******************
//新算法：眼睛区域、嘴巴区域的严格匹配
	if((tempEG==NULL)||(tempEG->m_dimension!=360))
	{
		MessageBox(NULL,"能量的参数必须是模板弹性图",NULL,MB_OK);
		return -1.0f;
	}
	int  i,j,m,n;
	FLOAT f_result, f_tmp;
	f_result=65000.0f;
	//模板可以在被测图上进行微小的整体偏移，取所有偏移中最小的值为最终结果
	for(i=-1;i<=1;i++)
		for(j=-1;j<=1;j++)
		{//******************************************
			f_tmp=0.0f;//累加
			///眼睛区域(14×5),权值为1.2
			for(n=2;n<7;n++)
				for(m=2;m<16;m++)///眼睛区域(14×5)
				{
					f_tmp+=1.2*Cal_neiji(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j])
						/((tempEG->m_module[18*n+m])*(m_module[18*(n+i)+m+j]));
				}		
			///嘴巴区域(8×6)，权值为1.5
				for(n=12;n<18;n++)
					for(m=5;m<13;m++)
					{
						f_tmp+=1.5*Cal_neiji(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j])
							/((tempEG->m_module[18*n+m])*(m_module[18*(n+i)+m+j]));					
					}
			///脸颊(4点)，权值为0.9
			n=10; m=7;
				f_tmp+=0.9*Cal_neiji(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j])
					/((tempEG->m_module[18*n+m])*(m_module[18*(n+i)+m+j]));
			n=11; m=7;
				f_tmp+=0.9*Cal_neiji(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j])
					/((tempEG->m_module[18*n+m])*(m_module[18*(n+i)+m+j]));
			n=10; m=11;
				f_tmp+=0.9*Cal_neiji(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j])
					/((tempEG->m_module[18*n+m])*(m_module[18*(n+i)+m+j]));
			n=11; m=11;
				f_tmp+=0.9*Cal_neiji(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j])
					/((tempEG->m_module[18*n+m])*(m_module[18*(n+i)+m+j]));	
			if(f_tmp>0) f_tmp*=-1.0f;
			if(f_result>f_tmp) f_result=f_tmp;
		}//*********************************************
		return f_result;
**************************************************************/
/**************************算法2**************************************
//老算法
//假设两个弹性图都是18×20个向量，则用本部分代码代替下面注释的部分
//首先在模板的m_keyPoints[]定义的关键点处进行匹配,然后移动关键点，再进行弹性匹配
/*	if((tempEG==NULL)||(tempEG->m_dimension!=360))
	{
		MessageBox(NULL,"能量的参数必须是模板弹性图",NULL,MB_OK);
		return -1.0f;
	}
	int  i;
	FLOAT f_result, f_tmp;
	f_result=0.0f;

	CPoint tmpPoint;
	//不同关键点的权值
	FLOAT afai[13]={1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,0.8f,1.2f,1.2f,1.2f,1.2f,0.9f,0.9f};
	//位置变化的权值
	FLOAT lamta=0.1f;
	int m,n;//记录在被测表情中的搜索位置,搜索深度为3，即在7*7的空间中完全搜索
	int c_x,c_y;//记录搜索的次数，分别是x和y方向
	for(i=0;i<KEY_NUM;i++)
	{
		//设置关键点,并定义搜索的开始点m,n
		tmpPoint.x=tempEG->m_keyPoints[i].x;
		tmpPoint.y=tempEG->m_keyPoints[i].y;
		m=(tmpPoint.x-3<0)?0:tmpPoint.x-3;
		n=(tmpPoint.y-3<0)?0:tmpPoint.y-3;
		//计算该点处弹性变形时的最小能量
		FLOAT f_minEng=10.0f;
		//f_tmp=0;
		for(c_y=0;(c_y<7)&&(n<20);c_y++,n++)
			for(c_x=0;(c_x<7)&&(m<18);c_x++,m++)
			{
				f_tmp=Cal_neiji(m_pvGraph[18*tmpPoint.y+tmpPoint.x],tempEG->m_pvGraph[18*tmpPoint.y+tmpPoint.x])
					/(m_module[18*tmpPoint.y+tmpPoint.x]*tempEG->m_module[18*tmpPoint.y+tmpPoint.x]);
				if(f_tmp>0) f_tmp*=-1;
				f_tmp=afai[i]*f_tmp+lamta*sqrt((3-c_x)*(3-c_x)+(3-c_y)*(3-c_y));
			}
		if(f_minEng>f_tmp) f_minEng=f_tmp;
		f_result+=f_minEng;
	}
	
	return f_result;
***********************************************************/
}

FLOAT CEGraph::sub_CalEnergy(FLOAT testVect[], FLOAT tempVect[])
{
/*
///采用论文中提出的计算向量相似度的公式代替下面注释的部分
	FLOAT result=0.0f;
	FLOAT neiji=0.0f;//内积
*/
//欧氏距离
	FLOAT result=0.0f;
	FLOAT ftmp1;
	int i;
	for(i=0;i<18;i++)
	{
		ftmp1=testVect[i]-tempVect[i];
		result+=ftmp1*ftmp1;
	}
	result=(FLOAT)sqrt(result);
	return result;
}

FLOAT CEGraph::CalModule(FLOAT * vector)
{
////计算向量模,要求输入的向量必须是18维
	FLOAT result;
	result=0.0f;
	int i;
	for(i=0;i<18;i++)
	{
		result+=vector[i]*vector[i];
	}
	result=sqrt(result);
	return result;
}

FLOAT CEGraph::Cal_neiji(FLOAT vec1[], FLOAT vec2[])
{//计算两个向量的内积,要求这两个向量必须为18维
	FLOAT result=0.0f;
	int i;
	for(i=0;i<18;i++)
	{
		result+=vec1[i]*vec2[1];
	}
	return result;
}

void CEGraph::DetectKeyPoints()
{
	if(m_dimension==0)
	{
		MessageBox(NULL,"请在检测关键点之前先进行Gabor变换!","INFO",MB_OK);
		return;
	}
	/*GetKeys(CRect(2,4,9,10),0,2);
	GetKeys(CRect(10,4,18,10),3,5);
	GetKeys(CRect(6,2,12,6),6,6);
	GetKeys(CRect(5,12,13,19),7,10);
	GetKeys(CRect(6,10,9,15),11,11);
	GetKeys(CRect(12,10,16,15),12,12);*/
	GetKeys(CRect(2,3,8,8),0,2);
	GetKeys(CRect(11,3,17,8),3,5);
	GetKeys(CRect(8,1,11,4),6,6);
	GetKeys(CRect(5,12,13,18),7,10);
	GetKeys(CRect(6,8,9,12),11,11);
	GetKeys(CRect(10,9,13,12),12,12);
}

//由DetectKeyPoints()调用，在某个子区域里获得模最大的几个点
//并将这几个点存入m_keyPoints[]数组中，从_from 到_to
void CEGraph::GetKeys(CRect _subRect, int _from, int _to)
{
	int num=_to-_from+1;
	if(num>4)
	{
		MessageBox(NULL,"在子区域中最多只能检测到4个最大模的点!","INFO",MB_OK);
		return;
	}
	FLOAT key_val[4]={0.0f,0.0f,0.0f,0.0f};//从大到小排序,且关键点间至少要相隔两个像素的距离
	CPoint key_point[4];
	key_point[0].x=_subRect.left;
	key_point[0].y=_subRect.top;
	int curx,cury;	
	curx=_subRect.left-3;
	cury=_subRect.top;
	int i,j,m,k=0;//k表示当前已经找到的关键点数目,
	for(i=_subRect.top;i<_subRect.bottom;i++)
		for(j=_subRect.left;j<_subRect.right;j++)
		{
			if((m_module[i*18+j]>key_val[k])&&((j>curx+2)||(i>cury)))
			{/////////////////////////////////////
				if(k < num-1)
				{
					key_val[k+1]=key_val[k];
					key_point[k+1]=key_point[k];
				}
				m=k-1;
				while((m>=0)&&(m_module[i*18+j]>key_val[m]))
				{
					key_val[m+1]=key_val[m];
					key_point[m+1]=key_point[m];
					m--;
				}
				key_val[m+1]=m_module[i*18+j];
				key_point[m+1].x=j;
				key_point[m+1].y=i;
				if(k < num-1)
					k++;
				//if(i>cury)
				//	curx=_subRect.left;
			//	else
					curx=j;
			//	cury=i;
			}///////////////////////////////////
			if(i>cury) {cury=i; curx=_subRect.left-1;}
		}
	for(i=0;i<num;i++)
	{
		m_keyPoints[_from+i].x=key_point[i].x;
		m_keyPoints[_from+i].y=key_point[i].y;
	}
}

/**
* 计算两个弹性图的模向量间的欧氏距离，用于关键帧的检测
* 计算欧氏距离时允许弹性图有微小的移动(在2*2范围内)
* 移动时，选择最小的欧氏距离作为最终结果
*/
FLOAT CEGraph::Cal_ModuleDis(CEGraph *tmpEGraph)
{
	if((m_dimension!=360)||(tmpEGraph->m_dimension!=360))
	{
		MessageBox(NULL,"未构造弹性图",NULL,MB_OK);
		return -1.0f;
	}
	FLOAT f_result=65000.0f;
	FLOAT x,y;
	int i,j,m,n;
	for(i=-2;i<=2;i++)
		for(j=-2;j<=2;j++)
		{
			FLOAT f_tmp=0.0f;
			for(m=0;m<20;m++)
				for(n=0;n<18;n++)
				{
					if((m+i>=0)&&(m+i<20)&&(n+j>=0)&&(n+j<18))
					{
						x=m_module[(m+i)*18+(n+j)];
						y=tmpEGraph->m_module[m*18+n];
						f_tmp+=(x-y)*(x-y);
					}
				}
			f_tmp=sqrt(f_tmp)/(360-2*(abs(i)*18+abs(j)*20-abs(i*j)));
			if(f_result>f_tmp)
				f_result=f_tmp;
		}
	return f_result;
}
