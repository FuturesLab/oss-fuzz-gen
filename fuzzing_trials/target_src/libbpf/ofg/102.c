#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "/src/libbpf/src/libbpf.h"

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    struct bpf_object *obj = NULL;
    int result;

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Load the BPF object from the temporary file
    obj = bpf_object__open(tmpl);
    if (!obj) {
        close(fd);
        return 0;
    }

    // Call the function-under-test
    result = bpf_object__load(obj);

    // Clean up
    bpf_object__close(obj);
    close(fd);
    unlink(tmpl);

    return 0;
}