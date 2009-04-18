// 
// simple
// Main.cpp
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
//���C��
//�A�C�h�����O���ɃA�j���[�V����������

#include "main.h"

CHAR szAppName[]="�A�C�h�����O�����ɂ��A�j���[�V����";

////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
HGLRC hRC=NULL;								//OpenGL
HDC		hDC=NULL;						//�f�o�C�X�R���e�L�X�g�n���h��

GLfloat LookAt[][4] = {
	{0.0, 0.0, 0.0},
	{1.0, 1.0, 2.5}
};										//���_�̏����ʒu

GLfloat Look_deg =0;	//���_�̊p�x
float tt=0;

////////////////////////////////////////////////////////////////////
//�E�B���h�E�֐�
LONG   WINAPI MainWndProc (HWND, UINT, WPARAM, LPARAM);
void Draw(void);
////////////////////////////////////////////////////////////////////
// �G���g���|�C���g
int APIENTRY WinMain(HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine,
                        int nCmdShow )
{
	WNDCLASSEX wcex;	// �E�C���h�E�N���X�\����
	HWND hWnd;			// �E�C���h�E�n���h��
	MSG msg;			// ���b�Z�[�W�\����

	// �E�B���h�E�N���X�\���̂�ݒ肵�܂��B
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = (WNDPROC)MainWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(NULL);
	wcex.lpszClassName = "ModelApp";
	wcex.hIconSm = NULL;//LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	
	// �E�C���h�E�N���X��o�^���܂��B
	RegisterClassEx(&wcex);

	// �E�C���h�E���쐬���܂��B
   	hWnd = CreateWindow(wcex.lpszClassName,						// �E�C���h�E�N���X��
		szAppName, 		// �L���v�V����������
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,									// �E�C���h�E�̃X�^�C��
		CW_USEDEFAULT,			// �����ʒu
		CW_USEDEFAULT,			// �����ʒu
		CW_USEDEFAULT,					// ��
		CW_USEDEFAULT,					// ����
		NULL,					// �e�E�C���h�E
		NULL,					// �E�C���h�E���j���[
		hInstance,				// �C���X�^���X�n���h��
		NULL);					// WM_CREATE���
	
	// �E�C���h�E��\�����܂��B
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//�A�C�h�����ɃA�j���[�V���������邽�߂̃��b�Z�[�W���[�v
	while(TRUE){
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
			//WM_QUIT�𖾎��I�ɏ�������
			if(msg.message==WM_QUIT){
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//���ɂȂɂ��������Ȃ��̂ŕ`�悷��
		else{
			Draw();
		}
	}
	// �߂�l��Ԃ��܂��B
	return msg.wParam;
}

////////////////////////////////////////////////////////////////////
//�E�B���h�E�v���V�[�W��
LONG WINAPI MainWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	LONG    lRet = 1;

    switch (uMsg)
    {
    	case WM_CREATE:
			//OpenGL�̏�����
			if((hRC=Init_Pixel(hWnd))==NULL){
				MessageBox(hWnd,"","",MB_OK);
			}
			//�J�����g�R���e�L�X�g
			hDC = GetDC(hWnd);
			wglMakeCurrent(hDC,hRC);
			StartFunction();
			break;			
		case WM_SIZE:
			//���T�C�Y����OpenGL�̏���
	        Resize(hWnd);
            break;
		case WM_DESTROY:
			//�R���e�L�X�g�̉��
			Release_GLWindow(hWnd);
			PostQuitMessage (0);
			break;
	   	default:
            lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
			break;
    }
    return lRet;
}
//�`��֐�
void Draw(void){
	//�E�B���h�E��h��Ԃ�
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//���_�̕ϊ��s��̏�����
	glLoadIdentity();
	//���_�̌���
	gluLookAt(LookAt[1][0],LookAt[1][1],LookAt[1][2],
		LookAt[0][0],LookAt[0][1],LookAt[0][2],
		0.0, 1.0, 0.0);
	//�l�p�`�̕`��
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3d(1.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glColor3d(1.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0);
			glColor3d(1.0, 0.0, 1.0);
			glVertex3f(1.0, 0.0, 1.0);
			glVertex3f(1.0, 0.0, 0.0);
		glEnd();
	glPopMatrix();
	hDC = wglGetCurrentDC();
	//�_�u���o�b�t�@
	SwapBuffers(hDC);
}