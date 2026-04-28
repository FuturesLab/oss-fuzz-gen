#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1251(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0; // Failed to create property, exit
    }

    // Create a null-terminated string from the input data
    char *scope = (char *)malloc(size + 1);
    if (scope == NULL) {
        icalproperty_free(prop);
        return 0; // Failed to allocate memory, exit
    }
    memcpy(scope, data, size);
    scope[size] = '\0';

    // Call the function-under-test
    icalproperty_set_scope(prop, scope);

    // Additional operations to increase code coverage
    icalproperty_kind kind = icalproperty_isa(prop);
    if (kind != ICAL_NO_PROPERTY) {
        const char *scope_value = icalproperty_get_scope(prop);
        if (scope_value != NULL) {
            // Perform some operation or validation on scope_value
            // This ensures the function is being utilized
        }
    }

    // Clean up
    free(scope);
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

    LLVMFuzzerTestOneInput_1251(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
