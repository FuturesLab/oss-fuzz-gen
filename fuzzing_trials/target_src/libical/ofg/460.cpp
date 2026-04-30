#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <cstring> // Include the C++ header for strlen

extern "C" {
    // Ensure all C headers and functions are wrapped in extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_460(const uint8_t *data, size_t size) {
    // Ensure we have enough data to form a valid icalproperty_kind value
    if (size < sizeof(icalproperty_kind)) {
        return 0;
    }

    // Extract icalproperty_kind from data
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0]);

    // Call the function-under-test
    const char *result = icalproperty_kind_to_string(kind);

    // Use the result in some way to avoid compiler optimizations
    if (result != nullptr) {
        volatile size_t len = std::strlen(result); // Use std::strlen from <cstring>
        (void)len;
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

    LLVMFuzzerTestOneInput_460(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
