// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Dget_type at H5D.c:706:1 in H5Dpublic.h
// H5Dget_type at H5D.c:706:1 in H5Dpublic.h
// H5Dget_space at H5D.c:597:1 in H5Dpublic.h
// H5Dget_space at H5D.c:597:1 in H5Dpublic.h
// H5Dget_create_plist at H5D.c:747:1 in H5Dpublic.h
// H5Dget_create_plist at H5D.c:747:1 in H5Dpublic.h
// H5Dget_space_status at H5D.c:668:1 in H5Dpublic.h
// H5Dget_space_status at H5D.c:668:1 in H5Dpublic.h
// H5Dget_storage_size at H5D.c:848:1 in H5Dpublic.h
// H5Dget_storage_size at H5D.c:848:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <hdf5.h>

static void cleanup(hid_t *ids, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (ids[i] >= 0) {
            H5Sclose(ids[i]);
        }
    }
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(hid_t)) {
        return 0;
    }

    hid_t dset_id = *((hid_t *)Data);

    hid_t type_id1 = H5Dget_type(dset_id);
    hid_t type_id2 = H5Dget_type(dset_id);

    hid_t space_id1 = H5Dget_space(dset_id);
    hid_t space_id2 = H5Dget_space(dset_id);

    hid_t plist_id1 = H5Dget_create_plist(dset_id);
    hid_t plist_id2 = H5Dget_create_plist(dset_id);

    H5D_space_status_t status1, status2;
    H5Dget_space_status(dset_id, &status1);
    H5Dget_space_status(dset_id, &status2);

    hsize_t storage_size1 = H5Dget_storage_size(dset_id);
    hsize_t storage_size2 = H5Dget_storage_size(dset_id);

    if (Size >= sizeof(hid_t) * 5) {
        hid_t mem_type_id = *((hid_t *)(Data + sizeof(hid_t)));
        hid_t mem_space_id = *((hid_t *)(Data + sizeof(hid_t) * 2));
        hid_t file_space_id = *((hid_t *)(Data + sizeof(hid_t) * 3));
        hid_t dxpl_id = *((hid_t *)(Data + sizeof(hid_t) * 4));

        void *buf = malloc(storage_size1 > 0 ? storage_size1 : 1);
        if (buf) {
            H5Dread(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf);
            H5Dread(dset_id, mem_type_id, mem_space_id, file_space_id, dxpl_id, buf);
            free(buf);
        }
    }

    hid_t ids_to_cleanup[] = { type_id1, type_id2, space_id1, space_id2, plist_id1, plist_id2 };
    cleanup(ids_to_cleanup, sizeof(ids_to_cleanup) / sizeof(ids_to_cleanup[0]));

    return 0;
}