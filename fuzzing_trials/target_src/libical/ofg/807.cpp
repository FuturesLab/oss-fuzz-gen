#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_807(const uint8_t *data, size_t size) {
    // Ensure that the data is large enough to be used
    if (size < 1) { // Adjusted to ensure we have at least some data
        return 0;
    }

    // Create a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_TZOFFSETFROM_PROPERTY);
    if (!prop) {
        return 0; // Return if property creation failed
    }

    // Set the tzoffsetfrom property using the provided data
    int32_t tzoffset = static_cast<int32_t>(data[0]); // Use the first byte of data
    icalproperty_set_tzoffsetfrom(prop, tzoffset);

    // Call the function-under-test
    int offset = icalproperty_get_tzoffsetfrom(prop);

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

    LLVMFuzzerTestOneInput_807(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
