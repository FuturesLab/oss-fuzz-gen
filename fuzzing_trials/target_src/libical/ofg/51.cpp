#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create an icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalproperty for testing
    icalproperty *prop = icalproperty_new_transp((icalproperty_transp)(data[0] % ICAL_TRANSP_X));

    // Check if the property was created successfully
    if (!prop) {
        return 0;
    }

    // Call the function-under-test
    icalproperty_transp result = icalproperty_get_transp(prop);

    // Use the result to ensure the code is not optimized away
    if (result == ICAL_TRANSP_OPAQUE || result == ICAL_TRANSP_TRANSPARENT) {
        // Do something with the result if needed
    }

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

    LLVMFuzzerTestOneInput_51(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
