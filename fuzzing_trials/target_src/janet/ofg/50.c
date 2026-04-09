#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *janet_dynfile(const char *filename, FILE *file);

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a filename and some file content
    if (size < 2) {
        return 0;
    }

    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fflush(file);
    fseek(file, 0, SEEK_SET);

    // Use the filename and file pointer to call the function-under-test
    janet_dynfile(tmpl, file);

    // Clean up
    fclose(file);
    remove(tmpl);

    return 0;
}