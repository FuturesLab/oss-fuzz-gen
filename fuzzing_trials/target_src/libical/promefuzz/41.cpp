// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalattach_new_from_url at icalattach.c:20:13 in icalattach.h
// icalattach_get_url at icalattach.c:117:13 in icalattach.h
// icalattach_new_from_data at icalattach.c:51:13 in icalattach.h
// icalattach_ref at icalattach.c:82:6 in icalattach.h
// icalattach_unref at icalattach.c:90:6 in icalattach.h
// icalattach_get_is_url at icalattach.c:110:6 in icalattach.h
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

#include <cstddef>
#include <cstdint>
#include <cstring>

static void free_fn(char *data, void *free_fn_data) {
    // Custom free function for icalattach_new_from_data
    if (data) {
        free(data);
    }
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *url = static_cast<char *>(malloc(Size + 1));
    if (!url) {
        return 0;
    }
    memcpy(url, Data, Size);
    url[Size] = '\0';

    // Test icalattach_new_from_url
    icalattach *attach_url = icalattach_new_from_url(url);
    if (attach_url) {
        bool is_url = icalattach_get_is_url(attach_url);
        if (is_url) {
            const char *retrieved_url = icalattach_get_url(attach_url);
            if (retrieved_url) {
                // Compare with the original URL
                (void)strcmp(retrieved_url, url);
            }
        }
        icalattach_unref(attach_url);
    }

    // Test icalattach_new_from_data
    char *data = static_cast<char *>(malloc(Size));
    if (data) {
        memcpy(data, Data, Size);
        icalattach *attach_data = icalattach_new_from_data(data, free_fn, nullptr);
        if (attach_data) {
            icalattach_ref(attach_data);
            icalattach_unref(attach_data);
            icalattach_unref(attach_data); // This should free the attach_data
        } else {
            free(data); // Free manually if attach creation failed
        }
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

        LLVMFuzzerTestOneInput_41(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    