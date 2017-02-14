// DIB.h: interface for the CDIB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__E2798D01_5370_4977_B88C_6C812B93B394__INCLUDED_)
#define AFX_DIB_H__E2798D01_5370_4977_B88C_6C812B93B394__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define DIB_HEADER_MARKER ((WORD)('M'<<8)|'B') //bfType="BM"
#define IS_WIN30_DIB(lpbi) (*(LPDWORD)lpbi==sizeof(BITMAPINFOHEADER))
#define PALVERSION 0x300
//�����������Ŀ��
#define RECTWIDTH(lpRect) ((lpRect)->right-(lpRect)->left)
//�����������ĸ߶�
#define RECTHEIGHT(lpRect) ((lpRect)->bottom-(lpRect)->top)
////����ͼ��ʵ�ʵĿ�ȣ����ֽڼ��㣬���룺λ
#define WIDTHBYTES(bits) (((bits)+31)/32*4)
//#define PI 3.1415926
const  DOUBLE PI=3.1415926;

DECLARE_HANDLE(HDIB); //����HDIB���


class CDIB  
{
public:
	BOOL ScaleNormal(CSize toSize);
	BOOL SaveDIB(HDIB hDib,CFile& file);
	BOOL SaveDIB(LPCTSTR lpszPathName);
	CDIB(CDIB* pDIB,int _left,int _top,int _right,int _bottom);
	CDIB(CDIB* pDIB,FLOAT *pGabor, CSize _size, BOOL _changePal=FALSE);
	CSize GetDIBSize();
	WORD PaletteSize(LPSTR lpbi);
	LPSTR FindDIBBits(LPSTR lpbi);
	BOOL PaintDIB(HDC hDC,LPRECT lpDCRect);
	HDIB GetHDIB() const;
	BOOL CreateDIBPalette(HDIB hDIB,CPalette *cPal);
	WORD NumColors(LPSTR lpbi);
	CSize GetDIBSize(LPSTR lpDIB);//����ͼ��ߴ磬������ʵ�ʴ洢�ߴ�
	HDIB CreateDIB(LPCTSTR lpPathName);
	HDIB ReadDIBFile(CFile& file);
	CDIB(LPCTSTR lpPathName);
	CDIB();
	virtual ~CDIB();
private:
	HDIB m_hDIB;//DIBͼ����
	CPalette* m_pPal; //��Ҫ������ʾͼ��
	CSize m_sizeDIB;//DIBͼ��ĳߴ�(����������)��������ʵ�ʴ洢�ߴ�

protected:
	void SetEmpty();
};

#endif // !defined(AFX_DIB_H__E2798D01_5370_4977_B88C_6C812B93B394__INCLUDED_)
