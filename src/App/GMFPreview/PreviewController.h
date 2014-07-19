// 
// GDCL Multigraph Framework
//
// GMFPreview Demo Application: PreviewController.h
// Declaration of class to manage capture device preview and capture
// using GMFBridge tools
//
// Copyright (c) GDCL 2004. All Rights Reserved. 
// You are free to re-use this as the basis for your own filter development,
// provided you retain this copyright notice in the source.
// http://www.gdcl.co.uk

#pragma once

#include <string>
using namespace std;

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

#include "Interface.h"
#include "Bridge.h"

_COM_SMARTPTR_TYPEDEF(ICreateDevEnum, IID_ICreateDevEnum);
_COM_SMARTPTR_TYPEDEF(IGMFBridgeController, __uuidof(IGMFBridgeController));
_COM_SMARTPTR_TYPEDEF(IGraphBuilder, IID_IGraphBuilder);
_COM_SMARTPTR_TYPEDEF(IMediaControl, IID_IMediaControl);
_COM_SMARTPTR_TYPEDEF(ICaptureGraphBuilder2, IID_ICaptureGraphBuilder2);
_COM_SMARTPTR_TYPEDEF(IVideoWindow, IID_IVideoWindow);
_COM_SMARTPTR_TYPEDEF(IBasicVideo, IID_IBasicVideo);
_COM_SMARTPTR_TYPEDEF(IBaseFilter, IID_IBaseFilter);
_COM_SMARTPTR_TYPEDEF(IAMStreamControl, IID_IAMStreamControl);
_COM_SMARTPTR_TYPEDEF(IPin, IID_IPin);

class PreviewController
{
public:
	PreviewController() : 
		m_bAudio(false),
		m_dwRegister(0)
	{
	}
	~PreviewController();
	HRESULT SelectDevice(const TCHAR* pVideo, const TCHAR* pAudio, HWND hwnd, RECT* prc);
	HRESULT SetNextFilename(const TCHAR* pFile);
	HRESULT StartCapture();
	HRESULT StopCapture();
	tstring GetFilename()
	{
		return m_strFile;
	}
    bool HasDevice()
    {
        return (m_pSourceGraph != NULL) ? true : false;
    }
	HRESULT Pause();
	HRESULT Resume();

private:
	HRESULT LocateFilter(const TCHAR* pName, REFIID catid, IBaseFilter** ppFilter);
	HRESULT AddToROT(IGraphBuilder* pGraphBuilder);
	HRESULT RemoveFromROT();

private:
	CComPtr<BridgeController> m_pBridge;
	IGraphBuilderPtr m_pSourceGraph;
	tstring m_strFile;
	IGraphBuilderPtr m_pCaptureGraph;
	IPinPtr m_pCapOutput;
	IUnknownPtr m_pSourceGraphSinkFilter;
	IUnknownPtr m_pCaptureGraphSourceFilter;

	bool m_bAudio;
	DWORD m_dwRegister;
};
