// RHtmlView.cpp : implementation file
//

#include "stdafx.h"
#include <..\src\occimpl.h>
#include "ROleControlSite.h"
#include "RHtmlView.h"
#include "StringTokenizer.h"

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RHtmlView

IMPLEMENT_DYNCREATE(RHtmlView, CHtmlView)
BEGIN_MESSAGE_MAP(RHtmlView, CHtmlView)
	//{{AFX_MSG_MAP(CDecodeView)
//	ON_COMMAND(ID_VIEW_FONTS_LARGEST, OnViewFontsLargest)
	ON_COMMAND(ID_VIEW_FONTS_LARGE, OnViewFontsLarge)
	ON_COMMAND(ID_VIEW_FONTS_MEDIUM, OnViewFontsMedium)
	ON_COMMAND(ID_VIEW_FONTS_SMALL, OnViewFontsSmall)
	ON_COMMAND(ID_VIEW_FONTS_SMALLEST, OnViewFontsSmallest)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RHtmlView construction/destruction

RHtmlView::RHtmlView()
{
	//{{AFX_DATA_INIT(RHtmlView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

RHtmlView::~RHtmlView()
{
}

void RHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RHtmlView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}



/////////////////////////////////////////////////////////////////////////////
// RHtmlView diagnostics

#ifdef _DEBUG
void RHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void RHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// RHtmlView message handlers

BOOL RHtmlView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	///////////////////////////////////
	// The following does the same as MFC source, except that
	// AfxEnableControlContainer() is called with our handler.
	///////////////////////////////////

	CRect c_clientRect;
//	GetClientRect(&c_clientRect);

	///////////////////////////////////
	// create the view window:

	m_pCreateContext = pContext;

	if (!CView::Create(lpszClassName, lpszWindowName, dwStyle, rect,
		pParentWnd,  nID, pContext))
	{
		return FALSE;
	}

	AfxEnableControlContainer(&m_pROccManager);

	///////////////////////////////////
	// create the control window:

	if (!m_wndBrowser.CreateControl(CLSID_WebBrowser, lpszWindowName,
				WS_VISIBLE | WS_CHILD, c_clientRect, this, AFX_IDW_PANE_FIRST))
	{
		DestroyWindow();
		return FALSE;
	}

	LPUNKNOWN lpUnk = m_wndBrowser.GetControlUnknown();
	HRESULT hr = lpUnk->QueryInterface(IID_IWebBrowser2, (void**) &m_pBrowserApp);
	if (!SUCCEEDED(hr))
	{
		m_pBrowserApp = NULL;
		m_wndBrowser.DestroyWindow();
		DestroyWindow();
		return FALSE;
	}

	///////////////////////////////////
	// Our initialisation:

	SetWindowText("RHtmlView");
	SetClassLong(this->m_hWnd, GCL_STYLE, CS_DBLCLKS);

	///////////////////////////////////

	return TRUE;	
}

/////////////////////////////////////////////////////////////////////////////
// XDocHostUI_DblClk interface

DWORD RHtmlView::GetXDocHostUI_DblClk()
{
	return m_pROccManager.m_pROleControlSite->GetXDocHostUI_DblClk();
}

void RHtmlView::SetXDocHostUI_DblClk(DWORD dwSet)
{
	m_pROccManager.m_pROleControlSite->SetXDocHostUI_DblClk(dwSet);
	Navigate2(GetLocationURL(), 0, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// XDocHostUI_Flag interface

DWORD RHtmlView::GetXDocHostUI_Flag()
{
	return m_pROccManager.m_pROleControlSite->GetXDocHostUI_Flag();
}

void RHtmlView::SetXDocHostUI_Flag(DWORD dwSet)
{
	m_pROccManager.m_pROleControlSite->SetXDocHostUI_Flag(dwSet);
	Navigate2(GetLocationURL(), 0, NULL, NULL);
}

BOOL RHtmlView::GetXDocHostUIFlag_Dialog()
{
	return GetXDocHostUI_Flag() & DOCHOSTUIFLAG_DIALOG;
}

BOOL RHtmlView::GetXDocHostUIFlag_DisableHelpMenu()
{
	return GetXDocHostUI_Flag() & DOCHOSTUIFLAG_DISABLE_HELP_MENU;
}

BOOL RHtmlView::GetXDocHostUIFlag_No3dBorder()
{
	return GetXDocHostUI_Flag() & DOCHOSTUIFLAG_NO3DBORDER;
}

BOOL RHtmlView::GetXDocHostUIFlag_ScrollNo()
{
	return GetXDocHostUI_Flag() & DOCHOSTUIFLAG_SCROLL_NO;
}

BOOL RHtmlView::GetXDocHostUIFlag_DisableScriptInactive()
{
	return GetXDocHostUI_Flag() & DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE;
}

BOOL RHtmlView::GetXDocHostUIFlag_OpenNewWin()
{
	return GetXDocHostUI_Flag() & DOCHOSTUIFLAG_OPENNEWWIN;
}

BOOL RHtmlView::GetXDocHostUIFlag_DisableOffscreen()
{
	return GetXDocHostUI_Flag() & DOCHOSTUIFLAG_DISABLE_OFFSCREEN;
}

BOOL RHtmlView::GetXDocHostUIFlag_FlatScrollbar()
{
	return GetXDocHostUI_Flag() & DOCHOSTUIFLAG_FLAT_SCROLLBAR;
}

BOOL RHtmlView::GetXDocHostUIFlag_DivBlockDefault()
{
	return GetXDocHostUI_Flag() & DOCHOSTUIFLAG_DIV_BLOCKDEFAULT;
}

BOOL RHtmlView::GetXDocHostUIFlag_ActivateClienthitOnly()
{
	return GetXDocHostUI_Flag() & DOCHOSTUIFLAG_ACTIVATE_CLIENTHIT_ONLY;
}

void RHtmlView::SetXDocHostUIFlag_Dialog(BOOL bSet)
{
	DWORD dwFlags = GetXDocHostUI_Flag();
	bSet ? dwFlags |= DOCHOSTUIFLAG_DIALOG : dwFlags &= ~DOCHOSTUIFLAG_DIALOG;
	SetXDocHostUI_Flag(dwFlags);
}

void RHtmlView::SetXDocHostUIFlag_DisableHelpMenu(BOOL bSet)
{
	DWORD dwFlags = GetXDocHostUI_Flag();
	bSet ? dwFlags |= DOCHOSTUIFLAG_DISABLE_HELP_MENU : dwFlags &= ~DOCHOSTUIFLAG_DISABLE_HELP_MENU;
	SetXDocHostUI_Flag(dwFlags);
}

void RHtmlView::SetXDocHostUIFlag_No3dBorder(BOOL bSet)
{
	DWORD dwFlags = GetXDocHostUI_Flag();
	bSet ? dwFlags |= DOCHOSTUIFLAG_NO3DBORDER : dwFlags &= ~DOCHOSTUIFLAG_NO3DBORDER;
	SetXDocHostUI_Flag(dwFlags);
}

void RHtmlView::SetXDocHostUIFlag_ScrollNo(BOOL bSet)
{
	DWORD dwFlags = GetXDocHostUI_Flag();
	bSet ? dwFlags |= DOCHOSTUIFLAG_SCROLL_NO : dwFlags &= ~DOCHOSTUIFLAG_SCROLL_NO;
	SetXDocHostUI_Flag(dwFlags);
}

void RHtmlView::SetXDocHostUIFlag_DisableScriptInactive(BOOL bSet)
{
	DWORD dwFlags = GetXDocHostUI_Flag();
	bSet ? dwFlags |= DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE : dwFlags &= ~DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE;
	SetXDocHostUI_Flag(dwFlags);
}

void RHtmlView::SetXDocHostUIFlag_OpenNewWin(BOOL bSet)
{
	DWORD dwFlags = GetXDocHostUI_Flag();
	bSet ? dwFlags |= DOCHOSTUIFLAG_OPENNEWWIN : dwFlags &= ~DOCHOSTUIFLAG_OPENNEWWIN;
	SetXDocHostUI_Flag(dwFlags);
}

void RHtmlView::SetXDocHostUIFlag_DisableOffscreen(BOOL bSet)
{
	DWORD dwFlags = GetXDocHostUI_Flag();
	bSet ? dwFlags |= DOCHOSTUIFLAG_DISABLE_OFFSCREEN : dwFlags &= ~DOCHOSTUIFLAG_DISABLE_OFFSCREEN;
	SetXDocHostUI_Flag(dwFlags);
}

void RHtmlView::SetXDocHostUIFlag_FlatScrollbar(BOOL bSet)
{
	DWORD dwFlags = GetXDocHostUI_Flag();
	bSet ? dwFlags |= DOCHOSTUIFLAG_FLAT_SCROLLBAR : dwFlags &= ~DOCHOSTUIFLAG_FLAT_SCROLLBAR;
	SetXDocHostUI_Flag(dwFlags);
}

void RHtmlView::SetXDocHostUIFlag_DivBlockDefault(BOOL bSet)
{
	DWORD dwFlags = GetXDocHostUI_Flag();
	bSet ? dwFlags |= DOCHOSTUIFLAG_DIV_BLOCKDEFAULT : dwFlags &= ~DOCHOSTUIFLAG_DIV_BLOCKDEFAULT;
	SetXDocHostUI_Flag(dwFlags);
}

void RHtmlView::SetXDocHostUIFlag_ActivateClienthitOnly(BOOL bSet)
{
	DWORD dwFlags = GetXDocHostUI_Flag();
	bSet ? dwFlags |= DOCHOSTUIFLAG_ACTIVATE_CLIENTHIT_ONLY : dwFlags &= ~DOCHOSTUIFLAG_ACTIVATE_CLIENTHIT_ONLY;
	SetXDocHostUI_Flag(dwFlags);
}


/////////////////////////////////////////////////////////////////////////////
// Updated functions

void RHtmlView::SetRegisterAsBrowser(BOOL bNewValue)
{
	CHtmlView::SetRegisterAsBrowser(bNewValue);
	Navigate2(GetLocationURL(), 0, NULL, NULL);
}

void RHtmlView::SetRegisterAsDropTarget(BOOL bNewValue)
{
	CHtmlView::SetRegisterAsDropTarget(bNewValue);
	Navigate2(GetLocationURL(), 0, NULL, NULL);
}

void RHtmlView::SetSilent(BOOL bNewValue)
{
	CHtmlView::SetSilent(bNewValue);
	Navigate2(GetLocationURL(), 0, NULL, NULL);
}

void RHtmlView::SetTheaterMode(BOOL bNewValue)
{
	CHtmlView::SetTheaterMode(bNewValue);
	Navigate2(GetLocationURL(), 0, NULL, NULL);
}





// these functions control the font size.  There is no explicit command in the
// CHtmlView class to do this, but we can do it by using the ExecWB() function.
void RHtmlView::OnViewFontsLargest()
{
	COleVariant vaZoomFactor(4l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void RHtmlView::OnViewFontsLarge()
{
	COleVariant vaZoomFactor(3l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void RHtmlView::OnViewFontsMedium()
{
	COleVariant vaZoomFactor(2l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void RHtmlView::OnViewFontsSmall()
{
	COleVariant vaZoomFactor(1l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}

void RHtmlView::OnViewFontsSmallest()
{
	COleVariant vaZoomFactor(0l);

	ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
		   &vaZoomFactor, NULL);
}


void RHtmlView::OnContextMenu( CWnd* pWnd, CPoint pos )
{
	int x=pos.x, y=pos.y;
}



void RHtmlView::OnEditCut()
{ 
#if defined ( BASE_CHtmlView ) || defined ( BASE_RHtmlView )
    ExecWB(OLECMDID_CUT, OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL); 
#endif
} 

void RHtmlView::OnEditCopy() 
{ 
#if defined ( BASE_CHtmlView ) || defined ( BASE_RHtmlView )
    ExecWB(OLECMDID_COPY, OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL); 
#endif
} 

void RHtmlView::OnEditPaste() 
{ 
#if defined ( BASE_CHtmlView ) || defined ( BASE_RHtmlView )
    ExecWB(OLECMDID_PASTE, OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL); 
#endif
} 

void RHtmlView::OnEditSelectall() 
{ 
#if defined ( BASE_CHtmlView ) || defined ( BASE_RHtmlView )
    ExecWB(OLECMDID_SELECTALL, OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL); 
#endif
} 



#include <initguid.h>
DEFINE_GUID(CGID_IWebBrowser,0xED016940L,0xBD5B,0x11cf,0xBA,
      0x4E,0x00,0xC0,0x4F,0xD7,0x08,0x16); 

// nCmdID's
#define HTMLID_FIND 1
#define HTMLID_VIEWSOURCE 2
#define HTMLID_OPTIONS 3 


void RHtmlView::ExecIE(INT nCmdID)
{
   CComQIPtr<IOleCommandTarget> spOleCmdTarget;
   spOleCmdTarget->Exec(&CGID_IWebBrowser, nCmdID, 
      0, NULL, NULL);
}


void RHtmlView::OnEditFind() 
{ 
	ExecIE( HTMLID_FIND );
} 


HRESULT RHtmlView::get_Width(long *pl)
{
	ASSERT(m_pBrowserApp != NULL);
	return m_pBrowserApp->get_Width(pl);
}

HRESULT RHtmlView::put_Width(long Width)
{
	ASSERT(m_pBrowserApp != NULL);
	return m_pBrowserApp->put_Width(Width);
}



void RHtmlView::FindText(CString searchText, long lFlags /* =2 */, BOOL bNNF /* =FALSE  (for internal use)*/)
{
	HCURSOR hSaveCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
	static CString sLastSearch;
	static BSTR lastBookmark = NULL;

	if(sLastSearch != searchText)
		lastBookmark = NULL;
	sLastSearch = searchText;
	

	IHTMLDocument2 *lpHtmlDocument = NULL;
	LPDISPATCH lpDispatch = NULL;
	lpDispatch = GetHtmlDocument();
	ASSERT(lpDispatch);

	lpDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&lpHtmlDocument);
	ASSERT(lpHtmlDocument);

	lpDispatch->Release();

	IHTMLElement *lpBodyElm;
	IHTMLBodyElement *lpBody;
	IHTMLTxtRange *lpTxtRange;

	lpHtmlDocument->get_body(&lpBodyElm);
	ASSERT(lpBodyElm);
	lpHtmlDocument->Release();
	lpBodyElm->QueryInterface(IID_IHTMLBodyElement,(void**)&lpBody);
	ASSERT(lpBody);
	lpBodyElm->Release();
	lpBody->createTextRange(&lpTxtRange);
	ASSERT(lpTxtRange);
	lpBody->Release();

	CComBSTR search(searchText.GetLength()+1,(LPCTSTR)searchText);
	bool bFound,bTest;
	long t;

	if(lastBookmark!=NULL)
	{
		lpTxtRange->moveToBookmark(lastBookmark,(VARIANT_BOOL*)&bTest);
		if(!bTest)
		{
			lastBookmark=NULL;
			lpTxtRange->moveStart((BSTR)CComBSTR("Textedit"),1,&t);
			lpTxtRange->moveEnd((BSTR)CComBSTR("Textedit"),1,&t);
		} else
		{
			lpTxtRange->moveStart((BSTR)CComBSTR("Character"),1,&t);
			lpTxtRange->moveEnd((BSTR)CComBSTR("Textedit"),1,&t);
		}
	} else
	{
		lpTxtRange->moveStart((BSTR)CComBSTR("Textedit"),0,&t);
		lpTxtRange->moveEnd((BSTR)CComBSTR("Textedit"),1,&t);
	}
	lpTxtRange->findText((BSTR)search,0,lFlags,(VARIANT_BOOL*)&bFound);

	if(!bFound)
	{
		if(lastBookmark==NULL && !bNNF)
		{
			CString message;
			message.Format("Cannot find the string: '%s'",searchText);
			AfxMessageBox(message);
		} else if(lastBookmark!=NULL)
		{
			lastBookmark = NULL;
			FindText(searchText,lFlags,TRUE);
		}
	} else
	{
		if(lpTxtRange->getBookmark(&lastBookmark)!=S_OK)
			lastBookmark=NULL;
		lpTxtRange->select();
		lpTxtRange->scrollIntoView(TRUE);
	}

	lpTxtRange->Release();
	SetCursor(hSaveCursor);
}


void RHtmlView::FindText2(CString searchText, long lFlags /* =2 */, CString matchStyle, CString searchID)
{
	HCURSOR hSaveCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
	ClearSearchResults(searchID);

	IHTMLDocument2 *lpHtmlDocument = NULL;
	LPDISPATCH lpDispatch = NULL;
	lpDispatch = GetHtmlDocument();
	ASSERT(lpDispatch);

	lpDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&lpHtmlDocument);
	ASSERT(lpHtmlDocument);

	lpDispatch->Release();

	IHTMLElement *lpBodyElm;
	IHTMLBodyElement *lpBody;
	IHTMLTxtRange *lpTxtRange;

	lpHtmlDocument->get_body(&lpBodyElm);
	ASSERT(lpBodyElm);
	lpHtmlDocument->Release();
	lpBodyElm->QueryInterface(IID_IHTMLBodyElement,(void**)&lpBody);
	ASSERT(lpBody);
	lpBodyElm->Release();
	lpBody->createTextRange(&lpTxtRange);
	ASSERT(lpTxtRange);
	lpBody->Release();

	CComBSTR html;
	CComBSTR newhtml;
	CComBSTR search(searchText.GetLength()+1,(LPCTSTR)searchText);

	long t;
	bool bFound;
	while(lpTxtRange->findText(search,0,lFlags,(VARIANT_BOOL*)&bFound),bFound)
	{
		newhtml.Empty();
		lpTxtRange->get_htmlText(&html);
		newhtml.Append("<span id='");
		newhtml.Append((LPCTSTR)searchID);
		newhtml.Append("' style='");
		newhtml.Append((LPCTSTR)matchStyle);
		newhtml.Append("'>");
		if(searchText==" ")
			newhtml.Append("&nbsp;"); // doesn't work very well, but prevents (some) shit
		else 
			newhtml.AppendBSTR(html);
		newhtml.Append("</span>");
		lpTxtRange->pasteHTML(newhtml);
				
		lpTxtRange->moveStart((BSTR)CComBSTR("Character"),1,&t);
		lpTxtRange->moveEnd((BSTR)CComBSTR("Textedit"),1,&t);
	}

	lpTxtRange->Release();
	SetCursor(hSaveCursor);
}

void RHtmlView::ClearSearchResults(CString searchID)
{
	HCURSOR hSaveCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));

	CComBSTR testid(searchID.GetLength()+1,searchID);
	CComBSTR testtag(5,"SPAN");
	IHTMLDocument2 *lpHtmlDocument = NULL;
	LPDISPATCH lpDispatch = NULL;
	lpDispatch = GetHtmlDocument();
	ASSERT(lpDispatch);

	lpDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&lpHtmlDocument);
	ASSERT(lpHtmlDocument);
	lpDispatch->Release();

	IHTMLElementCollection *lpAllElements;
	lpHtmlDocument->get_all(&lpAllElements);
	ASSERT(lpAllElements);
	lpHtmlDocument->Release();

	IUnknown *lpUnk;
	IEnumVARIANT *lpNewEnum;
	if (SUCCEEDED(lpAllElements->get__newEnum(&lpUnk)) && lpUnk != NULL)
	{
		lpUnk->QueryInterface(IID_IEnumVARIANT,(void**)&lpNewEnum);
		ASSERT(lpNewEnum);
		VARIANT varElement;
		IHTMLElement *lpElement;

		while (lpNewEnum->Next(1, &varElement, NULL) == S_OK)
		{
			_ASSERTE(varElement.vt == VT_DISPATCH);
			varElement.pdispVal->QueryInterface(IID_IHTMLElement,(void**)&lpElement);
			ASSERT(lpElement);
			if (lpElement)
			{
				CComBSTR id;
				CComBSTR tag;
				lpElement->get_id(&id);
				lpElement->get_tagName(&tag);
				if((id==testid)&&(tag==testtag))
				{
					BSTR innerText;
					lpElement->get_innerHTML(&innerText);
					lpElement->put_outerHTML(innerText);
				}
			}
			VariantClear(&varElement);
		}
	}
	SetCursor(hSaveCursor);
}


void RHtmlView::HighlightOnePhrase(CString searchText, long lFlags, CString matchStyle, CString searchID)
{
	searchText.TrimLeft(); searchText.TrimRight();
	if (searchText.GetLength() == 0) return;

	IHTMLDocument2 *lpHtmlDocument = NULL;
	LPDISPATCH lpDispatch = NULL;
	lpDispatch = GetHtmlDocument();
	ASSERT(lpDispatch);

	lpDispatch->QueryInterface(IID_IHTMLDocument2, (void**)&lpHtmlDocument);
	ASSERT(lpHtmlDocument);

	lpDispatch->Release();

	IHTMLElement *lpBodyElm;
	IHTMLBodyElement *lpBody;
	IHTMLTxtRange *lpTxtRange;

	lpHtmlDocument->get_body(&lpBodyElm);
	ASSERT(lpBodyElm);
	lpHtmlDocument->Release();
	lpBodyElm->QueryInterface(IID_IHTMLBodyElement,(void**)&lpBody);
	ASSERT(lpBody);
	lpBodyElm->Release();
	lpBody->createTextRange(&lpTxtRange);
	ASSERT(lpTxtRange);
	lpBody->Release();

	CComBSTR html;
	CComBSTR newhtml;
	CComBSTR search(searchText.GetLength()+1,(LPCTSTR)searchText);

	long t;
	bool bFound;
	while(lpTxtRange->findText(search,0,lFlags,(VARIANT_BOOL*)&bFound),bFound)
	{
		newhtml.Empty();
		lpTxtRange->get_htmlText(&html);
		newhtml.Append("<span id='");
		newhtml.Append((LPCTSTR)searchID);
		newhtml.Append("' style='");
		newhtml.Append((LPCTSTR)matchStyle);
		newhtml.Append("'>");
		if(searchText==" ")
			newhtml.Append("&nbsp;"); // doesn't work very well, but prevents (some) shit
		else 
			newhtml.AppendBSTR(html);
		newhtml.Append("</span>");
		lpTxtRange->pasteHTML(newhtml);
				
		lpTxtRange->moveStart((BSTR)CComBSTR("Character"),1,&t);
		lpTxtRange->moveEnd((BSTR)CComBSTR("Textedit"),1,&t);
	}

	lpTxtRange->Release();
}

void RHtmlView::HighlightAllLines(CString searchText, long lFlags /* =2 */, CString matchStyle, CString searchID)
{
	HCURSOR hSaveCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
	ClearHighlightResults(searchID);
	
	// for each substring in searchText, delimited by '|' call HighlightOnePhrase
	StringTokenizer *st = new StringTokenizer( searchText, '|' );
	CString xyz;
	do {
		xyz = st->nextToken();
		if ( xyz.GetLength() != 0 )
			HighlightOnePhrase( xyz, lFlags,matchStyle,searchID);

	} while ( xyz.GetLength() != 0 );

	delete st;
	SetCursor(hSaveCursor);
}

void RHtmlView::ClearHighlightResults(CString searchID)
{
	ClearSearchResults(searchID);
}




void RHtmlView::ResetSearchParams()
{
}

void RHtmlView::ResetHighlightParams()
{
}
