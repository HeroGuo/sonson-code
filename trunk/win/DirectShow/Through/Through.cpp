// 
// Through
// Through.cpp
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
//// Through.cpp : Ax �p�̏����������̒�`���s���܂��B
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// DirectShow�p
#include <streams.h>
#include <initguid.h>

#include <math.h>
#include "Through.h"

//////////////////////////////////////////////////////////////////////
// {52868D02-17B3-4373-AEE2-8C4FE1A2CCB6}
static const GUID CLSID_Through = { 0x52868d02, 0x17b3, 0x4373, { 0xae, 0xe2, 0x8c, 0x4f, 0xe1, 0xa2, 0xcc, 0xb6 } };


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
const AMOVIESETUP_FILTER sudThrough =
{
	&CLSID_Through,		// clsID
	L"Through",			// strName
	MERIT_DO_NOT_USE,	// dwMerit
	2,					// nPins
	sudpPins			// lpPin
};

//////////////////////////////////////////////////////////////////////
CFactoryTemplate g_Templates[] = {
	{
	L"Through"
	, &CLSID_Through
	, Through::CreateInstance
	, NULL
	, &sudThrough
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
// Through �N���X
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// �R���X�g���N�^
Through::Through(TCHAR *tszName, LPUNKNOWN pUnk, HRESULT *phr) :
    CTransformFilter(tszName, pUnk, CLSID_Through)
{
}
//////////////////////////////////////////////////////////////////////
// �f�X�g���N�^
Through::~Through()
{
}
//////////////////////////////////////////////////////////////////////
// �C���X�^���X�̐���
CUnknown *Through::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
    Through *pNewObject = new Through(NAME("Through filter"), punk, phr);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;
}
//////////////////////////////////////////////////////////////////////
// ���̓s���̃��f�B�A�^�C�v�`�F�b�N
HRESULT Through::CheckInputType(const CMediaType *mtIn)
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
HRESULT Through::CheckTransform(const CMediaType *mtIn, const CMediaType *mtOut)
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
BOOL Through::CheckMediaType(const CMediaType *pMediaType) const
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
HRESULT Through::Transform(IMediaSample *pIn, IMediaSample *pOut){
	// In��Out�ɃR�s�[���ďo��
	HRESULT hr = Copy(pIn, pOut);
    if (FAILED(hr)) {
        return hr;
    }  
    return NOERROR;
}
//////////////////////////////////////////////////////////////////////
// �o�b�t�@�T�C�Y�����߂�
HRESULT Through::DecideBufferSize(
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
HRESULT Through::GetMediaType(int iPosition, CMediaType *pMediaType)
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
HRESULT Through::Copy(IMediaSample *pSource, IMediaSample *pDest) const
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