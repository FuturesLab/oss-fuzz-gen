#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient for our needs
    if (size < sizeof(SF_VIRTUAL_IO) + sizeof(SF_INFO)) {
        return 0;
    }

    // Prepare SF_VIRTUAL_IO structure with dummy functions
    SF_VIRTUAL_IO vio;
    vio.get_filelen = [](void *user_data) -> sf_count_t { return 0; };
    vio.seek = [](sf_count_t offset, int whence, void *user_data) -> sf_count_t { return 0; };
    vio.read = [](void *ptr, sf_count_t count, void *user_data) -> sf_count_t { return 0; };
    vio.write = [](const void *ptr, sf_count_t count, void *user_data) -> sf_count_t { return 0; };
    vio.tell = [](void *user_data) -> sf_count_t { return 0; };

    // Prepare SF_INFO structure
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    // Dummy user data
    void *user_data = (void *)data;

    // Call the function-under-test
    SNDFILE *sndfile = sf_open_virtual(&vio, SFM_READ, &sfinfo, user_data);

    // If the file was successfully opened, close it
    if (sndfile != NULL) {
        sf_close(sndfile);
    }

    return 0;
}