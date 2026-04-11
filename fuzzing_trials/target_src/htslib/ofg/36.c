#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for mkstemp and close

// Assuming hFILE is defined in an included header file
typedef struct {
    FILE *file;
} hFILE;

// Mock implementation of hopen function
hFILE* hopen_36(const char *filename, const char *mode, void *options) {
    hFILE *hfile = malloc(sizeof(hFILE));
    if (hfile == NULL) return NULL;

    hfile->file = fopen(filename, mode);
    if (hfile->file == NULL) {
        free(hfile);
        return NULL;
    }

    return hfile;
}

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to create a valid filename and mode string
    if (size < 2) return 0;

    // Create a temporary file with the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Write the fuzz data to the temporary file
    write(fd, data, size);
    close(fd);

    // Define mode string
    const char *mode = "r";

    // Call the function-under-test
    hFILE *hfile = hopen_36(tmpl, mode, NULL);

    // Clean up
    if (hfile != NULL) {
        if (hfile->file != NULL) {
            fclose(hfile->file);
        }
        free(hfile);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}