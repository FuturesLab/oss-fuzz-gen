#include <fuzzer/FuzzedDataProvider.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include "/src/json-c/json_object.h"  // Correct header for json-c functions
#include "/src/json-c/json_util.h"    // Include necessary json-c utility functions

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit early
    }

    // Write the fuzzing data to the file
    write(fd, data, size);

    // Reset the file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume an integer value for the second parameter
    int option = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    struct json_object *obj = json_object_from_fd_ex(fd, option);

    // Clean up
    if (obj) {
        json_object_put(obj);
    }
    close(fd);
    unlink(tmpl);

    return 0;
}