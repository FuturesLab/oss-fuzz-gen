// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp9_dx at vp9_dx_iface.c:712:1 in vp8dx.h
// vpx_codec_dec_init_ver at vpx_decoder.c:24:17 in vpx_decoder.h
// vpx_codec_register_put_frame_cb at vpx_decoder.c:133:17 in vpx_decoder.h
// vpx_codec_decode at vpx_decoder.c:104:17 in vpx_decoder.h
// vpx_codec_peek_stream_info at vpx_decoder.c:65:17 in vpx_decoder.h
// vpx_codec_get_stream_info at vpx_decoder.c:85:17 in vpx_decoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "vp8dx.h"
#include "vpx_decoder.h"
#include "vpx/vp8cx.h"
}

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

static void dummy_put_frame_cb(void *user_priv, const vpx_image_t *img) {
  // Dummy callback function for put frame
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
  if (Size < 1) return 0;

  // Initialize codec interface
  vpx_codec_iface_t *iface = vpx_codec_vp9_dx();
  if (!iface) return 0;

  // Initialize codec context
  vpx_codec_ctx_t ctx;
  vpx_codec_dec_cfg_t cfg = {0};  // Default configuration
  vpx_codec_err_t res = vpx_codec_dec_init_ver(&ctx, iface, &cfg, 0, VPX_DECODER_ABI_VERSION);
  if (res != VPX_CODEC_OK) return 0;

  // Register dummy callback
  vpx_codec_register_put_frame_cb(&ctx, dummy_put_frame_cb, nullptr);

  // Decode data
  vpx_codec_decode(&ctx, Data, static_cast<unsigned int>(Size), nullptr, 0);

  // Peek stream info
  vpx_codec_stream_info_t si;
  si.sz = sizeof(si);
  vpx_codec_peek_stream_info(iface, Data, static_cast<unsigned int>(Size), &si);

  // Get stream info
  vpx_codec_get_stream_info(&ctx, &si);

  // Cleanup
  vpx_codec_destroy(&ctx);

  return 0;
}