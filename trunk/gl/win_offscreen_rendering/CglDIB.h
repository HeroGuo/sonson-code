// 
// win_offscreen_rendering
// CglDIB.h
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
//OpenGL�pDIB�N���X

#ifdef _CGLDIB
#else
#define _CGLDIB

#include "glos.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

class CglDIB{
protected:
	HDC					hDC;				//�R���e�L�X�g�n���h��
	BITMAPINFOHEADER*	BitmapInfo;			//�r�b�g�}�b�v�w�b�_
	HBITMAP				hBitmap;
	HBITMAP				hBitmapOld;			//�ȑO�̃r�b�g�}�b�v�n���h��
	void*				data;				//�r�b�g�}�b�v�f�[�^
	int					width;				//�������̃T�C�Y
	int					height;				
	int					color_bit;			//OpenGL�@�F��
	int					depth_bit;			//OpenGL�@�f�v�X�o�b�t�@
public:
	~CglDIB();								//�f�X�g���N�^
	BOOL	CreateGLDIB(int,int,int,int);	//�������̍쐬
	BOOL	Draw(HDC,int,int);				//�`��
	HDC		GetDC(void);					//�R���e�L�X�g�n���h����Ԃ�
	HBITMAP GetBitmap(void);				//�r�b�g�}�b�v�n���h����Ԃ�
};

#endif
