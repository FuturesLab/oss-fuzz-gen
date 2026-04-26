#include <libical/ical.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_907(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *queryid = (char *)malloc(size + 1);
    if (queryid == NULL) {
        return 0;
    }
    memcpy(queryid, data, size);
    queryid[size] = '\0';

    // Call the function-under-test with more checks
    icalproperty *prop = icalproperty_vanew_queryid(queryid, NULL);

    // Check if the property was created successfully
    if (prop != NULL) {
        // Further exercise the property if needed
        const char *retrieved_queryid = icalproperty_get_queryid(prop);
        if (retrieved_queryid != NULL) {
            // Compare the original and retrieved queryid
            if (strcmp(queryid, retrieved_queryid) != 0) {
                // Handle the case where they differ, if needed
            }
        }

        // Clean up
        icalproperty_free(prop);
    }

    free(queryid);

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

    LLVMFuzzerTestOneInput_907(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
