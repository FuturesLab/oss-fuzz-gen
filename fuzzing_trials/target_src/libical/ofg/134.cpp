#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalcomponent.h>
}

extern "C" int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to safely convert to a string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test with the fuzzed input
    icalcomponent *component = icalcomponent_new_x(null_terminated_data);

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }
    free(null_terminated_data);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_134(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
