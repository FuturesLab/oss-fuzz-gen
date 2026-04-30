// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalattach_get_data at icalattach.c:125:16 in icalattach.h
// icalattach_unref at icalattach.c:90:6 in icalattach.h
// icalattach_new_from_url at icalattach.c:20:13 in icalattach.h
// icalattach_new_from_data at icalattach.c:51:13 in icalattach.h
// icalattach_get_url at icalattach.c:117:13 in icalattach.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalattach.h"
}

#include <cstdint>
#include <cstring>
#include <cstdlib>

static void free_data(char *data, void *free_fn_data) {
    free(data);
}

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a URL string from the input data
    char *url = static_cast<char *>(malloc(Size + 1));
    if (!url) return 0;
    memcpy(url, Data, Size);
    url[Size] = '\0';

    // Test icalattach_new_from_url
    icalattach *attach_url = icalattach_new_from_url(url);
    if (attach_url) {
        if (icalattach_get_is_url(attach_url)) {
            const char *retrieved_url = icalattach_get_url(attach_url);
            if (retrieved_url) {
                // Do something with the URL
            }
        }
        icalattach_unref(attach_url);
    }

    // Test icalattach_new_from_data
    char *data = static_cast<char *>(malloc(Size + 1));
    if (!data) {
        free(url);
        return 0;
    }
    memcpy(data, Data, Size);
    data[Size] = '\0';

    icalattach *attach_data = icalattach_new_from_data(data, free_data, nullptr);
    if (attach_data) {
        unsigned char *retrieved_data = icalattach_get_data(attach_data);
        if (retrieved_data) {
            // Do something with the data
        }
        icalattach_unref(attach_data);
    }

    free(url);
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

        LLVMFuzzerTestOneInput_75(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    