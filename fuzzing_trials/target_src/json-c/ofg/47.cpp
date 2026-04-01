#include <fuzzer/FuzzedDataProvider.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
// Include the correct json-c headers for the functions used
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_util.h"

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Call the function-under-test with the temporary file path
    struct json_object *obj = json_object_from_file(tmpl);

    // Clean up
    json_object_put(obj);
    unlink(tmpl);

    return 0;
}