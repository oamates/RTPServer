// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// TODO: reference additional headers your program requires here
#include "streams.h"

#pragma warning(push)
#pragma warning(disable:4244)
extern "C" {
#define __STDC_CONSTANT_MACROS
#define FF_API_PIX_FMT 0
#include "libavformat/avformat.h"
#include "libavutil/intreadwrite.h"
#include "libavutil/pixdesc.h"
#include "libavutil/opt.h"

#include "libbluray/bluray.h"
}
#pragma warning(pop)

#define AVFORMAT_INTERNAL_H
typedef struct AVCodecTag {
	enum AVCodecID id;
	unsigned int tag;
} AVCodecTag;

#include "libbluray/bdnav/clpi_parse.h"

#include "util/log_control.h"

#include "DShowUtil.h"
#include <MMReg.h>

#include <Shlwapi.h>