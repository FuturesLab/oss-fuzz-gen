#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" {
    // Include the necessary header for the enumeration type
    #include <libical/icalproperty.h>

    // Forward declaration of the function-under-test
    icalproperty* icalproperty_new_xlicclass(icalproperty_xlicclass xlicclass);
}

extern "C" int LLVMFuzzerTestOneInput_741(const uint8_t *data, size_t size) {
    // Ensure the input size is appropriate for the enumeration type
    if (size < sizeof(icalproperty_xlicclass)) {
        return 0;
    }

    // Cast the input data to the enumeration type
    icalproperty_xlicclass xlicclass = 
        static_cast<icalproperty_xlicclass>(data[0]);

    // Call the function-under-test
    icalproperty *property = icalproperty_new_xlicclass(xlicclass);

    // Perform cleanup if necessary
    if (property != NULL) {
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_741(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
