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
#include <cstdint>
#include <cstddef>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
#include <cstring>
#include <cstdarg>
#include <cstdio>

static void test_icalcomponent_new() {
    for (int kind = ICAL_NO_COMPONENT; kind <= ICAL_NUM_COMPONENT_TYPES; ++kind) {
        icalcomponent *comp = icalcomponent_new(static_cast<icalcomponent_kind>(kind));
        if (comp) {
            icalcomponent_free(comp);
        }
    }
}

static void test_icalcomponent_new_vlocation() {
    icalcomponent *comp = icalcomponent_new_vlocation();
    if (comp) {
        icalcomponent_free(comp);
    }
}

static void test_icalcomponent_new_from_string(const char *str) {
    icalcomponent *comp = icalcomponent_new_from_string(str);
    if (comp) {
        icalcomponent_free(comp);
    }
}

static void test_icalcomponent_new_xvote() {
    icalcomponent *comp = icalcomponent_new_xvote();
    if (comp) {
        icalcomponent_free(comp);
    }
}

static void test_icalcomponent_vanew() {
    icalcomponent *comp = icalcomponent_vanew(ICAL_VEVENT_COMPONENT, NULL);
    if (comp) {
        icalcomponent_free(comp);
    }
}

static void test_icalcomponent_new_xpatch() {
    icalcomponent *comp = icalcomponent_new_xpatch();
    if (comp) {
        icalcomponent_free(comp);
    }
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Ensure null-termination for string input
    char *str = new char[Size + 1];
    memcpy(str, Data, Size);
    str[Size] = '\0';

    // Test various functions
    test_icalcomponent_new();
    test_icalcomponent_new_vlocation();
    test_icalcomponent_new_from_string(str);
    test_icalcomponent_new_xvote();
    test_icalcomponent_vanew();
    test_icalcomponent_new_xpatch();

    delete[] str;
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

    LLVMFuzzerTestOneInput_8(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
