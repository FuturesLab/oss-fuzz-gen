#include <fuzzer/FuzzedDataProvider.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_util.h"  // Include the header file, not the source file

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    write(fd, data, size);

    // Reset the file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Call the function-under-test
    struct json_object *obj = json_object_from_fd(fd);

    // Clean up
    if (obj) {
        json_object_put(obj);
    }
    close(fd);
    unlink(tmpl);

    return 0;
}