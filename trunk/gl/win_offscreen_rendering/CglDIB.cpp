// 
// win_offscreen_rendering
// CglDIB.cpp
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
/////////////////////////////////////////////////////////////////////////////////
//OpenGL�pDIB�N���X����

#include "CglDIB.h"

///////////////////////////////////////////////////////////////////////////////
//�f�X�g���N�^
CglDIB::~CglDIB(){
	HGLRC hRC;
	//�����_�����O�R���e�L�X�g�̊J��
	hRC = wglGetCurrentContext();
	//�J�����g�R���e�L�X�g�����
	wglMakeCurrent(NULL, NULL);
	if(hRC){
		//���
		wglDeleteContext(hRC);
	}
	//�ȑO�̃r�b�g�}�b�v�Ƃނ��т���
	SelectObject(hDC, hBitmapOld);
	//�r�b�g�}�b�v�I�u�W�F�N�g���폜
	DeleteObject(hBitmap);
	//DC���J��
	DeleteDC(hDC);
	//�r�b�g�}�b�v�w�b�_�̃������J��
	delete BitmapInfo;
};
///////////////////////////////////////////////////////////////////////////////
//�`��
BOOL CglDIB::Draw(HDC destDC,			//�R�s�[��̃f�o�C�X�R���e�L�X�g
				  int destWidth,		//�R�s�[��̈�͈̔�
				  int destHeight
				  ){
	//�]�����[�h�ݒ�
	SetStretchBltMode(destDC, COLORONCOLOR);
	//�]���i�R�s�[�j
	StretchDIBits(
		destDC,
		0,0,			//�R�s�[��̍��W
		destWidth,destHeight,
		0,0,			//�\�[�X�̍��W
		width, height,
		data,
		(BITMAPINFO*)BitmapInfo,
		DIB_RGB_COLORS,
		SRCCOPY
	);
  return TRUE;
};
///////////////////////////////////////////////////////////////////////////////
//�r�b�g�}�b�v�������̍쐬
BOOL CglDIB::CreateGLDIB(int inputWidth,		//�������̃T�C�Y
						 int inputHeight,
						 int inputColor,		//�������̐F��
						 int inputDepth			//�������̃f�v�X�o�b�t�@
						 ){
	HGLRC hRC;
	width = inputWidth;
	height = inputHeight;
	
	//�r�b�g�}�b�v���
	BitmapInfo = new BITMAPINFOHEADER;
	int iSize = sizeof(BITMAPINFOHEADER) ;
	memset(BitmapInfo, 0, iSize);
	//
	BitmapInfo->biSize = iSize;
	BitmapInfo->biWidth = width;
	BitmapInfo->biHeight = height;
	BitmapInfo->biPlanes = 1;
	BitmapInfo->biBitCount = inputColor;
	BitmapInfo->biCompression = BI_RGB;
	//�݊��f�o�C�X�R���e�L�X�g�̍쐬
	hDC = CreateCompatibleDC(NULL);
	//�r�b�g�}�b�v�������쐬
	hBitmap = CreateDIBSection(hDC,
		(BITMAPINFO*)BitmapInfo,
		DIB_RGB_COLORS,
		&data,
		NULL,
		0
		);
    //�ȑO�̃r�b�g�}�b�v����������ޔ�������
	if(hBitmap){
		hBitmapOld = (HBITMAP)SelectObject(hDC,hBitmap);
	}
	//�s�N�Z���t�H�[�}�b�g�ݒ�
	int pixelformat;
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),		//���̍\���̂̃T�C�Y
		1,									//OpenGL�o�[�W����
		PFD_DRAW_TO_BITMAP |                //�r�b�g�}�b�v�ݒ�
		PFD_SUPPORT_OPENGL |                    
		PFD_SUPPORT_GDI,
		PFD_TYPE_RGBA,						//RGBA�J���[
		inputColor,							//�F��
		0, 0,								//RGBA�̃r�b�g�ƃV�t�g�ݒ�		
		0, 0,								//G
		0, 0,								//B
		0, 0,								//A
		0,									//�A�L�������[�V�����o�b�t�@
		0, 0, 0, 0, 						//RGBA�A�L�������[�V�����o�b�t�@
		inputDepth,									//Z�o�b�t�@	
		0,									//�X�e���V���o�b�t�@
		0,									//�g�p���Ȃ�
		PFD_MAIN_PLANE,						//���C���[�^�C�v
		0,									//�\��
		0, 0, 0								//���C���[�}�X�N�̐ݒ�E���g�p
    };
    //�s�N�Z���t�H�[�}�b�g�̑I��
    if((pixelformat = ChoosePixelFormat(hDC, &pfd))==0){
		return FALSE;
	}
    //�s�N�Z���t�H�[�}�b�g�̓���
    if(SetPixelFormat(hDC, pixelformat, &pfd)==FALSE){
		return FALSE;
	}
	//�����_�����O�R���e�L�X�g�̍쐬
	if((hRC = wglCreateContext(hDC))==NULL){
		return FALSE;
	}
	wglMakeCurrent(hDC, hRC);
	return TRUE;
};
///////////////////////////////////////////////////////////////////////////////
HDC	CglDIB::GetDC(void){
	//�r�b�g�}�b�v�������N���X�̃R���e�L�X�g��Ԃ�
	return hDC;
}
///////////////////////////////////////////////////////////////////////////////
HBITMAP CglDIB::GetBitmap(void){
	//�r�b�g�}�b�v�������N���X�̃r�b�g�}�b�v�n���h����Ԃ�
	return hBitmap;
}