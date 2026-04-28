#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Ensure the size is at least large enough to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the data
    int patch_order = *(reinterpret_cast<const int*>(data));

    // Ensure the remaining data is large enough for a valid string
    if (size <= sizeof(int) + 1) {
        return 0;
    }

    // Extract a string from the remaining data
    const char* valid_string = reinterpret_cast<const char*>(data + sizeof(int));
    size_t string_length = size - sizeof(int);

    // Ensure the string is null-terminated
    char* valid_string_copy = static_cast<char*>(malloc(string_length + 1));
    if (!valid_string_copy) {
        return 0;
    }
    memcpy(valid_string_copy, valid_string, string_length);
    valid_string_copy[string_length] = '\0';

    // Check if the string is not empty to avoid passing an empty string
    if (valid_string_copy[0] == '\0') {
        free(valid_string_copy);
        return 0;
    }

    // Create a valid void* parameter
    void* valid_ptr = reinterpret_cast<void*>(valid_string_copy);

    // Call the function-under-test
    icalproperty* prop = icalproperty_vanew_patchorder(patch_order, valid_ptr, nullptr);

    // Clean up if necessary
    if (prop != nullptr) {
        icalproperty_free(prop);
    }
    free(valid_string_copy);

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

    LLVMFuzzerTestOneInput_67(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
