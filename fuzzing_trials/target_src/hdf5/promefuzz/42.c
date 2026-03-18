// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fis_hdf5 at H5Fdeprec.c:144:1 in H5Fpublic.h
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fis_hdf5 at H5Fdeprec.c:144:1 in H5Fpublic.h
// H5Fis_hdf5 at H5Fdeprec.c:144:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <H5Fpublic.h>
#include <H5Ppublic.h>

static void write_dummy_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fputs("Dummy data", file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    const char *filename = "./dummy_file";
    unsigned flags = H5F_ACC_TRUNC;
    hid_t fcpl_id = H5P_DEFAULT;
    hid_t fapl_id = H5P_DEFAULT;

    // Ensure the dummy file exists
    write_dummy_file(filename);

    // H5Fcreate
    hid_t file_id = H5Fcreate(filename, flags, fcpl_id, fapl_id);
    if (file_id >= 0) {
        // H5Fclose
        herr_t status = H5Fclose(file_id);
        if (status < 0) {
            fprintf(stderr, "Failed to close file\n");
        }
    }

    // Attempt to close again to test error handling
    herr_t close_status = H5Fclose(file_id);
    if (close_status < 0) {
        fprintf(stderr, "Expected failure on closing already closed file\n");
    }

    // H5Fis_hdf5
    htri_t is_hdf5 = H5Fis_hdf5(filename);
    if (is_hdf5 < 0) {
        fprintf(stderr, "Error determining if file is HDF5\n");
    }

    // H5Fcreate again
    file_id = H5Fcreate(filename, flags, fcpl_id, fapl_id);
    if (file_id >= 0) {
        // H5Fclose
        herr_t status = H5Fclose(file_id);
        if (status < 0) {
            fprintf(stderr, "Failed to close file\n");
        }
    }

    // H5Fis_hdf5
    is_hdf5 = H5Fis_hdf5(filename);
    if (is_hdf5 < 0) {
        fprintf(stderr, "Error determining if file is HDF5\n");
    }

    // H5Fis_hdf5 again
    is_hdf5 = H5Fis_hdf5(filename);
    if (is_hdf5 < 0) {
        fprintf(stderr, "Error determining if file is HDF5\n");
    }

    return 0;
}