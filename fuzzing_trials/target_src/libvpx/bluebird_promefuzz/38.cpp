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
#include "vpx/vp8dx.h"
#include "vpx/vpx_decoder.h"
#include "/src/libvpx/vpx/vp8cx.h"
}

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

static void dummy_put_frame_cb(void *user_priv, const vpx_image_t *img) {
  // Dummy callback function for put frame
}

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
  if (Size < 1) {
    return 0;
  }

  // Initialize codec interface
  vpx_codec_iface_t *iface = vpx_codec_vp9_dx();
  if (!iface) {
    return 0;
  }

  // Initialize codec context
  vpx_codec_ctx_t ctx;
  vpx_codec_dec_cfg_t cfg = {0};  // Default configuration
  vpx_codec_err_t res = vpx_codec_dec_init_ver(&ctx, iface, &cfg, 0, VPX_DECODER_ABI_VERSION);
  if (res != VPX_CODEC_OK) {
    return 0;
  }

  // Register dummy callback

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from vpx_codec_dec_init_ver to vpx_codec_peek_stream_info
  const uint8_t qjrmudja = 64;
  vpx_codec_stream_info_t ufyimgqq;
  memset(&ufyimgqq, 0, sizeof(ufyimgqq));

  vpx_codec_err_t ret_vpx_codec_peek_stream_info_somqs = vpx_codec_peek_stream_info(iface, &qjrmudja, 64, &ufyimgqq);

  // End mutation: Producer.APPEND_MUTATOR

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

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from vpx_codec_get_stream_info to vpx_codec_set_cx_data_buf


  // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of vpx_codec_set_cx_data_buf
  vpx_codec_err_t ret_vpx_codec_set_cx_data_buf_vqtqn = vpx_codec_set_cx_data_buf(&ctx, NULL, VPX_EFLAG_CALCULATE_PSNR, 1);
  // End mutation: Producer.REPLACE_ARG_MUTATOR



  // End mutation: Producer.APPEND_MUTATOR

  vpx_codec_destroy(&ctx);

  return 0;
}