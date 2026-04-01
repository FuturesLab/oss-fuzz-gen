// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_vp8_dx at vp8_dx_iface.c:726:1 in vp8dx.h
// vpx_codec_dec_init_ver at vpx_decoder.c:24:17 in vpx_decoder.h
// vpx_codec_peek_stream_info at vpx_decoder.c:65:17 in vpx_decoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_decode at vpx_decoder.c:104:17 in vpx_decoder.h
// vpx_codec_error at vpx_codec.c:54:13 in vpx_codec.h
// vpx_codec_error_detail at vpx_codec.c:59:13 in vpx_codec.h
// vpx_codec_get_caps at vpx_codec.c:85:18 in vpx_codec.h
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
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cstring>
#include "vpx_decoder.h"
#include "vp8dx.h"
#include "vpx_codec.h"
#include "vp8cx.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    std::ofstream file("./dummy_file", std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();
    }
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize codec context
    vpx_codec_ctx_t codec_ctx;
    std::memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Initialize codec interface
    vpx_codec_iface_t *iface = vpx_codec_vp8_dx();

    // Initialize decoder configuration
    vpx_codec_dec_cfg_t dec_cfg;
    dec_cfg.threads = 1;

    // Initialize stream info
    vpx_codec_stream_info_t stream_info;
    stream_info.sz = sizeof(stream_info);

    // Write data to dummy file
    write_dummy_file(Data, Size);

    // Initialize decoder
    vpx_codec_err_t res = vpx_codec_dec_init_ver(&codec_ctx, iface, &dec_cfg, 0, VPX_DECODER_ABI_VERSION);
    if (res != VPX_CODEC_OK) {
        return 0;
    }

    // Peek stream info
    res = vpx_codec_peek_stream_info(iface, Data, Size, &stream_info);
    if (res != VPX_CODEC_OK) {
        vpx_codec_destroy(&codec_ctx);
        return 0;
    }

    // Decode data
    res = vpx_codec_decode(&codec_ctx, Data, static_cast<unsigned int>(Size), nullptr, 0);
    if (res != VPX_CODEC_OK) {
        const char *error_msg = vpx_codec_error(&codec_ctx);
        const char *error_detail = vpx_codec_error_detail(&codec_ctx);
        std::cerr << "Error: " << error_msg << " Detail: " << (error_detail ? error_detail : "None") << std::endl;
    }

    // Retrieve capabilities
    vpx_codec_caps_t caps = vpx_codec_get_caps(iface);

    // Cleanup
    vpx_codec_destroy(&codec_ctx);

    return 0;
}