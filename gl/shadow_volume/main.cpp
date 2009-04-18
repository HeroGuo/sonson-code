// 
// shadow_volume
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
//
#ifdef WIN32
#include <GL/glut.h>
#else
#include <glut/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define V_SIZE 10		// ���e�̃T�C�Y

int flag_teapot=0;		// �I�}�P�̃t���O
int flag_volume=0;
int flag_sphere=0;

float look_y=0;			// �����_��Y���W
float t=0;				// ����

float ground_vertex[10][10][3];
						// ���̍��W
float object_vertex[4][3]={
	{-1, 3, -1},
	{ 2, 3, -1},
	{-1, 3,  2},
	{ 0, 5,  0}
};						//����p�̎l�ʑ̂̍��W�l
float base_object_vertex[4][3]={
	{-1, -1, -1},
	{ 2, -1, -1},
	{-1, -1,  2},
	{ 0, 1,  0}
};						// ���ɂȂ�l�ʑ̂̍��W�l
////////////////////////////////////////////////////////////////////
//�����x�N�g���̕������֐�
void Normalizef(float *vector){
	float tmp=0;
	//��Βl���v�Z
	tmp+=vector[0]*vector[0];
	tmp+=vector[1]*vector[1];
	tmp+=vector[2]*vector[2];
	//��Βl���O�̂Ƃ�����
	if(tmp!=0){
		tmp=sqrt(tmp);
		//�P�ʃx�N�g���ɏ���
		vector[0]/=tmp;
		vector[1]/=tmp;
		vector[2]/=tmp;
	}
}
////////////////////////////////////////////////////////////////////
//�^����ꂽ�R�_���炻�̖ʂ̖@���x�N�g�����Z�o����
void Normal_Vecf(GLfloat input1[3],GLfloat input2[3],GLfloat input3[3],GLfloat result[3]){
	float temp1[3];
	float temp2[3];
	//
	temp1[0]=input2[0]-input3[0];
	temp1[1]=input2[1]-input3[1];
	temp1[2]=input2[2]-input3[2];
	temp2[0]=input2[0]-input1[0];
	temp2[1]=input2[1]-input1[1];
	temp2[2]=input2[2]-input1[2];
	//�O��
	result[0]=temp1[1]*temp2[2]-temp1[2]*temp2[1];
	result[1]=temp1[2]*temp2[0]-temp1[0]*temp2[2];
	result[2]=temp1[0]*temp2[1]-temp1[1]*temp2[0];
	//������
	Normalizef(result);
}
////////////////////////////////////////////////////////////////////
//3*3�s���3�����x�N�g���̏�Z
void multMatrix(double *m,			//��Z����s��̃|�C���^
				float input[3],			//��Z����_�̃|�C���^
				float result[3]			//����
				 ){
	result[0] = m[0]*input[0] + m[4]*input[1] + m[8]*input[2];
	result[1] = m[1]*input[0] + m[5]*input[1] + m[9]*input[2];
	result[2] = m[2]*input[0] + m[6]*input[1] + m[10]*input[2];
}
///////////////////////////////////////////////////////////////////////////////
//�����̕`��֐�
void DrawRoom(void){
	int i,j;
	float normal[3];
	/////////////////////////////////////////////
	//�g�ł�
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			glBegin(GL_TRIANGLES);
				Normal_Vecf(ground_vertex[i][j],ground_vertex[i][j+1],ground_vertex[i+1][j+1],normal);
				glNormal3fv(normal);
				glVertex3fv(ground_vertex[i][j]);
				glVertex3fv(ground_vertex[i][j+1]);
				glVertex3fv(ground_vertex[i+1][j+1]);
				Normal_Vecf(ground_vertex[i][j],ground_vertex[i+1][j+1],ground_vertex[i+1][j],normal);
				glNormal3fv(normal);
				glVertex3fv(ground_vertex[i][j]);
				glVertex3fv(ground_vertex[i+1][j+1]);
				glVertex3fv(ground_vertex[i+1][j]);
			glEnd();
		}
	}
	/////////////////////////////////////////////
	//��
	glBegin(GL_QUADS);
		//1
		glVertex3f(-10, 15,-10);
		glVertex3f(-10, 15,  8);
		glVertex3f(-10, 0,  8);
		glVertex3f(-10, 0,-10);
		//2
		glVertex3f( 8, -5,-10);
		glVertex3f( 8,-5,  8);
		glVertex3f( 8, 15,  8);
		glVertex3f( 8, 15,-10);
		//3
		glVertex3f(-10, -5,-10);
		glVertex3f(  8, -5,-10);
		glVertex3f(  8, 15,-10);
		glVertex3f(-10, 15,-10);
		//4
		glVertex3f( 8, -5, 8);
		glVertex3f(-10, -5, 8);
		glVertex3f(-10, 15, 8);
		glVertex3f( 8, 15, 8);
	glEnd();
}
///////////////////////////////////////////////////////////////////////////////
//�����ƔC�ӂ̓_�̉�����ɂ���_���Z�o
void ClacShadowPoint(float *lightpos, float *point, float *result){
	float vec[3];

	vec[0] = point[0] - lightpos[0];
	vec[1] = point[1] - lightpos[1];
	vec[2] = point[2] - lightpos[2];

	result[0] = lightpos[0] + vec[0]*V_SIZE;
	result[1] = lightpos[1] + vec[1]*V_SIZE;
	result[2] = lightpos[2] + vec[2]*V_SIZE;
}
///////////////////////////////////////////////////////////////////////////////
//���͂��ꂽ�R�_����\�������|���S����Shadow Volume��`�悷��
void drawShadowPolygon(float *lightpos,float *point0,float *point1,float *point2){
	float shadow_point[3][3];

	/////////////////////////////////////////////
	//�ˉe��̓_�����ׂĎZ�o
	ClacShadowPoint(lightpos,point0, shadow_point[0]);
	ClacShadowPoint(lightpos,point1, shadow_point[1]);
	ClacShadowPoint(lightpos,point2, shadow_point[2]);
	/////////////////////////////////////////////
	//Shadow Volume�`��
	glBegin(GL_QUADS);
		//1
		glVertex3fv(point1);
		glVertex3fv(point0);
		glVertex3fv(shadow_point[0]);
		glVertex3fv(shadow_point[1]);
		//2
		glVertex3fv(point2);
		glVertex3fv(point1);
		glVertex3fv(shadow_point[1]);
		glVertex3fv(shadow_point[2]);
		//3
		glVertex3fv(point0);
		glVertex3fv(point2);
		glVertex3fv(shadow_point[2]);
		glVertex3fv(shadow_point[0]);
	glEnd();
}
///////////////////////////////////////////////////////////////////////////////
//�����ɑ΂��Ă̌������`�F�b�N����
int CheckShadow(float *lightpos, float *point0,float *point1,float *point2){
	float center[3];
	float light_direction[3];
	float polygon_normal[3];
	float inner_product;

	//�d�S�Z�o
	center[0] = (point0[0] + point1[0] + point2[0])*0.333f;
	center[1] = (point0[1] + point1[1] + point2[1])*0.333f;
	center[2] = (point0[2] + point1[2] + point2[2])*0.333f;
	//��������
	light_direction[0] = center[0] - lightpos[0];
	light_direction[1] = center[1] - lightpos[1];
	light_direction[2] = center[2] - lightpos[2];
	Normalizef(light_direction);
	//�|���S���̖@���x�N�g��
	Normal_Vecf(point0,point1,point2,polygon_normal);
	//���ώZ�o
	inner_product = light_direction[0]*polygon_normal[0]
					+ light_direction[1]*polygon_normal[1]
					+ light_direction[2]*polygon_normal[2];
	if(inner_product>=0){
		return 1;
	}
	else 
		return 0;
}
///////////////////////////////////////////////////////////////////////////////
//�`��֐�
void drawShadowVolume(float *lightpos){
	//�����ɑ΂��Č��������΂̂��̂�ShadowVolume���t�����ŕ`�悷��
	//CULL_FACE���g�p���邽��
	if( CheckShadow(lightpos,object_vertex[1],object_vertex[2],object_vertex[0])){
		drawShadowPolygon(lightpos,object_vertex[1],object_vertex[2],object_vertex[0]);
	}else{
		drawShadowPolygon(lightpos,object_vertex[0],object_vertex[2],object_vertex[1]);
	}
	if( CheckShadow(lightpos,object_vertex[2],object_vertex[1],object_vertex[3])){
		drawShadowPolygon(lightpos,object_vertex[2],object_vertex[1],object_vertex[3]);
	}else{
		drawShadowPolygon(lightpos,object_vertex[3],object_vertex[1],object_vertex[2]);
	}
	if( CheckShadow(lightpos,object_vertex[0],object_vertex[2],object_vertex[3])){
		drawShadowPolygon(lightpos,object_vertex[0],object_vertex[2],object_vertex[3]);
	}else{
		drawShadowPolygon(lightpos,object_vertex[3],object_vertex[2],object_vertex[0]);
	}
	if( CheckShadow(lightpos,object_vertex[1],object_vertex[0],object_vertex[3])){
		drawShadowPolygon(lightpos,object_vertex[1],object_vertex[0],object_vertex[3]);
	}else{
		drawShadowPolygon(lightpos,object_vertex[3],object_vertex[0],object_vertex[1]);
	}
}
///////////////////////////////////////////////////////////////////////////////
//�I�u�W�F�N�g����]������
void rotateObject(float t){
	float rotated[3];
	double rM[16] = { 
					1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					0,0,0,1};
	//Z�����S�ɉ�]
	rM[0] = cos(t);rM[4] = -sin(t);
	rM[1] = sin(t);rM[5] = cos(t);
	//original�̍��W�l�����Ɍv�Z����
	multMatrix(rM,base_object_vertex[0],rotated);
	object_vertex[0][0]=rotated[0];
	object_vertex[0][1]=rotated[1]+5;
	object_vertex[0][2]=rotated[2];
	multMatrix(rM,base_object_vertex[1],rotated);
	object_vertex[1][0]=rotated[0];
	object_vertex[1][1]=rotated[1]+5;
	object_vertex[1][2]=rotated[2];
	multMatrix(rM,base_object_vertex[2],rotated);
	object_vertex[2][0]=rotated[0];
	object_vertex[2][1]=rotated[1]+5;
	object_vertex[2][2]=rotated[2];
	multMatrix(rM,base_object_vertex[3],rotated);
	object_vertex[3][0]=rotated[0];
	object_vertex[3][1]=rotated[1]+5;
	object_vertex[3][2]=rotated[2];
}
///////////////////////////////////////////////////////////////////////////////
//�l�ʑ̕`��֐�
void drawObject(void){
	float normal[3];
	glBegin(GL_TRIANGLES);
		Normal_Vecf(object_vertex[1],object_vertex[2],object_vertex[0],normal);
		glNormal3fv(normal);
		glVertex3fv(object_vertex[1]);
		glVertex3fv(object_vertex[2]);
		glVertex3fv(object_vertex[0]);
		Normal_Vecf(object_vertex[2],object_vertex[1],object_vertex[3],normal);
		glNormal3fv(normal);
		glVertex3fv(object_vertex[2]);
		glVertex3fv(object_vertex[1]);
		glVertex3fv(object_vertex[3]);
		Normal_Vecf(object_vertex[0],object_vertex[2],object_vertex[3],normal);
		glNormal3fv(normal);
		glVertex3fv(object_vertex[0]);
		glVertex3fv(object_vertex[2]);
		glVertex3fv(object_vertex[3]);
		Normal_Vecf(object_vertex[1],object_vertex[0],object_vertex[3],normal);
		glNormal3fv(normal);
		glVertex3fv(object_vertex[1]);
		glVertex3fv(object_vertex[0]);
		glVertex3fv(object_vertex[3]);
	glEnd();
}

///////////////////////////////////////////////////////////////////////////////
//�`��֐�
void display(void){
	//�����ʒu
	float lightpos[4] = { 0, 10, 0, 1};
	look_y = 7+ 5*sin(t*0.01);
	//�E�B���h�E��h��Ԃ�
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//���_�̕ϊ��s��̏�����
	glLoadIdentity();
	//���_�̌���
	glPushMatrix();
	gluLookAt(
		0,look_y,10,
		0,4,0,
		0.0, 1.0, 0.0);
	//�V�[���S�̂���]
	glRotatef(t*0.5,0,1,0);
		/////////////////////////////////////////////
		//�����̈ʒu�̌v�Z�Ɛݒ�
		lightpos[0] = 4*sin(t*0.035);
		lightpos[1] = 10+2*cos(t*0.05);
		lightpos[2] = 4*cos(t*0.05);
		glLightfv(GL_LIGHT0, GL_POSITION, (float*)lightpos);
		/////////////////////////////////////////////
		//�����̕`��
		glColor3f(1.0,1.0,1.0);
		glDisable(GL_LIGHTING);
		glPushMatrix();
			glTranslatef(lightpos[0],lightpos[1],lightpos[2]);
			glutSolidSphere(0.2,10,10);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		/////////////////////////////////////////////
		//�t�����ʂ̃e�B�[�|�b�g�E�I�}�P
		if(flag_teapot || flag_sphere){
			glPushMatrix();
				glTranslatef(4*sin(t*0.01),2,4*cos(t*0.01));
				glDisable(GL_CULL_FACE);		
				if(flag_teapot)glutSolidTeapot(1.5);
				if(flag_sphere)glutSolidSphere(1.5,20,20);
				glEnable(GL_CULL_FACE);		
			glPopMatrix();
		}
		/////////////////////////////////////////////
		//�l�ʑ̕`��
		rotateObject(t*0.05);
		drawObject();
		glColor3f(0.0,0.0,0.6);
		/////////////////////////////////////////////
		//�����̕`��
		DrawRoom();
		//
		glDisable(GL_LIGHTING);
		/////////////////////////////////////////////
		//Shadow Volume�̕`��
		if(flag_volume){
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			glDisable(GL_CULL_FACE);
			glColor3f(1,1,1);
			drawShadowVolume(lightpos);
			glEnable(GL_CULL_FACE);		
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		}
		/////////////////////////////////////////////
		//Shadow Volume�X�e���V���̃Z�b�g
		//�J���[�E�f�v�X�}�X�N�C�Z�b�g
		glColorMask(0,0,0,0);
		glDepthMask( GL_FALSE );
		//�X�e���V��
		glEnable(GL_STENCIL_TEST);
		glStencilFunc( GL_ALWAYS, 1, ~0);
		/////////////////////////////////////////////
		//�O�ʂ̃X�e���V��
		glStencilOp( GL_KEEP, GL_KEEP, GL_INCR);
		glFrontFace(GL_CW);
		drawShadowVolume(lightpos);
		//�w�ʂ̃X�e���V��
		glStencilOp( GL_KEEP, GL_KEEP, GL_DECR);
		if(!flag_volume){
			glFrontFace(GL_CCW);
			drawShadowVolume(lightpos);
		}
		/////////////////////////////////////////////
		//�`��������E��n�ɍăZ�b�g
		glFrontFace(GL_CCW);
		//�}�X�N����
		glColorMask(1,1,1,1);
		glDepthMask(GL_TRUE);
	glPopMatrix();
	/////////////////////////////////////////////
	//�e�E�V�[��������O�Ƀh�[���ƕ`�悷��
	glStencilFunc( GL_NOTEQUAL, 0, ~0 );
	glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0f, 0.1f, 0.1f, 0.5f);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glBegin(GL_QUADS);
			//1
			glVertex3f( 10, 10,-2);
			glVertex3f( 10,-10,-2);
			glVertex3f(-10,-10,-2);
			glVertex3f(-10, 10,-2);
		glEnd();
		glEnable(GL_CULL_FACE);		
		glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_LIGHTING);

	glFinish();
	glutSwapBuffers();
	//����
	t++;
}
///////////////////////////////////////////////////////////////////////////////
//OpenGL�������R�}���h
void init (void){
	int i,j;
	glEnable(GL_DEPTH_TEST);

	//�N���C�A���g�̈�̓h��Ԃ��F�̐ݒ�
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
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
	//���̍쐬
	for(i=-5;i<5;i++){
		for(j=-5;j<5;j++){
			ground_vertex[i+5][j+5][0] = 2*i;
			ground_vertex[i+5][j+5][1] = 0.7*sin(i)-0.5*cos(j);
			ground_vertex[i+5][j+5][2] = 2*j;
		}
	}
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
	gluPerspective( 70.0, aspect, 1.0,100.0 );
	//�m�[�}���̃��f���r���[���[�h�ֈڍs
	glMatrixMode( GL_MODELVIEW );
}
void keyboard(unsigned char key,int x, int y){
	//�I�}�P�̑���
	if(key=='t'){
		if(flag_teapot)flag_teapot = 0;
		else{
			flag_sphere = 0;
			flag_teapot = 1;
		}
	}
	else if(key=='v'){
		if(flag_volume)flag_volume = 0;
		else flag_volume = 1;
	}
	else if(key=='s'){
		if(flag_sphere)flag_sphere = 0;
		else{
			flag_sphere = 1;
			flag_teapot = 0;
		}
	}
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
	glutCreateWindow ("Shadow Volume Sample");
	//OpenGL������
	init();
	//�e�����֐��̓o�^
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);

	//���C�����[�v
	glutMainLoop();
	return 0;
}