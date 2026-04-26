#include <sys/stat.h>
#include <string.h>
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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalattach.h"
}

#include <cstdint>
#include <cstring>
#include <cstdlib>

static void free_data(char *data, void *free_fn_data) {
    free(data);
}

extern "C" int LLVMFuzzerTestOneInput_294(const uint8_t *Data, size_t Size) {
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_294(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
