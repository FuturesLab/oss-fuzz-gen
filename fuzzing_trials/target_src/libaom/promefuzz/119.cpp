// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_av1_cx at av1_cx_iface.c:5284:20 in aomcx.h
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
#include <cstddef>
#include <cstdio>
#include <cstring>
#include "aom_frame_buffer.h"
#include "aom_external_partition.h"
#include "aomdx.h"
#include "aom_decoder.h"
#include "aom_encoder.h"
#include "aom_integer.h"
#include "aom_codec.h"
#include "aom_image.h"
#include "aom.h"
#include "aomcx.h"

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare the environment

    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    memset(&codec_ctx, 0, sizeof(codec_ctx));

    // Initialize codec interface
    aom_codec_iface_t *iface = aom_codec_av1_cx();
    codec_ctx.iface = iface;

    // Step 2: Invoke target functions

    // Test aom_codec_version_str
    const char *version_str = aom_codec_version_str();
    if (version_str) {
        printf("Version String: %s\n", version_str);
    }

    // Test aom_codec_version
    int version = aom_codec_version();
    printf("Version: %d\n", version);

    // Test aom_codec_version_extra_str
    const char *extra_version_str = aom_codec_version_extra_str();
    if (extra_version_str) {
        printf("Extra Version String: %s\n", extra_version_str);
    }

    // Step 3: Clean up

    // Normally, you would clean up codec context here if it was fully initialized
    // aom_codec_destroy(&codec_ctx);

    return 0;
}