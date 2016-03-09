; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgLogAndDecode
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "decoder.h"
LastPage=0

ClassCount=15
Class1=Cdecode1Frm
Class2=CDecodeIMDoc
Class3=CDecodeIMFrm
Class4=CDecodeIMView
Class5=CDecodeLFDoc
Class6=CDecodeLFFrm
Class7=CDecodeLFView
Class8=CDecoderApp
Class9=CAboutDlg
Class10=CDecodeView
Class11=CMainFrame
Class12=CUserInputDlg

ResourceCount=10
Resource1=IDD_LFOPTIONS
Resource2=IDR_SEARCHBAR
Resource3=IDR_LOGFILE
Resource4=IDD_ABOUTBOX
Resource5=IDR_MESSAGE
Class13=CLFOptionsDlg
Resource6=IDD_USERINPUTPORTBOX
Resource7=IDD_USERINPUTBOX
Resource8=IDR_MAINFRAME2
Class14=CUserInputPortDlg
Resource9=IDR_MAINFRAME
Class15=CDlgLogAndDecode
Resource10=IDD_RT_LOG_AND_DECODE

[CLS:Cdecode1Frm]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CDecodeIMDoc]
Type=0
BaseClass=CDocument
HeaderFile=decodeIMDoc.h
ImplementationFile=decodeIMDoc.cpp

[CLS:CDecodeIMFrm]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=decodeIMFrm.h
ImplementationFile=decodeIMFrm.cpp

[CLS:CDecodeIMView]
Type=0
BaseClass=CDecodeView
HeaderFile=decodeIMView.h
ImplementationFile=decodeIMView.cpp

[CLS:CDecodeLFDoc]
Type=0
BaseClass=CDocument
HeaderFile=decodeLFDoc.h
ImplementationFile=decodeLFDoc.cpp

[CLS:CDecodeLFFrm]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=decodeLFFrm.h
ImplementationFile=decodeLFFrm.cpp

[CLS:CDecodeLFView]
Type=0
BaseClass=CDecodeView
HeaderFile=decodeLFView.h
ImplementationFile=decodeLFView.cpp

[CLS:CDecoderApp]
Type=0
BaseClass=CWinApp
HeaderFile=decoder.h
ImplementationFile=decoder.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=decoder.cpp
ImplementationFile=decoder.cpp
LastObject=CAboutDlg

[CLS:CDecodeView]
Type=0
BaseClass=CHtmlView
HeaderFile=decodeView.h
ImplementationFile=decodeView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDC_BN_DOHIGHLIGHT
VirtualFilter=fWC

[CLS:CUserInputDlg]
Type=0
BaseClass=CDialog
HeaderFile=UserInputDlg.h
ImplementationFile=UserInputDlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_APP_AND_VER,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LFOPTIONS]
Type=1
Class=CLFOptionsDlg
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GRP_TIMESTAMP,button,1342308359
Control4=IDC_NONE,button,1342373897
Control5=IDC_LOGFILE,button,1342177289
Control6=IDC_UDPLISTEN,button,1342177289
Control7=IDC_FORCE_CR,button,1342242819
Control8=IDC_NEWLINE_DELIM,edit,1484849280
Control9=IDC_CONDITION,static,1476526080
Control10=IDC_DROPCALLFILTER,button,1342242819
Control11=IDC_STATIC,static,1342308352
Control12=IDC_VERSION_SELECT,combobox,1344471043
Control13=IDC_DECODEISDNINOG,button,1342242819

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEWMSG
Command2=ID_FILE_OPENLOG
Command3=ID_FILE_REALTIME
Command4=ID_FILE_SAVEx
Command5=ID_EDIT_CUTx
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTEx
Command8=ID_FILE_PRINT
Command9=ID_APP_ABOUT
Command10=ID_LOADMESSAGE
Command11=ID_VIEW_FONTS_SMALLEST
Command12=ID_VIEW_FONTS_SMALL
Command13=ID_VIEW_FONTS_MEDIUM
Command14=ID_VIEW_FONTS_LARGE
Command15=ID_OPTIONS
CommandCount=15

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEWMSG
Command2=ID_FILE_OPENLOG
Command3=ID_FILE_REALTIME
Command4=ID_FILE_PRINT_SETUP
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MESSAGE]
Type=1
Class=?
Command1=ID_FILE_NEWMSG
Command2=ID_FILE_NEWLOG
Command3=ID_FILE_REALTIME
Command4=ID_FILE_CLOSE
Command5=ID_FILE_SAVE
Command6=ID_FILE_SAVE_AS
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

[MNU:IDR_LOGFILE]
Type=1
Class=?
Command1=ID_FILE_NEWMSG
Command2=ID_FILE_NEWLOG
Command3=ID_FILE_REALTIME
Command4=ID_FILE_CLOSE
Command5=ID_FILE_SAVE
Command6=ID_FILE_SAVE_AS
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_FIND
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_FILE_REALTIME
Command7=ID_FILE_SAVE
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CUT
Command16=ID_EDIT_UNDO
CommandCount=16

[CLS:CLFOptionsDlg]
Type=0
HeaderFile=LFOptionsDlg.h
ImplementationFile=LFOptionsDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CLFOptionsDlg
VirtualFilter=dWC

[DLG:IDR_SEARCHBAR]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_WORD,button,1342242819
Control3=IDC_HALL,button,1342242819
Control4=IDC_HCOLOR,edit,1342242944
Control5=IDC_HCOL,static,1342308352
Control6=IDC_STATIC,static,1342177298

[DLG:IDR_MAINFRAME]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_WORD,button,1342242819
Control3=IDC_HALL,button,1342242819
Control4=IDC_HCOLOR,edit,1342242944
Control5=IDC_HCOL,static,1342308352
Control6=IDC_STATIC,static,1342177298

[DLG:IDR_MAINFRAME2]
Type=1
Class=CMainFrame
ControlCount=3
Control1=65535,static,1342308352
Control2=IDC_HHIGHLIGHT,edit,1342242944
Control3=IDC_BN_DOHIGHLIGHT,button,1342242816

[DLG:IDD_USERINPUTPORTBOX]
Type=1
Class=CUserInputPortDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PORTNO,edit,1350631552

[DLG:IDD_USERINPUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ISDNMESSAGE,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CUserInputPortDlg]
Type=0
HeaderFile=UserInputPortDlg.h
ImplementationFile=UserInputPortDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_EXIT
VirtualFilter=dWC

[DLG:IDD_RT_LOG_AND_DECODE]
Type=1
Class=CDlgLogAndDecode
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_PORTNO_LABEL,static,1342308352
Control3=IDC_PORTNO,edit,1350631552
Control4=IDC_BTN_START,button,1342242816
Control5=IDC_BTN_STOP,button,1342242816
Control6=IDC_STATIC_RICHEDIT,static,1073741828
Control7=IDC_BTN_CLEAR,button,1342242816

[CLS:CDlgLogAndDecode]
Type=0
HeaderFile=DlgLogAndDecode.h
ImplementationFile=DlgLogAndDecode.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BTN_CLEAR

