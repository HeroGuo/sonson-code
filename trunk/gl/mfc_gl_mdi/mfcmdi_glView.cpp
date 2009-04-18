// 
// mfc_gl_mdi
// mfcmdi_glView.cpp
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
//// mfcmdi_glView.cpp : CMfcmdi_glView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "mfcmdi_gl.h"

#include "mfcmdi_glDoc.h"
#include "mfcmdi_glView.h"

#include "InitGL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView

IMPLEMENT_DYNCREATE(CMfcmdi_glView, CView)

BEGIN_MESSAGE_MAP(CMfcmdi_glView, CView)
	//{{AFX_MSG_MAP(CMfcmdi_glView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView �N���X�̍\�z/����

CMfcmdi_glView::CMfcmdi_glView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B

}

CMfcmdi_glView::~CMfcmdi_glView()
{
	// OpenGL�̊J��
	wglMakeCurrent(NULL,NULL);
    wglDeleteContext(hRC);
	delete cDC;
}

BOOL CMfcmdi_glView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView �N���X�̕`��

void CMfcmdi_glView::OnDraw(CDC* pDC)
{
	CMfcmdi_glDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
	
	wglMakeCurrent (cDC->m_hDC, hRC);    // ���݂�context�؂�ւ�

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	glLoadIdentity();
	gluLookAt(
		1,1,2,
		0,0,0,
		0,1,0);
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
	glFinish();
	SwapBuffers(cDC->m_hDC) ;
}

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView �N���X�̈��

BOOL CMfcmdi_glView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �f�t�H���g�̈������
	return DoPreparePrinting(pInfo);
}

void CMfcmdi_glView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CMfcmdi_glView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView �N���X�̐f�f

#ifdef _DEBUG
void CMfcmdi_glView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcmdi_glView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcmdi_glDoc* CMfcmdi_glView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcmdi_glDoc)));
	return (CMfcmdi_glDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glView �N���X�̃��b�Z�[�W �n���h��

int CMfcmdi_glView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: ���̈ʒu�ɌŗL�̍쐬�p�R�[�h��ǉ����Ă�������
	
	cDC = new CClientDC(this) ;             // DC�̐���
	hRC = Init_Pixel(cDC->m_hDC) ;          // OpenGL�p��Pixel Format���w��
	wglMakeCurrent (cDC->m_hDC, hRC);    // ���݂�context�ݒ�
	StartFunction();
	return 0;
}

void CMfcmdi_glView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	Resize(cx,cy);
}
