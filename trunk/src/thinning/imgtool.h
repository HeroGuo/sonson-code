// 
// thinning
// imgtool.h
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
//#include <string.h>#include <stdio.h>#include <stdlib.h>#include <magick/api.h>#ifdef _CH_#pragma package <opencv>#endif#include <opencv/cv.h>#include <opencv/highgui.h>void showRGBPixelsInWindow( unsigned char*pixel, int width, int height );void showGrayPixelsInWindow( unsigned char*pixel, int width, int height );// �f�t�H���g�ł́C�㉺���E�t���܂Ńs�N�Z���ɔz�u�����D// ���̃t���O�ł�����������D//#define __RE_ALIGNE_PIXELS/** * �����Ă��̉摜��ǂݍ���ł��܂��֐� * * - ���ʂ� unsigned char ��1�����z�� * - ���ʔz��͎g�p�ґ��ŉ�����邱�� * - ��f�̃t�H�[�}�b�g�� colormap �Ŏw�肷��K�v������ *   - colormap �� R,G,B,A,C,Y,M,K,I �̔C�ӂ̑g�ݍ��킹 *   - �ӂ��CPPM �t�@�C���Ȃ� colormap = "RGB" *   - R �����ق������ colormap = "R" �Ƃ���΂悢 * * @param filename [in] �t�@�C���� * @param width [out] �ǂݍ��񂾉摜�̉��T�C�Y * @param height [out] �ǂݍ��񂾉摜�̏c�T�C�Y * @param colormap [in] �擾�����f�`�� * @return ���������Ƃ��͓���ꂽ1�����z��̐擪�ւ̃|�C���^���C���s�����Ƃ���NULL��Ԃ� */unsigned char * magick_read(const char * filename, int * width, int *height, const char * colormap);/** * �����Ă��̉摜�`���ŏ�������ł��܂��֐� * * - �n���f�[�^�� unsigned char ��1�����z�� * - �n���f�[�^�̃t�H�[�}�b�g�� colormap �Ŏw�肷��K�v������ *	 - colormap �� R,G,B,A,C,Y,M,K,I �̔C�ӂ̑g�ݍ��킹 *	 - R,G,B 8bit ���̃f�[�^�Ȃ� colormap = "RGB" * * @param filename [in] �t�@�C���� * @param data [in] �摜�f�[�^ * @param width [in] �摜�̉��T�C�Y * @param height [in] �摜�̏c�T�C�Y * @param colormap [in] �n�����f�[�^�̉�f�`�� * @return ���������Ƃ���0��Ԃ� */int magick_write(const char * filename, unsigned char * data, int width, int height, const char * colormap);