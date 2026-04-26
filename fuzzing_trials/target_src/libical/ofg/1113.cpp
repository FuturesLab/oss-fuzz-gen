#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Added for malloc and free

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for ical.h
}

extern "C" int LLVMFuzzerTestOneInput_1113(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *url = (char *)malloc(size + 1);
    if (url == NULL) {
        return 0;
    }
    memcpy(url, data, size);
    url[size] = '\0';

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        free(url);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_replyurl(prop, url);

    // Check if the URL was set correctly
    const char *retrieved_url = icalproperty_get_replyurl(prop);
    if (retrieved_url != NULL && strcmp(retrieved_url, url) == 0) {
        // The URL was set and retrieved correctly
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

    LLVMFuzzerTestOneInput_1113(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
