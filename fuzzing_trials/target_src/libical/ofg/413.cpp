#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_413(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create an icalproperty_resourcetype value
    if (size < sizeof(icalproperty_resourcetype)) {
        return 0;
    }

    // Cast the input data to an icalproperty_resourcetype
    icalproperty_resourcetype resourcetype = static_cast<icalproperty_resourcetype>(data[0]);

    // Call the function under test
    const char *result = icalproperty_resourcetype_to_string(resourcetype);

    // Use the result to prevent it from being optimized away
    if (result != NULL) {
        volatile const char *volatile_result = result;
        (void)volatile_result;
    }

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

    LLVMFuzzerTestOneInput_413(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
