#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_860(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be used as a string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *relcalid = (char *)malloc(size + 1);
    if (relcalid == NULL) {
        return 0;
    }
    memcpy(relcalid, data, size);
    relcalid[size] = '\0';

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_RELCALID_PROPERTY);
    if (prop == NULL) {
        free(relcalid);
        return 0;
    }

    // Call the function under test
    icalproperty_set_relcalid(prop, relcalid);

    // Additional check to ensure the property is set correctly
    const char *retrieved_relcalid = icalproperty_get_relcalid(prop);
    if (retrieved_relcalid == NULL || strcmp(retrieved_relcalid, relcalid) != 0) {
        // If the retrieved value does not match, it indicates an issue
        icalproperty_free(prop);
        free(relcalid);
        return 0;
    }

    // Clean up
    icalproperty_free(prop);
    free(relcalid);

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

    LLVMFuzzerTestOneInput_860(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
