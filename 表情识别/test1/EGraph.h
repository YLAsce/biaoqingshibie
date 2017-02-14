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
  ������Ҫ���ڴ洢����ͼ��ĵ���ͼ
*/
#define KEY_NUM 13//�������ؼ���ĸ���
enum expressionKind{angry,sadness,surprise,disgust,smile,fear};

class CEGraph  
{
public:
	CEGraph();
	virtual ~CEGraph();
public://��������
	FLOAT Cal_ModuleDis(CEGraph* tmpEGraph);
	void DetectKeyPoints();
	FLOAT sub_CalEnergy(FLOAT testVect[18],FLOAT tempVect[18]);
	FLOAT CalEnergy(CEGraph *tempEG);
	BOOL init_testExpr(CDIB *pDIB, CExpStrategy *pExpStr);
	BOOL init_tempExpr(CDIB *pDIB, CExpStrategy *pExpStr);

//	FLOAT *m_pvGraph[43];//���ڴ洢����ͼ�е�������0��Ԫ���ã�1��39
	FLOAT *m_pvGraph[360];//���ڴ洢����ͼ�е�������0��Ԫ�ã�0��359
	int m_dimension;//����ʵ�ʴ洢������ά��
	enum expressionKind m_kind;//����õ���ͼ�ı�������(6+1������)
	CEGraph *m_pNext;//���ڹ��쵥������
///���ӵ����ԣ�
	FLOAT m_module[360];//����ÿ��������ģ,��һ����Ԫ��
	CPoint m_keyPoints[KEY_NUM];
protected:
	FLOAT Cal_neiji(FLOAT vec1[], FLOAT vec2[]);
	FLOAT CalModule(FLOAT * vector);
	//��DetectKeyPoints()���ã���ĳ������������ģ���ļ�����
	//�����⼸�������m_keyPoints[]�����У���_from ��_to
	void GetKeys(CRect _subRect, int _from, int _to);
};

#endif // !defined(AFX_EGRAPH_H__CFBC70CC_A889_4559_83BB_AE78EFCD86E5__INCLUDED_)
