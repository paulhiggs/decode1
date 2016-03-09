; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUserInputDlg
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "decode1.h"
LastPage=0

ClassCount=8
Class1=CDecode1App
Class2=CDecode1Doc
Class3=CDecode1View
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDR_DECODETYPE
Resource3=IDD_ABOUTBOX
Class5=CChildFrame
Class6=CAboutDlg
Class7=CUserInputDlg
Class8=CBitSet
Resource4=IDD_USERINPUTBOX

[CLS:CDecode1App]
Type=0
HeaderFile=decode1.h
ImplementationFile=decode1.cpp
Filter=N

[CLS:CDecode1Doc]
Type=0
HeaderFile=decode1Doc.h
ImplementationFile=decode1Doc.cpp
Filter=N

[CLS:CDecode1View]
Type=0
HeaderFile=decode1View.h
ImplementationFile=decode1View.cpp
Filter=C
BaseClass=CHtmlView
VirtualFilter=7VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=decode1.cpp
ImplementationFile=decode1.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPENx
Command3=ID_FILE_SAVEx
Command4=ID_EDIT_CUTx
Command5=ID_EDIT_COPYx
Command6=ID_EDIT_PASTEx
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_LOADMESSAGE
CommandCount=9

[MNU:IDR_DECODETYPE]
Type=1
Class=CDecode1View
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_WINDOW_NEW
Command17=ID_WINDOW_CASCADE
Command18=ID_WINDOW_TILE_HORZ
Command19=ID_WINDOW_ARRANGE
Command20=ID_APP_ABOUT
CommandCount=20

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_USERINPUTBOX]
Type=1
Class=CUserInputDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ISDNMESSAGE,edit,1350631552
Control4=IDC_PROMPT,static,1342308352

[CLS:CUserInputDlg]
Type=0
HeaderFile=UserInputDlg.h
ImplementationFile=UserInputDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserInputDlg
VirtualFilter=dWC

[CLS:CBitSet]
Type=0
HeaderFile=BitSet.h
ImplementationFile=BitSet.cpp
BaseClass=CView
Filter=C

