#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_700(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for string operations
    if (size == 0) {
        return 0; // Exit early if size is 0 to avoid unnecessary processing
    }

    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_xlicmimecid(null_terminated_data);

    // Additional processing to increase code coverage
    if (prop != NULL) {
        // Access some properties to ensure more code paths are executed
        const char *cid = icalproperty_get_xlicmimecid(prop);
        if (cid != NULL) {
            // Perform some operations with cid to ensure it's being used
            size_t cid_length = strlen(cid);
            if (cid_length > 0) {
                // Example operation: check if cid starts with a specific prefix
                if (strncmp(cid, "prefix", 6) == 0) {
                    // Do something if it matches
                }
            }
        }
        icalproperty_free(prop);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_700(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
