#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // Include for debugging purposes if needed

// Assume sam_hdr_t is defined somewhere in the library
typedef struct {
    // Placeholder for actual structure members
    int dummy;
} sam_hdr_t;

// Assume the function is defined somewhere in the library
int sam_hdr_add_line(sam_hdr_t *hdr, const char *line, void *unused);

int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Initialize sam_hdr_t
    sam_hdr_t hdr;
    memset(&hdr, 0, sizeof(hdr));

    // Prepare a null-terminated string from the input data
    char *line = (char *)malloc(size + 1);
    if (line == NULL) {
        return 0;
    }
    memcpy(line, data, size);
    line[size] = '\0';

    // Ensure the input is a valid line for sam_hdr_add_line
    // This could involve checking for specific format or content
    // For demonstration, we'll just ensure it starts with a valid character
    if (line[0] != '@') {
        free(line);
        return 0;
    }

    // Add additional checks to ensure the line is valid
    // For example, checking for a minimum length or specific structure
    if (strlen(line) < 3) { // Assuming a minimal valid line length
        free(line);
        return 0;
    }

    // Additional validation to prevent potential buffer overflow
    // Ensure the line does not contain unexpected characters or structure
    // This is a simple example; real validation would depend on expected format
    for (size_t i = 0; i < size; i++) {
        if (line[i] < 32 || line[i] > 126) { // Check for non-printable characters
            free(line);
            return 0;
        }
    }

    // Call the function under test
    sam_hdr_add_line(&hdr, line, NULL);

    // Clean up
    free(line);

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

    LLVMFuzzerTestOneInput_112(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
