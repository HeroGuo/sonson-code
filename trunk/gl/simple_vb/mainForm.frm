' 
' simple_vb
' mainForm.frm
' 
' The MIT License
' 
' Copyright (c) 2009 sonson, sonson@Picture&Software
' 
' Permission is hereby granted, free of charge, to any person obtaining a copy
' of this software and associated documentation files (the "Software"), to deal
' in the Software without restriction, including without limitation the rights
' to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, subject to the following conditions:
' 
' The above copyright notice and this permission notice shall be included in
' all copies or substantial portions of the Software.
' 
' THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
' IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
' FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
' AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
' LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
' OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
' THE SOFTWARE.
'VERSION 5.00
Begin VB.Form mainForm 
   Caption         =   "OpenGL�X�P���g���R�[�h version3.0"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows �̊���l
End
Attribute VB_Name = "mainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'�����_�����O�R���e�L�X�g
Dim hRC&
Public Function CreateGLWindow() As Boolean
    Dim PixelFormat As GLuint
    Dim pfd As PIXELFORMATDESCRIPTOR                '�s�N�Z���t�H�[�}�b�g�\����

    With pfd
        .cColorBits = 16
        .cDepthBits = 16
        .dwFlags = PFD_DRAW_TO_WINDOW Or PFD_SUPPORT_OPENGL Or PFD_DOUBLEBUFFER
        .iLayerType = PFD_MAIN_PLANE
        .iPixelType = PFD_TYPE_RGBA
        .nVersion = 1
    End With
    
    mainForm.ScaleMode = vbPixels
        
    PixelFormat = ChoosePixelFormat(mainForm.hDC, pfd)
    If PixelFormat = 0 Then                     '�s�N�Z���t�H�[�}�b�g�̑I��Ɏ��s
        Call KillGLWindow                            '�E�B���h�E�j��
        MsgBox "�s�N�Z���t�H�[�}�b�g�I�����s", vbExclamation, "�x��"
        CreateGLWindow = False                  '�߂�l
        Exit Function
    End If

    If SetPixelFormat(mainForm.hDC, PixelFormat, pfd) = 0 Then '�s�N�Z���t�H�[�}�b�g�̐ݒ�Ɏ��s
        Call KillGLWindow                            '�E�B���h�E�j��
        MsgBox "�s�N�Z���t�H�[�}�b�g�ݒ莸�s", vbExclamation, "�x��"
        CreateGLWindow = False                  '�߂�l
        Exit Function
    End If
    
    hRC = wglCreateContext(mainForm.hDC)
    If (hRC = 0) Then                           '�����_�����O�R���e�L�X�g�̍쐬�Ɏ��s
        Call KillGLWindow                            '�E�B���h�E�j��
        MsgBox "�����_�����O�R���e�L�X�g�쐬���s", vbExclamation, "�x��"
        CreateGLWindow = False                  '�߂�l
        Exit Function
    End If

    If wglMakeCurrent(mainForm.hDC, hRC) = 0 Then    '�����_�����O�R���e�L�X�g���J�����g�R���e�L�X�g�ɐݒ�
        Call KillGLWindow
         MsgBox "�R���e�L�X�g�̐ݒ莸�s", vbExclamation, "�x��"
        CreateGLWindow = False
        Exit Function
    End If

    CreateGLWindow = True
End Function

Public Function InitGL()
'OpenGL�ɗp����֐��̏��������Ɋւ���֐�

    glClearColor 0#, 0#, 0#, 0#         '�w�i�F�̐ݒ�
    glClearDepth 1#                     '�f�v�X�o�b�t�@�̐ݒ�
    glEnable glcDepthTest               '�f�v�X�o�b�t�@�̎g�p�J�n

End Function
Public Sub KillGLWindow()
'OpenGL�Ŏg�p���������_�����O�R���e�L�X�g�̔j��
    If hRC Then                                     '�����_�����O�R���e�L�X�g�̗L���̊m�F
        If wglMakeCurrent(0, 0) = 0 Then            '�����_�����O�R���e�L�X�g�̊m�F
            MsgBox "�R���e�L�X�g�j�����s", vbInformation, "�x��"
        End If

        If wglDeleteContext(hRC) = 0 Then           '�����_�����O�R���e�L�X�g�̔j��
            MsgBox "�����_�����O�R���e�L�X�g�j�����s", vbInformation, "�x��"
        End If
        hRC = 0                                     '�ꉞNULL�����H
    End If
End Sub
Public Function DrawGLScene()
'�`��֐�
'�`��R�[�h�͂����ɋL�q���܂�
    glClear clrColorBufferBit Or clrDepthBufferBit  '�J���[�o�b�t�@�ƃf�v�X�o�b�t�@�̃N���A
    glLoadIdentity                                  '�P�ʍs��̌Ăяo��
    gluLookAt 0, 0, 4, 0, 0, 0, 0, 1, 0
'�l�p�`�̕`��R�[�h
    glBegin bmTriangles
        glColor3f 1, 0, 0
        glVertex3f 0#, 1#, 0#
        glColor3f 0, 1, 0
        glVertex3f -1#, 0#, 0#
        glColor3f 0, 0, 1
        glVertex3f 1#, 0#, 0#
    glEnd
End Function
Private Sub Form_Initialize()
'���������
    'GL�E�B���h�E�̍쐬
    If CreateGLWindow = False Then
        Call KillGLWindow
        End
    End If
    'OpenGL�̖��ߐݒ�
    Call InitGL

End Sub
Private Sub Form_Paint()
'�`�施�ߎ��ɍĕ`�悷��
    Call DrawGLScene
    '�_�u���o�b�t�@����������
    SwapBuffers mainForm.hDC
End Sub

Private Sub Form_Unload(Cancel As Integer)
'�E�B���h�E��j����
    Call KillGLWindow
End Sub
Private Sub Form_Resize()
    Dim Height As Integer
'�E�B���h�E�̃��T�C�Y���̏���
    '�r���[�|�[�g�Ȃǂ�ݒ肷��
    '�E�B���h�E�T�C�Y���O�ɂȂ��
    '�A�X�y�N�g��Z�o�̂Ƃ���Devide by 0�G���[�ɂȂ�̂�
    '�T�C�Y���O�̂Ƃ��͂P�Ƃ��ď�������B
    Height = mainForm.ScaleHeight
    If Height = 0 Then
        Height = 1
    End If
    
'�r���[�|�[�g�̐ݒ�
    glViewport 0, 0, mainForm.ScaleWidth, Height  '�r���[�|�[�g���E�B���h�E�̑傫���ɍ��킹��
    glMatrixMode mmProjection       '�v���W�F�N�V�����}�g���N�X���[�h�ֈڍs
    glLoadIdentity                  '�v���W�F�N�V�����}�g���N�X��P�ʍs��Ƀ��Z�b�g

    '�E�B���h�E�̃A�X�y�N�g����Z�o���A�A�X�y�N�g���������
    gluPerspective 45#, mainForm.ScaleWidth / Height, 0.1, 100#

    glMatrixMode mmModelView        '���f���r���[���[�h�ֈڍs
    glLoadIdentity

'���T�C�Y���ɍĕ`��
    Call DrawGLScene
    SwapBuffers mainForm.hDC
End Sub

