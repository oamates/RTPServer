#pragma once

#pragma warning(push)
#pragma warning(disable:4312)
#pragma warning(disable:4995)
#include <streams.h>

#include <comdef.h>

_COM_SMARTPTR_TYPEDEF(IMemAllocator, IID_IMemAllocator);
_COM_SMARTPTR_TYPEDEF(IGraphBuilder, IID_IGraphBuilder);
_COM_SMARTPTR_TYPEDEF(IBaseFilter, IID_IBaseFilter);
_COM_SMARTPTR_TYPEDEF(IEnumMediaTypes, IID_IEnumMediaTypes);
_COM_SMARTPTR_TYPEDEF(IMediaSample, IID_IMediaSample);
_COM_SMARTPTR_TYPEDEF(IMediaSample2, IID_IMediaSample2);
_COM_SMARTPTR_TYPEDEF(IEnumFilters, IID_IEnumFilters);
_COM_SMARTPTR_TYPEDEF(IQualityControl, IID_IQualityControl);
_COM_SMARTPTR_TYPEDEF(IEnumPins, IID_IEnumPins);
_COM_SMARTPTR_TYPEDEF(IPin, IID_IPin);
_COM_SMARTPTR_TYPEDEF(IEnumMediaTypes, IID_IEnumMediaTypes);
_COM_SMARTPTR_TYPEDEF(IMediaControl, IID_IMediaControl);
_COM_SMARTPTR_TYPEDEF(IMediaSeeking, IID_IMediaSeeking);
_COM_SMARTPTR_TYPEDEF(IVideoWindow, IID_IVideoWindow);
_COM_SMARTPTR_TYPEDEF(IBasicVideo, IID_IBasicVideo);
_COM_SMARTPTR_TYPEDEF(IPinConnection, IID_IPinConnection);
#pragma warning(pop)

#include "SmartPtr.h"


typedef enum
{
    eUncompressed,
    eMuxInputs,
    eAny,
} eFormatType;

MIDL_INTERFACE("cb3baaf2-8206-4ac3-b6de-eeb65e8e636f")
IGMFBridgeController : public IUnknown
{
public:
    HRESULT AddStream(BOOL bVideo, eFormatType AllowedTypes, BOOL bDiscardUnconnected);

    HRESULT InsertSinkFilter(IUnknown * pGraph, IUnknown **ppFilter);

    HRESULT InsertSourceFilter(IUnknown * pUnkSourceGraphSinkFilter, IUnknown * pRenderGraph, IUnknown **ppFilter);

    HRESULT CreateSourceGraph(BSTR strFile, IUnknown * pGraph, IUnknown **pSinkFilter);

    HRESULT CreateRenderGraph(IUnknown * pSourceGraphSinkFilter, IUnknown * pRenderGraph, IUnknown **pRenderGraphSourceFilter);

    // equivalent to BridgeAtDiscont(pS, pR, FALSE)
    HRESULT BridgeGraphs(IUnknown * pSourceGraphSinkFilter, IUnknown * pRenderGraphSourceFilter);

    HRESULT SetNotify(LONG_PTR hwnd, long msg);

    HRESULT SetBufferMinimum(long nMillisecs);

    HRESULT GetSegmentTime(double * pdSeconds);

    HRESULT NoMoreSegments();

    HRESULT GetSegmentOffset(double * pdOffset);
};

MIDL_INTERFACE("d58ae110-2152-4715-b2aa-52d5f59ae1ab")
IGMFBridgeController2 : public IGMFBridgeController
{
public:
    // using this method allows the app to indicate that
    // this clip is not contiguous with previous clips.
    HRESULT BridgeAtDiscont(IUnknown * pSourceGraphSinkFilter, IUnknown * pRenderGraphSourceFilter, BOOL bIsDiscontinuity);
};

MIDL_INTERFACE("ddb8e19f-7688-41d2-b998-2c56a3b65001")
IGMFBridgeController3 : public IGMFBridgeController2
{
public:
    // using this option, you can share a common clock
    // and avoid any time mapping (essential if audio is in mux graph)
    HRESULT SetLiveTiming(BOOL bIsLiveTiming);
};

MIDL_INTERFACE("6da84274-ba02-4bf7-8d36-f454077caccc")
_IGMFBridgeEvents : public IUnknown
{
public:
    HRESULT OnEndOfSegment();
};
