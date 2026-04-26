#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Added for malloc and free

extern "C" {
    #include <libical/icalproperty.h> // Correct header for libical
}

extern "C" int LLVMFuzzerTestOneInput_730(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated to be used as a string
    char *deny_string = (char *)malloc(size + 1);
    if (deny_string == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(deny_string, data, size);
    deny_string[size] = '\0';

    // Call the function-under-test
    icalproperty_set_deny(prop, deny_string);

    // Clean up
    free(deny_string);
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

    LLVMFuzzerTestOneInput_730(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
