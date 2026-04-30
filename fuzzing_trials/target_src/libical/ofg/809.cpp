#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_809(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) {
        return 0;
    }

    // Initialize the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Use the data to create a null-terminated string for the permission
    size_t permission_length = size - 1;
    char permission[permission_length + 1];
    for (size_t i = 0; i < permission_length; ++i) {
        permission[i] = static_cast<char>(data[i]);
    }
    permission[permission_length] = '\0';

    // Call the function-under-test
    icalproperty_set_permission(property, permission);

    // Clean up
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

    LLVMFuzzerTestOneInput_809(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
