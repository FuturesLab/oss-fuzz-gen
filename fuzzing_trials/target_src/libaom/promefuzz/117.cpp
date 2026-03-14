// This fuzz driver is generated for library libaom, aiming to fuzz the following functions:
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_control at aom_codec.c:88:17 in aom_codec.h
// aom_codec_build_config at aom_config.c:13:13 in aom_codec.h
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
#include "aom_codec.h"
#include "aom_encoder.h"
#include "aomcx.h"
}

#include <cstdint>
#include <cstdio>
#include <cstring>

static void fuzz_set_min_gf_interval(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) return;
    unsigned int min_gf_interval = *reinterpret_cast<const unsigned int *>(Data);
    aom_codec_control(codec, AV1E_SET_MIN_GF_INTERVAL, min_gf_interval);
}

static void fuzz_set_partition_info_path(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    const char *dummy_file = "./dummy_file";
    FILE *file = fopen(dummy_file, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
        aom_codec_control(codec, AV1E_SET_PARTITION_INFO_PATH, dummy_file);
    }
}

static void fuzz_set_enable_palette(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int enable_palette = *reinterpret_cast<const int *>(Data);
    aom_codec_control(codec, AV1E_SET_ENABLE_PALETTE, enable_palette);
}

static void fuzz_set_rate_distribution_info(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(const char *)) return;
    const char *rate_dist_info = reinterpret_cast<const char *>(Data);
    aom_codec_control(codec, AV1E_SET_RATE_DISTRIBUTION_INFO, rate_dist_info);
}

static void fuzz_set_rtc_external_rc(aom_codec_ctx_t *codec, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int rtc_external_rc = *reinterpret_cast<const int *>(Data);
    aom_codec_control(codec, AV1E_SET_RTC_EXTERNAL_RC, rtc_external_rc);
}

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size) {
    aom_codec_ctx_t codec;
    memset(&codec, 0, sizeof(codec));

    fuzz_set_min_gf_interval(&codec, Data, Size);
    fuzz_set_partition_info_path(&codec, Data, Size);
    fuzz_set_enable_palette(&codec, Data, Size);
    fuzz_set_rate_distribution_info(&codec, Data, Size);
    fuzz_set_rtc_external_rc(&codec, Data, Size);

    const char *build_config = aom_codec_build_config();
    if (build_config) {
        printf("Build config: %s\n", build_config);
    }

    return 0;
}