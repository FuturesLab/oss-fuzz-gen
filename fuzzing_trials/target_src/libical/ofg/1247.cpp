#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1247(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    int percent_complete = 0;

    // Ensure the data is large enough to extract an integer
    if (size >= sizeof(int)) {
        // Copy data into percent_complete, ensuring no overflow
        percent_complete = *((const int *)data);
    }

    // Call the function-under-test
    icalproperty_set_percentcomplete(property, percent_complete);

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

    LLVMFuzzerTestOneInput_1247(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
