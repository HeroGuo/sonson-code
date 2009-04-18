// 
// mfc_gl_mdi
// InitGL.cpp
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
//////////////////////////////////////////////////////////////////////
//OpenGL�̏������A���T�C�Y�Ɋւ���֐� InitGL.cpp
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "InitGL.h"

//OpenGL�����_�����O�R���e�L�X�g�̍쐬
//�s�N�Z���t�H�[�}�b�g�̐ݒ�
HGLRC Init_Pixel(HDC hDC)
{
	HGLRC hRC;
	int pixelformat;

    static PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),		//���̍\���̂̃T�C�Y
	1,									//OpenGL�o�[�W����
	PFD_DRAW_TO_WINDOW |				//Window�X�^�C��
		PFD_SUPPORT_OPENGL |			//OpenGL
		PFD_DOUBLEBUFFER,				//�_�u���o�b�t�@�g�p�\
	PFD_TYPE_RGBA,						//RGBA�J���[
	24,									//�F��
	0, 0,								//RGBA�̃r�b�g�ƃV�t�g�ݒ�		
	0, 0,								//G
	0, 0,								//B
	0, 0,								//A
	0,									//�A�L�������[�V�����o�b�t�@
	0, 0, 0, 0, 						//RGBA�A�L�������[�V�����o�b�t�@
	32,									//Z�o�b�t�@	
	0,									//�X�e���V���o�b�t�@
	0,									//�g�p���Ȃ�
	PFD_MAIN_PLANE,						//���C���[�^�C�v
	0,									//�\��
	0, 0, 0								//���C���[�}�X�N�̐ݒ�E���g�p
    };

	//�f�o�C�X�R���e�L�X�g
	if (!hDC){
		MessageBox(NULL,"Getting HDC Failed....","ERROR",MB_OK);
		return NULL;
	}
	//�s�N�Z���t�H�[�}�b�g�̎w��
    if ( (pixelformat = ChoosePixelFormat(hDC, &pfd)) == 0 ){
        MessageBox(NULL, "ChoosePixelFormat Failed....", "Error", MB_OK);
        return NULL;
    }
	//�s�N�Z���t�H�[�}�b�g�̐ݒ�
    if (SetPixelFormat(hDC, pixelformat, &pfd) == FALSE){
        MessageBox(NULL, "SetPixelFormat Failed....", "Error", MB_OK);
        return NULL;
    }
	//OpenGL�����_�����O�R���e�L�X�g�̍쐬
	if (!(hRC=wglCreateContext(hDC))){
		MessageBox(NULL,"Creating HGLRC Failed....","ERROR",MB_OK);
		return NULL;
	}

	return hRC;
}
//�E�B���h�E�̃��T�C�Y���̏���
void Resize(int x, int y){
	//����ɂ���ăr���[�|�[�g��ݒ肷��
	glViewport(0, 0, x, y);
	GLdouble aspect = (GLdouble)x/(GLdouble)y;
	//�v���W�F�N�V�������[�h�Ŏˉe
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, aspect, 1.0, 1000.0 );
	//�m�[�}���̃��f���r���[���[�h�ֈڍs
	glMatrixMode( GL_MODELVIEW );
}
//�e�R���e�L�X�g�̉��
void Release_GLWindow(HGLRC hRC){
	//OpenGL�����_�����O�R���e�L�X�g��
	//�f�o�C�X�R���e�L�X�g���擾
//	hRC = wglGetCurrentContext();
//	hDC = wglGetCurrentDC();
	//�J�����g�R���e�L�X�g�����
	wglMakeCurrent(NULL, NULL);
	if(!hRC){
		//OpenGL�����_�����O�R���e�L�X�g���Ȃ�
		MessageBox(NULL,"Release HGLRC Failed....","ERROR",MB_OK);
	}
	if(hRC){
		//���
		wglDeleteContext(hRC);
	}
}
//�eGL Function�̊J�n
void StartFunction(void){
	//�N���C�A���g�̈�̏�����
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0 );
	glClearDepth( 1.0 );
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}