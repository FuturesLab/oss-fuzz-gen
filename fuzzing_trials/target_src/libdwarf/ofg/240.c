#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Assuming Dwarf_Cmdline_Options is a struct, define it accordingly
typedef struct {
    char *option1;
    int option2;
    double option3;
} Dwarf_Cmdline_Options;

// Placeholder for the actual function-under-test
void dwarf_record_cmdline_options(Dwarf_Cmdline_Options options);

int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
    // Ensure there's enough data to initialize the struct
    if (size < sizeof(int) + sizeof(double) + 1) {
        return 0;
    }

    Dwarf_Cmdline_Options options;
    
    // Initialize option1 as a string from the data
    size_t option1_len = size - sizeof(int) - sizeof(double);
    options.option1 = (char *)malloc(option1_len + 1);
    if (options.option1 == NULL) {
        return 0;
    }
    memcpy(options.option1, data, option1_len);
    options.option1[option1_len] = '\0'; // Null-terminate the string

    // Initialize option2 as an integer from the data
    options.option2 = *((int *)(data + option1_len));

    // Initialize option3 as a double from the data
    options.option3 = *((double *)(data + option1_len + sizeof(int)));

    // Call the function-under-test
    dwarf_record_cmdline_options(options);

    // Clean up
    free(options.option1);

    return 0;
}