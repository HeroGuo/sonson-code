# Microsoft Developer Studio Project File - Name="ThroughEx" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** �ҏW���Ȃ��ł������� **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ThroughEx - Win32 Debug
!MESSAGE ����͗L����Ҳ�̧�قł͂���܂���B ������ۼު�Ă�����ނ��邽�߂ɂ� NMAKE ���g�p���Ă��������B
!MESSAGE [Ҳ�̧�ق̴���߰�] ����ނ��g�p���Ď��s���Ă�������
!MESSAGE 
!MESSAGE NMAKE /f "ThroughEx.mak".
!MESSAGE 
!MESSAGE NMAKE �̎��s���ɍ\�����w��ł��܂�
!MESSAGE ����� ײݏ��ϸۂ̐ݒ���`���܂��B��:
!MESSAGE 
!MESSAGE NMAKE /f "ThroughEx.mak" CFG="ThroughEx - Win32 Debug"
!MESSAGE 
!MESSAGE �I���\������� Ӱ��:
!MESSAGE 
!MESSAGE "ThroughEx - Win32 Release" ("Win32 (x86) Application" �p)
!MESSAGE "ThroughEx - Win32 Debug" ("Win32 (x86) Application" �p)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ThroughEx - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /Gz /MD /W3 /GX /O2 /I "C:\DXMedia\INCLUDE" /I "C:\DXMedia\classes\base" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "INC_OLE2" /D "STRICT" /D "_MT" /D "_WINDLL" /D _X86_=1 /D WINVER=0x0400 /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 strmbase.lib quartz.lib msvcrt.lib winmm.lib vfw32.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib /nologo /base:"0x1d1c0000" /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /nodefaultlib /out:"Release\ThroughEx.ax" /pdbtype:sept /libpath:"C:\DXMedia\lib"

!ELSEIF  "$(CFG)" == "ThroughEx - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MDd /W3 /Gm /GX /ZI /Od /I "C:\DXMedia\INCLUDE" /I "C:\DXMedia\classes\base" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "INC_OLE2" /D "STRICT" /D "_MT" /D "_WINDLL" /D _X86_=1 /D WINVER=0x0400 /D "DEBUG" /D DBG=1 /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib strmbasd.lib quartz.lib msvcrt.lib winmm.lib vfw32.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib /nologo /base:"0x1d1c0000" /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /nodefaultlib /out:"Debug\ThroughEx.ax" /pdbtype:sept /libpath:"C:\DXMedia\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\Debug\ThroughEx.ax C:\WINDOWS\system32\	regsvr32.exe /s C:\WINDOWS\system32\ThroughEx.ax
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ThroughEx - Win32 Release"
# Name "ThroughEx - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ThroughEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ThroughEx.def
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\IThroughEx.h
# End Source File
# Begin Source File

SOURCE=.\ThroughEx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
