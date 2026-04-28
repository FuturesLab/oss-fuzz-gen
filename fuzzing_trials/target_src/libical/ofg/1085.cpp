#include <cstdint> // For uint8_t
#include <cstddef> // For size_t
#include <cstring> // For memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1085(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    struct icaltimetype dtend;
    // Copy data into dtend ensuring no overflow
    memcpy(&dtend, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_dtend(dtend, nullptr);

    // Clean up
    if (prop != nullptr) {
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

    LLVMFuzzerTestOneInput_1085(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
