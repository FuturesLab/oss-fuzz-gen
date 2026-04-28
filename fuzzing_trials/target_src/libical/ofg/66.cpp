#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and non-empty
    if (size == 0) return 0;

    // Allocate memory for the null-terminated string
    char *queryid = (char *)malloc(size + 1);
    if (queryid == NULL) return 0;

    // Copy data and null-terminate
    memcpy(queryid, data, size);
    queryid[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_queryid(queryid);

    // Check if the property was created successfully
    if (prop != NULL) {
        // Utilize the property to ensure code paths are exercised
        const char *retrieved_queryid = icalproperty_get_queryid(prop);
        
        // Compare the original and retrieved queryid to ensure correctness
        if (retrieved_queryid != NULL && strcmp(queryid, retrieved_queryid) == 0) {
            // Additional logic can be added here to further exercise the property
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

    LLVMFuzzerTestOneInput_66(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
