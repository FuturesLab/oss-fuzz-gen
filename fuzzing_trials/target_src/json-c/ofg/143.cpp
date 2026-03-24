#include <fuzzer/FuzzedDataProvider.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_util.h" // Include the correct header for json_object_to_file

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Create a FuzzedDataProvider instance to extract data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a string for the file path
    std::string file_path = fuzzed_data.ConsumeRandomLengthString(20);

    // Ensure the file path is null-terminated
    if (file_path.empty()) {
        return 0;
    }

    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Consume a boolean to decide whether to use a valid json_object
    bool use_valid_json = fuzzed_data.ConsumeBool();
    struct json_object *jobj;

    if (use_valid_json) {
        // Create a simple JSON object if the boolean is true
        jobj = json_object_new_object();
        json_object_object_add(jobj, "key", json_object_new_string("value"));
    } else {
        // Otherwise, create a JSON object from remaining fuzz data
        std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();
        jobj = json_tokener_parse(json_string.c_str());
        if (!jobj) {
            // If parsing fails, clean up and exit
            unlink(tmpl);
            return 0;
        }
    }

    // Call the function-under-test
    json_object_to_file(tmpl, jobj); // Correctly use json_object_to_file

    // Clean up
    json_object_put(jobj);
    unlink(tmpl);

    return 0;
}