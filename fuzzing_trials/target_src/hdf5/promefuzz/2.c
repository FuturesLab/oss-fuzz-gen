// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fget_create_plist at H5F.c:106:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Fget_intent at H5F.c:1540:1 in H5Fpublic.h
// H5Fget_fileno at H5F.c:1579:1 in H5Fpublic.h
// H5Fget_freespace at H5F.c:1617:1 in H5Fpublic.h
// H5Fget_vfd_handle at H5F.c:422:1 in H5Fpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Ppublic.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare the environment
    write_dummy_file();
    hid_t file_id, dset_id, fapl_id, plist_id;
    unsigned intent;
    unsigned long fileno;
    void *file_handle;

    // Open the HDF5 file
    file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // 1. H5Fget_access_plist
    plist_id = H5Fget_access_plist(file_id);
    if (plist_id >= 0) H5Pclose(plist_id);

    // 2. H5Dopen2
    dset_id = H5Dopen2(file_id, "dataset", H5P_DEFAULT);
    if (dset_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // 3. H5Fget_create_plist
    plist_id = H5Fget_create_plist(file_id);
    if (plist_id >= 0) H5Pclose(plist_id);

    // 4. H5Fget_access_plist
    plist_id = H5Fget_access_plist(file_id);
    if (plist_id >= 0) H5Pclose(plist_id);

    // 5. H5Fget_intent
    H5Fget_intent(file_id, &intent);

    // 6. H5Fget_fileno
    H5Fget_fileno(file_id, &fileno);

    // 7. H5Fget_freespace
    H5Fget_freespace(file_id);

    // 8. H5Fget_vfd_handle
    H5Fget_vfd_handle(file_id, H5P_DEFAULT, &file_handle);

    // 9. H5Dclose
    H5Dclose(dset_id);

    // 10. H5Fclose
    H5Fclose(file_id);

    return 0;
}