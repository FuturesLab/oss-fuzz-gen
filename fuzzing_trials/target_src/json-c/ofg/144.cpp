#include <fuzzer/FuzzedDataProvider.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_util.h" // Ensure this header is included for json_object_to_file_ext

extern "C" int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    FuzzedDataProvider fuzzed_data(data, size);

    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Generate a random json_object
    std::string json_string = fuzzed_data.ConsumeRandomLengthString();
    struct json_object *jobj = json_tokener_parse(json_string.c_str());
    if (jobj == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Generate a random integer for the third parameter
    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    json_object_to_file_ext(tmpl, jobj, flags);

    // Clean up
    json_object_put(jobj);
    unlink(tmpl);

    return 0;
}