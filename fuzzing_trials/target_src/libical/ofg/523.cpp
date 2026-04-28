#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include the standard library for malloc and free

extern "C" {
    #include <libical/ical.h>  // Adjust the include path to the correct location of ical.h
}

extern "C" int LLVMFuzzerTestOneInput_523(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a non-empty string
    if (size == 0) {
        return 0;
    }

    // Initialize the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_VERSION_PROPERTY);

    // Create a null-terminated string from the input data
    char *version_str = (char *)malloc(size + 1);
    if (version_str == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(version_str, data, size);
    version_str[size] = '\0';

    // Call the function under test
    icalproperty_set_version(property, version_str);

    // Clean up
    free(version_str);
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

    LLVMFuzzerTestOneInput_523(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
