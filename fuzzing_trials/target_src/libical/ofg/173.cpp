#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h> // Correct path for the libical header

    // Ensure all C headers and functions are wrapped with extern "C"
    icalcomponent_kind icalcomponent_string_to_kind(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely use it as a C-string
    char *inputStr = (char *)malloc(size + 1);
    if (inputStr == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(inputStr, data, size);
    inputStr[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalcomponent_kind kind = icalcomponent_string_to_kind(inputStr);

    // Clean up allocated memory
    free(inputStr);

    return 0;
}