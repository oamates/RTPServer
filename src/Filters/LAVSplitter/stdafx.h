// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// TODO: reference additional headers your program requires here
#include "version.h"

// include headers
#include <Windows.h>
#include <Commctrl.h>

#pragma warning(push)
#pragma warning(disable:4244)
extern "C" {
#define __STDC_CONSTANT_MACROS
#define FF_API_PIX_FMT 0
#include "libavformat/avformat.h"
#include "libbluray/bluray.h"
#include "libavutil/intreadwrite.h"
}
#pragma warning(pop)

#include "streams.h"

#include "DShowUtil.h"
#include "BaseDemuxer.h"

#include "resource.h"
