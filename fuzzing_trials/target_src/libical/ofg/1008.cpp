#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h> // Assuming the correct path to the libical headers

    // Include the necessary headers for the function-under-test
    void icalproperty_set_taskmode(icalproperty *, icalproperty_taskmode);
}

extern "C" int LLVMFuzzerTestOneInput_1008(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract a task mode
    if (size < sizeof(icalproperty_taskmode)) {
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Extract a task mode from the input data
    icalproperty_taskmode taskmode = 
        static_cast<icalproperty_taskmode>(data[0] % ICAL_TASKMODE_X);

    // Call the function-under-test
    icalproperty_set_taskmode(property, taskmode);

    // Clean up the icalproperty object
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_1008(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
