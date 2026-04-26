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
#include <cstdlib>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalrecur.h"

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a new icalrecurrencetype instance
    struct icalrecurrencetype *recur = icalrecurrencetype_new();
    if (!recur) return 0;

    // Fuzz icalrecurrencetype_ref
    icalrecurrencetype_ref(recur);

    // Convert recurrence type to string
    char *recurStr = icalrecurrencetype_as_string(recur);
    if (recurStr) {
        // Fuzz icalrecurrencetype_new_from_string
        struct icalrecurrencetype *newRecur = icalrecurrencetype_new_from_string(recurStr);
        if (newRecur) {
            // Fuzz icalrecurrencetype_as_string_r
            char *recurStrR = icalrecurrencetype_as_string_r(newRecur);
            if (recurStrR) {
                free(recurStrR);
            }
            icalrecurrencetype_unref(newRecur);
        }
        free(recurStr);
    }

    // Fuzz icalrecurrencetype_unref
    icalrecurrencetype_unref(recur);

    // Use the input data to create a string and fuzz icalrecurrencetype_new_from_string
    char *inputStr = static_cast<char*>(malloc(Size + 1));
    if (inputStr) {
        memcpy(inputStr, Data, Size);
        inputStr[Size] = '\0';

        struct icalrecurrencetype *inputRecur = icalrecurrencetype_new_from_string(inputStr);
        if (inputRecur) {
            char *inputRecurStr = icalrecurrencetype_as_string_r(inputRecur);
            if (inputRecurStr) {
                free(inputRecurStr);
            }
            icalrecurrencetype_unref(inputRecur);
        }
        free(inputStr);
    }

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

    LLVMFuzzerTestOneInput_28(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
