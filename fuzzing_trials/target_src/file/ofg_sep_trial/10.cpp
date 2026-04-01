#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <magic.h>
#include <cstdio>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Ensure the data is null-terminated for string operations
    char *file_path = (char *)malloc(size + 1);
    if (file_path == NULL) {
        return 0;
    }
    memcpy(file_path, data, size);
    file_path[size] = '\0';

    // Use a temporary file to ensure the file_path is valid
    char temp_filename[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(temp_filename);
    if (fd == -1) {
        free(file_path);
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(temp_filename);
        free(file_path);
        return 0;
    }
    close(fd);

    // Initialize magic_set
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        unlink(temp_filename);
        free(file_path);
        return 0;
    }

    // Load default magic database
    if (magic_load(magic, NULL) != 0) {
        magic_close(magic);
        unlink(temp_filename);
        free(file_path);
        return 0;
    }

    // Call the function-under-test
    const char *result = magic_file(magic, temp_filename);
    // Optionally, check the result for further processing
    if (result != NULL) {
        // Process result if needed
    }

    // Clean up
    magic_close(magic);
    unlink(temp_filename);
    free(file_path);

    return 0;
}