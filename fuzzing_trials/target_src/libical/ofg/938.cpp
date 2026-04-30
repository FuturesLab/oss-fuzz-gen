#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_938(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int pollwinner_value = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        pollwinner_value |= data[i] << (i * 8);
    }

    // Call the function-under-test
    icalproperty *property = icalproperty_new_pollwinner(pollwinner_value);

    // Perform any necessary cleanup
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

    LLVMFuzzerTestOneInput_938(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
