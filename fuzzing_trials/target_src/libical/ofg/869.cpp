#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_869(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to be used as a string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *query_name = (char *)malloc(size + 1);
    if (query_name == NULL) {
        return 0;
    }
    memcpy(query_name, data, size);
    query_name[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_queryname(query_name, NULL);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    free(query_name);

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

    LLVMFuzzerTestOneInput_869(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
