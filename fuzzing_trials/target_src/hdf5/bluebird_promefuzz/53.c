#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/src/hdf5/src/H5Dpublic.h"
#include "/src/hdf5/src/H5Ppublic.h" // Include for H5Pclose

static herr_t safe_H5Dread(hid_t dset_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t dxpl_id, void *buf) {
    herr_t status = H5Dread(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf);
    if (status < 0) {
        fprintf(stderr, "H5Dread failed\n");
    }
    return status;
}

static hid_t safe_H5Dget_access_plist(hid_t dset_id) {
    hid_t plist_id = H5Dget_access_plist(dset_id);
    if (plist_id < 0) {
        fprintf(stderr, "H5Dget_access_plist failed\n");
    }
    return plist_id;
}

static herr_t safe_H5Dvlen_reclaim(hid_t type_id, hid_t space_id, hid_t dxpl_id, void *buf) {
    herr_t status = H5Dvlen_reclaim(type_id, space_id, dxpl_id, buf);
    if (status < 0) {
        fprintf(stderr, "H5Dvlen_reclaim failed\n");
    }
    return status;
}

static herr_t safe_H5Dget_space_status(hid_t dset_id, H5D_space_status_t *allocation) {
    herr_t status = H5Dget_space_status(dset_id, allocation);
    if (status < 0) {
        fprintf(stderr, "H5Dget_space_status failed\n");
    }
    return status;
}

static herr_t safe_H5Dfill(const void *fill, hid_t fill_type_id, void *buf, hid_t buf_type_id, hid_t space_id) {
    herr_t status = H5Dfill(fill, fill_type_id, buf, buf_type_id, space_id);
    if (status < 0) {
        fprintf(stderr, "H5Dfill failed\n");
    }
    return status;
}

static herr_t safe_H5Dwrite(hid_t dset_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t dxpl_id, const void *buf) {
    herr_t status = H5Dwrite(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf);
    if (status < 0) {
        fprintf(stderr, "H5Dwrite failed\n");
    }
    return status;
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t) * 5) {
        return 0; // Not enough data to proceed
    }

    hid_t dset_id = *((hid_t *)Data);
    hid_t mem_type_id = *((hid_t *)(Data + sizeof(hid_t)));
    hid_t mem_space_id = *((hid_t *)(Data + 2 * sizeof(hid_t)));
    hid_t file_space_id = *((hid_t *)(Data + 3 * sizeof(hid_t)));
    hid_t dxpl_id = *((hid_t *)(Data + 4 * sizeof(hid_t)));

    void *buf = malloc(1024); // Allocate a buffer for reading/writing
    if (!buf) {
        fprintf(stderr, "Memory allocation failed\n");
        return 0;
    }

    safe_H5Dread(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf);
    safe_H5Dwrite(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf);

    hid_t access_plist = safe_H5Dget_access_plist(dset_id);
    if (access_plist >= 0) {
        H5Pclose(access_plist);
    }

    H5D_space_status_t allocation;
    safe_H5Dget_space_status(dset_id, &allocation);

    safe_H5Dvlen_reclaim(mem_type_id, mem_space_id, dxpl_id, buf);
    safe_H5Dfill(NULL, mem_type_id, buf, mem_type_id, mem_space_id);

    free(buf);
    return 0;
}