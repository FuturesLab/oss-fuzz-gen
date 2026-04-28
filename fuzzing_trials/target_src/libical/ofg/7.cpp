#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <cstring> // Include the C++ header for memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    // Ensure that the size of data is sufficient to create an icaltriggertype
    if (size < sizeof(struct icaltriggertype)) {
        return 0;
    }

    // Initialize an icaltriggertype from the input data
    struct icaltriggertype trigger;
    memcpy(&trigger, data, sizeof(struct icaltriggertype));

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_trigger(trigger, nullptr);

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

    LLVMFuzzerTestOneInput_7(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
