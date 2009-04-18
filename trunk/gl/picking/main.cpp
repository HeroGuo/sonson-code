// 
// picking
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

#define WIDTH	300
#define HEIGHT	300
#define BUFSIZE 512

///////////////////////////////////////////////////////////////////////////////
//�I�u�W�F�N�g��`�悷��
void DrawObjects(GLenum mode){
	///////////////////////////////////////////////////////
	//���ʔԍ�1
	if (mode == GL_SELECT)glPushName(1);
		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3i(3, 2, -1);
		glVertex3i(3, 8, -1);
		glVertex3i(8, 8, -1);
		glVertex3i(8, 2, -1);
		glEnd();
	glPopName();
	///////////////////////////////////////////////////////
	//���ʔԍ�2
	if(mode == GL_SELECT)glPushName(2);
		///////////////////////////////////////////////////////
		//���ʔԍ�2-1
		glPushName(1);
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 0.0);
			glVertex3i(2, 0,-0.1);
			glVertex3i(2, 6,-0.1);
			glVertex3i(6, 6,-0.1);
			glVertex3i(6, 0,-0.1);
			glEnd();
		glPopName();
			///////////////////////////////////////////////////////
			//���ʔԍ�2-2
			glPushName(2);
			///////////////////////////////////////////////////////
			//���ʔԍ�2-2-1
			glPushName(1);
				glBegin(GL_QUADS);
				glColor3f(1.0, 0.0, 0.0);
				glVertex3i(2, 0, -0.05);
				glVertex3i(2, 1, -0.05);
				glVertex3i(8, 1, -0.05);
				glVertex3i(8, 0, -0.05);
				glEnd();
			glPopName();
			///////////////////////////////////////////////////////
			//���ʔԍ�2-2-2
			glPushName(2);
				glBegin(GL_QUADS);
				glColor3f(1.0, 1.0, 1.0);
				glVertex3i( 1, 0, 0);
				glVertex3i( 1, 1, 0);
				glVertex3i(-1, 1, 0);
				glVertex3i(-1, 0, 0);
				glEnd();
			glPopName();
		glPopName();
	glPopName();
	///////////////////////////////////////////////////////
	//���ʔԍ�3
	if (mode == GL_SELECT)glPushName(3);
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3i(0, 2, -2);
	glVertex3i(0, 7, -2);
	glVertex3i(5, 7, -2);
	glVertex3i(5, 2, -2);
	glEnd();
	glPopName();
}
///////////////////////////////////////////////////////////////////////////////
//�Z���N�V�����o�b�t�@�𐮗�����
int SelectHits(GLuint hits,GLuint *buf){
	unsigned int i,j;
	// �ő�K�w����4�Ɖ��肵������
	GLuint hit_name[4]={-1, -1, -1, -1};
	float depth_min=10.0f;
	float depth_1=1.0f;
	float depth_2=1.0f;
	GLuint depth_name;
	GLuint *ptr;
	// �q�b�g�����f�[�^�Ȃ�
	if(hits<=0)return -1;
	// �|�C���^����Ɨpptr�֓n���D
	ptr = (GLuint*)buf;

	printf("�q�b�g���� %d\n\n",(int)hits);
	for(i=0; i<hits; i++){
		printf("  �q�b�g %d",(int)i+1);
		// ���ʔԍ��̊K�w�̐[��
		depth_name = *ptr;
		printf("  ���ʔԍ��̊K�w�� %d\n",(int)depth_name);
		ptr++;
		depth_1 = (float) *ptr/0x7fffffff;
		printf("    �f�v�X�̍ŏ��l %f\n",depth_1);
		ptr++;
		depth_2 = (float) *ptr/0x7fffffff;
		printf("    �f�v�X�̍ő�l %f\n",depth_2);
		ptr++;
		printf("    ���ʔԍ� ");
		// �ŏ��f�v�X�̊m�F
		if(depth_min>depth_1){
			depth_min = depth_1;
			// ���ʔԍ���ۑ�
			for(j=0; j<depth_name; j++){
				printf("%d ",*ptr);
				hit_name[j] = *ptr;
				ptr++;
			}
		}
		else{
			for(j=0; j<depth_name; j++){
				printf("%d ",*ptr);
				ptr++;
			}
		}
		printf("\n");
	}
	printf("\n�f�v�X�ŏ��̎��ʔԍ�\n");
	for(i=0;i<4;i++){
		if(hit_name[i]==-1)break;
		printf("%d ",hit_name[i]);
	}
	printf("\n\n\n");
	return 1;
}
///////////////////////////////////////////////////////////////////////////////
//�s�b�N�A�b�v
void pick(int x, int y){
  GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];
	float current_aspect;
	glGetIntegerv(GL_VIEWPORT, viewport);

	glSelectBuffer(BUFSIZE, selectBuf);
	(void) glRenderMode(GL_SELECT);

	glInitNames();
	glMatrixMode(GL_PROJECTION);			//�v���W�F�N�V�������[�h
	glPushMatrix();							//�Z���N�V�������[�h�̂Ƃ��̂݉��̍s��v�Z
		glLoadIdentity();					//�𔽉f�����邽�߂�Push����
		gluPickMatrix(x,viewport[3]-y,		//�s�b�L���O�s��̏�Z
			5.0,5.0, viewport);
		current_aspect = (float)viewport[2]/(float)viewport[3];
		gluPerspective( 60.0, current_aspect, 1.0, 100.0 );
		glMatrixMode( GL_MODELVIEW );		//�����Ń��f���r���[���[�h�ɂ���I�I�I�I
		DrawObjects(GL_SELECT);				//�Z���N�V�������[�h�ŕ`�悷��
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );			//���f���r���[���[�h�֖߂�

	hits = glRenderMode(GL_RENDER);
	SelectHits(hits, selectBuf);
}
///////////////////////////////////////////////////////////////////////////////
//�`��֐�
void display(void){
	//�E�B���h�E��h��Ԃ�
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//���_�̕ϊ��s��̏�����
	glLoadIdentity();
	//���_�̌���
	gluLookAt(
		4,4,12,
		4,4,0,
		0.0, 1.0, 0.0);

	DrawObjects(GL_RENDER);
	glFlush();
	glutSwapBuffers();
}
///////////////////////////////////////////////////////////////////////////////
//OpenGL�������R�}���h
void init (void){
	glEnable(GL_DEPTH_TEST);
	//�N���C�A���g�̈�̓h��Ԃ��F�̐ݒ�
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	//�f�v�X�o�b�t�@�N���A�l�̐ݒ�
	glClearDepth( 1.0 );
}
///////////////////////////////////////////////////////////////////////////////
//�}�E�X����
void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN)pick(x,y);
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