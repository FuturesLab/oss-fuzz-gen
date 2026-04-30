#include <cstdint>
#include <cstdlib>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_202(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a valid enumeration value
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to determine the enumeration value
    icalproperty_pollcompletion pollcompletion_value = 
        static_cast<icalproperty_pollcompletion>(data[0] % 3);

    // Call the function-under-test
    icalproperty *property = icalproperty_new_pollcompletion(pollcompletion_value);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_202(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
