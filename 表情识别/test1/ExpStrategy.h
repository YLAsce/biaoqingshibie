// ExpStrategy.h: interface for the CExpStrategy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPSTRATEGY_H__8D703278_CE89_4867_A649_EF272ADEAA1E__INCLUDED_)
#define AFX_EXPSTRATEGY_H__8D703278_CE89_4867_A649_EF272ADEAA1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DIB.h"

class CExpStrategy  
{
public:
	void Draw(CDC* pDC);
	BOOL Initialize();
	FLOAT* GaborTF(CDIB* pDIB,int _left, int _top, int _right, int _bottom, BOOL _createDIB=FALSE);
	CExpStrategy();
	virtual ~CExpStrategy();
private:
	FLOAT sub_calEuDis(int x,int y,FLOAT *_tmp,CSize _tmpSize);
	FLOAT sub_GaborTF(LPSTR image);
	 FLOAT* m_GaborsImage;
	 FLOAT* m_GaborsReal;
	 FLOAT* m_GaborsImage5;
	 FLOAT* m_GaborsReal5;
	 int m_coefNum;
public:
	FLOAT *EGraph;
	int grids_x;//弹性图的x方向上网格数
	int grids_y;//弹性图的y方向上网格数
public:
	FLOAT * GetGaborVector_5(BYTE *image, int _x, int _y, int _widthBytes);
	FLOAT * GetGaborVector(BYTE *image,int _x,int _y, int _widthBytes);
	FLOAT CalEuDis(FLOAT *_tmp,CSize _tmpSize, int _location);
	//_location:1-lefteye, 2-righteye, 3-mouth
		CDIB* m_pDIB;
};

#endif // !defined(AFX_EXPSTRATEGY_H__8D703278_CE89_4867_A649_EF272ADEAA1E__INCLUDED_)
