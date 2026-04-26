#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_929(const uint8_t *data, size_t size) {
    // Ensure that size is at least 1 to create a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *grant_string = (char *)malloc(size + 1);
    if (grant_string == NULL) {
        return 0;
    }
    memcpy(grant_string, data, size);
    grant_string[size] = '\0';

    // Create a dummy non-null pointer for the second parameter
    void *dummy_void_ptr = (void *)grant_string;

    // Call the function-under-test with a sentinel value
    icalproperty *prop = icalproperty_vanew_grant(grant_string, dummy_void_ptr, nullptr);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }
    free(grant_string);

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

    LLVMFuzzerTestOneInput_929(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
