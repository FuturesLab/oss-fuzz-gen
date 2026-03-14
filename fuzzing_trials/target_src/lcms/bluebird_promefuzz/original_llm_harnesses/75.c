// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsVEC3init at cmsmtrx.c:34:16 in lcms2_plugin.h
// _cmsVEC3minus at cmsmtrx.c:42:16 in lcms2_plugin.h
// _cmsVEC3dot at cmsmtrx.c:58:28 in lcms2_plugin.h
// _cmsVEC3distance at cmsmtrx.c:72:28 in lcms2_plugin.h
// _cmsVEC3cross at cmsmtrx.c:50:16 in lcms2_plugin.h
// _cmsVEC3length at cmsmtrx.c:64:28 in lcms2_plugin.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "lcms2_plugin.h"

static void fuzz_cmsVEC3init(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsVEC3) + 3 * sizeof(cmsFloat64Number)) return;

    cmsVEC3 vec;
    cmsFloat64Number x, y, z;
    memcpy(&x, Data, sizeof(cmsFloat64Number));
    memcpy(&y, Data + sizeof(cmsFloat64Number), sizeof(cmsFloat64Number));
    memcpy(&z, Data + 2 * sizeof(cmsFloat64Number), sizeof(cmsFloat64Number));

    _cmsVEC3init(&vec, x, y, z);
}

static void fuzz_cmsVEC3minus(const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(cmsVEC3)) return;

    cmsVEC3 a, b, result;
    memcpy(&a, Data, sizeof(cmsVEC3));
    memcpy(&b, Data + sizeof(cmsVEC3), sizeof(cmsVEC3));

    _cmsVEC3minus(&result, &a, &b);
}

static void fuzz_cmsVEC3dot(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsVEC3)) return;

    cmsVEC3 u, v;
    memcpy(&u, Data, sizeof(cmsVEC3));
    memcpy(&v, Data + sizeof(cmsVEC3), sizeof(cmsVEC3));

    cmsFloat64Number dot = _cmsVEC3dot(&u, &v);
    (void)dot; // Suppress unused variable warning
}

static void fuzz_cmsVEC3distance(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsVEC3)) return;

    cmsVEC3 a, b;
    memcpy(&a, Data, sizeof(cmsVEC3));
    memcpy(&b, Data + sizeof(cmsVEC3), sizeof(cmsVEC3));

    cmsFloat64Number distance = _cmsVEC3distance(&a, &b);
    (void)distance; // Suppress unused variable warning
}

static void fuzz_cmsVEC3cross(const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(cmsVEC3)) return;

    cmsVEC3 u, v, result;
    memcpy(&u, Data, sizeof(cmsVEC3));
    memcpy(&v, Data + sizeof(cmsVEC3), sizeof(cmsVEC3));

    _cmsVEC3cross(&result, &u, &v);
}

static void fuzz_cmsVEC3length(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsVEC3)) return;

    cmsVEC3 a;
    memcpy(&a, Data, sizeof(cmsVEC3));

    cmsFloat64Number length = _cmsVEC3length(&a);
    (void)length; // Suppress unused variable warning
}

int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    fuzz_cmsVEC3init(Data, Size);
    fuzz_cmsVEC3minus(Data, Size);
    fuzz_cmsVEC3dot(Data, Size);
    fuzz_cmsVEC3distance(Data, Size);
    fuzz_cmsVEC3cross(Data, Size);
    fuzz_cmsVEC3length(Data, Size);

    return 0;
}