#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_410(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the string and ensure it's null-terminated
    char *tzname = static_cast<char *>(malloc(size + 1));
    if (tzname == nullptr) {
        return 0;
    }
    memcpy(tzname, data, size);
    tzname[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_tzname(tzname, nullptr);

    // Clean up
    if (prop != nullptr) {
        icalproperty_free(prop);
    }
    free(tzname);

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

    LLVMFuzzerTestOneInput_410(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
