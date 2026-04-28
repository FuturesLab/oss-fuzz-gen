#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_472(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to prevent buffer overflow
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Handle memory allocation failure
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create a new icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(null_terminated_data);

    if (component != NULL) {
        // Call the function-under-test
        const char *uid = icalcomponent_get_uid(component);

        // Perform any necessary checks or operations with the returned UID
        if (uid != NULL) {
            // For this fuzzing harness, we'll just ensure the UID is accessed
            // In a real fuzzing scenario, additional checks or logging might be performed
        }

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated memory for null-terminated data
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

    LLVMFuzzerTestOneInput_472(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
