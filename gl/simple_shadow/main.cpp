// 
// simple_shadow
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

////////////////////////////////////////////////////////////////////
//�C�ӂ̕��ʂ։e���ˉe����s��\�z�֐�
void projectShadowMatrix(double *m,				//�쐬����s��̃|�C���^
						 double plane[4],		//�ˉe����\�ʂ̕��ʕ�����
						 float light[4]			//�����̓������W�l
						 ){
	float dot = plane[0]*light[0] + plane[1]*light[1] +
				plane[2]*light[2] + plane[3]*light[3];

	m[0]  = dot - light[0]*plane[0];
	m[4]  =     - light[0]*plane[1];
	m[8]  =     - light[0]*plane[2];
	m[12] =     - light[0]*plane[3];

	m[1]  =     - light[1]*plane[0];
	m[5]  = dot - light[1]*plane[1];
	m[9]  =     - light[1]*plane[2];
	m[13] =     - light[1]*plane[3];

	m[2]  =     - light[2]*plane[0];
	m[6]  =     - light[2]*plane[1];
	m[10] = dot - light[2]*plane[2];
	m[14] =     - light[2]*plane[3];

	m[3]  =     - light[3]*plane[0];
	m[7]  =     - light[3]*plane[1];
	m[11] =     - light[3]*plane[2];
	m[15] = dot - light[3]*plane[3];
}
///////////////////////////////////////////////////////////////////////////////
//���̕`��
void DrawFloor(void){	
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
		glVertex3f( 10, -2, 10);
		glVertex3f( 10, -2,-10);
		glVertex3f(-10, -2,-10);
		glVertex3f(-10, -2, 10);
	glEnd();
	glEnable(GL_LIGHTING);
}
///////////////////////////////////////////////////////////////////////////////
//�`��֐�
void display(void){
	//
	double floor_planar[4] = {0,1,0,2};
	double pM[16];
	float lightpos[4] = { 10, 8, 0, 1};

	//�E�B���h�E��h��Ԃ�
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//���_�̕ϊ��s��̏�����
	glLoadIdentity();      
	//���_�̌���
	gluLookAt(
		5,5,20,
		0,0,0,
		0.0, 1.0, 0.0);
	
	/////////////////////////////////////////////
	//�����̈ʒu�̌v�Z�Ɛݒ�
	lightpos[0] = 3*sin(t*0.05);
	lightpos[2] = 6*cos(t*0.05);
	glLightfv(GL_LIGHT0, GL_POSITION, (float*)lightpos);
	
	/////////////////////////////////////////////
	// Plannar Projected Shadow Matrix
	// ���ʎˉe�s��̎Z�o
	projectShadowMatrix(pM,floor_planar,lightpos);

	/////////////////////////////////////////////
	//�����̕`��
	glColor3f(0.7,0.0,0.7);
	glPushMatrix();
		glTranslatef(lightpos[0],lightpos[1],lightpos[2]);
		glutSolidSphere(0.2,10,10);
	glPopMatrix();

	/////////////////////////////////////////////
	//�e�B�[�|�b�g�E�I�u�W�F�N�g�̕`��
	glColor3f(1,0.5,0.5);
	glDisable(GL_CULL_FACE);	
		glutSolidTeapot(3);
	glEnable(GL_CULL_FACE);	

	/////////////////////////////////////////////
	//���̃X�e���V����t����
	glEnable(GL_STENCIL_TEST);
	glStencilFunc( GL_ALWAYS, 1, ~0);
	//���ꂩ��`�悷����̂̃X�e���V���l�ɂ��ׂĂP�^�O������
	glStencilOp(GL_KEEP,GL_KEEP ,GL_REPLACE);
	glColor4f(0.7f, 0.4f, 0.0f, 1.0f);
	DrawFloor();
	/////////////////////////////////////////////
	//�J���[�E�f�v�X�o�b�t�@�}�X�N���Z�b�g����
	//����ňȉ��̓��e�̃s�N�Z���̐F�̒l�́A�������܂�Ȃ��B
	glColorMask(0,0,0,0);
	glDepthMask(0);
	/////////////////////////////////////////////
	//���Ƀe�B�[�|�b�g�̉e�̃X�e���V����t����
	glEnable(GL_STENCIL_TEST);
	glStencilFunc( GL_EQUAL, 1, ~0);
	//���ꂩ��`�悷����̂̃X�e���V���l�ɂ��ׂĂP�^�O������
	glStencilOp(GL_KEEP,GL_KEEP ,GL_INCR);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
		glMultMatrixd(pM);
		glDisable(GL_CULL_FACE);	
			glutSolidTeapot(3);
		glEnable(GL_CULL_FACE);	
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

	/////////////////////////////////////////////
	//�r�b�g�}�X�N������
	glColorMask(1,1,1,1);
	glDepthMask(1);
	
	/////////////////////////////////////////////
	//�e������
	glStencilFunc( GL_EQUAL, 2, ~0 );
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.1f, 0.1f, 0.1f, 0.5f);
		glDisable(GL_DEPTH_TEST);		
			DrawFloor();
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);

	/////////////////////////////////////////////
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
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);		
	//�����ƍގ��̐ݒ�
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL );
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);

	printf("%u", ~0);
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