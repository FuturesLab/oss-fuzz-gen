#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Assuming the correct path to the ical.h file
}

extern "C" int LLVMFuzzerTestOneInput_922(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 1) {
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_RELCALID_PROPERTY);
    
    // Create a temporary buffer to store a string from the input data
    char buffer[256];
    size_t copy_size = size < sizeof(buffer) - 1 ? size : sizeof(buffer) - 1;
    memcpy(buffer, data, copy_size);
    buffer[copy_size] = '\0'; // Null-terminate the string

    // Set the relcalid property using the buffer
    icalproperty_set_relcalid(prop, buffer);

    // Call the function-under-test
    const char *relcalid = icalproperty_get_relcalid(prop);

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_922(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
