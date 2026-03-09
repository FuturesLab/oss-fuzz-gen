// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_destroy at aom_codec.c:68:17 in aom_codec.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "aom.h"
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
  if (Size < sizeof(int) + sizeof(int)) return 0;

  aom_codec_ctx_t codec_ctx;
  memset(&codec_ctx, 0, sizeof(codec_ctx));

  // Assume the first byte determines the function to call
  uint8_t function_selector = Data[0];
  int param = 0;
  memcpy(&param, Data + 1, sizeof(int));

  // Initialize codec context with dummy values
  codec_ctx.err = AOM_CODEC_OK;
  codec_ctx.iface = aom_codec_av1_cx();

  // Select function based on the first byte of input data
  switch (function_selector % 6) {
    case 0:
      aom_codec_control(&codec_ctx, AV1E_SET_SVC_FRAME_DROP_MODE, param);
      break;
    case 1:
      aom_codec_control(&codec_ctx, AV1E_SET_DELTAQ_STRENGTH, param);
      break;
    case 2:
      aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_QM, param);
      break;
    case 3:
      aom_codec_control(&codec_ctx, AV1E_SET_AUTO_INTRA_TOOLS_OFF, param);
      break;
    case 4:
      aom_codec_control(&codec_ctx, AV1E_SET_ENABLE_KEYFRAME_FILTERING, param);
      break;
    case 5:
      aom_codec_control(&codec_ctx, AV1E_SET_FRAME_PARALLEL_DECODING, param);
      break;
    default:
      break;
  }

  // Clean up
  aom_codec_destroy(&codec_ctx);

  return 0;
}