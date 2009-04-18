// 
// mac_gl_mdi
// SonsonOpenGLView.m
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
//#import "SonsonOpenGLView.h"
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>

@implementation SonsonOpenGLView
//////////////////////////////////////////////////////////////////////////
//�I�[�o�[���C�h
-(id)initWithFrame:(NSRect)frameRect{
    // �s�N�Z���t�H�[�}�b�g��z��ɑ������
    NSOpenGLPixelFormatAttribute attrs[] =
    {
        NSOpenGLPFADoubleBuffer,	// �_�u���o�b�t�@
        NSOpenGLPFAColorSize, 24,	// �J���[�o�b�t�@�E24bit
        NSOpenGLPFAAlphaSize, 8,	// �A���t�@�o�b�t�@�E8bit
        NSOpenGLPFADepthSize, 16,	// �f�v�X�o�b�t�@�E16bit
	NSOpenGLPFAAccelerated,		// �n�[�h�E�F�A�A�N�Z�����[�V����
	0
    };
    // attrs�z������Ƀs�N�Z���t�H�[�}�b�g���m�ۂ���
    NSOpenGLPixelFormat* pixFmt = [[[NSOpenGLPixelFormat alloc] 							initWithAttributes:attrs] autorelease];
    // view������������
    self = [super initWithFrame:frameRect pixelFormat:pixFmt];
    // �J�����g�R���e�L�X�g��ݒ�
    [ [ self openGLContext ] makeCurrentContext ];
    return( self );
}
//////////////////////////////////////////////////////////////////////////
//���T�C�Y����
- (void)reshape{
    // view�T�C�Y���擾����D
    NSRect bounds = [self bounds];
    // view�T�C�Y����Viewport��ݒ肷��D
    glViewport(
        (int)bounds.origin.x, (int)bounds.origin.y,
        (int)bounds.size.width, (int)bounds.size.height);
    // �ˉe�ϊ��̐ݒ�
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, ( float ) bounds.size.width/ ( float ) bounds.size.height, 1.0, 500.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1,1,1,1);
}
////////////////////////////////////////////////////////////////////////////////////
//�ĕ`�揈��
- (void)drawRect:(NSRect)aRect
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFinish();
    //�o�b�t�@����ւ�
    [ [ self openGLContext ] flushBuffer ];
    [super drawRect:aRect];    
}
////////////////////////////////////////////////////////////////////////////////////
//�}�E�X�_�E��
- (void)mouseDown:(NSEvent*)theEvent{
    // view�T�C�Y���擾����D
    NSRect bounds = [self bounds];
    glClearColor(0,0,0,1);
    [self drawRect:bounds];
}
////////////////////////////////////////////////////////////////////////////////////
//�}�E�X�A�b�v
- (void)mouseUp:(NSEvent*)theEvent{
    // view�T�C�Y���擾����D
    NSRect bounds = [self bounds];
    glClearColor(1,1,1,1);
    [self drawRect:bounds];
}
////////////////////////////////////////////////////////////////////////////////////
//View���t�H�[�J�X���ꂽ�Ƃ��̏���
//NSWindow�̃f���Q�[�g�ɐݒ肳�ꂽMyDocument���������CMyDocument�ɂ���ČĂяo�����
- (void)DidViewFocused
{
    [ [ self openGLContext ] makeCurrentContext ]; 
    // Set the drawable
    [[self openGLContext] setView:self];
}
@end
