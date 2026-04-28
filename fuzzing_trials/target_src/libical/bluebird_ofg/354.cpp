#include <string.h>
#include <sys/stat.h>
#include "libical/ical.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_354(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an integer and at least one character
    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Extract an integer from the input data
    int tzoffsetto = *(reinterpret_cast<const int*>(data));

    // Create a buffer for the second parameter, ensuring it is null-terminated
    // Allocate a larger buffer to avoid overflow
    const size_t buffer_size = 256; // Arbitrary size, large enough for testing
    char dummy_param[buffer_size] = {0};
    
    // Copy data into dummy_param ensuring it does not exceed buffer_size - 1
    size_t copy_size = (size - sizeof(int) < buffer_size - 1) ? size - sizeof(int) : buffer_size - 1;
    std::memcpy(dummy_param, data + sizeof(int), copy_size);
    dummy_param[copy_size] = '\0'; // Ensure null-termination

    // Check if dummy_param is a valid string for the function
    if (dummy_param[0] == '\0') {
        return 0;
    }

    // Ensure dummy_param is a valid string for the function
    // Check if dummy_param is a valid UTF-8 string to prevent issues in the function-under-test
    bool is_valid_utf8 = true;
    for (size_t i = 0; i < copy_size; ++i) {
        if ((dummy_param[i] & 0x80) == 0) {
                continue;
        } // ASCII
        if ((dummy_param[i] & 0xE0) == 0xC0) { // 2-byte sequence
            if (i + 1 >= copy_size || (dummy_param[i+1] & 0xC0) != 0x80) {
                is_valid_utf8 = false;
                break;
            }
            i += 1;
        } else if ((dummy_param[i] & 0xF0) == 0xE0) { // 3-byte sequence
            if (i + 2 >= copy_size || (dummy_param[i+1] & 0xC0) != 0x80 || (dummy_param[i+2] & 0xC0) != 0x80) {
                is_valid_utf8 = false;
                break;
            }
            i += 2;
        } else if ((dummy_param[i] & 0xF8) == 0xF0) { // 4-byte sequence
            if (i + 3 >= copy_size || (dummy_param[i+1] & 0xC0) != 0x80 || (dummy_param[i+2] & 0xC0) != 0x80 || (dummy_param[i+3] & 0xC0) != 0x80) {
                is_valid_utf8 = false;
                break;
            }
            i += 3;
        } else {
            is_valid_utf8 = false;
            break;
        }
    }

    if (!is_valid_utf8) {
        return 0;
    }

    // Call the function-under-test
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalproperty_vanew_tzoffsetto with icalproperty_new_pollwinner
    icalproperty *prop = icalproperty_new_pollwinner(tzoffsetto);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR

    // Clean up if necessary
    if (prop != NULL) {
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_354(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
