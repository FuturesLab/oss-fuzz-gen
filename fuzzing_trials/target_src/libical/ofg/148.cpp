#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create an icalcomponent from the input data
    icalcomponent *component = icalparser_parse_string(inputData);
    if (component != NULL) {
        // Call the function-under-test
        const char *uid = icalcomponent_get_uid(component);

        // Use the result in some way to prevent compiler optimizations from removing the call
        if (uid != NULL) {
            // For fuzzing purposes, we can simply print the UID or do nothing
            // printf("UID: %s\n", uid);
        }

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated input data
    free(inputData);

    return 0;
}