#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid icalproperty
    if (size == 0) {
        return 0;
    }

    // Create a temporary string from the input data
    char *tempStr = (char *)malloc(size + 1);
    if (tempStr == NULL) {
        return 0;
    }
    memcpy(tempStr, data, size);
    tempStr[size] = '\0';

    // Create an icalproperty from the string
    icalproperty *prop = icalproperty_new_from_string(tempStr);
    free(tempStr);

    if (prop != NULL) {
        // Call the function-under-test
        icalproperty_pollmode pollmode = icalproperty_get_pollmode(prop);

        // Clean up
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

    LLVMFuzzerTestOneInput_155(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
