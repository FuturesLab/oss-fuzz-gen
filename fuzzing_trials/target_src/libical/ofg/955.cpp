#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_955(const uint8_t *data, size_t size) {
    // Ensure the input size is large enough to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the URL string
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        return 0;
    }

    // Copy the data into the URL string and null-terminate it
    memcpy(url, data, size);
    url[size] = '\0';

    // Create a new icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_URL_PROPERTY);
    if (prop == NULL) {
        free(url);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_url(prop, url);

    // Verify that the URL was set correctly
    const char *retrieved_url = icalproperty_get_url(prop);
    if (retrieved_url == NULL || strcmp(retrieved_url, url) != 0) {
        // If the URL was not set correctly, log an error or handle it as needed
        icalproperty_free(prop);
        free(url);
        return 0;
    }

    // Additional operations to increase code coverage
    // Serialize the property to a string and then parse it back
    const char *serialized = icalproperty_as_ical_string(prop);
    if (serialized != NULL) {
        icalproperty *parsed_prop = icalproperty_new_from_string(serialized);
        if (parsed_prop != NULL) {
            // Ensure the parsed property is valid
            icalproperty_free(parsed_prop);
        }
        // No need to free serialized as it is managed by libical
    }

    // Clean up
    icalproperty_free(prop);
    free(url);

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

    LLVMFuzzerTestOneInput_955(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
