#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to be useful
    if (size < 2) {
        return 0;
    }
    
    // Create a dummy bpf_object structure
    struct bpf_object *bpf_obj = bpf_object__open_mem(data, size, NULL);
    if (bpf_obj == NULL) {
        return 0;
    }

    // Allocate memory for the map name
    size_t map_name_len = size - 1;
    char *map_name = (char *)malloc(map_name_len + 1);
    if (map_name == NULL) {
        bpf_object__close(bpf_obj);
        return 0;
    }

    // Copy part of the data to be used as a map name
    memcpy(map_name, data + 1, map_name_len);
    map_name[map_name_len] = '\0'; // Null-terminate the string

    // Call the function-under-test
    int fd = bpf_object__find_map_fd_by_name(bpf_obj, map_name);

    // Clean up
    free(map_name);
    bpf_object__close(bpf_obj);

    return 0;
}