// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalpvl_unshift at icalpvl.c:160:6 in icalpvl.h
// icalpvl_pop at icalpvl.c:234:7 in icalpvl.h
// icalpvl_push at icalpvl.c:206:6 in icalpvl.h
// icalpvl_free at icalpvl.c:110:6 in icalpvl.h
// icalpvl_clear at icalpvl.c:460:6 in icalpvl.h
// icalpvl_shift at icalpvl.c:189:7 in icalpvl.h
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
#include <cstring>
#include <cstdlib>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalpvl.h"

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void*)) {
        return 0;
    }

    icalpvl_list list = icalpvl_newlist();
    if (!list) {
        return 0;
    }

    // Use a portion of Data as a pointer value for list operations
    void *dataPointer = nullptr;
    memcpy(&dataPointer, Data, sizeof(void*));
    Data += sizeof(void*);
    Size -= sizeof(void*);

    // Fuzz different operations on the list
    icalpvl_unshift(list, dataPointer);
    icalpvl_push(list, dataPointer);

    void *shiftedData = icalpvl_shift(list);
    if (shiftedData != nullptr) {
        // Optionally do something with shiftedData
    }

    void *poppedData = icalpvl_pop(list);
    if (poppedData != nullptr) {
        // Optionally do something with poppedData
    }

    // Clear and free the list
    icalpvl_clear(list);
    icalpvl_free(list);

    return 0;
}
    #ifdef INC_MAIN
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    int main(int argc, char *argv[])
    {
        FILE *f;
        uint8_t *data = NULL;
        long size;

        if(argc < 2)
            exit(0);

        f = fopen(argv[1], "rb");
        if(f == NULL)
            exit(0);

        fseek(f, 0, SEEK_END);

        size = ftell(f);
        rewind(f);

        if(size < 1 + 1)
            exit(0);

        data = (uint8_t *)malloc((size_t)size);
        if(data == NULL)
            exit(0);

        if(fread(data, (size_t)size, 1, f) != 1)
            exit(0);

        LLVMFuzzerTestOneInput_59(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    