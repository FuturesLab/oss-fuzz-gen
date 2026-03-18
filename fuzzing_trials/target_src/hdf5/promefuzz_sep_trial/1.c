// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Dopen2 at H5D.c:393:1 in H5Dpublic.h
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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <H5Dpublic.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        // Write some dummy data to the file
        const char *dummy_data = "HDF5 dummy data";
        fwrite(dummy_data, sizeof(char), sizeof(dummy_data), file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    // Open the dummy file
    hid_t file_id = H5Fopen("./dummy_file", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Get access property list
    hid_t access_plist_id = H5Fget_access_plist(file_id);
    if (access_plist_id >= 0) {
        H5Pclose(access_plist_id);
    }

    // Open a dataset
    hid_t dataset_id = H5Dopen2(file_id, "dummy_dataset", H5P_DEFAULT);
    if (dataset_id >= 0) {
        // Get create property list
        hid_t create_plist_id = H5Fget_create_plist(file_id);
        if (create_plist_id >= 0) {
            H5Pclose(create_plist_id);
        }

        // Get access property list again
        access_plist_id = H5Fget_access_plist(file_id);
        if (access_plist_id >= 0) {
            H5Pclose(access_plist_id);
        }

        // Get intent
        unsigned intent;
        H5Fget_intent(file_id, &intent);

        // Get file number
        unsigned long fileno;
        H5Fget_fileno(file_id, &fileno);

        // Get free space
        hssize_t freespace = H5Fget_freespace(file_id);

        // Get VFD handle
        void *vfd_handle;
        H5Fget_vfd_handle(file_id, H5P_DEFAULT, &vfd_handle);

        // Close the dataset
        H5Dclose(dataset_id);
    }

    // Close the file
    H5Fclose(file_id);

    return 0;
}