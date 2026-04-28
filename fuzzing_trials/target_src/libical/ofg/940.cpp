#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_940(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input string and copy the data
    char *contentType = (char *)malloc(size + 1);
    if (contentType == nullptr) {
        return 0;
    }
    memcpy(contentType, data, size);
    contentType[size] = '\0'; // Null-terminate the string

    // Create a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_NO_PROPERTY);
    if (prop == nullptr) {
        free(contentType);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_xlicmimecontenttype(prop, contentType);

    // Clean up
    icalproperty_free(prop);
    free(contentType);

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

    LLVMFuzzerTestOneInput_940(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
