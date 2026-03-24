#include "fuzzer/FuzzedDataProvider.h"
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include "/src/json-c/json_object.h"  // Include the header file for json-c
#include "/src/json-c/json_util.h"    // Include the header file for json-c utilities

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzzing data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) {
        return 0;  // If file creation fails, exit early
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;  // If write fails, exit early
    }

    // Use FuzzedDataProvider to generate the second parameter
    FuzzedDataProvider fuzzed_data(data, size);
    int option = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    struct json_object *obj = json_object_from_fd_ex(fd, option);

    // Clean up
    if (obj != nullptr) {
        json_object_put(obj);  // Decrease reference count if object is created
    }
    close(fd);
    unlink(tmpl);

    return 0;
}