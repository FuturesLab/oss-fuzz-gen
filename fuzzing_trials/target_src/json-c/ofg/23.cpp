#include <fuzzer/FuzzedDataProvider.h>
#include <json-c/json_util.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Create a FuzzedDataProvider instance to handle the input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Consume a part of the data to create a temporary file name
    std::string temp_filename = fuzzed_data.ConsumeRandomLengthString(10);
    if (temp_filename.size() != 10) {
        return 0; // Exit if the generated string is not of the expected length
    }

    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0; // If file creation fails, exit early
    }

    // Close the file descriptor as we only need the filename
    close(fd);

    // Consume the remaining bytes as a string to create a JSON object
    std::string json_data = fuzzed_data.ConsumeRemainingBytesAsString();
    struct json_object *jobj = json_tokener_parse(json_data.c_str());

    // Ensure the json_object is not NULL
    if (jobj == NULL) {
        return 0; // Exit early if JSON parsing failed
    }

    // Call the function under test
    json_object_to_file(tmpl, jobj);

    // Clean up
    json_object_put(jobj);
    std::remove(tmpl);

    return 0;
}