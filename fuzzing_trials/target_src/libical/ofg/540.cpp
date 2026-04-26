#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_540(const uint8_t *data, size_t size) {
    // Ensure the input size is non-zero and within a reasonable limit
    if (size == 0 || size > 1024) {
        return 0;
    }

    // Allocate memory for the string and ensure it is null-terminated
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        return 0;
    }

    // Copy the input data to the name buffer
    memcpy(name, data, size);
    name[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    icalproperty *property = icalproperty_new_name(name);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    free(name);

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

    LLVMFuzzerTestOneInput_540(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
