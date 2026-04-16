#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static int janet_initialized = 0;

static void initialize_janet() {
    if (!janet_initialized) {
        janet_init();
        janet_initialized = 1;
    }
}

static void cleanup_janet() {
    if (janet_initialized) {
        janet_deinit();
        janet_initialized = 0;
    }
}

static void fuzz_janet_scan_uint64(const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        uint64_t out;
        janet_scan_uint64(Data, (int32_t)Size, &out);
    }
}

static void fuzz_janet_unwrap_u64(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(uint64_t)) {
        uint64_t bits;
        memcpy(&bits, Data, sizeof(uint64_t));
        Janet janet_value = janet_nanbox_from_bits(bits);
        // Attempt to unwrap and catch errors manually
        if (janet_checkuint64(janet_value)) {
            janet_unwrap_u64(janet_value);
        }
    }
}

static void fuzz_janet_nanbox_from_bits(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(uint64_t)) {
        uint64_t bits;
        memcpy(&bits, Data, sizeof(uint64_t));
        janet_nanbox_from_bits(bits);
    }
}

static void fuzz_janet_wrap_u64(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(uint64_t)) {
        uint64_t value;
        memcpy(&value, Data, sizeof(uint64_t));
        janet_wrap_u64(value);
    }
}

static void fuzz_janet_getuinteger64(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(Janet) * 2) {
        Janet argv[2];
        memcpy(argv, Data, sizeof(Janet) * 2);
        // Attempt to get the integer and handle errors manually
        if (janet_checkuint64(argv[1])) {
            janet_getuinteger64(argv, 1); // Safe index within bounds
        }
    }
}

static void fuzz_janet_checkuint64(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(uint64_t)) {
        uint64_t bits;
        memcpy(&bits, Data, sizeof(uint64_t));
        Janet janet_value = janet_nanbox_from_bits(bits);
        janet_checkuint64(janet_value);
    }
}

int LLVMFuzzerTestOneInput_1397(const uint8_t *Data, size_t Size) {
    initialize_janet();
    fuzz_janet_scan_uint64(Data, Size);
    fuzz_janet_unwrap_u64(Data, Size);
    fuzz_janet_nanbox_from_bits(Data, Size);
    fuzz_janet_wrap_u64(Data, Size);
    fuzz_janet_getuinteger64(Data, Size);
    fuzz_janet_checkuint64(Data, Size);
    cleanup_janet();
    return 0;
}