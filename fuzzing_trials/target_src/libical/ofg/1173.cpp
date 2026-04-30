extern "C" {
    #include <libical/ical.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput_1173(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        return 0;
    }

    memcpy(str, data, size);
    str[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_defaulttzid(str, nullptr);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }
    free(str);

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

    LLVMFuzzerTestOneInput_1173(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
