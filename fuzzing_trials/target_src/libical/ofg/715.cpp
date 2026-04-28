#include <cstdint>
#include <cstddef>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_715(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for our needs
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer value from the input data
    int repeat_value = *(reinterpret_cast<const int*>(data));

    // Use the remaining data as a void pointer
    void *extra_data = (void*)(data + sizeof(int));

    // Call the function-under-test with a sentinel value
    icalproperty *prop = icalproperty_vanew_repeat(repeat_value, extra_data, nullptr);

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

    LLVMFuzzerTestOneInput_715(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
