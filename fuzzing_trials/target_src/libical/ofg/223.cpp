#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to create a meaningful input
    if (size == 0) {
        return 0;
    }

    // Declare and initialize the parameters for icalproperty_set_image
    icalproperty *prop = icalproperty_new(ICAL_ATTACH_PROPERTY);

    // Define a dummy free function as the second argument
    auto dummy_free_fn = [](char *data, void *user_data) {
        // No specific free operation needed
    };

    // Ensure the data is null-terminated for safety
    char *data_copy = (char *)malloc(size + 1);
    if (data_copy == NULL) {
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    icalattach *attach = icalattach_new_from_data(data_copy, dummy_free_fn, NULL);

    // Call the function-under-test
    icalproperty_set_attach(prop, attach);

    // Clean up
    icalproperty_free(prop);
    icalattach_unref(attach);

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

    LLVMFuzzerTestOneInput_223(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
