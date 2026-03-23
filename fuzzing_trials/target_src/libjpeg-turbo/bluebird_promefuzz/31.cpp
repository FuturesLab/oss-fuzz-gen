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
#include <cstdio>
#include "../src/turbojpeg.h"

static void writeDummyFile(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) {
        return 0;
    }

    writeDummyFile(Data, Size);

    if (tj3DecompressHeader(handle, Data, Size) == 0) {
        // Using tj3Get and tj3Set with some hypothetical parameters

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of tj3Get
        int param1 = tj3Get(handle, TJFLAG_PROGRESSIVE);  // Example parameter
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        int param2 = tj3Get(handle, 1);
        int param3 = tj3Get(handle, 2);

        tj3Set(handle, 0, param1);
        int param4 = tj3Get(handle, 3);


        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of tj3Set
        tj3Set(handle, Size, param2);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        tj3Set(handle, 2, param3);
        tj3Set(handle, 3, param4);

        // Example scaling factors
        tjscalingfactor scalingFactor1 = {1, 8};
        tjscalingfactor scalingFactor2 = {1, 4};

        tj3SetScalingFactor(handle, scalingFactor1);
        tj3SetScalingFactor(handle, scalingFactor2);

        void *buffer = tj3Alloc(Size);
        if (buffer) {
            tj3Free(buffer);
        }
    }

    tj3Destroy(handle);
    return 0;
}