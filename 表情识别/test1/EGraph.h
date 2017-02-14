// EGraph.h: interface for the CEGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EGRAPH_H__CFBC70CC_A889_4559_83BB_AE78EFCD86E5__INCLUDED_)
#define AFX_EGRAPH_H__CFBC70CC_A889_4559_83BB_AE78EFCD86E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "dib.h"
#include "expstrategy.h"
/**
  该类主要用于存储表情图像的弹性图
*/
#define KEY_NUM 13//定义表情关键点的个数
enum expressionKind{angry,sadness,surprise,disgust,smile,fear};

class CEGraph  
{
public:
	CEGraph();
	virtual ~CEGraph();
public://公有属性
	FLOAT Cal_ModuleDis(CEGraph* tmpEGraph);
	void DetectKeyPoints();
	FLOAT sub_CalEnergy(FLOAT testVect[18],FLOAT tempVect[18]);
	FLOAT CalEnergy(CEGraph *tempEG);
	BOOL init_testExpr(CDIB *pDIB, CExpStrategy *pExpStr);
	BOOL init_tempExpr(CDIB *pDIB, CExpStrategy *pExpStr);

//	FLOAT *m_pvGraph[43];//用于存储弹性图中的向量，0单元不用，1～39
	FLOAT *m_pvGraph[360];//用于存储弹性图中的向量，0单元用，0～359
	int m_dimension;//保存实际存储向量的维数
	enum expressionKind m_kind;//保存该弹性图的表情类型(6+1种类型)
	CEGraph *m_pNext;//用于构造单向链表
///增加的属性：
	FLOAT m_module[360];//保存每个向量的模,第一个单元用
	CPoint m_keyPoints[KEY_NUM];
protected:
	FLOAT Cal_neiji(FLOAT vec1[], FLOAT vec2[]);
	FLOAT CalModule(FLOAT * vector);
	//由DetectKeyPoints()调用，在某个子区域里获得模最大的几个点
	//并将这几个点存入m_keyPoints[]数组中，从_from 到_to
	void GetKeys(CRect _subRect, int _from, int _to);
};

#endif // !defined(AFX_EGRAPH_H__CFBC70CC_A889_4559_83BB_AE78EFCD86E5__INCLUDED_)
