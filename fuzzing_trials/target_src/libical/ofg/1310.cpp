#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_1310(const uint8_t *data, size_t size) {
    // Create a dummy icalproperty structure
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure that the property is not NULL
    if (prop == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *permission = icalproperty_get_permission(prop);

    // Perform any necessary cleanup
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

    LLVMFuzzerTestOneInput_1310(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
