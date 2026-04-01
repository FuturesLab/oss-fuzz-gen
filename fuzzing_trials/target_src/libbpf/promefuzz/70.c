// This fuzz driver is generated for library libbpf, aiming to fuzz the following functions:
// bpf_map__btf_value_type_id at libbpf.c:10752:7 in libbpf.h
// bpf_map__max_entries at libbpf.c:5037:7 in libbpf.h
// bpf_map__ifindex at libbpf.c:10803:7 in libbpf.h
// bpf_map__map_flags at libbpf.c:10586:7 in libbpf.h
// bpf_map__value_size at libbpf.c:10638:7 in libbpf.h
// bpf_map__numa_node at libbpf.c:10612:7 in libbpf.h
#include <stdint.h>
#include <stddef.h>
#include <libbpf.h>

static void fuzz_bpf_map_functions(const struct bpf_map *map) {
    // Fuzzing bpf_map__numa_node
    __u32 numa_node = bpf_map__numa_node(map);

    // Fuzzing bpf_map__btf_value_type_id
    __u32 btf_value_type_id = bpf_map__btf_value_type_id(map);

    // Fuzzing bpf_map__max_entries
    __u32 max_entries = bpf_map__max_entries(map);

    // Fuzzing bpf_map__ifindex
    __u32 ifindex = bpf_map__ifindex(map);

    // Fuzzing bpf_map__map_flags
    __u32 map_flags = bpf_map__map_flags(map);

    // Fuzzing bpf_map__value_size
    __u32 value_size = bpf_map__value_size(map);

    // Use the return values in some way to avoid compiler optimizations
    (void)numa_node;
    (void)btf_value_type_id;
    (void)max_entries;
    (void)ifindex;
    (void)map_flags;
    (void)value_size;
}

int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    // We cannot determine the size of struct bpf_map because it's incomplete, so we assume
    // a minimum size for fuzzing purposes. This value should be adjusted according to the actual
    // expected size when known.
    if (Size < 128) { // Arbitrary minimum size for fuzzing
        return 0;
    }

    // Create a dummy bpf_map from the input data
    const struct bpf_map *map = (const struct bpf_map *)Data;

    // Fuzz the target functions
    fuzz_bpf_map_functions(map);

    return 0;
}