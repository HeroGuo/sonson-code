// 
// simple_stencil
// main.cpp
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
//#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WIDTH	300
#define HEIGHT	300

float t=0;

///////////////////////////////////////////////////////////////////////////////
//�`��֐�
void display(void){

	//�E�B���h�E��h��Ԃ�
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//���_�̕ϊ��s��̏�����
	glLoadIdentity();      
	//���_�̌���
	gluLookAt(
		0,0,8,
		0,0,0,
		0.0, 1.0, 0.0);
	/////////////////////////////////////////////
	//�l�p�`�̕`��͈͂ɃX�e���V���P��t������
	glEnable(GL_STENCIL_TEST);
	glStencilFunc( GL_ALWAYS, 1, ~0);
	//���ꂩ��`�悷����̂̃X�e���V���l�ɂ��ׂĂP�^�O������
	glStencilOp(GL_KEEP,GL_REPLACE,GL_REPLACE);
	/////////////////////////////////////////////
	//�J���[�E�f�v�X�o�b�t�@�}�X�N���Z�b�g����
	//����ňȉ��̓��e�̃s�N�Z���̐F�̒l�́C�������܂�Ȃ��D
	glColorMask(0,0,0,0);
	glDepthMask(0);
	//
	glPushMatrix();
		//�l�p�`�𓮂�������
		glTranslatef(4*cos(t*0.1),sin(t*0.1),0);
		glBegin(GL_QUADS);
			glVertex3f( 1, 1,0);
			glVertex3f(-1, 1,0);
			glVertex3f(-1,-1,0);
			glVertex3f( 1,-1,0);
		glEnd();
	glPopMatrix();
	/////////////////////////////////////////////
	//�r�b�g�}�X�N������
	glColorMask(1,1,1,1);
	glDepthMask(1);
	glStencilOp(GL_KEEP,GL_KEEP ,GL_KEEP);
	/////////////////////////////////////////////
	//�e�B�[�|�b�g�E�I�u�W�F�N�g�̕`��
	//�X�e���V����1�̃s�N�Z���Ƀ��C���[�t���[���ŕ`��
	glStencilFunc( GL_EQUAL, 1, ~0);
	glColor3f(1,0.5,0.5);
	glutWireTeapot(3);
	/////////////////////////////////////////////
	//�e�B�[�|�b�g�E�I�u�W�F�N�g�̕`��
	//�X�e���V����1�̃s�N�Z���Ƀ\���b�h���f���ŕ`��
	glStencilFunc( GL_EQUAL, 0, ~0);
	glColor3f(1,0.5,0.5);
	glutSolidTeapot(3);

	/////////////////////////////////////////////
	//�X�e���V���e�X�g�I��
	glDisable(GL_STENCIL_TEST);
	glFinish();
	glutSwapBuffers();
	t++;
}
///////////////////////////////////////////////////////////////////////////////
//OpenGL�������R�}���h
void init (void){
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//�N���C�A���g�̈�̓h��Ԃ��F�̐ݒ�
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	//�f�v�X�o�b�t�@�N���A�l�̐ݒ�
	glClearDepth( 1.0 );
	//�X�e���V���o�b�t�@�N���A�l�̐ݒ�
	glClearStencil(0);
	//�����ƍގ��̐ݒ�
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL );
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
}
///////////////////////////////////////////////////////////////////////////////
//�}�E�X����
void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			break;
	}
}
///////////////////////////////////////////////////////////////////////////////
//���T�C�Y����
void resize(int w, int h)
{
	GLdouble aspect;
	//����ɂ���ăr���[�|�[�g��ݒ肷��
	glViewport(0, 0, w, h);
	//�A�X�y�N�g��̏�����
	aspect = (GLdouble)w/(GLdouble)h;
	//�v���W�F�N�V�������[�h�Ŏˉe
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60.0, aspect, 1.0,100.0 );
	//�m�[�}���̃��f���r���[���[�h�ֈڍs
	glMatrixMode( GL_MODELVIEW );
}
///////////////////////////////////////////////////////////////////////////////
//���C���֐�
int main(int argc, char** argv){
	//GLUT������
	glutInit(&argc, argv);
	//GLUT�s�N�Z���t�H�[�}�b�g
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	//�E�B���h�E�̏������ƍ쐬
	glutInitWindowSize (800,600); 
	glutInitWindowPosition (200,200);
	glutCreateWindow ("Simple GLUT");
	//OpenGL������
	init();
	//�e�����֐��̓o�^
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutIdleFunc(display);
	//���C�����[�v
	glutMainLoop();
	return 0;
}