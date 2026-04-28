#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1204(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to be used as a C-string
    char *refid = (char *)malloc(size + 1);
    if (refid == NULL) {
        return 0; // Exit if memory allocation fails
    }
    
    memcpy(refid, data, size);
    refid[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty *property = icalproperty_new_refid(refid);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    free(refid);

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

    LLVMFuzzerTestOneInput_1204(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
