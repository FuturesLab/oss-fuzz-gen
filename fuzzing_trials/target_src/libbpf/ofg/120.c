#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Assuming the definition of DW_TAG_enumeration_typebpf_attach_type
typedef struct {
    int dummy; // Placeholder for actual fields
} DW_TAG_enumeration_typebpf_attach_type;

// Function-under-test declaration
int libbpf_attach_type_by_name(const char *name, DW_TAG_enumeration_typebpf_attach_type *attach_type);

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the name string and ensure it's null-terminated
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        return 0; // Memory allocation failed
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Initialize the DW_TAG_enumeration_typebpf_attach_type structure
    DW_TAG_enumeration_typebpf_attach_type attach_type;
    memset(&attach_type, 0, sizeof(attach_type));

    // Call the function-under-test
    libbpf_attach_type_by_name(name, &attach_type);

    // Free allocated memory
    free(name);

    return 0;
}