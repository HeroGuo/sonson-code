// 
// win_offscreen_rendering
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

#include "InitGL.h"

//�E�B���h�E�̏������E�r���[�̍쐬
void Init_GLWindow(int width,int height){
	GLdouble aspect;
	//�N���C�A���g�̈�̓h��Ԃ��F�̐ݒ�
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	//�f�v�X�o�b�t�@�N���A�l�̐ݒ�
	glClearDepth( 1.0 );
	//�A�X�y�N�g��̏�����
	aspect = (GLdouble)width/(GLdouble)height;
	//�v���W�F�N�V�������[�h�Ŏˉe
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, aspect, 1.0, 100.0 );
	//�m�[�}���̃��f���r���[���[�h�ֈڍs
	glMatrixMode( GL_MODELVIEW );
}
//�E�B���h�E�̃��T�C�Y���̏���
void Resize(int width,int height){
	//����ɂ���ăr���[�|�[�g��ݒ肷��
	glViewport(0, 0, width,height);
}
//�eGL Function�̊J�n
void StartFunction(void){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}