// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// perf_buffer__free at libbpf.c:13691:6 in libbpf.h
// perf_buffer__new at libbpf.c:13767:21 in libbpf.h
// perf_buffer__buffer_fd at libbpf.c:14068:5 in libbpf.h
// perf_buffer__consume_buffer at libbpf.c:14106:5 in libbpf.h
// perf_buffer__buffer at libbpf.c:14082:5 in libbpf.h
// perf_buffer__buffer_cnt at libbpf.c:14058:8 in libbpf.h
// perf_buffer__free at libbpf.c:13691:6 in libbpf.h
// perf_buffer__new_raw at libbpf.c:13800:21 in libbpf.h
// perf_buffer__buffer_fd at libbpf.c:14068:5 in libbpf.h
// perf_buffer__consume_buffer at libbpf.c:14106:5 in libbpf.h
// perf_buffer__buffer at libbpf.c:14082:5 in libbpf.h
// perf_buffer__buffer_cnt at libbpf.c:14058:8 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libbpf.h>
#include <linux/perf_event.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void sample_cb(void *ctx, int cpu, void *data, __u32 size) {
    // Sample callback function
}

static void lost_cb(void *ctx, int cpu, __u64 cnt) {
    // Lost callback function
}

static enum bpf_perf_event_ret event_cb(void *ctx, int cpu, struct perf_event_header *event) {
    // Event callback function
    return LIBBPF_PERF_EVENT_CONT;
}

int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size) {
    int map_fd = open("./dummy_file", O_RDWR | O_CREAT, 0600);
    if (map_fd < 0) {
        perror("Failed to open dummy file");
        return 0;
    }

    // Prepare dummy data
    if (write(map_fd, Data, Size) != Size) {
        perror("Failed to write to dummy file");
        close(map_fd);
        return 0;
    }

    // Reset file offset
    lseek(map_fd, 0, SEEK_SET);

    // Initialize options
    struct perf_buffer_opts opts = { .sz = sizeof(opts), .sample_period = 1 };
    struct perf_buffer_raw_opts raw_opts = { .sz = sizeof(raw_opts), .cpu_cnt = 0 };

    // Attempt to create a new perf buffer
    struct perf_buffer *pb = perf_buffer__new(map_fd, 1, sample_cb, lost_cb, NULL, &opts);
    if (pb) {
        // Explore states with perf_buffer__buffer_fd
        int fd = perf_buffer__buffer_fd(pb, 0);
        if (fd < 0) {
            perror("perf_buffer__buffer_fd failed");
        }

        // Explore states with perf_buffer__consume_buffer
        if (perf_buffer__consume_buffer(pb, 0) < 0) {
            perror("perf_buffer__consume_buffer failed");
        }

        // Explore states with perf_buffer__buffer
        void *buf;
        size_t buf_size;
        if (perf_buffer__buffer(pb, 0, &buf, &buf_size) < 0) {
            perror("perf_buffer__buffer failed");
        }

        // Explore states with perf_buffer__buffer_cnt
        size_t buffer_count = perf_buffer__buffer_cnt(pb);
        (void)buffer_count; // Use buffer_count to avoid unused variable warning

        // Cleanup
        perf_buffer__free(pb);
    } else {
        perror("perf_buffer__new failed");
    }

    // Attempt to create a new raw perf buffer
    struct perf_event_attr attr = { .type = 0, .size = sizeof(struct perf_event_attr) };
    pb = perf_buffer__new_raw(map_fd, 1, &attr, event_cb, NULL, &raw_opts);
    if (pb) {
        // Similar exploration as above
        int fd = perf_buffer__buffer_fd(pb, 0);
        if (fd < 0) {
            perror("perf_buffer__buffer_fd failed");
        }

        if (perf_buffer__consume_buffer(pb, 0) < 0) {
            perror("perf_buffer__consume_buffer failed");
        }

        void *buf;
        size_t buf_size;
        if (perf_buffer__buffer(pb, 0, &buf, &buf_size) < 0) {
            perror("perf_buffer__buffer failed");
        }

        size_t buffer_count = perf_buffer__buffer_cnt(pb);
        (void)buffer_count; 

        perf_buffer__free(pb);
    } else {
        perror("perf_buffer__new_raw failed");
    }

    close(map_fd);
    return 0;
}