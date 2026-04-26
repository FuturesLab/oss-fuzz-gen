#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_859(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to avoid passing a NULL pointer
    if (size == 0) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_RELCALID_PROPERTY);

    // Ensure the data is null-terminated for use as a C string
    char *relcalid = (char *)malloc(size + 1);
    if (relcalid == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(relcalid, data, size);
    relcalid[size] = '\0';

    // Call the function-under-test
    icalproperty_set_relcalid(prop, relcalid);

    // Clean up
    free(relcalid);
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_859(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
