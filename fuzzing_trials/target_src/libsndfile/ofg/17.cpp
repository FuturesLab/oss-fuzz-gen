#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
    // Initialize SF_VIRTUAL_IO structure
    SF_VIRTUAL_IO sf_virtual_io;
    sf_virtual_io.get_filelen = [](void *user_data) -> sf_count_t {
        return *(sf_count_t *)user_data;
    };
    sf_virtual_io.seek = [](sf_count_t offset, int whence, void *user_data) -> sf_count_t {
        sf_count_t *pos = (sf_count_t *)user_data;
        switch (whence) {
            case SEEK_SET: *pos = offset; break;
            case SEEK_CUR: *pos += offset; break;
            case SEEK_END: *pos = *(sf_count_t *)user_data - offset; break;
            default: return -1;
        }
        return *pos;
    };
    sf_virtual_io.read = [](void *ptr, sf_count_t count, void *user_data) -> sf_count_t {
        sf_count_t *pos = (sf_count_t *)user_data;
        if (*pos + count > *(sf_count_t *)user_data) {
            count = *(sf_count_t *)user_data - *pos;
        }
        memcpy(ptr, (uint8_t *)user_data + *pos, count);
        *pos += count;
        return count;
    };
    sf_virtual_io.write = [](const void *ptr, sf_count_t count, void *user_data) -> sf_count_t {
        return 0; // No-op for write as we are reading
    };
    sf_virtual_io.tell = [](void *user_data) -> sf_count_t {
        return *(sf_count_t *)user_data;
    };

    // Initialize SF_INFO structure
    SF_INFO sf_info;
    memset(&sf_info, 0, sizeof(SF_INFO));

    // Use data as user_data for virtual IO
    sf_count_t user_data = size;

    // Call the function-under-test
    SNDFILE *sndfile = sf_open_virtual(&sf_virtual_io, SFM_READ, &sf_info, &user_data);

    // Cleanup
    if (sndfile != NULL) {
        sf_close(sndfile);
    }

    return 0;
}