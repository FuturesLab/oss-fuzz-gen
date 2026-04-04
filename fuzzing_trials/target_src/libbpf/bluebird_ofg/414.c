#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "/src/libbpf/include/uapi/linux/fcntl.h"
#include "libbpf.h"

int LLVMFuzzerTestOneInput_414(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from bpf_object__open to bpf_object__load

    int ret_bpf_object__load_hdisv = bpf_object__load(obj);
    if (ret_bpf_object__load_hdisv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    result = bpf_object__load(obj);

    // Clean up
    bpf_object__close(obj);
    close(fd);
    unlink(tmpl);

    return 0;
}