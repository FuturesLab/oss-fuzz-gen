#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include for close()
#include "janet.h"

extern Janet janet_makefile(FILE *, int32_t);

int LLVMFuzzerTestOneInput_1230(const uint8_t *data, size_t size) {
    FILE *temp_file;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    temp_file = fdopen(fd, "wb+");
    if (!temp_file) {
        close(fd);
        return 0;
    }

    if (fwrite(data, 1, size, temp_file) != size) {
        fclose(temp_file);
        return 0;
    }

    // Rewind the file to the beginning for reading
    rewind(temp_file);

    // Initialize the Janet VM
    janet_init();

    // Call the function-under-test
    int32_t flags = 0; // Initialize flags with a default value
    Janet result = janet_makefile(temp_file, flags);

    // Check the result to ensure the function is being exercised
    if (janet_checktype(result, JANET_NIL)) {
        fprintf(stderr, "janet_makefile returned nil\n");
    } else {
        // Optionally, perform further operations on the result
        // For example, convert it to a string and print
        JanetString str = janet_to_string(result);
        printf("janet_makefile result: %s\n", str);
    }

    // Clean up
    // Do not fclose(temp_file) here as it might be managed by Janet
    remove(tmpl);

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}