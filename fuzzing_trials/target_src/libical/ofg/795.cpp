#include <libical/ical.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

extern "C" int LLVMFuzzerTestOneInput_795(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Ensure the data is null-terminated to be used as a string
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(url, data, size);
    url[size] = '\0'; // Null-terminate the string

    // Check if the URL starts with a valid scheme
    if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) {
        free(url);
        return 0; // Skip processing if it's not a valid URL format
    }

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_url(url);

    // Use the property in a meaningful way
    if (prop != NULL) {
        // Example: Get the URL value back from the property
        const char *retrieved_url = icalproperty_get_url(prop);
        if (retrieved_url != NULL) {
            // Perform some operation with retrieved_url if needed
            // For example, compare it with the original URL
            if (strcmp(retrieved_url, url) != 0) {
                // Log or handle the mismatch if necessary
            }
        }
        icalproperty_free(prop);
    }

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

    LLVMFuzzerTestOneInput_795(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
