// ROleControlSite.h : interface of the ROleControlSite class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _R_OLE_CONTROL_SITE_H_
#define _R_OLE_CONTROL_SITE_H_

#include <mshtmhst.h>

class ROleControlSite : public COleControlSite
{
	DWORD m_dwXDocHostUI_DblClk;
	DWORD m_dwXDocHostUI_Flag;

public:
	ROleControlSite(COleControlContainer *pCnt = NULL):COleControlSite(pCnt)
	{
		m_dwXDocHostUI_DblClk = DOCHOSTUIDBLCLK_DEFAULT;
		m_dwXDocHostUI_Flag = 0;
	}

// m_dwXDocHostUI_DblClk interface
	DWORD GetXDocHostUI_DblClk();
	void SetXDocHostUI_DblClk(DWORD dwSet);

// m_dwXDocHostUI_Flag interface
	DWORD GetXDocHostUI_Flag();
	void SetXDocHostUI_Flag(DWORD dwSet);


protected:

DECLARE_INTERFACE_MAP();
BEGIN_INTERFACE_PART(DocHostUIHandler, IDocHostUIHandler)

// EnableModeless
	STDMETHODIMP EnableModeless(
		/* [in ] */	BOOL fEnable);

// FilterDataObject
	STDMETHODIMP FilterDataObject( 
		/* [in ] */	IDataObject __RPC_FAR *pDO,
		/* [out] */	IDataObject __RPC_FAR *__RPC_FAR *ppDORet);

// GetDropTarget
	STDMETHODIMP GetDropTarget(
		/* [in ] */	IDropTarget __RPC_FAR *pDropTarget,
		/* [out] */	IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget);

// GetExternal
	STDMETHODIMP GetExternal( 
		/* [out] */	IDispatch __RPC_FAR *__RPC_FAR *ppDispatch);

// GetHostInfo
	STDMETHODIMP GetHostInfo( 
		/* [i/o] */	DOCHOSTUIINFO __RPC_FAR *pInfo);

// GetOptionKeyPath
	STDMETHODIMP GetOptionKeyPath( 
		/* [out] */	LPOLESTR __RPC_FAR *pchKey,
		/* [in ] */	DWORD dwReserved);

// HideUI
	STDMETHODIMP HideUI(void);

// OnDocWindowActivate
	STDMETHODIMP OnDocWindowActivate(
		/* [in ] */	BOOL fActive);

// OnFrameWindowActivate
	STDMETHODIMP OnFrameWindowActivate(
		/* [in ] */	BOOL fActive);

// ResizeBorder
	STDMETHODIMP ResizeBorder( 
		/* [in ] */	LPCRECT prcBorder,
		/* [in ] */	IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
		/* [in ] */	BOOL fFrameWindow);

// ShowContextMenu
	STDMETHODIMP ShowContextMenu(
		/* [in ] */	DWORD dwID,
		/* [in ] */	POINT __RPC_FAR *ppt,
		/* [in ] */	IUnknown __RPC_FAR *pcmdtReserved,
		/* [in ] */	IDispatch __RPC_FAR *pdispReserved);

// ShowUI
	STDMETHODIMP ShowUI( 
		/* [in ] */	DWORD dwID,
		/* [in ] */	IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
		/* [in ] */	IOleCommandTarget __RPC_FAR *pCommandTarget,
		/* [in ] */	IOleInPlaceFrame __RPC_FAR *pFrame,
		/* [in ] */	IOleInPlaceUIWindow __RPC_FAR *pDoc);

// TranslateAccelerator
	STDMETHODIMP TranslateAccelerator( 
		/* [in ] */	LPMSG lpMsg,
		/* [in ] */	const GUID __RPC_FAR *pguidCmdGroup,
		/* [in ] */	DWORD nCmdID);

// TranslateUrl
	STDMETHODIMP TranslateUrl( 
		/* [in ] */	DWORD dwTranslate,
		/* [in ] */	OLECHAR __RPC_FAR *pchURLIn,
		/* [out] */	OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut);

// UpdateUI
	STDMETHODIMP UpdateUI(void);


END_INTERFACE_PART(DocHostUIHandler)

BEGIN_INTERFACE_PART(DocHostShowUI, IDocHostShowUI)

// ShowHelp
	STDMETHODIMP ShowHelp(
		/* [in ] */	HWND hwnd,
		/* [in ] */	LPOLESTR pszHelpFile,
		/* [in ] */	UINT uCommand,
		/* [in ] */	DWORD dwData,
		/* [in ] */	POINT ptMouse,
		/* [out] */	IDispatch __RPC_FAR *pDispatchObjectHit);

// ShowMessage
	STDMETHODIMP ShowMessage(
		/* [in ] */	HWND hwnd,
		/* [in ] */	LPOLESTR lpstrText,
		/* [in ] */	LPOLESTR lpstrCaption,
		/* [in ] */	DWORD dwType,
		/* [in ] */	LPOLESTR lpstrHelpFile,
		/* [in ] */	DWORD dwHelpContext,
		/* [out] */	LRESULT __RPC_FAR *plResult);


END_INTERFACE_PART(DocHostShowUI)
};


class ROccManager :public COccManager
{
public:
	ROleControlSite *m_pROleControlSite;

	ROccManager()
	{
		m_pROleControlSite = NULL;
	}

	COleControlSite* CreateSite(COleControlContainer* pCtrlCont)
	{
		m_pROleControlSite = new ROleControlSite(pCtrlCont);
		return m_pROleControlSite;
	}
};


#endif