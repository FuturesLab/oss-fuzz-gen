// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalpvl_find at icalpvl.c:414:14 in icalpvl.h
// icalpvl_insert_before at icalpvl.c:327:6 in icalpvl.h
// icalpvl_remove at icalpvl.c:359:7 in icalpvl.h
// icalpvl_insert_after at icalpvl.c:297:6 in icalpvl.h
// icalpvl_newlist at icalpvl.c:90:14 in icalpvl.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalpvl.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_138(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void*)) return 0;

    // Create a new list
    icalpvl_list list = icalpvl_newlist();
    if (!list) return 0;

    // Prepare dummy data
    void *dummyData = malloc(Size);
    if (!dummyData) return 0;
    memcpy(dummyData, Data, Size);

    // Insert the dummy data into the list
    icalpvl_insert_after(list, nullptr, dummyData);

    // Find an element in the list, using a simple comparison function
    auto findFunc = [](void *context, void *data) -> int {
        return memcmp(context, data, sizeof(void*)) == 0;
    };
    icalpvl_elem foundElem = icalpvl_find(list, findFunc, dummyData);

    // Insert before and after the found element
    icalpvl_insert_before(list, foundElem, dummyData);
    icalpvl_insert_after(list, foundElem, dummyData);

    // Remove the found element
    if (foundElem) {
        icalpvl_remove(list, foundElem);
    }

    // Shift the first element
    void *shiftedData = icalpvl_shift(list);
    if (shiftedData && shiftedData != dummyData) {
        free(shiftedData);
    }

    // Cleanup
    free(dummyData);
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

        LLVMFuzzerTestOneInput_138(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    