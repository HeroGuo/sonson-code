// 
// simple_glut
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
//#include <glut/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH	300
#define HEIGHT	300

///////////////////////////////////////////////////////////////////////////////
//�`��֐�
void display(void){
	//�E�B���h�E��h��Ԃ�
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//���_�̕ϊ��s��̏�����
	glLoadIdentity();
	//���_�̌���
	gluLookAt(
		2,2,2,
		0,0,0,
		0.0, 1.0, 0.0);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	//glEnable(GL_AUTO_NORMAL );
	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);

	glColor3f(1,0.5,0.5);
	glutSolidTeapot(1);
	glFinish();
	glutSwapBuffers();
}
///////////////////////////////////////////////////////////////////////////////
//OpenGL�������R�}���h
void init (void){
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//�N���C�A���g�̈�̓h��Ԃ��F�̐ݒ�
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	//�f�v�X�o�b�t�@�N���A�l�̐ݒ�
	glClearDepth( 1.0 );
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
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	//�E�B���h�E�̏������ƍ쐬
	glutInitWindowSize (WIDTH,HEIGHT); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Simple GLUT");
	//OpenGL������
	init();
	//�e�����֐��̓o�^
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	//���C�����[�v
	glutMainLoop();
	return 0;
}