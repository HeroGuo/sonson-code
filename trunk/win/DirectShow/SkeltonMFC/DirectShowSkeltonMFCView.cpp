// 
// SkeltonMFC
// DirectShowSkeltonMFCView.cpp
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
//// DirectShowSkeltonMFCView.cpp : CDirectShowSkeltonMFCView �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "DirectShowSkeltonMFC.h"

#include "DirectShowSkeltonMFCDoc.h"
#include "DirectShowSkeltonMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment( lib, "strmBasd.lib" )		// DirectShow
#pragma comment( lib, "Quartz.lib" )		// AMGetErrorText()�̂��߂ɕK�v

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCView

IMPLEMENT_DYNCREATE(CDirectShowSkeltonMFCView, CView)

BEGIN_MESSAGE_MAP(CDirectShowSkeltonMFCView, CView)
	//{{AFX_MSG_MAP(CDirectShowSkeltonMFCView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCView �N���X�̍\�z/����

CDirectShowSkeltonMFCView::CDirectShowSkeltonMFCView()
{
	// TODO: ���̏ꏊ�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	m_pGraph    = NULL;				// �O���t �r���_
	m_pMediaCtrl = NULL;			// ���f�B�A �R���g���[��
	m_pVideoWindow=NULL;			// �`��p�̃E�B���h�E
	m_pBuilder = NULL;				// �L���v�`���r���_�[
	m_pMediaEvent = NULL;			// ���f�B�A�C�x���g

	m_pSrc		= NULL;				// �\�[�X
	m_pVideoRenderer = NULL;		// �����_��

	m_pThrough = NULL;				// ���̃v���O�����ł����t�B���^
}

CDirectShowSkeltonMFCView::~CDirectShowSkeltonMFCView()
{
	ReleaseAll();
	CoUninitialize();		// COM�̏I��
}

BOOL CDirectShowSkeltonMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCView �N���X�̕`��

void CDirectShowSkeltonMFCView::OnDraw(CDC* pDC)
{
	CDirectShowSkeltonMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	RECT rect;
	this->GetWindowRect(&rect);
	// TODO: ���̏ꏊ�Ƀl�C�e�B�u �f�[�^�p�̕`��R�[�h��ǉ����܂��B
}

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCView �N���X�̐f�f

#ifdef _DEBUG
void CDirectShowSkeltonMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CDirectShowSkeltonMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDirectShowSkeltonMFCDoc* CDirectShowSkeltonMFCView::GetDocument() // ��f�o�b�O �o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDirectShowSkeltonMFCDoc)));
	return (CDirectShowSkeltonMFCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDirectShowSkeltonMFCView �N���X�̃��b�Z�[�W �n���h��

/////////////////////////////////////////////////////////////////////////////////////////
// ���������̃��b�Z�[�W�n���h��
void CDirectShowSkeltonMFCView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// DirectShow�̏�����
	if( !InitializeDirectShow()){
		// ���������s
		ReleaseAll();
		CoUninitialize();		// COM�̏I
		this->MessageBox("DirectShow�̏������Ɏ��s���܂����D\n�����I�����܂��D","",MB_OK);
		::PostMessage(this->GetParent()->m_hWnd, WM_CLOSE, 0, 0);
								// �A�v���P�[�V�����I��
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// ���T�C�Y�̃��b�Z�[�W�n���h��
void CDirectShowSkeltonMFCView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// DirectShow�̃E�B���h�E���L�����𒲂ׂ�
	if( !m_pVideoWindow )return;

	HRESULT hResult;
	// �E�B���h�E��s����Ԃɂ���
	hResult = m_pVideoWindow->put_Visible(OAFALSE);
	if (hResult != S_OK)return;

	// �E�B���h�E�̏ꏊ�Ƒ傫�����Z�b�g
	hResult = m_pVideoWindow->SetWindowPosition(0, 0, cx, cy);
	if (hResult != S_OK)return;

	// �E�B���h�E������Ԃɂ���
	hResult = m_pVideoWindow->put_Visible(OATRUE);
	if (hResult != S_OK)return;
	
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�t�B���^�̍쐬
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::CreateFilters(void){
	HRESULT hResult;
	// Through�t�B���^�̃C���X�^���X���쐬
	hResult = CoCreateInstance(CLSID_Through, NULL,
		CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void **)&m_pThrough);
	if (hResult != S_OK)return FALSE;
	// �O���t�r���_�ɒǉ�����
	hResult = m_pGraph->AddFilter(m_pThrough, L"Through");
	if (hResult != S_OK)return FALSE;

	// VideoRenderer�̃C���X�^���X���쐬
	hResult = CoCreateInstance(CLSID_VideoRenderer, NULL, 
		CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void **)&m_pVideoRenderer);
	if (hResult != S_OK)return FALSE;
	// �O���t�r���_�ɒǉ�����
	hResult = m_pGraph->AddFilter(m_pVideoRenderer, L"Video Renderer");
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�t�B���^�̐ڑ�
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::ConectFilters(void){
	HRESULT hResult;
	// �\�[�X�̃t�B���^��Through�t�B���^�ɐڑ�
	hResult = m_pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,m_pSrc,0,m_pThrough);
	if (hResult != S_OK)return FALSE;

	// Through�t�B���^��VideoRenderer�ɐڑ�
	hResult = m_pBuilder->RenderStream( 0, &MEDIATYPE_Video, m_pThrough, NULL, m_pVideoRenderer );
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�`��̈�̐ݒ�
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::SetWindow(void){
	HRESULT hResult;
	// �O���t�r���_����E�B���h�E���擾����
    hResult = m_pGraph->QueryInterface(IID_IVideoWindow, (void **) &m_pVideoWindow);
	if (hResult != S_OK)return FALSE;

	// �E�B���h�E�̃I�[�i�[�ƂȂ�E�B���h�E�̃n���h�����w�肷��
	hResult = m_pVideoWindow->put_Owner( (OAHWND)this->m_hWnd );
	if (hResult != S_OK)return FALSE;

	// �E�B���h�E�̃X�^�C�����w�肷��
	hResult = m_pVideoWindow->put_WindowStyle(WS_CHILD);
	if (hResult != S_OK)return FALSE;

	// �E�B���h�E�̗̈�T�C�Y���擾���C�������ޔ͈͂�ݒ肷��
	RECT rect;
	this->GetWindowRect(&rect);
	hResult = m_pVideoWindow->SetWindowPosition(0, 0, rect.right-rect.left,rect.bottom-rect.top);
	if (hResult != S_OK)return FALSE;

	// �E�B���h�E������Ԃɂ���
	hResult = m_pVideoWindow->put_Visible(OATRUE);
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�t�B���^�̉��
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::ReleaseAll(void){
	if(m_pMediaCtrl)m_pMediaCtrl->Stop();
	if(m_pGraph)m_pGraph->Release();
	if(m_pMediaCtrl)m_pMediaCtrl->Release();
	if(m_pSrc)m_pSrc->Release();
	if(m_pThrough)m_pThrough->Release();
	if(m_pVideoRenderer)m_pVideoRenderer->Release();
	if(m_pBuilder)m_pBuilder->Release();
	if(m_pVideoWindow)m_pVideoWindow->Release();
	if(m_pMediaEvent)m_pMediaEvent->Release();
	
	m_pGraph    = NULL;				// �O���t �r���_
	m_pMediaCtrl = NULL;			// ���f�B�A �R���g���[��
	m_pVideoWindow=NULL;			// �`��p�̃E�B���h�E
	m_pBuilder = NULL;				// �L���v�`���r���_�[
	m_pMediaEvent = NULL;			// ���f�B�A�C�x���g

	m_pSrc		= NULL;				// �\�[�X
	m_pVideoRenderer = NULL;		// �����_��

	m_pThrough = NULL;				// ���̃v���O�����ł����t�B���^
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�L���v�`���f�o�C�X�̎擾�Ɨ�
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::GetCaptureDevice(IBaseFilter **ppSrcFilter)
{
	HRESULT hResult;

	// �f�o�C�X��񋓂���
	ICreateDevEnum *pDevEnum = NULL;
	hResult = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC, IID_ICreateDevEnum, (void **)&pDevEnum);
	if (hResult != S_OK)return FALSE;

	// �񋓂����f�o�C�X�̈�Ԗڂ��f�o�C�X�Ƃ��Ď擾����
	IEnumMoniker *pClassEnum = NULL;
	hResult = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
	if (hResult != S_OK)return FALSE;

	// �f�o�C�X���t�B���^�ɐڑ�����
	ULONG cFetched;
	IMoniker *pMoniker = NULL;
	if (pClassEnum->Next(1, &pMoniker, &cFetched) == S_OK){
		// �ŏ��̃��j�J���t�B���^�I�u�W�F�N�g�Ƀo�C���h����
		pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void **)ppSrcFilter);
		pMoniker->Release();
	}else
		return FALSE;

	// �O���t�r���_�ɒǉ�����
	hResult = m_pGraph->AddFilter(m_pSrc, L"Video Capture");
	if (hResult != S_OK)return FALSE;

	// �I�u�W�F�N�g�̕ЂÂ�
	pClassEnum->Release();
	pDevEnum->Release();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�̏�����
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CDirectShowSkeltonMFCView::InitializeDirectShow(void){
	HRESULT		hResult;

	hResult = CoInitialize( NULL );
	// �t�B���^�O���t�쐬
	hResult = CoCreateInstance(CLSID_FilterGraph, NULL, 
		CLSCTX_INPROC, IID_IGraphBuilder, (void **)&m_pGraph);
	if (hResult != S_OK)return FALSE;

	// �L���v�`���f�o�C�X�擾
	hResult = GetCaptureDevice(&m_pSrc);
	if (hResult != TRUE)return FALSE;

	// �L���v�`���r���_�̍쐬
	hResult = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, 
		CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void **)&m_pBuilder);
	if (hResult != S_OK)return FALSE;

	// �O���t�ɃL���v�`���r���_���Z�b�g
	hResult = m_pBuilder->SetFiltergraph(m_pGraph);
	if (hResult != S_OK)return FALSE;

	// ���f�B�A�R���g���[�����擾
	m_pGraph->QueryInterface(IID_IMediaControl, (void **)&m_pMediaCtrl);

	// �t�B���^�̍쐬
	if( !CreateFilters() )return FALSE;
	// �t�B���^�̐ڑ�
	if( !ConectFilters() )return FALSE;
	// �E�B���h�E�̃Z�b�g
	if( !SetWindow() )return FALSE;
	
	// �����J�n
	hResult = m_pMediaCtrl->Run();
	return TRUE;
}