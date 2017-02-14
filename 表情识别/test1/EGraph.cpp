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
{//�����ͷ�m_pvGraph�еĸ�������
	int i;
	for(i=0;i<m_dimension;i++)
		delete [] m_pvGraph[i];
}

BOOL CEGraph::init_tempExpr(CDIB *pDIB, CExpStrategy *pExpStr)
{
////����ģ��Ҳ�ͱ������ͼһ��������������Ϣ�����õ�����ָ��18��20��
////�ò��ִ������汻ע�͵Ĳ���
	if(m_dimension!=0)
		return FALSE;
	CSize sizeDIB=pDIB->GetDIBSize();
	if((sizeDIB.cx!=90)||(sizeDIB.cy!=100))
	{
		MessageBox(NULL,"���Ƚ�ͼ���һΪ90��100","Information",MB_OK);
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
	for(i=0;i<20;i++)//��
		for(j=0;j<18;j++)//��
		{//m_pvGraph�ĵ�0��Ԫ�洢����
			m_pvGraph[i*18+j]=pExpStr->GetGaborVector_5(image,j*5,100-i*5-5,widthBytes);
		}
		m_dimension=360;
/////////////////////
	::GlobalUnlock((HGLOBAL)tmp_hDIB);
////����ÿ��������ģ����������m_module������
	for(i=0;i<360;i++)
	{
		m_module[i]=CalModule(m_pvGraph[i]);
	}
//////////////���ӵ���䣺���ڼ��ؼ��㣬ֻҪģ����Ҫ�����������ͼ����Ҫ
//	DetectKeyPoints();
	return TRUE;
///�ú������ڴ�����׼ģ�����ͼ��(pDIB,��С90��100)�ĵ���ͼ
 ///�����ֲ����۽ǡ�üë����ǡ���͵ȹ�15��
/*
	if(m_dimension!=0)
		return FALSE;
	CSize sizeDIB=pDIB->GetDIBSize();
	if((sizeDIB.cx!=90)||(sizeDIB.cy!=100))
	{
		MessageBox(NULL,"���Ƚ�ͼ���һΪ90��100","Information",MB_OK);
		return FALSE;
	}
	int widthBytes=WIDTHBYTES(8*sizeDIB.cx);
	LPSTR lpbi;
	int i;
	//����ģ������ؼ��������,0��Ԫ����
	//ע��ͼ�񷵹�������
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
{///������һ����ı������ͼ��(pDIB,90��100)�ĵ���ͼ
 ///�ֱ���ȡ�۾�(ͼ����ϰ벿��,90��30)�����(�°벿��,40��30)����������
	if(m_dimension!=0)
		return FALSE;
	CSize sizeDIB=pDIB->GetDIBSize();
	if((sizeDIB.cx!=90)||(sizeDIB.cy!=100))
	{
		MessageBox(NULL,"���Ƚ�ͼ���һΪ90��100","Information",MB_OK);
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
/*	for(i=0;i<3;i++)//��
		for(j=0;j<9;j++)//��
		{//m_pvGraph�ĵ�0��Ԫ���洢����
			m_pvGraph[i*9+j+1]=pExpStr->GetGaborVector(image,j*10,100-i*10-10,widthBytes);
		}
	for(i=0;i<3;i++)
		for(j=0;j<5;j++)
		{
			m_pvGraph[27+i*5+j+1]=pExpStr->GetGaborVector(image,20+j*10,35-i*10-10,widthBytes);
		}
	m_dimension=42;*/
///////////////5*5:
	for(i=0;i<20;i++)//��
		for(j=0;j<18;j++)//��
		{//m_pvGraph�ĵ�0��Ԫ�洢����
			m_pvGraph[i*18+j]=pExpStr->GetGaborVector_5(image,j*5,100-i*5-5,widthBytes);
		}
		m_dimension=360;
/////////////////////
	::GlobalUnlock((HGLOBAL)tmp_hDIB);
/////����ÿ��������ģ����������m_module������
	for(i=0;i<360;i++)
	{
		m_module[i]=CalModule(m_pvGraph[i]);
	}
/*	for(i=0;i<20;i++)//��
		for(j=0;j<18;j++)//��
			m_module[i*18+j]=j;*/
	return TRUE;
}

/**
���õ���ƥ���㷨���㱾����ͼ(�������)��ģ�嵯��ͼ����С����
* ���㷨��������������֮һ
*/
FLOAT CEGraph::CalEnergy(CEGraph *tempEG)
{
////////*********************************�㷨0************************
//����ŷ�Ͼ����������ͼ���������
	if((tempEG==NULL)||(tempEG->m_dimension!=360))
	{
		MessageBox(NULL,"�����Ĳ���������ģ�嵯��ͼ",NULL,MB_OK);
		return -1.0f;
	}
	int  i,j,m,n;
	FLOAT f_result, f_tmp;
	f_result=65000.0f;
	//ģ������ڱ���ͼ�Ͻ���΢С������ƫ�ƣ�ȡ����ƫ������С��ֵΪ���ս��
	for(i=-1;i<=1;i++)
		for(j=-1;j<=1;j++)
		{//******************************************
			f_tmp=0.0f;//�ۼ�
			///�۾�����(14��5),ȨֵΪ1.2
			for(n=2;n<7;n++)
				for(m=2;m<16;m++)///�۾�����(14��5)
				{
					f_tmp+=1.2*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
				}		
			///�������(8��6)��ȨֵΪ1.5
				for(n=12;n<18;n++)
					for(m=5;m<13;m++)
					{
						f_tmp+=1.5*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
					}
			///����(4��)��ȨֵΪ0.9
			n=10; m=7;
				f_tmp+=0.9*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
			n=11; m=7;
				f_tmp+=0.9*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
			n=10; m=11;
				f_tmp+=0.9*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
			n=11; m=11;
				f_tmp+=0.9*sub_CalEnergy(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j]);
		//	if(f_tmp>0) f_tmp*=-1.0f;
			f_tmp/=112.0f;//��112���㣬�ʣ�ȡ���ֵ
			if(f_result>f_tmp) f_result=f_tmp;
		}//*********************************************
		return f_result;
////******************************************************
/***********************************************�㷨1*******************
//���㷨���۾��������������ϸ�ƥ��
	if((tempEG==NULL)||(tempEG->m_dimension!=360))
	{
		MessageBox(NULL,"�����Ĳ���������ģ�嵯��ͼ",NULL,MB_OK);
		return -1.0f;
	}
	int  i,j,m,n;
	FLOAT f_result, f_tmp;
	f_result=65000.0f;
	//ģ������ڱ���ͼ�Ͻ���΢С������ƫ�ƣ�ȡ����ƫ������С��ֵΪ���ս��
	for(i=-1;i<=1;i++)
		for(j=-1;j<=1;j++)
		{//******************************************
			f_tmp=0.0f;//�ۼ�
			///�۾�����(14��5),ȨֵΪ1.2
			for(n=2;n<7;n++)
				for(m=2;m<16;m++)///�۾�����(14��5)
				{
					f_tmp+=1.2*Cal_neiji(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j])
						/((tempEG->m_module[18*n+m])*(m_module[18*(n+i)+m+j]));
				}		
			///�������(8��6)��ȨֵΪ1.5
				for(n=12;n<18;n++)
					for(m=5;m<13;m++)
					{
						f_tmp+=1.5*Cal_neiji(tempEG->m_pvGraph[18*n+m],m_pvGraph[18*(n+i)+m+j])
							/((tempEG->m_module[18*n+m])*(m_module[18*(n+i)+m+j]));					
					}
			///����(4��)��ȨֵΪ0.9
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
/**************************�㷨2**************************************
//���㷨
//������������ͼ����18��20�����������ñ����ִ����������ע�͵Ĳ���
//������ģ���m_keyPoints[]����Ĺؼ��㴦����ƥ��,Ȼ���ƶ��ؼ��㣬�ٽ��е���ƥ��
/*	if((tempEG==NULL)||(tempEG->m_dimension!=360))
	{
		MessageBox(NULL,"�����Ĳ���������ģ�嵯��ͼ",NULL,MB_OK);
		return -1.0f;
	}
	int  i;
	FLOAT f_result, f_tmp;
	f_result=0.0f;

	CPoint tmpPoint;
	//��ͬ�ؼ����Ȩֵ
	FLOAT afai[13]={1.5f,1.5f,1.5f,1.5f,1.5f,1.5f,0.8f,1.2f,1.2f,1.2f,1.2f,0.9f,0.9f};
	//λ�ñ仯��Ȩֵ
	FLOAT lamta=0.1f;
	int m,n;//��¼�ڱ�������е�����λ��,�������Ϊ3������7*7�Ŀռ�����ȫ����
	int c_x,c_y;//��¼�����Ĵ������ֱ���x��y����
	for(i=0;i<KEY_NUM;i++)
	{
		//���ùؼ���,�����������Ŀ�ʼ��m,n
		tmpPoint.x=tempEG->m_keyPoints[i].x;
		tmpPoint.y=tempEG->m_keyPoints[i].y;
		m=(tmpPoint.x-3<0)?0:tmpPoint.x-3;
		n=(tmpPoint.y-3<0)?0:tmpPoint.y-3;
		//����õ㴦���Ա���ʱ����С����
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
///��������������ļ����������ƶȵĹ�ʽ��������ע�͵Ĳ���
	FLOAT result=0.0f;
	FLOAT neiji=0.0f;//�ڻ�
*/
//ŷ�Ͼ���
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
////��������ģ,Ҫ�����������������18ά
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
{//���������������ڻ�,Ҫ����������������Ϊ18ά
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
		MessageBox(NULL,"���ڼ��ؼ���֮ǰ�Ƚ���Gabor�任!","INFO",MB_OK);
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

//��DetectKeyPoints()���ã���ĳ������������ģ���ļ�����
//�����⼸�������m_keyPoints[]�����У���_from ��_to
void CEGraph::GetKeys(CRect _subRect, int _from, int _to)
{
	int num=_to-_from+1;
	if(num>4)
	{
		MessageBox(NULL,"�������������ֻ�ܼ�⵽4�����ģ�ĵ�!","INFO",MB_OK);
		return;
	}
	FLOAT key_val[4]={0.0f,0.0f,0.0f,0.0f};//�Ӵ�С����,�ҹؼ��������Ҫ����������صľ���
	CPoint key_point[4];
	key_point[0].x=_subRect.left;
	key_point[0].y=_subRect.top;
	int curx,cury;	
	curx=_subRect.left-3;
	cury=_subRect.top;
	int i,j,m,k=0;//k��ʾ��ǰ�Ѿ��ҵ��Ĺؼ�����Ŀ,
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
* ������������ͼ��ģ�������ŷ�Ͼ��룬���ڹؼ�֡�ļ��
* ����ŷ�Ͼ���ʱ������ͼ��΢С���ƶ�(��2*2��Χ��)
* �ƶ�ʱ��ѡ����С��ŷ�Ͼ�����Ϊ���ս��
*/
FLOAT CEGraph::Cal_ModuleDis(CEGraph *tmpEGraph)
{
	if((m_dimension!=360)||(tmpEGraph->m_dimension!=360))
	{
		MessageBox(NULL,"δ���쵯��ͼ",NULL,MB_OK);
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
