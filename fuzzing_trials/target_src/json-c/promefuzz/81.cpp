// This fuzz driver is generated for library json-c, aiming to fuzz the following functions:
// json_object_from_file at json_util.c:145:21 in json_util.h
// json_object_to_json_string_length at json_object.c:408:13 in json_object.h
// json_object_to_json_string_ext at json_object.c:434:13 in json_object.h
// json_object_to_file at json_util.c:230:5 in json_util.h
// json_object_to_fd at json_util.c:187:5 in json_util.h
// json_object_to_file_ext at json_util.c:163:5 in json_util.h
// json_object_put at json_object.c:272:5 in json_object.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <json_util.h>
#include <json_object.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

static void write_to_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    // Step 1: Write data to a dummy file
    write_to_dummy_file(Data, Size);

    // Step 2: Test json_object_from_file
    struct json_object *obj = json_object_from_file("./dummy_file");
    if (obj) {
        // Step 3: Test json_object_to_json_string_length
        size_t length;
        const char *json_str = json_object_to_json_string_length(obj, JSON_C_TO_STRING_PLAIN, &length);

        // Step 4: Test json_object_to_json_string_ext
        const char *json_str_ext = json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY);

        // Step 5: Test json_object_to_file
        int result = json_object_to_file("./dummy_file", obj);

        // Step 6: Test json_object_to_fd
        int fd = open("./dummy_file", O_WRONLY | O_CREAT, 0644);
        if (fd != -1) {
            result = json_object_to_fd(fd, obj, JSON_C_TO_STRING_PLAIN);
            close(fd);
        }

        // Step 7: Test json_object_to_file_ext
        result = json_object_to_file_ext("./dummy_file", obj, JSON_C_TO_STRING_PRETTY);

        // Clean up
        json_object_put(obj);
    }

    return 0;
}