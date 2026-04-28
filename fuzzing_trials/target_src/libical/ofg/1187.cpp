#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_1187(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_url(url, NULL);

    // Additional operations to ensure code coverage
    if (prop != NULL) {
        // Retrieve the URL from the property to ensure the property was set correctly
        const char *retrieved_url = icalproperty_get_url(prop);
        if (retrieved_url != NULL) {
            // Perform a simple check to simulate usage
            if (strcmp(url, retrieved_url) == 0) {
                // URLs match, perform further operations if needed
            }
        }
        // Free the property after use
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

    LLVMFuzzerTestOneInput_1187(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
