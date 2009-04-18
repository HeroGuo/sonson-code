// 
// mfc_gl_sdi
// mfcsdi_glView.cpp
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
//// mfcsdi_glView.cpp : CMfcsdi_glView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "mfcsdi_gl.h"

#include "mfcsdi_glDoc.h"
#include "mfcsdi_glView.h"

#include "InitGL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcsdi_glView

IMPLEMENT_DYNCREATE(CMfcsdi_glView, CView)

BEGIN_MESSAGE_MAP(CMfcsdi_glView, CView)
	//{{AFX_MSG_MAP(CMfcsdi_glView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// �W������R�}���h
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcsdi_glView �N���X�̍\�z/����

CMfcsdi_glView::CMfcsdi_glView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B

}

CMfcsdi_glView::~CMfcsdi_glView()
{
	// OpenGL�̊J��
	wglMakeCurrent(NULL,NULL);
    wglDeleteContext(hRC);
	delete cDC;
}

BOOL CMfcsdi_glView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMfcsdi_glView �N���X�̕`��

void CMfcsdi_glView::OnDraw(CDC* pDC)
{
	CMfcsdi_glDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	glLoadIdentity();
	gluLookAt(
		2,2,3,
		0,0,0,
		0,1,0);
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
// CMfcsdi_glView �N���X�̈��

BOOL CMfcsdi_glView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �f�t�H���g�̈������
	return DoPreparePrinting(pInfo);
}

void CMfcsdi_glView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ����O�̓��ʂȏ�����������ǉ����Ă��������B
}

void CMfcsdi_glView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �����̌㏈����ǉ����Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// CMfcsdi_glView �N���X�̐f�f

#ifdef _DEBUG
void CMfcsdi_glView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcsdi_glView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcsdi_glDoc* CMfcsdi_glView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcsdi_glDoc)));
	return (CMfcsdi_glDoc*)m_pDocument;
}
#endif //_DEBUG

int CMfcsdi_glView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void CMfcsdi_glView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	Resize(cx,cy);	
}
