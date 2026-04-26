extern "C" {
    #include <libical/ical.h>
    #include <stdint.h>
    #include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create at least one icalattach object
    if (size == 0) {
        return 0;
    }

    // Create a new icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Define a dummy free function
    auto dummy_free_fn = [](char *data, void *user_data) {
        // No-op free function
    };

    // Create a new icalattach object using the provided data
    icalattach *attachment = icalattach_new_from_data((const char *)data, dummy_free_fn, NULL);
    if (attachment == NULL) {
        icalproperty_free(property);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_structureddata(property, attachment);

    // Clean up
    icalattach_unref(attachment);
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

    LLVMFuzzerTestOneInput_132(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
