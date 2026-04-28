#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_784(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract an integer.
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data.
    int response_code = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test with the extracted integer.
    icalproperty *property = icalproperty_new_response(response_code);

    // Clean up the created icalproperty object to prevent memory leaks.
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

    LLVMFuzzerTestOneInput_784(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
