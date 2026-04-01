#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    // Assuming the necessary function prototypes from the libical project
    #include "libical/icalcomponent.h" // Adjust the path as needed for the actual project structure

    // Function prototype for the function-under-test
    icalcomponent * icalcomponent_new_x(const char *);
    void icalcomponent_free(icalcomponent *);
}

extern "C" int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0; // Exit early if there's no data to process
    }

    // Ensure the input data is null-terminated before passing it as a string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_x(input);

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component); // Free the component if it was successfully created
    }
    free(input);

    return 0;
}