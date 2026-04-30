#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1225(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract a valid enumeration value
    if (size < sizeof(icalproperty_taskmode)) {
        return 0;
    }

    // Extract a icalproperty_taskmode value from the input data
    icalproperty_taskmode taskmode = 
        static_cast<icalproperty_taskmode>(data[0] % 4); // Assuming there are 4 valid enum values

    // Call the function-under-test
    icalproperty *property = icalproperty_new_taskmode(taskmode);

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

    LLVMFuzzerTestOneInput_1225(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
