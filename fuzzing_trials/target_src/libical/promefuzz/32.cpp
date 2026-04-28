// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icallangbind_quote_as_ical_r at icallangbind.c:282:7 in icallangbind.h
// icalmemory_tmp_copy at icalmemory.c:215:7 in icalmemory.h
// icallangbind_quote_as_ical at icallangbind.c:294:13 in icallangbind.h
// icalmemory_append_encoded_string at icalmemory.c:476:6 in icalmemory.h
// icalproperty_new_from_string at icalproperty.c:130:15 in icalproperty.h
// icalproperty_as_ical_string at icalproperty.c:352:13 in icalproperty.h
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
#include <icalmemory.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icallangbind.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalproperty.h>
#include <cstdint>
#include <cstring>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // 1. Test icalproperty_new_from_string
    char *ical_string = new char[Size + 1];
    memcpy(ical_string, Data, Size);
    ical_string[Size] = '\0';

    icalproperty *prop = icalproperty_new_from_string(ical_string);
    if (prop) {
        // 3. Test icalproperty_as_ical_string
        const char *ical_str = icalproperty_as_ical_string(prop);

        // 4. Test icallangbind_quote_as_ical
        const char *quoted_str = icallangbind_quote_as_ical(ical_str);

        // 5. Test icallangbind_quote_as_ical_r
        char *quoted_str_r = icallangbind_quote_as_ical_r(ical_str);

        // Cleanup
        if (quoted_str_r) {
            icalmemory_free_buffer(quoted_str_r);
        }

        icalproperty_free(prop);
    }

    // 6. Test icalmemory_append_encoded_string
    char *buffer = static_cast<char*>(malloc(Size * 2 + 1)); // Allocate a buffer using malloc
    char *pos = buffer;
    size_t buf_size = Size * 2 + 1;
    icalmemory_append_encoded_string(&buffer, &pos, &buf_size, ical_string);

    // 7. Test icalmemory_tmp_copy
    char *tmp_copy = icalmemory_tmp_copy(ical_string);

    // Cleanup
    delete[] ical_string;
    free(buffer); // Free the buffer using free

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

        LLVMFuzzerTestOneInput_32(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    