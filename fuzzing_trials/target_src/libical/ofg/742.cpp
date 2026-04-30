#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
    #include <libical/icalproperty.h>
}

// Use the existing enumeration type from libical
extern "C" int LLVMFuzzerTestOneInput_742(const uint8_t *data, size_t size) {
    // Ensure we have enough data to select an enumeration value
    if (size < 1) return 0;

    // Map the first byte of data to a valid enumeration value
    icalproperty_xlicclass xlicclass = 
        static_cast<icalproperty_xlicclass>(data[0] % 20);

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_xlicclass(xlicclass);

    // Clean up if necessary
    if (prop != NULL) {
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_742(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
