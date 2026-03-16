// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fclear_elink_file_cache at H5F.c:2194:1 in H5Fpublic.h
// H5Fflush at H5F.c:957:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fis_accessible at H5F.c:464:1 in H5Fpublic.h
// H5Fopen at H5F.c:812:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Freopen at H5F.c:1440:1 in H5Fpublic.h
// H5Fget_access_plist at H5F.c:152:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "H5Fpublic.h"
#include "H5Ppublic.h" // Include this header for H5P_DEFAULT

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fprintf(file, "HDF5 dummy content");
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    hid_t file_id = -1;
    hid_t fapl_id = H5P_DEFAULT;
    htri_t accessible;
    herr_t status;
    hid_t access_plist_id;
    hid_t reopened_file_id;

    // Call H5Fclear_elink_file_cache with invalid file_id
    status = H5Fclear_elink_file_cache(file_id);

    // Call H5Fflush with invalid file_id and scope
    status = H5Fflush(file_id, H5F_SCOPE_LOCAL);

    // Call H5Fclose with invalid file_id
    status = H5Fclose(file_id);

    // Call H5Fis_accessible to check if the dummy file is accessible
    accessible = H5Fis_accessible("./dummy_file", fapl_id);

    // If the file is accessible, proceed with opening it
    if (accessible > 0) {
        // Open the file with read-only access
        file_id = H5Fopen("./dummy_file", H5F_ACC_RDONLY, fapl_id);
        if (file_id >= 0) {
            // Get the file access property list
            access_plist_id = H5Fget_access_plist(file_id);
            if (access_plist_id >= 0) {
                H5Pclose(access_plist_id);
            }

            // Reopen the file
            reopened_file_id = H5Freopen(file_id);
            if (reopened_file_id >= 0) {
                // Get the file access property list again
                access_plist_id = H5Fget_access_plist(reopened_file_id);
                if (access_plist_id >= 0) {
                    H5Pclose(access_plist_id);
                }
                // Close the reopened file
                H5Fclose(reopened_file_id);
            }

            // Close the original file
            H5Fclose(file_id);
        }
    }

    // Attempt to close the file multiple times
    H5Fclose(file_id);
    H5Fclose(file_id);
    H5Fclose(file_id);
    H5Fclose(file_id);

    return 0;
}