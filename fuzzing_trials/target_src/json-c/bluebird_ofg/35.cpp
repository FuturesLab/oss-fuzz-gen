#include "fuzzer/FuzzedDataProvider.h"
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sys/stat.h>  // Include this header for fchmod and file permission macros
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_util.h"  // Include the header file instead of the source file

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a temporary file to get a valid file descriptor
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Ensure the file is writable
    fchmod(fd, S_IRUSR | S_IWUSR);

    // Consume data to create a json_object
    std::string json_str = fuzzed_data.ConsumeRemainingBytesAsString();
    struct json_object *json_obj = json_tokener_parse(json_str.c_str());

    // If json_obj is NULL, clean up and exit
    if (!json_obj) {
        close(fd);
        return 0;
    }

    // Consume an integer for the flags parameter
    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of json_object_to_fd
    json_object_to_fd(JSON_C_TO_STRING_PLAIN, json_obj, flags);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    json_object_put(json_obj);
    close(fd);
    unlink(tmpl);

    return 0;
}