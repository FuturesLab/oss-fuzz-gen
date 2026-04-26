#include <cstdint>  // Include standard library for uint8_t
#include <cstddef>  // Include standard library for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a valid icalvalue
    if (size < 1) {
        return 0;
    }

    // Create an icalvalue object
    icalvalue *value = icalvalue_new(ICAL_NO_VALUE);

    // Check if the icalvalue was created successfully
    if (value == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalvalue_reset_kind(value);

    // Clean up the icalvalue object
    icalvalue_free(value);

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

    LLVMFuzzerTestOneInput_148(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
