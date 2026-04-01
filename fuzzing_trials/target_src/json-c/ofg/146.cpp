#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_util.h" // Changed from .c to .h
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Initialize FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Consume a portion of the data to create a JSON object
    size_t json_data_size = fuzzed_data.ConsumeIntegralInRange<size_t>(0, size);
    std::string json_data = fuzzed_data.ConsumeRandomLengthString(json_data_size);

    // Parse the JSON data
    struct json_object *jobj = json_tokener_parse(json_data.c_str());
    if (jobj == nullptr) {
        close(fd);
        return 0;
    }

    // Consume an integer for the flags parameter
    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    json_object_to_fd(fd, jobj, flags);

    // Clean up
    json_object_put(jobj);
    close(fd);
    unlink(tmpl);

    return 0;
}