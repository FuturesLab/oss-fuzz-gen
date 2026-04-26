#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_921(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be meaningful
    if (size < 1) {
        return 0;
    }

    // Create an icalproperty object from the input data
    // For fuzzing purposes, we'll assume the data is a string
    char *dataStr = (char *)malloc(size + 1);
    if (dataStr == NULL) {
        return 0;
    }
    memcpy(dataStr, data, size);
    dataStr[size] = '\0';

    icalproperty *prop = icalproperty_new_from_string(dataStr);

    if (prop != NULL) {
        // Call the function under test
        const char *relcalid = icalproperty_get_relcalid(prop);

        // Use the result in some way to avoid optimizing it out
        if (relcalid != NULL) {
            // Simple check to use the result
            volatile size_t len = strlen(relcalid);
            (void)len; // Suppress unused variable warning
        }

        // Clean up
        icalproperty_free(prop);
    }

    free(dataStr);
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

    LLVMFuzzerTestOneInput_921(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
