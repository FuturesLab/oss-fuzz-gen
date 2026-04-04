#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Assuming these types are defined somewhere in the library
typedef int DW_TAG_enumeration_typebpf_prog_type;
typedef int DW_TAG_enumeration_typebpf_attach_type;

// Function prototype
int libbpf_prog_type_by_name(const char *, DW_TAG_enumeration_typebpf_prog_type *, DW_TAG_enumeration_typebpf_attach_type *);

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Ensure that the input size is large enough to extract a meaningful string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the string and ensure it is null-terminated
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Initialize the enumeration type variables
    DW_TAG_enumeration_typebpf_prog_type prog_type = 0;
    DW_TAG_enumeration_typebpf_attach_type attach_type = 0;

    // Call the function-under-test
    libbpf_prog_type_by_name(name, &prog_type, &attach_type);

    // Free allocated memory
    free(name);

    return 0;
}