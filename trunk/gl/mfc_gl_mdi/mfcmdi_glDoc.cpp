// 
// mfc_gl_mdi
// mfcmdi_glDoc.cpp
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
//// mfcmdi_glDoc.cpp : CMfcmdi_glDoc �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "mfcmdi_gl.h"

#include "mfcmdi_glDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glDoc

IMPLEMENT_DYNCREATE(CMfcmdi_glDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcmdi_glDoc, CDocument)
	//{{AFX_MSG_MAP(CMfcmdi_glDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glDoc �N���X�̍\�z/����

CMfcmdi_glDoc::CMfcmdi_glDoc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CMfcmdi_glDoc::~CMfcmdi_glDoc()
{
}

BOOL CMfcmdi_glDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glDoc �V���A���C�[�[�V����

void CMfcmdi_glDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glDoc �N���X�̐f�f

#ifdef _DEBUG
void CMfcmdi_glDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcmdi_glDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcmdi_glDoc �R�}���h
