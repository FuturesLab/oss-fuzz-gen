#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <cstring> // Include this for memcpy

extern "C" {
    #include "/src/libical/src/libical/icalproperty.h"
    #include "/src/libical/src/libical/icalderivedproperty.h"
}

extern "C" int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    // Remove the size check based on sizeof(icalproperty) since icalproperty is an incomplete type
    // Instead, ensure that the data is null-terminated before passing it to icalproperty_new_from_string
    char *null_terminated_data = new char[size + 1];
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create an icalproperty object from the input data
    icalproperty *property = icalproperty_new_from_string(null_terminated_data);

    delete[] null_terminated_data;

    if (property != NULL) {
        // Call the function-under-test
        icalproperty_querylevel query_level = icalproperty_get_querylevel(property);

        // Clean up
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

    LLVMFuzzerTestOneInput_223(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
