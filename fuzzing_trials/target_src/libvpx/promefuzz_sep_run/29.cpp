// This fuzz driver is generated for library libvpx, aiming to fuzz the following functions:
// vpx_codec_version_extra_str at vpx_codec.c:28:13 in vpx_codec.h
// vpx_codec_build_config at vpx_config.c:10:13 in vpx_codec.h
// vpx_codec_iface_name at vpx_codec.c:30:13 in vpx_codec.h
// vpx_codec_dec_init_ver at vpx_decoder.c:24:17 in vpx_decoder.h
// vpx_codec_destroy at vpx_codec.c:66:17 in vpx_codec.h
// vpx_codec_version at vpx_codec.c:24:5 in vpx_codec.h
// vpx_codec_version_str at vpx_codec.c:26:13 in vpx_codec.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "vpx_decoder.h"
#include "vp8dx.h"
#include "vpx_codec.h"
#include "vp8cx.h"

// Dummy implementation of vpx_codec_iface_t for testing purposes
struct vpx_codec_iface {
    const char *name;
    int abi_version;
    vpx_codec_caps_t caps;
    struct vpx_codec_dec_iface {
    } dec;
    struct vpx_codec_enc_iface {
    } enc;
};

static struct vpx_codec_iface dummy_iface = {
    "dummy_iface", // name
    VPX_DECODER_ABI_VERSION, // abi_version
    0, // caps
    {}, // dec
    {}  // enc
};

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    // Handle empty input
    if (Size == 0) {
        return 0;
    }

    // 1. Test vpx_codec_version_extra_str
    const char *version_extra = vpx_codec_version_extra_str();
    if (version_extra) {
        printf("Version Extra: %s\n", version_extra);
    }

    // 2. Test vpx_codec_build_config
    const char *build_config = vpx_codec_build_config();
    if (build_config) {
        printf("Build Config: %s\n", build_config);
    }

    // 3. Test vpx_codec_iface_name
    const char *iface_name = vpx_codec_iface_name(&dummy_iface);
    if (iface_name) {
        printf("Interface Name: %s\n", iface_name);
    }

    // 4. Test vpx_codec_dec_init_ver
    vpx_codec_ctx_t ctx;
    ctx.name = nullptr;
    ctx.iface = &dummy_iface;
    ctx.err = static_cast<vpx_codec_err_t>(0);
    ctx.init_flags = 0;
    ctx.config.dec = nullptr;
    ctx.priv = nullptr;

    vpx_codec_dec_cfg_t cfg;
    cfg.threads = static_cast<unsigned int>(Data[0]);

    vpx_codec_err_t err = vpx_codec_dec_init_ver(&ctx, &dummy_iface, &cfg, 0, VPX_DECODER_ABI_VERSION);
    if (err == VPX_CODEC_OK) {
        printf("Decoder initialized successfully.\n");
        vpx_codec_destroy(&ctx);
    } else {
        printf("Decoder initialization failed with error: %d\n", err);
    }

    // 5. Test vpx_codec_version
    int version = vpx_codec_version();
    printf("Version: %d\n", version);

    // 6. Test vpx_codec_version_str
    const char *version_str = vpx_codec_version_str();
    if (version_str) {
        printf("Version String: %s\n", version_str);
    }

    return 0;
}