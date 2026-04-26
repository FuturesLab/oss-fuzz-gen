#include <cstdint> // Include for uint8_t

extern "C" {
    #include <libical/ical.h> // Include libical headers within extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_1224(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an enumeration value
    if (size < sizeof(icalproperty_taskmode)) {
        return 0;
    }

    // Cast the input data to the enumeration type
    icalproperty_taskmode taskmode = 
        static_cast<icalproperty_taskmode>(data[0] % (ICAL_TASKMODE_X + 1)); // Ensure valid enum range

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_taskmode(taskmode);

    // Clean up
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

    LLVMFuzzerTestOneInput_1224(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
