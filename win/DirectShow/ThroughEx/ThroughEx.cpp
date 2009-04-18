// 
// ThroughEx
// ThroughEx.cpp
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
//// ThroughEx.cpp : Ax �p�̏����������̒�`���s���܂��B
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// DirectShow�p
#include <streams.h>
#include <initguid.h>

#pragma comment( lib, "strmBasd.lib" )		// DirectShow
#pragma comment( lib, "Quartz.lib" )		// AMGetErrorText()�̂��߂ɕK�v

#include "ThroughEx.h"

// {FF03E0A2-DF3A-499B-9DD1-7DB677D03D45}
static const GUID CLSID_ThroughEx = {0xff03e0a2,0xdf3a,0x499b,{0x9d,0xd1,0x7d,0xb6,0x77,0xd0,0x3d,0x45}};

// ���̓s���̃��f�B�A�^�C�v
// �K�v�ɉ����ĕύX����
const AMOVIESETUP_MEDIATYPE sudIPinTypes =
{
	&MEDIATYPE_Video,		// Major type
	&MEDIASUBTYPE_NULL		// Minor type
};

//////////////////////////////////////////////////////////////////////
// �o�̓s���̃��f�B�A�^�C�v
// �K�v�ɉ����ĕύX����
const AMOVIESETUP_MEDIATYPE sudOPinTypes =
{
	&MEDIATYPE_Video,		// Major type
	&MEDIASUBTYPE_NULL		// Minor type
};

//////////////////////////////////////////////////////////////////////
// �s���\�����
const AMOVIESETUP_PIN sudpPins[] =
{
	{
		L"Input",			// Pins string name
		FALSE,				// Is it rendered
		FALSE,				// Is it an output
		FALSE,				// Are we allowed none
		FALSE,				// And allowed many
		&CLSID_NULL,		// Connects to filter
		NULL,				// Connects to pin
		1,					// Number of types
		&sudIPinTypes		// Pin information
	},
	{
		L"Output",			// Pins string name
		FALSE,				// Is it rendered
		TRUE,				// Is it an output
		FALSE,				// Are we allowed none
		FALSE,				// And allowed many
		&CLSID_NULL,		// Connects to filter
		NULL,				// Connects to pin
		1,					// Number of types
		&sudOPinTypes		// Pin information
	}
};

//////////////////////////////////////////////////////////////////////
// �t�B���^�ݒ�
const AMOVIESETUP_FILTER sudThroughEx =
{
	&CLSID_ThroughEx,		// clsID
	L"ThroughEx",			// strName
	MERIT_DO_NOT_USE,	// dwMerit
	2,					// nPins
	sudpPins			// lpPin
};

//////////////////////////////////////////////////////////////////////
CFactoryTemplate g_Templates[] = {
	{
	L"ThroughEx"
	, &CLSID_ThroughEx
	, ThroughEx::CreateInstance
	, NULL
	, &sudThroughEx
	}
};

//////////////////////////////////////////////////////////////////////
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);

//////////////////////////////////////////////////////////////////////
// ���W�X�g���ւ̓o�^
STDAPI DllRegisterServer()
{
    return AMovieDllRegisterServer2( TRUE );

}

//////////////////////////////////////////////////////////////////////
// ���W�X�g������̉���
STDAPI DllUnregisterServer()
{
    return AMovieDllRegisterServer2( FALSE );

}

//////////////////////////////////////////////////////////////////////
// ThroughEx �N���X
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// �R���X�g���N�^
ThroughEx::ThroughEx(TCHAR *tszName, LPUNKNOWN pUnk, HRESULT *phr) :
    CTransformFilter(tszName, pUnk, CLSID_ThroughEx)
{
}
//////////////////////////////////////////////////////////////////////
// �f�X�g���N�^
ThroughEx::~ThroughEx()
{
}
//////////////////////////////////////////////////////////////////////
// �C���X�^���X�̐���
CUnknown *ThroughEx::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
    ThroughEx *pNewObject = new ThroughEx(NAME("ThroughEx filter"), punk, phr);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;
}
//////////////////////////////////////////////////////////////////////
// ���̓s���̃��f�B�A�^�C�v�`�F�b�N
HRESULT ThroughEx::CheckInputType(const CMediaType *mtIn)
{
   CheckPointer(mtIn,E_POINTER);

    // check this is a VIDEOINFOHEADER type

    if (*mtIn->FormatType() != FORMAT_VideoInfo) {
        return E_INVALIDARG;
    }

    // Can we transform this type

    if (CheckMediaType(mtIn)) {
        return NOERROR;
    }
    return E_FAIL;
}
//////////////////////////////////////////////////////////////////////
// �o�̓s���̃��f�B�A�^�C�v�`�F�b�N
HRESULT ThroughEx::CheckTransform(const CMediaType *mtIn, const CMediaType *mtOut)
{
	// ���̏ꏊ��output�s�����ڑ��ł��郁�f�B�A�^�C�v���`�F�b�N����
	CheckPointer(mtIn,E_POINTER);
	CheckPointer(mtOut,E_POINTER);
	if (*mtIn == *mtOut)
		return NOERROR;

	return E_FAIL;
}
//////////////////////////////////////////////////////////////////////
// ���̃t�B���^�Ŏg�p�ł���t�H�[�}�b�g�����`�F�b�N����
BOOL ThroughEx::CheckMediaType(const CMediaType *pMediaType) const
{
	// �|�C���^�̃`�F�b�N
    CheckPointer(pMediaType,FALSE);
	// ���f�B�A�^�C�v�̃`�F�b�N
    if (IsEqualGUID(*pMediaType->Type(), MEDIATYPE_Video)) 
    {
        if (IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_RGB24)) 
        {
            VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *) pMediaType->Format();
            return (pvi->bmiHeader.biBitCount == 24);
        }
    }
    return FALSE;
}
//////////////////////////////////////////////////////////////////////
// �t�B���^�����̏���
HRESULT ThroughEx::Transform(IMediaSample *pIn, IMediaSample *pOut){
	// In��Out�ɃR�s�[���ďo��
	HRESULT hr = Copy(pIn, pOut);
    if (FAILED(hr)) {
        return hr;
    }  
    return NOERROR;
}
//////////////////////////////////////////////////////////////////////
// �o�b�t�@�T�C�Y�����߂�
HRESULT ThroughEx::DecideBufferSize(
				IMemAllocator *pAlloc,ALLOCATOR_PROPERTIES *pProperties)
{
	// �f�[�^�ϊ��ɕK�v�ȃo�b�t�@�T�C�Y��ݒ肷��    
    if (m_pInput->IsConnected() == FALSE) {
        return E_UNEXPECTED;
    }

    CheckPointer(pAlloc,E_POINTER);
    CheckPointer(pProperties,E_POINTER);
    HRESULT hr = NOERROR;

    pProperties->cBuffers = 1;
    pProperties->cbBuffer = m_pInput->CurrentMediaType().GetSampleSize();
    ASSERT(pProperties->cbBuffer);

    // Ask the allocator to reserve us some sample memory, NOTE the function
    // can succeed (that is return NOERROR) but still not have allocated the
    // memory that we requested, so we must check we got whatever we wanted

    ALLOCATOR_PROPERTIES Actual;
    hr = pAlloc->SetProperties(pProperties,&Actual);
    if (FAILED(hr)) {
        return hr;
    }

    ASSERT( Actual.cBuffers == 1 );

    if (pProperties->cBuffers > Actual.cBuffers ||
            pProperties->cbBuffer > Actual.cbBuffer) {
                return E_FAIL;
    }
    return NOERROR;
}
//////////////////////////////////////////////////////////////////////
// ���̃t�B���^�̃A�E�g�s�����ڑ��\�ȃ��f�B�A�̃^�C�v��Ԃ�
HRESULT ThroughEx::GetMediaType(int iPosition, CMediaType *pMediaType)
{
	// output�s�����Ή����郁�f�B�A�^�C�v��Ԃ�    
    if (m_pInput->IsConnected() == FALSE) {
        return E_UNEXPECTED;
    }

    // �s���̈ʒu�̃`�F�b�N

    if (iPosition < 0) {
        return E_INVALIDARG;
    }
    if (iPosition > 0) {
        return VFW_S_NO_MORE_ITEMS;
    }

	// �s�����`�F�b�N
    CheckPointer(pMediaType,E_POINTER);
    *pMediaType = m_pInput->CurrentMediaType();

    return NOERROR;
}
//////////////////////////////////////////////////////////////////////
// �t�B���^�����ōs�������͂��o�͂ɕԂ�����
HRESULT ThroughEx::Copy(IMediaSample *pSource, IMediaSample *pDest) const
{
	// �o�b�t�@�̊m��
    BYTE *pSourceBuffer, *pDestBuffer;
    long lSourceSize = pSource->GetActualDataLength();
    long lDestSize	= pDest->GetSize();

    ASSERT(lDestSize >= lSourceSize);

	// ���͑��̃��f�B�A��񂩂�摜�f�[�^�̃|�C���^���擾
    pSource->GetPointer(&pSourceBuffer);
	// �o�͑��̃��f�B�A��񂩂�摜�f�[�^�̃|�C���^���擾
    pDest->GetPointer(&pDestBuffer);

	// �f�[�^���R�s�[
    CopyMemory( (PVOID) pDestBuffer,(PVOID) pSourceBuffer,lSourceSize);
/*
    DbgLog((LOG_TRACE,4,TEXT("CopyMemory::dest=%#x,source=%#x"),
    									pDestBuffer,pSourceBuffer));
*/
    // �T���v�����O�^�C�����R�s�[����D
    REFERENCE_TIME TimeStart, TimeEnd;
    if (NOERROR == pSource->GetTime(&TimeStart, &TimeEnd)) {
        pDest->SetTime(&TimeStart, &TimeEnd);
    }
	// ���f�B�A�̃^�C�~���O�����R�s�[����
    LONGLONG MediaStart, MediaEnd;
    if (pSource->GetMediaTime(&MediaStart,&MediaEnd) == NOERROR) {
        pDest->SetMediaTime(&MediaStart,&MediaEnd);
    }

    // �����p�̃|�C���g��ݒ肷��D
    HRESULT hResult = pSource->IsSyncPoint();
    if (hResult == S_OK) {
        pDest->SetSyncPoint(TRUE);
    }
    else if (hResult == S_FALSE) {
        pDest->SetSyncPoint(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // ���̓s�����̃��f�B�A�^�C�v���o�͑��̃��f�B�A�^�C�v�փR�s�[����
    AM_MEDIA_TYPE *pMediaType;
    pSource->GetMediaType(&pMediaType);
    pDest->SetMediaType(pMediaType);
    DeleteMediaType(pMediaType);

    // Preroll�̃`�F�b�N
    hResult = pSource->IsPreroll();
    if (hResult == S_OK) {
        pDest->SetPreroll(TRUE);
    }
    else if (hResult == S_FALSE) {
        pDest->SetPreroll(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // �A�����̃`�F�b�N�ƃR�s�[
    hResult = pSource->IsDiscontinuity();
    if (hResult == S_OK) {
	pDest->SetDiscontinuity(TRUE);
    }
    else if (hResult == S_FALSE) {
        pDest->SetDiscontinuity(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // ���ۂ̉摜�̃f�[�^�̒������R�s�[����
    long lDataLength = pSource->GetActualDataLength();
    pDest->SetActualDataLength(lDataLength);

    return NOERROR;

}
//////////////////////////////////////////////////////////////////////
// �O������Ăяo����邽�߂̃C���^�t�F�[�X�̒�
STDMETHODIMP ThroughEx::NonDelegatingQueryInterface(REFIID riid, void **ppv)
{
	// �t�B���^�̃C���^�[�t�F�[�X
	if( riid==IID_IThroughEx)
		return GetInterface( (IThroughEx *)this,ppv );

	return CTransformFilter::NonDelegatingQueryInterface( riid,ppv );
}
//////////////////////////////////////////////////////////////////////
// �O������Ăяo�����C���^�t�F�[�X�̎���
STDMETHODIMP ThroughEx::Call(void){
	CAutoLock cAutolock(&m_ThroughExLock);
	MessageBox( NULL, "�v���O�������烁�\�b�h���Ăяo����܂����D\n����Ƀv���O�����Ƀ��b�Z�[�W�𑗂�܂��D","ThroughExFilter",MB_OK);
	HRESULT hResult = NotifyEvent(EC_USER,PARAM_MESSAGE_FROM_FILTER,PARAM_MESSAGE_FROM_FILTER);
    return NOERROR;
}
