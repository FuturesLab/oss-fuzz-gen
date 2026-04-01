#include <fuzzer/FuzzedDataProvider.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_util.h"  // Include the header file instead of the implementation file

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    write(fd, data, size);
    close(fd);

    // Call the function-under-test with the temporary file path
    struct json_object *json_obj = json_object_from_file(tmpl);

    // Clean up
    if (json_obj) {
        json_object_put(json_obj);
    }
    unlink(tmpl);

    return 0;
}