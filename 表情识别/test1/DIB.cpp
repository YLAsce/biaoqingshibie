// DIB.cpp: implementation of the CDIB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "test1.h"
#include "DIB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDIB::CDIB()
{
	m_hDIB=NULL;
	m_sizeDIB=CSize(0,0);
	m_pPal=NULL;
}

CDIB::~CDIB()
{
	if(m_hDIB!=NULL)//ɾ���洢ͼ�������
		::GlobalFree((HGLOBAL)m_hDIB);
	if(m_pPal!=NULL)
		delete m_pPal;
}

CDIB::CDIB(LPCTSTR lpPathName)
{

	m_hDIB=CreateDIB(lpPathName);
	if(m_hDIB==NULL)
	{
		MessageBox(NULL,"����DIB��ʧ�ܣ�",NULL,MB_OK);
		m_sizeDIB=CSize(0,0);
		m_pPal=NULL;
	}
	else
	{
		LPSTR _lpDIB=(LPSTR)::GlobalLock((HGLOBAL)m_hDIB);
		m_sizeDIB=GetDIBSize(_lpDIB);
		::GlobalUnlock((HGLOBAL)m_hDIB);
		m_pPal=new CPalette;
		if(!CreateDIBPalette(m_hDIB,m_pPal))
		{delete m_pPal; m_pPal=NULL;}
	}
}

HDIB CDIB::ReadDIBFile(CFile& file)
{
	BITMAPFILEHEADER bmfHeader;
	DWORD dwBitsSize;
	HDIB hDIB;
	LPSTR pDIB;
	dwBitsSize=file.GetLength();
	if(file.Read((LPSTR)&bmfHeader,sizeof(bmfHeader))!=sizeof(bmfHeader))
	{return NULL;}
    if(bmfHeader.bfType!=DIB_HEADER_MARKER)
	{return NULL;}
	hDIB=(HDIB)::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,dwBitsSize-sizeof(BITMAPFILEHEADER));
	if(hDIB==0)
		return NULL;
	pDIB=(LPSTR)::GlobalLock((HGLOBAL)hDIB);
	if(file.Read(pDIB,dwBitsSize-sizeof(BITMAPFILEHEADER))!=dwBitsSize-sizeof(BITMAPFILEHEADER))
	{
		::GlobalUnlock((HGLOBAL)hDIB);
		::GlobalFree((HGLOBAL)hDIB);
		return NULL;
	}
	::GlobalUnlock((HGLOBAL)hDIB);
	return hDIB;
}

HDIB CDIB::CreateDIB(LPCTSTR lpPathName)
{
	HDIB _hDIB;
	CFile file;
	CFileException fe;
	if(!file.Open(lpPathName,CFile::modeRead|CFile::shareDenyWrite,&fe))
	{
	//	ReportSaveLoadException(lpPathName,&fe,FALSE,AFX_IDP_FAILED_TO_OPEN_DOC);
		//_hDIB=NULL;
		return NULL;
	}
	TRY{
		_hDIB=ReadDIBFile(file);
	}
	CATCH(CFileException,eLoad)
	{
		file.Abort();
		_hDIB=NULL;
	//	return ;
	}
	END_CATCH
	return _hDIB;
}

CSize CDIB::GetDIBSize(LPSTR lpDIB)//����ͼ��ߴ磬������ʵ�ʴ洢�ߴ�
{
	LPBITMAPINFOHEADER lpbmi;
	LPBITMAPCOREHEADER lpbmc;
	lpbmi=(LPBITMAPINFOHEADER)lpDIB;
	lpbmc=(LPBITMAPCOREHEADER)lpDIB;
	if(IS_WIN30_DIB(lpDIB))
	{
		return CSize((int)lpbmi->biWidth,(int)lpbmi->biHeight);	
	}
	else
	{
		return CSize((int)lpbmc->bcWidth,(int)lpbmc->bcHeight);
	}
}

WORD CDIB::NumColors(LPSTR lpbi)
{
	WORD wBitCount;
	WORD wNumCol;
	if(IS_WIN30_DIB(lpbi))
	{
		DWORD dwClrUsed;
		dwClrUsed=((LPBITMAPINFOHEADER)lpbi)->biClrUsed;
		if(dwClrUsed!=0)
			return (WORD)dwClrUsed;
	}

		if(IS_WIN30_DIB(lpbi))
			wBitCount=((LPBITMAPINFOHEADER)lpbi)->biBitCount;
		else
			wBitCount=((LPBITMAPCOREHEADER)lpbi)->bcBitCount;
		switch(wBitCount)
		{
		case 1:
			wNumCol=2;
			break;
		case 4:
			wNumCol=16;
			break;
		case 8:
			wNumCol=256;
			break;
		default:
			wNumCol=0;		
		}
		return wNumCol;
}

BOOL CDIB::CreateDIBPalette(HDIB hDIB, CPalette *cPal)
{
	LPLOGPALETTE lpPal;//ָ�룬ָ���߼���ɫ��
	HANDLE hLogPal;//��ɫ����
	int i;
	WORD wNumColors;
	LPSTR lpbi;//DIBָ��
	LPBITMAPINFO lpbmi;//BITMAPINFO�ṹָ�룬���к���û�н�������ṹ,����ֱ�Ӱ�DIB�����ָ�븳����
	LPBITMAPCOREINFO lpbmc;
	BOOL bResult=FALSE;
	if(hDIB==NULL)
		return FALSE;
	lpbi=(LPSTR)::GlobalLock((HGLOBAL)hDIB);
	lpbmi=(LPBITMAPINFO)lpbi;
	lpbmc=(LPBITMAPCOREINFO)lpbi;
	wNumColors=NumColors(lpbi);
	if(wNumColors!=0){
		hLogPal=::GlobalAlloc(GHND,sizeof(LOGPALETTE)+sizeof(PALETTEENTRY)*wNumColors);
		if(hLogPal==0)
		{
			::GlobalUnlock((HGLOBAL)hDIB);
			return FALSE;		
		}
		lpPal=(LPLOGPALETTE)::GlobalLock((HGLOBAL)hLogPal);
		lpPal->palVersion=PALVERSION;
		lpPal->palNumEntries=(WORD)wNumColors;
		if(IS_WIN30_DIB(lpbi)){
			for(i=0;i<(int)wNumColors;i++){
				lpPal->palPalEntry[i].peRed=lpbmi->bmiColors[i].rgbRed;
				lpPal->palPalEntry[i].peGreen=lpbmi->bmiColors[i].rgbGreen;
				lpPal->palPalEntry[i].peBlue=lpbmi->bmiColors[i].rgbBlue;
				lpPal->palPalEntry[i].peFlags=0;			
			}
		}
		else{
			for(i=0;i<(int)wNumColors;i++){
				lpPal->palPalEntry[i].peRed=lpbmc->bmciColors[i].rgbtRed;
				lpPal->palPalEntry[i].peGreen=lpbmc->bmciColors[i].rgbtGreen;
				lpPal->palPalEntry[i].peBlue=lpbmc->bmciColors[i].rgbtBlue;
				lpPal->palPalEntry[i].peFlags=0;			
			}
		}//end else
		bResult=cPal->CreatePalette(lpPal);
		::GlobalUnlock((HGLOBAL)hLogPal);
		::GlobalFree((HGLOBAL)hLogPal);
	}
	::GlobalUnlock((HGLOBAL)hDIB);
	return bResult;
}

HDIB CDIB::GetHDIB() const
{
	return m_hDIB;
}

BOOL CDIB::PaintDIB(HDC hDC, LPRECT lpDCRect)
{
 CRect rcDIB;
 rcDIB.left=0; rcDIB.top=0; rcDIB.right=m_sizeDIB.cx; rcDIB.bottom=m_sizeDIB.cy;
 BOOL bSuccess=FALSE;
 LPSTR lpDIBHdr; //��Ϣͷ
 LPSTR lpDIBBits; //ͼ����ʼλ��
 HPALETTE hPal=NULL;//DIB��ɫ����
 HPALETTE hOldPal=NULL;
 if(m_hDIB==NULL)
	 return FALSE;
 lpDIBHdr=(LPSTR)::GlobalLock((HGLOBAL)m_hDIB);
 lpDIBBits=FindDIBBits(lpDIBHdr);
 if(m_pPal!=NULL)
 {
	 hPal=(HPALETTE)m_pPal->m_hObject;
	 hOldPal=::SelectPalette(hDC,hPal,TRUE);//ȫ�ֺ���(API)������ǰ����hDC�����µĵ�ɫ�壬��������ǰ�ĵ�ɫ�� 
 }
 ::SetStretchBltMode(hDC,COLORONCOLOR);//(API)
 if((RECTWIDTH(lpDCRect)==m_sizeDIB.cx)&&(RECTHEIGHT(lpDCRect)==m_sizeDIB.cy))//Ŀ�������Դ������ͬ,����ȫ�ֺ���SetDIBitsToDevice
	 bSuccess=::SetDIBitsToDevice(hDC,lpDCRect->left,lpDCRect->top,RECTWIDTH(lpDCRect),RECTHEIGHT(lpDCRect),rcDIB.left,rcDIB.top,0,m_sizeDIB.cy,lpDIBBits,(LPBITMAPINFO)lpDIBHdr,DIB_RGB_COLORS);
 else //Ŀ��������Դ����ͬʱ����������,����ȫ�ֺ���StretchDIBits
	 bSuccess=::StretchDIBits(hDC,lpDCRect->left,lpDCRect->top,RECTWIDTH(lpDCRect),RECTHEIGHT(lpDCRect),rcDIB.left,rcDIB.top,m_sizeDIB.cx,m_sizeDIB.cy,lpDIBBits,(LPBITMAPINFO)lpDIBHdr,DIB_RGB_COLORS,SRCCOPY);
 ::GlobalUnlock((HGLOBAL)m_hDIB);
 if(hOldPal!=NULL)
	 ::SelectPalette(hDC,hOldPal,TRUE);
 
 return bSuccess;
}

//����DIB��������ص���ʼλ�ã���������ָ��
LPSTR CDIB::FindDIBBits(LPSTR lpbi)
{
	return (lpbi+*(LPWORD)lpbi+PaletteSize(lpbi));//*(LPWORD)lpbiΪ��Ϣͷ��һ��Ԫ�أ���biSize����ʾ����Ϣͷ�ĳ���
}

WORD CDIB::PaletteSize(LPSTR lpbi)
{
	if(IS_WIN30_DIB(lpbi)){
		return (WORD)(NumColors(lpbi)*sizeof(RGBQUAD));
	}
	else{
		return (WORD)(NumColors(lpbi)*sizeof(RGBTRIPLE));
	}
}

CSize CDIB::GetDIBSize()
{
	return m_sizeDIB;
}

//����pDIB�����е�һ����������һ����ͼ����
CDIB::CDIB(CDIB* pDIB, int _left, int _top, int _right, int _bottom)
{
	int _width,_height,i,j,m,n;
	_width=_right-_left;
	_height=_bottom-_top;
	int _widthBytes=WIDTHBYTES(8*_width);
	int srcWidth=pDIB->GetDIBSize().cx;
	int srcHeight=pDIB->GetDIBSize().cy;
	int srcwidthBytes=WIDTHBYTES(8*srcWidth);
	LPSTR lpbi,destLpbi;
	unsigned char* destImage, * srcImage;
	LPBITMAPINFOHEADER lpbmi,destLpbmi;
	HDIB _hDIB;

	if(!((_left>=0)&&(_right<=srcWidth)&&(_top>=0)&&(_bottom<=srcHeight)))
	{
		MessageBox(NULL,"��ͼ��ı߽綨�����",NULL,MB_OK);
		SetEmpty();
		return;
	}

	_hDIB=pDIB->GetHDIB();
	lpbi=(LPSTR)::GlobalLock((HGLOBAL)_hDIB);
	if(NumColors(lpbi)!=256)//��֧�ֶ�256ɫλͼ��ȡ��λͼ
	{
		MessageBox(NULL,"��֧��256λͼ��",NULL,MB_OK);
		::GlobalUnlock((HGLOBAL)_hDIB);
		SetEmpty();
		return;
	}
	if(!IS_WIN30_DIB(lpbi))
	{
		MessageBox(NULL,"��֧��WIN30λͼ!",NULL,MB_OK);
		::GlobalUnlock((HGLOBAL)_hDIB);
		SetEmpty();
		return;
	}
	WORD _paletteSize=pDIB->PaletteSize(lpbi);
//	m_hDIB=(HDIB)::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,sizeof(BITMAPINFOHEADER)+_paletteSize+_widthBytes*_height);
	m_hDIB=(HDIB)::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,*(LPWORD)lpbi+_paletteSize+_widthBytes*_height);
	if(m_hDIB==NULL)
	{
		::GlobalUnlock((HGLOBAL)_hDIB);
		SetEmpty();
		return;
	}
	destLpbi=(LPSTR)::GlobalLock((HGLOBAL)m_hDIB);
	::memcpy(destLpbi,lpbi,sizeof(BITMAPINFOHEADER)+_paletteSize);
	destLpbmi=(LPBITMAPINFOHEADER)destLpbi;
	lpbmi=(LPBITMAPINFOHEADER)lpbi;
	destLpbmi->biBitCount=8;
	destLpbmi->biClrUsed=256;
	destLpbmi->biHeight=_height;
	destLpbmi->biWidth=_width;
	destLpbmi->biSizeImage=_widthBytes*_height;
	destImage=(unsigned char*)FindDIBBits(destLpbi);
	srcImage=(unsigned char*)FindDIBBits(lpbi);
	for(j=_top,n=_height-1;j<_bottom;j++,n--)
		for(i=_left,m=0;i<_right;i++,m++)
		{
			*(destImage+n*_widthBytes+m)=*(srcImage+(srcHeight-j-1)*srcwidthBytes+i);
		}
	::GlobalUnlock((HGLOBAL)_hDIB);
	::GlobalUnlock((HGLOBAL)m_hDIB);
	//m_sizeDIB.cx=_widthBytes;
	m_sizeDIB.cx=_width;
	m_sizeDIB.cy=_height;
	m_pPal=new CPalette;
	if(!CreateDIBPalette(m_hDIB,m_pPal))
	{delete m_pPal; m_pPal=NULL;}
}

/**
* �ú�����pDIBΪģ�壬��Gabor��ģpGaborΪ���ݣ�����һ���µ�
* DIB�ļ������ļ��ĳ���ֱ�Ϊԭͼ���1/5
* _changePal���Ϊ�Ƿ�ı��ɫ��
*/
CDIB::CDIB(CDIB* pDIB,FLOAT *pGabor, CSize _size, BOOL _changePal)
{
	int _width,_height,i,m,n;
	_width=_size.cx;
	_height=_size.cy;
	int _widthBytes=WIDTHBYTES(8*_width);
	int srcWidth=pDIB->GetDIBSize().cx;
	int srcHeight=pDIB->GetDIBSize().cy;
	int srcwidthBytes=WIDTHBYTES(8*srcWidth);
	LPSTR lpbi,destLpbi;
	unsigned char* destImage, * srcImage;
	LPBITMAPINFOHEADER lpbmi,destLpbmi;
	HDIB _hDIB;

	if(pGabor==NULL)
		return;
	_hDIB=pDIB->GetHDIB();
	lpbi=(LPSTR)::GlobalLock((HGLOBAL)_hDIB);
	if(NumColors(lpbi)!=256)//��֧�ֶ�256ɫλͼ��ȡ��λͼ
	{
		MessageBox(NULL,"��֧��256λͼ��",NULL,MB_OK);
		::GlobalUnlock((HGLOBAL)_hDIB);
		SetEmpty();
		return;
	}
	if(!IS_WIN30_DIB(lpbi))
	{
		MessageBox(NULL,"��֧��WIN30λͼ!",NULL,MB_OK);
		::GlobalUnlock((HGLOBAL)_hDIB);
		SetEmpty();
		return;
	}
	WORD _paletteSize=pDIB->PaletteSize(lpbi);
//	m_hDIB=(HDIB)::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,sizeof(BITMAPINFOHEADER)+_paletteSize+_widthBytes*_height);
	m_hDIB=(HDIB)::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,*(LPWORD)lpbi+_paletteSize+_widthBytes*_height);
	if(m_hDIB==NULL)
	{
		::GlobalUnlock((HGLOBAL)_hDIB);
		SetEmpty();
		return;
	}
	destLpbi=(LPSTR)::GlobalLock((HGLOBAL)m_hDIB);
	::memcpy(destLpbi,lpbi,sizeof(BITMAPINFOHEADER)+_paletteSize);
	destLpbmi=(LPBITMAPINFOHEADER)destLpbi;
	lpbmi=(LPBITMAPINFOHEADER)lpbi;
	destLpbmi->biBitCount=8;
	destLpbmi->biClrUsed=256;
	destLpbmi->biHeight=_height;
	destLpbmi->biWidth=_width;
	destLpbmi->biSizeImage=_widthBytes*_height;
	destImage=(unsigned char*)FindDIBBits(destLpbi);
	srcImage=(unsigned char*)FindDIBBits(lpbi);
	
	FLOAT _max=0.0f;
	FLOAT _min, _scope;
	for(i=0;i<_width*_height;i++)
		_max=(_max>pGabor[i])?_max:pGabor[i];
	_min=_max;
	for(i=0;i<_width*_height;i++)
		_min=(_min<pGabor[i])?_min:pGabor[i];
	_scope=_max-_min;
	for(n=0;n<_height;n++)
		for(m=0;m<_width;m++)
		{
			*(destImage+(_height-1-n)*_widthBytes+m)=(unsigned char)((pGabor[n*_width+m]-_min)/_scope*255);
			//*(destImage+n*_widthBytes+m)=(BYTE)(m*10);
		}
/////change Palette:
	if(_changePal)
	{
	WORD wNumColors;
	wNumColors=NumColors(destLpbi);
	LPBITMAPINFO lpbmi;//BITMAPINFO�ṹָ�룬���к���û�н�������ṹ,����ֱ�Ӱ�DIB�����ָ�븳����
	LPBITMAPCOREINFO lpbmc; 
	lpbmi=(LPBITMAPINFO)destLpbi;
	lpbmc=(LPBITMAPCOREINFO)destLpbi;
		if(IS_WIN30_DIB(destLpbi))
		{
			for(i=0;i<(int)wNumColors;i++)
			{
				lpbmi->bmiColors[i].rgbBlue=(BYTE)i;
				lpbmi->bmiColors[i].rgbGreen=(BYTE)i;
				lpbmi->bmiColors[i].rgbRed=(BYTE)i;
				lpbmi->bmiColors[i].rgbReserved=0;
			}
		}
		else
		{
			for(i=0;i<(int)wNumColors;i++)
			{
				lpbmc->bmciColors[i].rgbtBlue=(BYTE)i;
				lpbmc->bmciColors[i].rgbtGreen=(BYTE)i;
				lpbmc->bmciColors[i].rgbtRed=(BYTE)i;
			}		
		}
	}
//////////////////
	::GlobalUnlock((HGLOBAL)_hDIB);
	::GlobalUnlock((HGLOBAL)m_hDIB);
	//m_sizeDIB.cx=_widthBytes;
	m_sizeDIB.cx=_width;
	m_sizeDIB.cy=_height;
	m_pPal=new CPalette;
	if(!CreateDIBPalette(m_hDIB,m_pPal))
	{delete m_pPal; m_pPal=NULL;}
}

void CDIB::SetEmpty()
{
		m_hDIB=NULL;
		m_pPal=NULL;
		m_sizeDIB=CSize(0,0);
}

BOOL CDIB::SaveDIB(LPCTSTR lpszPathName)
{
	CFile file;
	CFileException fe;
	if(!file.Open(lpszPathName,CFile::modeCreate|CFile::modeReadWrite|CFile::shareExclusive,&fe))
	{
	//	ReportSaveLoadException(lpszPathName,&fe,FALSE,AFX_IDP_INVALID_FILENAME);
		return FALSE;	
	}
	BOOL bSuccess=FALSE;
	TRY{
//		BeginWaitCursor();
		bSuccess=SaveDIB(m_hDIB,file);
		file.Close();
	}
	CATCH(CException,eSave){
		file.Abort();
//		EndWaitCursor();
//		ReportSaveLoadException(lpszPathName,eSave,TRUE,AFX_IDP_FAILED_TO_SAVE_DOC);
		return FALSE;
	}
	END_CATCH

//	EndWaitCursor();
	if(!bSuccess)
	{
		CString strMsg="�޷�����BMPͼ��";
		MessageBox(NULL,strMsg,NULL,MB_ICONINFORMATION|MB_OK);			
	}
	return bSuccess;
}

BOOL CDIB::SaveDIB(HDIB hDib, CFile &file)
{
	BITMAPFILEHEADER bmfHdr;
	LPBITMAPINFOHEADER lpBI;
	DWORD dwDIBSize;
	if(hDib==NULL)
		return FALSE;
	lpBI=(LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL)hDib);
	if(lpBI==NULL)
		return FALSE;
	if(!IS_WIN30_DIB(lpBI))
	{
		::GlobalUnlock((HGLOBAL)hDib);
		return FALSE;
	}
	bmfHdr.bfType=DIB_HEADER_MARKER;
	//�����ļ��ܴ�С
	dwDIBSize=*(LPDWORD)lpBI+PaletteSize((LPSTR)lpBI);
	if((lpBI->biCompression==BI_RLE8)||(lpBI->biCompression==BI_RLE4))
		dwDIBSize+=lpBI->biSizeImage;
	else{
	
		DWORD dwBmBitsSize;
		dwBmBitsSize=WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount))*lpBI->biHeight;
		dwDIBSize+=dwBmBitsSize;
		lpBI->biSizeImage=dwBmBitsSize;
	}
	bmfHdr.bfSize=dwDIBSize+sizeof(BITMAPFILEHEADER);
	bmfHdr.bfReserved1=0;
	bmfHdr.bfReserved2=0;
	bmfHdr.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+*(LPDWORD)lpBI+PaletteSize((LPSTR)lpBI);
	//write:
	TRY{
		file.Write((LPSTR)&bmfHdr,sizeof(BITMAPFILEHEADER));
		file.Write(lpBI,dwDIBSize);	
	}
	CATCH(CFileException, e){
		::GlobalUnlock((HGLOBAL)hDib);
		THROW_LAST();
	}
	END_CATCH
	::GlobalUnlock((HGLOBAL)hDib);

	return TRUE;
}

BOOL CDIB::ScaleNormal(CSize toSize)
{//�ߴ��һ������Ҫ���һ����ĳߴ�>=10*10
	if((toSize.cx<10)||(toSize.cy<10))
	{
		MessageBox(NULL,"��һ�ߴ�������10��10",NULL,MB_OK);
		return FALSE;
	}
	int destWidth,destHeight,srcWidth,srcHeight;
	destWidth=toSize.cx;
	destHeight=toSize.cy;
	srcWidth=this->GetDIBSize().cx;
	srcHeight=this->GetDIBSize().cy;
	int srcWidthBytes=WIDTHBYTES(8*srcWidth);
	int destWidthBytes=WIDTHBYTES(8*destWidth);
	LPSTR lpbi,destLpbi;
	LPBITMAPINFO destLpbmi;
	BYTE *srcImage,*destImage;
	HDIB tmp_hDIB;
	lpbi=(LPSTR)::GlobalLock((HGLOBAL)m_hDIB);
	tmp_hDIB=(HDIB)::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,*(LPWORD)lpbi+PaletteSize(lpbi)+destWidthBytes*destHeight);
	if(tmp_hDIB==NULL)
	{
		MessageBox(NULL,"�����ڴ����",NULL,MB_OK);
		::GlobalUnlock((HGLOBAL)m_hDIB);
		return FALSE;
	}
	destLpbi=(LPSTR)::GlobalLock((HGLOBAL)tmp_hDIB);
	::memcpy(destLpbi,lpbi,*(LPWORD)lpbi+PaletteSize(lpbi));
	destLpbmi=(LPBITMAPINFO)destLpbi;
	destLpbmi->bmiHeader.biHeight=destHeight;//��һ���ͼ���
	destLpbmi->bmiHeader.biWidth=destWidth;//��һ���ͼ���
	destLpbmi->bmiHeader.biSizeImage=destWidthBytes*destHeight;//ͼ���ʵ�ʴ洢��С
	srcImage=(BYTE*)FindDIBBits(lpbi);
	destImage=(BYTE*)FindDIBBits(destLpbi);
	/////////˫���Բ�ֵ���гߴ��һ������
	FLOAT sx,sy;//���ŵı�������
	sx=((FLOAT)srcWidth)/destWidth;
	sy=((FLOAT)srcHeight)/destHeight;
	//BYTE I_00,I_01,I_10,I_11,I_tmp1,I_tmp2;//����˫���Բ�ֵʱ��Ӧ���ĸ���ĻҶ�ֵ
	int x0,y0,x1,y1;//����˫���Բ�ֵʱ��Ӧ���ĸ��������ֵ
	int i,j;//ѭ������

	for(i=0;i<destHeight;i++)
		for(j=0;j<destWidth;j++)
		{
			x0=(int)(j*sx);
			x1=x0+1;
			y0=(int)(i*sy);
			y1=y0+1;
			if(x1>=srcWidth) x1=srcWidth-1;
			if(y1>=srcHeight) y1=srcHeight-1;
			/**
				������˫���Բ�ֵʱ(���汻ע�͵��Ĳ���)����Ȼ�������Ͽ���
				����ʾЧ�������ã���ʹ������һ�д������滻���÷������Ǽ򵥵Ľ��������滻
			*/
			*(destImage+i*destWidthBytes+j)=*(srcImage+y0*srcWidthBytes+x0);
			/*I_00=*(srcImage+y0*srcWidthBytes+x0);
			I_01=*(srcImage+y0*srcWidthBytes+x1);
			I_10=*(srcImage+y1*srcWidthBytes+x0);
			I_11=*(srcImage+y1*srcWidthBytes+x1);
			I_tmp1=I_00+(BYTE)((sx*j-x0)*(int)(I_01-I_00));
			I_tmp2=I_10+(BYTE)((sx*j-x0)*(int)(I_11-I_10));
			*(destImage+i*destWidthBytes+j)=I_tmp1+(BYTE)((sy*i-y0)*(int)(I_tmp2-I_tmp1));
		/////////////////////���´��벻��
			if(I_01>I_00)
				I_tmp1=I_00+(BYTE)((sx*j-x0)*(I_01-I_00));
			else
				I_tmp1=I_01+(BYTE)((x1-sx*j)*(I_00-I_01));
			if(I_11>I_10)
				I_tmp2=I_10+(BYTE)((sx*j-x0)*(I_11-I_10));
			else
				I_tmp2=I_11+(BYTE)((x1-sx*j)*(I_10-I_11));
			if(I_tmp2>I_tmp1)
				*(destImage+i*destWidthBytes+j)=I_tmp1+(BYTE)((sy*i-y0)*(I_tmp2-I_tmp1));
			else
				*(destImage+i*destWidthBytes+j)=I_tmp2+(BYTE)((y1-sy*i)*(I_tmp1-I_tmp2));
	  ////////////////////////////////////////////////////////////
			*/		
		}
		::GlobalUnlock((HGLOBAL)m_hDIB);
		::GlobalUnlock((HGLOBAL)tmp_hDIB);
		::GlobalFree((HGLOBAL)m_hDIB);
		m_hDIB=tmp_hDIB;
		m_sizeDIB=CSize(destWidth,destHeight);
	return TRUE;
}
