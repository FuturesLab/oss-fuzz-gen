#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include "/src/libvpx/vpx/vpx_codec.h"
#include "/src/libvpx/vpx/vp8cx.h"
#include "vpx/vp8dx.h"

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(vpx_codec_ctx_t)) {
        return 0;
    }

    // Prepare a dummy codec context
    vpx_codec_ctx_t ctx;
    std::memset(&ctx, 0, sizeof(ctx));

    // Randomly choose a codec interface to test
    vpx_codec_iface_t *iface = nullptr;
    if (Size % 2 == 0) {
        iface = vpx_codec_vp8_cx();
    } else {
        iface = vpx_codec_vp8_dx();
    }
    ctx.iface = iface;

    // Fuzz vpx_codec_error_detail function
    const char *error_detail = vpx_codec_error_detail(&ctx);
    if (error_detail) {
        std::cout << "Error Detail: " << error_detail << std::endl;
    }

    // Fuzz vpx_codec_version_extra_str function
    const char *version_extra_str = vpx_codec_version_extra_str();
    if (version_extra_str) {
        std::cout << "Version Extra String: " << version_extra_str << std::endl;
    }

    // Fuzz vpx_codec_version function
    int version = vpx_codec_version();
    std::cout << "Version: " << version << std::endl;

    // Fuzz vpx_codec_version_str function
    const char *version_str = vpx_codec_version_str();
    if (version_str) {
        std::cout << "Version String: " << version_str << std::endl;
    }

    // Fuzz vpx_codec_build_config function
    const char *build_config = vpx_codec_build_config();
    if (build_config) {
        std::cout << "Build Config: " << build_config << std::endl;
    }

    // Fuzz vpx_codec_iface_name function
    const char *iface_name = vpx_codec_iface_name(iface);
    if (iface_name) {
        std::cout << "Interface Name: " << iface_name << std::endl;
    }

    return 0;
}