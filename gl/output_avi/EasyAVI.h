// 
// output_avi
// EasyAVI.h
// 
// The MIT License
// 
// Copyright (c) 2009 sonson, sonson@Picture&Software
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
///*********************************************************
	"EasyAVI.h"			2001/6/19 (c)���g

�y�v���O�����̐����z
AVI�̍쐬�Ɋւ��鏈�����N���X���������̂ł��B
"Microsoft Visual C++ 6.0"�̊��ɍ��킹�č쐬���Ă��܂��B
���̊��̏ꍇ�́A�ꕔ�ύX��������K�v�����邩������܂���B

�y��Ȋ֐��̐����z
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
EasyAVI()

����:
new ���g����EasyAVI�N���X���쐬���ꂽ���K���Ăяo�����֐��ł��B
�e��ϐ������������܂��B
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
~EasyAVI()

����:
delete ���g����EasyAVI�N���X���폜���ꂽ���Ăяo�����֐��ł��B
�e��ϐ����J�����܂��B
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
Start(HWND hWnd,int width,int height,const char* file,int scale,int rate)

����: 
hWnd	�쐬�����摜��`�悵�����E�B���h�̃n���h���ł��B
		NULL������ƃf�B�X�v���C���w�肳��܂��B
width	�쐬������AVI�̕��ł��B
height	�쐬������AVI�̍����ł��B
file	�쐬������AVI�̃t�@�C�����ł��B
scale	�쐬������AVI�̎��ԒP�ʂł��B
rate	�쐬������AVI�̃��[�g�ł��B
		�t���[�����[�g��"step"�b�Ԃ�"rate"�t���[���ƂȂ�܂��B

����:
�^��̑O�������s���܂��B
�Ȃ��A�g�p��J�����g�f�B���N�g�����ω����Ă���\��������܂��B

�Ԃ�l:
�쐬���ꂽ�������R���e�L�X�g�f�o�C�X�̃n���h�����Ԃ���܂��B
���̃������R���e�L�X�g�f�o�C�X�ɕ`�����񂾓��e���A
Save()���s�����Ƃɂ����AVI�ɒǉ�����܂��B
���s�����Ƃ��̕Ԃ�l��NULL�ł��B
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
Save()
����:
����܂���B

����:
Start�ŕԂ���HDC�̓��e��AVI�ɒǉ����܂��B

�Ԃ�l:
��������� true �A���s����� false ��Ԃ��܂��B
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
Clear()
����:
����܂���B

����:
�e�탁�������J�����܂��B
���̊֐��̒���Start�ŊJ���ꂽ�t�@�C������Ă��܂��B
���̂��߂��̊֐����Ă΂ꂽ�ȍ~��AVI�t�@�C���Ƀt���[���̒ǉ��͏o���܂���B

�Ԃ�l:
����܂���B
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
GetBuf(),GetHBITMAP(),GetWidth,GetHeight(),GetHDC();
����:
���O���琄�����Ă��������B

�y���̃v���O�����̎g�p�ɂ��āz
�ȉ��̂��Ƃ�������g�p�͎��R�ł��B
���������R�ł��B

 1. ���p���Ȃ��B�i�ǂ�����Έ��p�ł���̂�������܂��񂪁E�E�E�j
 2. ���l�����̃\�[�X���g�p����̂�W���Ȃ��B
 3. �e�l�̐ӔC�̌��Ɏg�p����B

���Ȃ݂�2.�Ɋւ��Ă�
�u����ɒ��쌠���咣��������w���̃\�[�X�͗��p�֎~�I�x�Ƃ������ȁB�v
�Ƃ����Ӗ��ł��B
�ʂɃ\�[�X�̏o�T�⒘�쌠�̗L�����ǂ��̂����̌����`���͂���܂���B
�u�I�[�v���\�[�X�ɂ���I�v�Ƃ������܂���B
�����A���̐l��������g�p����̂�W����悤�ȍs�ׂ͍s���Ȃƌ����Ӗ��ł��B
��������Ǝg�����ɂ͑S����肠��܂��񂵁A�I�����C���Ɍ��J����̂�����ł��B
����𗘗p�����\�t�g���t���[��V�F�A�ŗ����̂��S���̎��R�ł��B

��A���̃\�[�X�͗L�p�ł���Ƃ͎v���܂����A��΂ł���Ƃ͎v���܂���B
�����牽�����Ƀo�O�����݂��Ă��邩������܂��񂵁A
���炩�̈��e�����y�ڂ��\��������܂��B
���������̂悤�Ȃ��ƂɂȂ��Ă��A���͈�ؐӔC�͎����܂���B
�g�p�͊e�l�̐ӔC�̌��ɍs���Ă��������B

�y�X�V�����z
2001/6/19
	��������k���ĕۑ��ł���悤�ɂȂ����B
**********************************************************/
#ifndef _INCLUDE_EASYAVI_
#define _INCLUDE_EASYAVI_

//Vfw32.lib�������N���܂�
#pragma comment(lib,"Vfw32.lib")
#include <windows.h>
#include <direct.h>
#include <vfw.h>
class EasyAVI{
public:
	EasyAVI();
	~EasyAVI();
	//�^��̑O����
	HDC Start(HWND,unsigned int,unsigned int,const char*,DWORD,DWORD);
	//��荞�񂾉摜��AVI�t�@�C���ɕt������
	bool Save(void);
	//HDC�������ׂĊJ��
	void Clear(void);
	//lpBmp���擾
	LPVOID GetBuf(void);
	//hBmp���擾
	HBITMAP GetHBITMAP(void);
	//�����擾
	unsigned int GetWidth(void);
	//�������擾
	unsigned int GetHeight(void);
	//hMemDC���擾
	HDC GetHDC(void);
	HDC SetBits(LPBITMAPINFOHEADER);
	//�X�g���[����ۑ����Ă���
	bool SaveStream(PAVISTREAM);
private:
	LPVOID lpBmp;
	HBITMAP hBmp;
	HBITMAP hBmpOld;
	HDC hMemDC;
	PAVISTREAM pstm,ptmp;
	PAVIFILE pavi;
	COMPVARS cv;
	AVICOMPRESSOPTIONS opt;
	unsigned int nWidth,nHeight,nSize;
	unsigned int pos;
};
EasyAVI::EasyAVI()
{
	lpBmp = NULL;
	hBmp = NULL;
	hMemDC = NULL;
	pstm = NULL;
	ptmp = NULL;
	pavi = NULL;
	nWidth = nHeight = nSize = 0;
	pos = 0;

}
EasyAVI::~EasyAVI()
{
	Clear();
}
HDC EasyAVI::Start(HWND hWnd,unsigned int width,unsigned int height,const char* file,DWORD scale,DWORD rate)
{
	//�܂��͏�����
	Clear();

	//�e��ϐ��ɒl������
	nWidth = width;
	nHeight = height;
	nSize = (((nWidth*24+31)&~31)/8)*nHeight;

	HDC hDC;
	BITMAPINFOHEADER bmih={sizeof(BITMAPINFOHEADER),nWidth
		,nHeight,1,24,BI_RGB
		,nSize
		,0,0,0,0};
	AVISTREAMINFO si={streamtypeVIDEO,comptypeDIB,0,0,0,0,
						scale,rate,0,0,0,0,(DWORD)-1,0,{0,0,nWidth,nHeight},0,0,"VIDEO"};


	AVIFileInit();

	memset(&cv,0,sizeof(COMPVARS));
	cv.cbSize=sizeof(COMPVARS);
	cv.dwFlags=ICMF_COMPVARS_VALID;
	cv.fccHandler=comptypeDIB;
	cv.lQ=ICQUALITY_DEFAULT;

	if (!ICCompressorChoose(NULL,ICMF_CHOOSE_DATARATE | ICMF_CHOOSE_KEYFRAME,
		&bmih,NULL,&cv,NULL)){
		AVIFileExit();
		return NULL;
	}

	si.fccHandler=cv.fccHandler;
	opt.fccType=streamtypeVIDEO;
	opt.fccHandler=cv.fccHandler;
	opt.dwKeyFrameEvery=cv.lKey;
	opt.dwQuality=cv.lQ;
	opt.dwBytesPerSecond=cv.lDataRate;
	opt.dwFlags=(cv.lDataRate>0?AVICOMPRESSF_DATARATE:0)
		|(cv.lKey>0?AVICOMPRESSF_KEYFRAMES:0);
	opt.lpFormat=NULL;
	opt.cbFormat=0;
	opt.lpParms=cv.lpState;
	opt.cbParms=cv.cbState;
	opt.dwInterleaveEvery=0;

//#define MOVE_CURRENT
#ifdef MOVE_CURRENT
	//OS�ɂ���Ă͂��΂��΂悻�̃f�B���N�g�����w��ł��Ȃ����Ƃ�����܂�
	//���̂Ƃ��͏��"#define MOVE_CURRENT"�̃R�����g�A�E�g���͂����Ă�������
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char name[_MAX_FNAME+4];
	_splitpath(file,drive,dir,name,NULL);
		
	//�f�B���N�g���ƃh���C�u�̈ړ�
	_chdrive(drive[0]-'A'+1);
	_chdir(dir);
	strcat(name,".AVI");

	if (AVIFileOpen(&pavi,name,OF_CREATE
		| OF_WRITE | OF_SHARE_DENY_NONE,NULL)!=0) {
		MessageBox(hWnd,"�ۑ�����t�@�C�����J���܂���ł�����B","���܂�܂�����",MB_OK);
		AVIFileExit();
		return NULL;
	}
#else
	if (AVIFileOpen(&pavi,file,OF_CREATE
		| OF_WRITE | OF_SHARE_DENY_NONE,NULL)!=0) {
		MessageBox(hWnd,"�ۑ�����t�@�C�����J���܂���ł�����B","���܂�܂�����",MB_OK);
		AVIFileExit();
		return NULL;
	}
#endif

	if (AVIFileCreateStream(pavi,&pstm,&si)!=0) {
		MessageBox(hWnd,"�ҏW�p�X�g���[��������܂���ł�����B","���܂�܂�����",MB_OK);
		AVIFileRelease(pavi);
		pavi = NULL;
		AVIFileExit();
		return NULL;
	}
	
	if (AVIMakeCompressedStream(&ptmp,pstm,&opt,NULL)!=AVIERR_OK){
		MessageBox(hWnd,"���k�X�g���[���̍쐬�Ɏ��s���܂����B","�����ւ�ł���",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		AVIFileExit();
		return NULL;
	}

	//�X�g���[���̃t�H�[�}�b�g��ݒ肵�܂���
    if(AVIStreamSetFormat(ptmp,0,&bmih,sizeof(BITMAPINFOHEADER))!=0){
		MessageBox(hWnd,"�X�g���[���̃t�H�[�}�b�g��ݒ肷��̂Ɏ��s���܂�����B","�����ւ�ł���",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIStreamRelease(ptmp);
		ptmp = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		AVIFileExit();
		return NULL;
	}
	


	if ((hDC=GetDC(hWnd))==NULL) {
		MessageBox(hWnd,"HDC���擾�ł��܂���ł�����B","�����ւ�ł���",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		AVIFileExit();
		return NULL;
	}

	if ((hMemDC=CreateCompatibleDC(hDC))==NULL) {
		MessageBox(hWnd,"������DC�����܂���ł�����B","�����ւ�ł���",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		ReleaseDC(NULL,hDC);
		AVIFileExit();
		return NULL;
	}

	if (ReleaseDC(hWnd,hDC)!=1) {
		MessageBox(hWnd,"HDC���J���ł��܂���ł�����B","�����ւ�ł���",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		DeleteDC(hMemDC);
		hMemDC = NULL;
		AVIFileExit();
		return NULL;
	}

	hBmp = CreateDIBSection(hMemDC,(LPBITMAPINFO)&bmih,DIB_RGB_COLORS,&lpBmp,NULL,0);
	
	if(hBmp==NULL){
		MessageBox(hWnd,"HBITMAP�����܂���ł�����B","�����ւ�ł���",MB_OK);
		AVIStreamRelease(pstm);
		pstm = NULL;
		AVIFileRelease(pavi);
		pavi=NULL;
		DeleteDC(hMemDC);
		hMemDC = NULL;
		AVIFileExit();
		return NULL;
	}

	hBmpOld = (HBITMAP)SelectObject(hMemDC,hBmp);

	return hMemDC;
}
bool EasyAVI::Save(void)
{
	if(pstm==NULL||lpBmp==NULL){
		return false;
	}
	if (AVIStreamWrite(ptmp,pos++,1,lpBmp,nSize,AVIIF_KEYFRAME,NULL,NULL)!=0) {
		return false;
	}
	return true;
}
void EasyAVI::Clear(void)
{
	if(ptmp!=NULL){
		AVIStreamRelease(ptmp);
		ptmp = NULL;
	}

	if(pstm!=NULL){
		AVIStreamRelease(pstm);
		pstm = NULL;
	}
	if (pavi!=NULL) {
		AVIFileRelease(pavi);
		pavi=NULL;
	}
	if (hBmp!=NULL) {
		DeleteObject(SelectObject(hMemDC,hBmpOld));
		hBmp=NULL;
	}
	if (hMemDC!=NULL) {
		DeleteDC(hMemDC);
		hMemDC = NULL;
	}
	ICCompressorFree(&cv);
	lpBmp = NULL;
	pos = 0;
	AVIFileExit();
}
LPVOID EasyAVI::GetBuf(void)
{
	return lpBmp;
}
HBITMAP EasyAVI::GetHBITMAP(void)
{
	return hBmp;
}
unsigned int EasyAVI::GetHeight(void)
{
	return nHeight;
}
unsigned int EasyAVI::GetWidth(void)
{
	return nWidth;
}
HDC EasyAVI::GetHDC(void)
{
	return hMemDC;
}
HDC EasyAVI::SetBits(LPBITMAPINFOHEADER pbmih)
{
	LPBYTE bits = ((LPBYTE)pbmih) + sizeof(BITMAPINFOHEADER);

	if (pbmih->biClrUsed==0){
		switch (pbmih->biBitCount) {
			case  1:bits += sizeof(RGBQUAD)*2;break;
			case  4:bits += sizeof(RGBQUAD)*16;break;
			case  8:bits += sizeof(RGBQUAD)*256;break;
			case 24:bits += 0;break;
			case 16:
			case 32:
				bits += (pbmih->biCompression==BI_RGB?0:sizeof(DWORD)*3);
		}
	}else{
			bits += pbmih->biClrUsed*sizeof(RGBQUAD);
	}

	SetDIBits(hMemDC,hBmp,0,pbmih->biHeight,(void*)bits,(LPBITMAPINFO)pbmih,DIB_RGB_COLORS);
	return hMemDC;
}
#endif