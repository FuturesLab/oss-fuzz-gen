#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_834(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to be used meaningfully
    if (size < 1) {
        return 0;
    }

    // Create a buffer to hold the input data as a string
    char *inputData = (char *)malloc(size + 1);
    if (!inputData) {
        return 0;
    }

    // Copy the input data and null-terminate it
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into an icalproperty
    icalproperty *prop = icalproperty_new_from_string(inputData);
    if (prop != NULL) {
        // Call the function-under-test
        const char *uid = icalproperty_get_uid(prop);

        // Use the result (in a real fuzzing scenario, you might want to do more checks)
        if (uid != NULL) {
            // For demonstration purposes, we simply print the UID
            // In practice, this print statement would be removed or replaced with assertions
            printf("UID: %s\n", uid);
        }

        // Clean up
        icalproperty_free(prop);
    }

    // Free the allocated input data
    free(inputData);

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

    LLVMFuzzerTestOneInput_834(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
