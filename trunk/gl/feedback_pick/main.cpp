// 
// feedback_pick
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

////////////////////////////////////////////////////////////////////
//�t�B�[�h�o�b�N�ɗp����z��
//�e�I�u�W�F�N�g�̏����ʒu
GLdouble object_position[3][3] = {
	{0.0, 0.0, 0.0},
	{1.0, 3.0, 4.5},
	{-1.0, -3.0, 0.0}
};

////////////////////////////////////////////////////////////////////
//�h���b�O�ɗp����
GLuint	object_number=0;
double	object_depth=-1;
static GLuint	move_flag=0;

////////////////////////////////////////////////////////////////////
//3�_�ƎO�p�`�̕`��
void DrawObjects(GLenum mode){
	glColor3f(1,1,1);
	// �_1
	if(mode==GL_SELECT){
		glPushName(1);
	}
	glBegin(GL_POINTS);
	glVertex3dv(object_position[0]);
	glEnd();
	glPopName();
	// �_2
	if(mode==GL_SELECT){
			glPushName(2);
	}
	glBegin(GL_POINTS);
	glVertex3dv(object_position[1]);
	glEnd();
	glPopName();
	// �_3
	if(mode==GL_SELECT){
		glPushName(3);
	}
	glBegin(GL_POINTS);
	glVertex3dv(object_position[2]);
	glEnd();
	glPopName();
	//3�_�����ԎO�p�`
	glColor3f(1,0,0);
	if(mode==GL_RENDER){
		glBegin(GL_LINE_LOOP);
		glVertex3dv(object_position[0]);
		glVertex3dv(object_position[1]);
		glVertex3dv(object_position[2]);
		glEnd();
	}
}
///////////////////////////////////////////////////////////////////////////////
//�Z���N�V�����o�b�t�@�𐮗�����
int SelectHits(GLuint hits,GLuint *buf){
	unsigned int i;
	GLuint hit_name;
	float depth_min=10.0f;
	float depth_1=1.0f;
	float depth_2=1.0f;
	GLuint depth_name;
	GLuint *ptr;
	// �q�b�g�����f�[�^�Ȃ�
	if(hits<=0)return -1;
	// �|�C���^����Ɨpptr�֓n���D
	ptr = (GLuint*)buf;

	for(i=0; i<hits; i++){
		// ���ʔԍ��̊K�w�̐[��
		depth_name = *ptr;
		ptr++;
		depth_1 = (float) *ptr/0x7fffffff;
		ptr++;
		depth_2 = (float) *ptr/0x7fffffff;
		ptr++;
		// �ŏ��f�v�X�̊m�F
		if(depth_min>depth_1){
			depth_min = depth_1;
			hit_name = *ptr;
		}
		ptr++;
	}
	return hit_name;
}
///////////////////////////////////////////////////////////////////////////////
//�s�b�N�A�b�v
int PickUp(int x, int y){
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
	return SelectHits(hits,selectBuf);
}
////////////////////////////////////////////////////////////////////
//�N���b�N�����Ƃ���̕`�悵�����̂̃f�v�X�l���擾����D
float returnDepth(int x, int y){
	float z;
	GLint viewport[4];			//�r���[�|�[�g
	//�f�o�C�X���W�n�ƃE�B���h�E���W�n�̕ϊ�
	glGetIntegerv(GL_VIEWPORT,viewport);	//���݂̃r���[�|�[�g����
	glReadPixels(x,viewport[3]-y,1,1,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		&z);
	return z;
}
////////////////////////////////////////////////////////////////////
//�N���b�N�����_�ɂ���s�N�Z���̃f�v�X�l��p���āC���E���W������o���D
void  CalculateWorldCo(int x, int y, float depth, double &wx, double &wy,double &wz){
	GLdouble mvMatrix[16],pjMatrix[16];
	GLint viewport[4];

	//�r���[�|�[�g�p�����[�^���擾����D
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, pjMatrix);
	//���E���W���擾����
	gluUnProject((double)x,(double)viewport[3]-y,depth,
		mvMatrix,
		pjMatrix,
		viewport,
		&wx,
		&wy,
		&wz);
}
////////////////////////////////////////////////////////////////////
//�I�u�W�F�N�g���h���b�O����
void PickObject(int x, int y){
	if((object_number = PickUp(x,y))==-1){
		return;
	}
	//Z�o�b�t�@�l���Q�b�g
	object_depth = returnDepth(x,y);
}
void DruggingObject(int x, int y){
	double xx[3];
	if(object_depth>0 && object_depth<1){
		CalculateWorldCo(x,y,object_depth,xx[0],xx[1],xx[2]);
		object_position[object_number-1][0] = xx[0];
		object_position[object_number-1][1] = xx[1];
		object_position[object_number-1][2] = xx[2];
	}
}
void FreeObject(int x, int y){
	object_number=0;
	object_depth=-1;
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
		0,0,12,
		0,0,0,
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
	//�_�̃s�N�Z���T�C�Y�̐ݒ�
	glPointSize(5.0f);
}
///////////////////////////////////////////////////////////////////////////////
//�}�E�X����
void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){
				if(move_flag==0){
					PickObject(x,y);
					move_flag = 1;
				}
			}
			else if(state == GLUT_UP){
				FreeObject(x,y);
				move_flag=0;
			}
			break;
	}
}
///////////////////////////////////////////////////////////////////////////////
//�}�E�X�E�h���b�O����
void drag(int x, int y){
	if(move_flag==1){
		DruggingObject(x,y);
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
	glutMotionFunc(drag);
	glutIdleFunc(display);
	//���C�����[�v
	glutMainLoop();
	return 0;
}