// ExpStrategy.cpp: implementation of the CExpStrategy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "test1.h"
#include "ExpStrategy.h"
#include <complex>
#include <math.h>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExpStrategy::CExpStrategy()
{
	m_GaborsImage=NULL;
	m_GaborsReal=NULL;
	m_GaborsImage5=NULL;
	m_GaborsReal5=NULL;
	EGraph=NULL;
	m_pDIB=NULL;
	//m_coefNum=450;//5×5×18
	m_coefNum=1800;//10×10×18
	grids_x=0;
	grids_y=0;
}

CExpStrategy::~CExpStrategy()
{
	if(m_GaborsImage!=NULL)
		delete[] m_GaborsImage;
	if(m_GaborsReal!=NULL)
		delete[] m_GaborsReal;
	if(EGraph!=NULL)
		delete[] EGraph;
	if(m_pDIB!=NULL)
		delete m_pDIB;
}

FLOAT* CExpStrategy::GaborTF(CDIB *pDIB,int _left, int _top, int _right, int _bottom, BOOL _createDIB)
{
	//注意：该函数仅能实现对整个DIB图像进行Gabor变换
	//而不是如接口声明那样可以对图像的特定区域进行Gabor变换
	if(pDIB==NULL)
		return NULL;
	int i,j;
//	FLOAT gabor_image;
//	FLOAT gabor_real;
	//弹性图的每个向量网格为5×5,即使用5×5的网格分割CDIB图
	//HDIB _hDIB;
	LPSTR _lpbi;
	LPSTR _image;//图像数据的起始地址
	int _widthBytes;
//	int grids_x;//弹性图的x方向上网格数
//	int grids_y;//弹性图的y方向上网格数
//	grids_x=(_right-_left)/5;//
//	grids_y=(_bottom-_top)/5;
	grids_x=pDIB->GetDIBSize().cx/5;//
	grids_y=pDIB->GetDIBSize().cy/5;
	_widthBytes=WIDTHBYTES(8*pDIB->GetDIBSize().cx);

	if((grids_x<=0)||(grids_y<=0))
		return NULL;
	if(EGraph!=NULL)
		delete [] EGraph;
	EGraph=new FLOAT[grids_x*grids_y];
	_lpbi=(LPSTR)::GlobalLock((HGLOBAL)pDIB->GetHDIB());
	_image=pDIB->FindDIBBits(_lpbi);
	//Transforming……
	for(i=0;i<grids_y;i++)
		for(j=0;j<grids_x;j++)
		{
			//EGraph[i*grids_x+j]=sub_GaborTF(_image+5*(_right-_left)*i+5*j);
			EGraph[i*grids_x+j]=sub_GaborTF(_image+5*_widthBytes*i+5*j);
		}
	///////////////////////////Create DIB
	if(_createDIB==TRUE)
	{
		if(m_pDIB!=NULL)
			delete m_pDIB;
		m_pDIB=new CDIB(pDIB,EGraph,CSize(grids_x,grids_y));
	
	}
	//////////////////////////end of Create DIB
	::GlobalUnlock((HGLOBAL)pDIB->GetHDIB());
	return EGraph;
}

BOOL CExpStrategy::Initialize()
{
	int i,m,n;
	FLOAT m_n;
	FLOAT k_x0;
	FLOAT k_x1;
	FLOAT k_x2;
	FLOAT sikma_sq;
	FLOAT kv[18][2];//小波的频率向量(2维)，6×3(6个方向,3个带宽,[6][3])
	FLOAT kv_abs[18];
	FLOAT sita_sin[6];
	FLOAT sita_cos[6];
	FLOAT kv_coef[3]={1.5708f,1.1107f,0.7854f};
	FLOAT sub_kv_abs_0;
	FLOAT sub_kv_abs_1;
	FLOAT sub_kv_abs_2;
	sikma_sq=PI*PI;
	for(i=0;i<6;i++)
	{
		sita_sin[i]=sin((i+1)*PI/6.0);
		sita_cos[i]=cos((i+1)*PI/6.0);
	}
	for(i=0;i<6;i++)
	{
		//cos,即Kj的第一个分量
		kv[i*3][0]=kv_coef[0]*sita_cos[i];
		kv[i*3+1][0]=kv_coef[1]*sita_cos[i];
		kv[i*3+2][0]=kv_coef[2]*sita_cos[i];
		//sin,即Kj的第二个分量
		kv[i*3][1]=kv_coef[0]*sita_sin[i];
		kv[i*3+1][1]=kv_coef[1]*sita_sin[i];
		kv[i*3+2][1]=kv_coef[2]*sita_sin[i];
	}
	for(i=0;i<6;i++)
	{//计算Kj的模
	  kv_abs[i*3]=sqrt(kv[i*3][0]*kv[i*3][0]+kv[i*3][1]*kv[i*3][1]);
	  kv_abs[i*3+1]=sqrt(kv[i*3+1][0]*kv[i*3+1][0]+kv[i*3+1][1]*kv[i*3+1][1]);
	  kv_abs[i*3+2]=sqrt(kv[i*3+2][0]*kv[i*3+2][0]+kv[i*3+2][1]*kv[i*3+2][1]);
	}
///////////10*10:
	if(m_GaborsReal!=NULL)
		delete[] m_GaborsReal;
	if(m_GaborsImage!=NULL)
		delete[] m_GaborsImage;
	m_GaborsReal=new FLOAT[m_coefNum];
	m_GaborsImage=new FLOAT[m_coefNum];
//////////////5*5:
	if(m_GaborsReal5!=NULL)
		delete[] m_GaborsReal5;
	if(m_GaborsImage5!=NULL)
		delete[] m_GaborsImage5;
	m_GaborsReal5=new FLOAT[450];
	m_GaborsImage5=new FLOAT[450];
////////////////
	for(i=0;i<6;i++)///0到6代表有6个不同方向的小波(sita=1/6*pi,…,pi)
	{               ////0到3代表每个方向小波由3个频率组成(v=0,1,2)
		sub_kv_abs_0=kv_abs[i*3+0]*kv_abs[i*3+0];
		sub_kv_abs_1=kv_abs[i*3+1]*kv_abs[i*3+1];
		sub_kv_abs_2=kv_abs[i*3+2]*kv_abs[i*3+2];
	///10×10,代替下面的注释的部分
		///参考Gabor函数的定义
	   for(m=0;m<10;m++)
		   for(n=0;n<10;n++)
		   {
			   m_n=(m+1)*(m+1)+(n+1)*(n+1);
			   //V_Kj*V_x
			   k_x0=kv[i*3+0][0]*(m+1)+kv[i*3+0][1]*(n+1);
			   k_x1=kv[i*3+1][0]*(m+1)+kv[i*3+1][1]*(n+1);
			   k_x2=kv[i*3+2][0]*(m+1)+kv[i*3+2][1]*(n+1);
			   //real:
		     m_GaborsReal[100*(i*3+0)+(m*10+n)]
				=kv_abs[i*3+0]/(sikma_sq)*exp((-0.5)*sub_kv_abs_0*m_n/sikma_sq)
				*(cos(k_x0)-exp((-0.5)*sikma_sq));
		     m_GaborsReal[100*(i*3+1)+(m*10+n)]
				 =kv_abs[i*3+1]/(sikma_sq)*exp((-0.5)*sub_kv_abs_1*m_n/sikma_sq)
				 *(cos(k_x1)-exp((-0.5)*sikma_sq));
		     m_GaborsReal[100*(i*3+2)+(m*10+n)]
				 =kv_abs[i*3+2]/(sikma_sq)*exp((-0.5)*sub_kv_abs_2*m_n/sikma_sq)
				 *(cos(k_x2)-exp((-0.5)*sikma_sq));
			 //Image:
			 m_GaborsImage[100*(i*3+0)+(m*10+n)]
				 =kv_abs[i*3+0]/(sikma_sq)*exp((-0.5)*sub_kv_abs_0*m_n/sikma_sq)
				 *sin(k_x0);
			 m_GaborsImage[100*(i*3+1)+(m*10+n)]
				 =kv_abs[i*3+1]/(sikma_sq)*exp((-0.5)*sub_kv_abs_1*m_n/sikma_sq)
				 *sin(k_x1);
			 m_GaborsImage[100*(i*3+2)+(m*10+n)]
				 =kv_abs[i*3+2]/(sikma_sq)*exp((-0.5)*sub_kv_abs_2*m_n/sikma_sq)
				 *sin(k_x2);
		   }
//////////////5*5的Gabor变换
	   for(m=0;m<5;m++)
		   for(n=0;n<5;n++)
		   {
			   m_n=(m+1)*(m+1)+(n+1)*(n+1);
			   k_x0=kv[i*3+0][0]*(m+1)+kv[i*3+0][1]*(n+1);
			   k_x1=kv[i*3+1][0]*(m+1)+kv[i*3+1][1]*(n+1);
			   k_x2=kv[i*3+2][0]*(m+1)+kv[i*3+2][1]*(n+1);
			   //real:
		     m_GaborsReal5[25*(i*3+0)+(m*5+n)]
				=kv_abs[i*3+0]/(sikma_sq)*exp((-0.5)*sub_kv_abs_0*m_n/sikma_sq)
				*(cos(k_x0)-exp((-0.5)*sikma_sq));
		     m_GaborsReal5[25*(i*3+1)+(m*5+n)]
				 =kv_abs[i*3+1]/(sikma_sq)*exp((-0.5)*sub_kv_abs_1*m_n/sikma_sq)
				 *(cos(k_x1)-exp((-0.5)*sikma_sq));
		     m_GaborsReal5[25*(i*3+2)+(m*5+n)]
				 =kv_abs[i*3+2]/(sikma_sq)*exp((-0.5)*sub_kv_abs_2*m_n/sikma_sq)
				 *(cos(k_x2)-exp((-0.5)*sikma_sq));
			 //Image:
			 m_GaborsImage5[25*(i*3+0)+(m*5+n)]
				 =kv_abs[i*3+0]/(sikma_sq)*exp((-0.5)*sub_kv_abs_0*m_n/sikma_sq)
				 *sin(k_x0);
			 m_GaborsImage5[25*(i*3+1)+(m*5+n)]
				 =kv_abs[i*3+1]/(sikma_sq)*exp((-0.5)*sub_kv_abs_1*m_n/sikma_sq)
				 *sin(k_x1);
			 m_GaborsImage5[25*(i*3+2)+(m*5+n)]
				 =kv_abs[i*3+2]/(sikma_sq)*exp((-0.5)*sub_kv_abs_2*m_n/sikma_sq)
				 *sin(k_x2);
		   }		   
	}

	return TRUE;
}


FLOAT CExpStrategy::sub_GaborTF(LPSTR image)
{
	if((m_GaborsReal==NULL)||(m_GaborsImage==NULL))
		return 0.0;
	int i,j,m,n;
	FLOAT _image=0.0;
	FLOAT _real=0.0;
	for(i=0;i<6;i++)
		for(j=0;j<3;j++)
			for(m=0;m<5;m++)
				for(n=0;n<5;n++)
				{
					_real+=((int)image[5*m+n])*m_GaborsReal5[25*(i*3+j)+5*m+n];
					_image+=((int)image[5*m+n])*m_GaborsImage5[25*(i*3+j)+5*m+n];
				}
	return sqrt(_image*_image+_real*_real);

}

void CExpStrategy::Draw(CDC *pDC)
{
	if (EGraph==NULL)
		return;
	CString str;
	int i,j;
	for(i=0;i<grids_y;i++)
		for(j=0;j<grids_x;j++)
		{
			str.Empty();
			str.Format("%d",(int)EGraph[i*grids_x+j]);
			pDC->TextOut(j*30,i*20,str);
		}

}

FLOAT CExpStrategy::CalEuDis(FLOAT *_tmp, CSize _tmpSize, int _location)
{//_location:1-lefteye, 2-righteye, 3-mouth
	FLOAT distance=650000.0f;
	FLOAT tmpdis=0.0f;
	if(EGraph==NULL)
		return 0.0f;
	int _initX,_initY;
	int i,j;
	switch (_location)
	{
	case 1://lefteye
		_initY=grids_y-_tmpSize.cy-5;
		if(_initY<0)
			_initY=0;
		_initX=0;
		break;
	case 2://righteye
		_initY=grids_y-_tmpSize.cy-5;
		if(_initY<0)
			_initY=0;
		_initX=grids_x-_tmpSize.cx-5;
		if(_initX<0)
			_initX=0;
		break;
	case 3://mouth
		_initY=0;
		_initX=grids_x/2-_tmpSize.cx/2-3;
		if(_initX<0)
			_initX=0;
		break;
	default:
		break;
	}
		for(i=0;i<5;i++)
			for(j=0;j<5;j++)
			{
				tmpdis=sub_calEuDis(_initX+j,_initY+i,_tmp,_tmpSize);
				//tmpdis=sub_calEuDis(EGraph+grids_x*(_initY+i)+j,_tmp,_tmpSize);
				if(distance>tmpdis)
					distance=tmpdis;
			}
	return distance;
}

FLOAT CExpStrategy::sub_calEuDis(int x,int y,FLOAT *_tmp, CSize _tmpSize)
{
	FLOAT _result=0.0f;
	int m,n,s,t;
	s=grids_x*grids_y;
	for(m=0;m<_tmpSize.cy;m++)
		for(n=0;n<_tmpSize.cx;n++)
		{
			if((t=(y+m)*grids_x+x+n)<s)
			_result+=(EGraph[t]-_tmp[m*_tmpSize.cx+n])*(EGraph[t]-_tmp[m*_tmpSize.cx+n]);
		}
	_result=sqrt(_result);
	return _result;
}

FLOAT * CExpStrategy::GetGaborVector(BYTE *image, int _x, int _y, int _widthBytes)
{
	if((m_GaborsReal==NULL)||(m_GaborsImage==NULL))
		return NULL;
	int i,j,m,n;
	FLOAT *vector;
	FLOAT _image=0.0;
	FLOAT _real=0.0;
	vector=new FLOAT[18];
	BYTE pixelValue;
	////对10×10的单元格构造一个Gabor矢量(由18个分量组成)
	for(i=0;i<6;i++)
		for(j=0;j<3;j++)
		{
			_image=0.0;
			_real=0.0;
			for(m=0;m<10;m++)
				for(n=0;n<10;n++)
				{
					pixelValue=(BYTE)*(image+(_y+m)*_widthBytes+_x+n);
					_real+=(int)pixelValue*m_GaborsReal[100*(i*3+j)+10*m+n];
					//_real+=((int)image[5*m+n])*m_GaborsReal[25*(i*3+j)+5*m+n];
					_image+=(int)pixelValue*m_GaborsImage[100*(i*3+j)+10*m+n];
				}
			vector[i*3+j]=sqrt(_real*_real+_image*_image);
		}
	//return sqrt(_image*_image+_real*_real);
	return vector;
}

/**
* 得到一个5*5矩形块的Gabor向量
* 输入：image:被处理的灰度图像.
* _x, _y: 矩形块在image中的位置
* _widthBytes: image图像的宽度
*输出: FLOAT型的向量(18维)，表示一个Gabor向量
*/
FLOAT * CExpStrategy::GetGaborVector_5(BYTE *image, int _x, int _y, int _widthBytes)
{
	if((m_GaborsReal5==NULL)||(m_GaborsImage5==NULL))
		return NULL;
	int i,j,m,n;
	FLOAT *vector;
	FLOAT _image=0.0;
	FLOAT _real=0.0;
	vector=new FLOAT[18];
	BYTE pixelValue;
	////对10×10的单元格构造一个Gabor矢量(由18个分量组成)
	for(i=0;i<6;i++)
		for(j=0;j<3;j++)
		{
			_image=0.0;
			_real=0.0;
			for(m=0;m<5;m++)//行
				for(n=0;n<5;n++)//列
				{
					pixelValue=(BYTE)*(image+(_y+m)*_widthBytes+_x+n);
					_real+=(int)pixelValue*m_GaborsReal5[25*(i*3+j)+5*m+n];
					//_real+=((int)image[5*m+n])*m_GaborsReal[25*(i*3+j)+5*m+n];
					_image+=(int)pixelValue*m_GaborsImage5[25*(i*3+j)+5*m+n];
				}
			vector[i*3+j]=sqrt(_real*_real+_image*_image);
		}
	//return sqrt(_image*_image+_real*_real);
	return vector;
}
