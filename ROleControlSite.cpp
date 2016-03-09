// ROleControlSite.cpp : implementation of the ROleControlSite class
//

#include "stdafx.h"
#undef AFX_DATA
#define AFX_DATA AFX_DATA_IMPORT

#include <..\src\occimpl.h>

#undef AFX_DATA
#define AFX_DATA AFX_DATA_EXPORT

#include "ROleControlSite.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// m_dwXDocHostUI_DblClk interface

DWORD ROleControlSite::GetXDocHostUI_DblClk()
{
	return m_dwXDocHostUI_DblClk;
}

void ROleControlSite::SetXDocHostUI_DblClk(DWORD dwSet)
{
	m_dwXDocHostUI_DblClk = dwSet;
}


/////////////////////////////////////////////////////////////////////////////
// m_dwXDocHostUI_Flag interface

DWORD ROleControlSite::GetXDocHostUI_Flag()
{
	return m_dwXDocHostUI_Flag;
}

void ROleControlSite::SetXDocHostUI_Flag(DWORD dwSet)
{
	m_dwXDocHostUI_Flag = dwSet;
}


/////////////////////////////////////////////////////////////////////////////
// IDocHostUIHandler interface declaration

BEGIN_INTERFACE_MAP(ROleControlSite, COleControlSite)
	INTERFACE_PART(ROleControlSite, IID_IDocHostUIHandler, DocHostUIHandler)
	INTERFACE_PART(ROleControlSite, IID_IDocHostShowUI, DocHostShowUI)
END_INTERFACE_MAP()

	
/////////////////////////////////////////////////////////////////////////////
// ROleControlSite: IDocHostUIHandler::IUnknown methods

ULONG ROleControlSite::XDocHostUIHandler::AddRef()
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return pThis->ExternalAddRef();
}

ULONG ROleControlSite::XDocHostUIHandler::Release()
{                            
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return pThis->ExternalRelease();
}

HRESULT ROleControlSite::XDocHostUIHandler::QueryInterface(REFIID riid, void **ppvObj)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
	return hr;
}


/////////////////////////////////////////////////////////////////////////////
// ROleControlSite: IDocHostUIHandler methods

// EnableModeless
STDMETHODIMP ROleControlSite::XDocHostUIHandler::EnableModeless(
		/* [in ] */	BOOL fEnable)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}

// FilterDataObject
STDMETHODIMP ROleControlSite::XDocHostUIHandler::FilterDataObject( 
		/* [in ] */	IDataObject __RPC_FAR *pDO,
		/* [out] */	IDataObject __RPC_FAR *__RPC_FAR *ppDORet)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}

// GetDropTarget
STDMETHODIMP ROleControlSite::XDocHostUIHandler::GetDropTarget( 
		/* [in ] */	IDropTarget __RPC_FAR *pDropTarget,
		/* [out] */	IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}

// GetExternal
STDMETHODIMP ROleControlSite::XDocHostUIHandler::GetExternal( 
		/* [out] */	IDispatch __RPC_FAR *__RPC_FAR *ppDispatch)
{
	return E_NOTIMPL;
}

// GetHostInfo
STDMETHODIMP ROleControlSite::XDocHostUIHandler::GetHostInfo(
		/* [i/o] */	DOCHOSTUIINFO __RPC_FAR *pInfo)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)

	pInfo->cbSize = sizeof(DOCHOSTUIINFO);
	pInfo->dwFlags = pThis->GetXDocHostUI_Flag();
	pInfo->dwDoubleClick = pThis->GetXDocHostUI_DblClk();

	return S_OK;
}

// GetOptionKeyPath
STDMETHODIMP ROleControlSite::XDocHostUIHandler::GetOptionKeyPath(
		/* [out] */	LPOLESTR __RPC_FAR *pchKey,
		/* [in ] */	DWORD dwReserved)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}

// HideUI
STDMETHODIMP ROleControlSite::XDocHostUIHandler::HideUI(void)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return S_OK;
}

// OnDocWindowActivate
STDMETHODIMP ROleControlSite::XDocHostUIHandler::OnDocWindowActivate(
		/* [in ] */	BOOL fActive)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}

// OnFrameWindowActivate
STDMETHODIMP ROleControlSite::XDocHostUIHandler::OnFrameWindowActivate(
		/* [in ] */	BOOL fActive)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}

// ResizeBorder
STDMETHODIMP ROleControlSite::XDocHostUIHandler::ResizeBorder(
		/* [in ] */	LPCRECT prcBorder,
		/* [in ] */	IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
		/* [in ] */	BOOL fFrameWindow)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}

// ShowContextMenu
STDMETHODIMP ROleControlSite::XDocHostUIHandler::ShowContextMenu(
		/* [in ] */	DWORD dwID,
		/* [in ] */	POINT __RPC_FAR *ppt,
		/* [in ] */	IUnknown __RPC_FAR *pcmdtReserved,
		/* [in ] */	IDispatch __RPC_FAR *pdispReserved)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)

	// Don't show context menu
	if (pThis->GetXDocHostUI_Flag() & DOCHOSTUIFLAG_DISABLE_HELP_MENU) return S_OK;

	// Otherwise, show default
 	return S_FALSE;
}

// ShowUI
STDMETHODIMP ROleControlSite::XDocHostUIHandler::ShowUI(
		/* [in ] */	DWORD dwID,
		/* [in ] */	IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
		/* [in ] */	IOleCommandTarget __RPC_FAR *pCommandTarget,
		/* [in ] */	IOleInPlaceFrame __RPC_FAR *pFrame,
		/* [in ] */	IOleInPlaceUIWindow __RPC_FAR *pDoc)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return S_OK;
}

// TranslateAccelerator
STDMETHODIMP ROleControlSite::XDocHostUIHandler::TranslateAccelerator(
		/* [in ] */	LPMSG lpMsg,
		/* [in ] */	const GUID __RPC_FAR *pguidCmdGroup,
		/* [in ] */	DWORD nCmdID)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}
        
// TranslateUrl
STDMETHODIMP ROleControlSite::XDocHostUIHandler::TranslateUrl( 
		/* [in ] */	DWORD dwTranslate,
		/* [in ] */	OLECHAR __RPC_FAR *pchURLIn,
		/* [out] */	OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return E_NOTIMPL;
}

// UpdateUI
STDMETHODIMP ROleControlSite::XDocHostUIHandler::UpdateUI(void)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostUIHandler)
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// ROleControlSite: IDocHostShowUI::IUnknown methods

ULONG ROleControlSite::XDocHostShowUI::AddRef()
{
	METHOD_PROLOGUE(ROleControlSite, DocHostShowUI)
	return pThis->ExternalAddRef();
}

ULONG ROleControlSite::XDocHostShowUI::Release()
{                            
	METHOD_PROLOGUE(ROleControlSite, DocHostShowUI)
	return pThis->ExternalRelease();
}

HRESULT ROleControlSite::XDocHostShowUI::QueryInterface(REFIID riid, void **ppvObj)
{
	METHOD_PROLOGUE(ROleControlSite, DocHostShowUI)
	HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&riid, ppvObj);
	return hr;
}


/////////////////////////////////////////////////////////////////////////////
// ROleControlSite: IDocHostShowUI methods

// ShowHelp
STDMETHODIMP ROleControlSite::XDocHostShowUI::ShowHelp(
		/* [in ] */	HWND hwnd,
		/* [in ] */	LPOLESTR pszHelpFile,
		/* [in ] */	UINT uCommand,
		/* [in ] */	DWORD dwData,
		/* [in ] */	POINT ptMouse,
		/* [out] */	IDispatch __RPC_FAR *pDispatchObjectHit)
{
	return S_OK;
}

// ShowMessage
STDMETHODIMP ROleControlSite::XDocHostShowUI::ShowMessage(
		/* [in ] */	HWND hwnd,
		/* [in ] */	LPOLESTR lpstrText,
		/* [in ] */	LPOLESTR lpstrCaption,
		/* [in ] */	DWORD dwType,
		/* [in ] */	LPOLESTR lpstrHelpFile,
		/* [in ] */	DWORD dwHelpContext,
		/* [out] */	LRESULT __RPC_FAR *plResult)
{
	return S_OK;
}

