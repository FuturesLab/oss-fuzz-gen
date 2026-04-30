#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string for icalattach
    if (size == 0) return 0;

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_IMAGE_PROPERTY);
    if (prop == NULL) return 0;

    // Create a buffer to hold the data for icalattach
    char *attach_data = (char *)malloc(size + 1);
    if (attach_data == NULL) {
        icalproperty_free(prop);
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(attach_data, data, size);
    attach_data[size] = '\0';

    // Define a custom free function that matches the expected signature
    auto custom_free = [](char *data, void *user_data) {
        free(data);
    };

    // Create an icalattach object using the data
    icalattach *attachment = icalattach_new_from_data(attach_data, custom_free, NULL);
    if (attachment == NULL) {
        free(attach_data);
        icalproperty_free(prop);
        return 0;
    }

    // Call the function under test
    icalproperty_set_image(prop, attachment);

    // Clean up
    icalattach_unref(attachment);
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

    LLVMFuzzerTestOneInput_224(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
