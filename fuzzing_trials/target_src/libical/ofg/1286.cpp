#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1286(const uint8_t *data, size_t size) {
    // Ensure the data is not empty and is null-terminated to be used as a C string
    if (size == 0) return 0;

    // Allocate memory for the string and ensure null-termination
    char *uid_str = (char *)malloc(size + 1);
    if (uid_str == NULL) return 0; // Allocation failed

    memcpy(uid_str, data, size);
    uid_str[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty *property = icalproperty_new_uid(uid_str);

    // Check if property was created successfully
    if (property != NULL) {
        // Perform additional operations to increase code coverage
        const char *retrieved_uid = icalproperty_get_uid(property);
        if (retrieved_uid != NULL) {
            // Further processing or validation can be done here if needed
            // For example, check if the retrieved UID matches the input
            if (strcmp(uid_str, retrieved_uid) == 0) {
                // The UID was set and retrieved correctly
            }
        }
        
        // Clean up
        icalproperty_free(property);
    }

    free(uid_str);

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

    LLVMFuzzerTestOneInput_1286(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
