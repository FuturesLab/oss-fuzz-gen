#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_481(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a status code
    if (size < sizeof(icalproperty_status)) {
        return 0;
    }

    // Extract a status code from the input data
    icalproperty_status status = static_cast<icalproperty_status>(data[0] % 6); // Assuming there are 6 possible statuses

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_status(status);

    // Clean up
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

    LLVMFuzzerTestOneInput_481(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
