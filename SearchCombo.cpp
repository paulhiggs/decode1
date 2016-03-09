// SearchCombo.cpp : implementation file
//

#include "stdafx.h"
//#include "CHtmlView_Search.h"
#include "resource.h"
#include "SearchCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchCombo

CSearchCombo::CSearchCombo()
{
}

CSearchCombo::~CSearchCombo()
{
}


BEGIN_MESSAGE_MAP(CSearchCombo, CComboBox)
	//{{AFX_MSG_MAP(CSearchCombo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchCombo message handlers

BOOL CSearchCombo::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		CFrameWnd* pMainFrame = GetTopLevelFrame();
		if (pMainFrame != NULL)
		{
			switch (pMsg->wParam)
			{
			case VK_ESCAPE:
				pMainFrame->SetFocus();
				return TRUE;

			case VK_RETURN:
				CString txt;
				GetWindowText(txt);
				if(txt != "")
				{
					if(FindStringExact(0,txt)==-1)
					{
						InsertString(0,txt);
						if(GetCount()>15)
							DeleteString(15);
					}					
				}
				pMainFrame->SendMessage (WM_COMMAND, IDC_SEARCHCOMBO,
										(LPARAM) GetSafeHwnd ());
				return TRUE;
			}
		}
	}	
	return CComboBox::PreTranslateMessage(pMsg);
}
