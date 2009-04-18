// 
// SkeltonMFC
// DirectShowSkeltonMFCView.h
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
//// DirectShowSkeltonMFCView.h : CDirectShowSkeltonMFCView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTSHOWSKELTONMFCVIEW_H__A53B3383_FCC4_46A8_86BD_B80C586C3070__INCLUDED_)
#define AFX_DIRECTSHOWSKELTONMFCVIEW_H__A53B3383_FCC4_46A8_86BD_B80C586C3070__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dshow.h>

//////////////////////////////////////////////////////////////////////
// {52868D02-17B3-4373-AEE2-8C4FE1A2CCB6}
const GUID CLSID_Through = { 0x52868d02, 0x17b3, 0x4373, { 0xae, 0xe2, 0x8c, 0x4f, 0xe1, 0xa2, 0xcc, 0xb6 } };

class CDirectShowSkeltonMFCView : public CView
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CDirectShowSkeltonMFCView();
	DECLARE_DYNCREATE(CDirectShowSkeltonMFCView)

// �A�g���r���[�g
public:
	CDirectShowSkeltonMFCDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDirectShowSkeltonMFCView)
	public:
	virtual void OnDraw(CDC* pDC);  // ���̃r���[��`�悷��ۂɃI�[�o�[���C�h����܂��B
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

private:
	IGraphBuilder			*m_pGraph;				// �O���t �r���_
	IMediaControl			*m_pMediaCtrl;			// ���f�B�A �R���g���[��
	IVideoWindow			*m_pVideoWindow;		// �`��p�̃E�B���h�E
	ICaptureGraphBuilder2	*m_pBuilder;			// �L���v�`���r���_�[
	IMediaEventEx			*m_pMediaEvent;			// ���f�B�A�C�x���g

	IBaseFilter				*m_pSrc;				// �\�[�X
	IBaseFilter				*m_pVideoRenderer;		// �����_��

	IBaseFilter				*m_pThrough;			// ���̃v���O�����ł����t�B���^

	// DirectShow�t�B���^�̍쐬
	BOOL					CreateFilters(void);
	// DirectShow�t�B���^�̐ڑ�
	BOOL					ConectFilters(void);
	// DirectShow�`��̈�̐ݒ�
	BOOL					SetWindow(void);
	// DirectShow�t�B���^�̉��
	BOOL					ReleaseAll(void);
	// DirectShow�L���v�`���f�o�C�X�̎擾�Ɨ�
	BOOL					GetCaptureDevice(IBaseFilter **ppSrcFilter);
	// DirectShow�̏�����
	BOOL					InitializeDirectShow(void);

// �C���v�������e�[�V����
public:
	virtual ~CDirectShowSkeltonMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CDirectShowSkeltonMFCView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DirectShowSkeltonMFCView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CDirectShowSkeltonMFCDoc* CDirectShowSkeltonMFCView::GetDocument()
   { return (CDirectShowSkeltonMFCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DIRECTSHOWSKELTONMFCVIEW_H__A53B3383_FCC4_46A8_86BD_B80C586C3070__INCLUDED_)
