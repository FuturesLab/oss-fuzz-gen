// This fuzz driver is generated for library hdf5, aiming to fuzz the following functions:
// H5Fcreate at H5F.c:638:1 in H5Fpublic.h
// H5Fset_mdc_config at H5F.c:1814:1 in H5Fpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dcreate2 at H5D.c:179:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dget_space at H5D.c:597:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Dwrite at H5D.c:1350:1 in H5Dpublic.h
// H5Fset_mdc_config at H5F.c:1814:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fset_mdc_config at H5F.c:1814:1 in H5Fpublic.h
// H5Dread at H5D.c:1041:1 in H5Dpublic.h
// H5Dclose at H5D.c:463:1 in H5Dpublic.h
// H5Fclose at H5F.c:1027:1 in H5Fpublic.h
// H5Fdelete at H5F.c:1117:1 in H5Fpublic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "H5Dpublic.h"
#include "H5Fpublic.h"
#include "H5Spublic.h"
#include "H5Tpublic.h"
#include "H5ACpublic.h"
#include "H5Ppublic.h"

// Define constants
#define FILENAME "./dummy_file"
#define DATASETNAME "dset"
#define DIM0 4
#define DIM1 6

static void write_dummy_data_to_file(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        int data[DIM0][DIM1] = {{0}};
        fwrite(data, sizeof(int), DIM0 * DIM1, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    // Prepare environment
    write_dummy_data_to_file(FILENAME);

    // Create a new HDF5 file
    hid_t file_id = H5Fcreate(FILENAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Set up metadata cache configuration
    H5AC_cache_config_t mdc_config;
    memset(&mdc_config, 0, sizeof(mdc_config));
    mdc_config.version = H5AC__CURR_CACHE_CONFIG_VERSION;
    H5Fset_mdc_config(file_id, &mdc_config);

    // Create dataspace for the dataset
    hsize_t dims[2] = {DIM0, DIM1};
    hid_t space_id = H5Screate_simple(2, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a new dataset
    hid_t dset_id = H5Dcreate2(file_id, DATASETNAME, H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Get dataspace of the dataset
    hid_t space_id_copy = H5Dget_space(dset_id);
    if (space_id_copy < 0) {
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Write data to the dataset
    int data[DIM0][DIM1] = {{0}};
    H5Dwrite(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

    // Configure metadata cache again
    H5Fset_mdc_config(file_id, &mdc_config);

    // Read data from the dataset
    int read_data[DIM0][DIM1] = {{0}};
    H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, read_data);

    // Close dataset and dataspace
    H5Dclose(dset_id);
    H5Sclose(space_id_copy);

    // Configure metadata cache once more
    H5Fset_mdc_config(file_id, &mdc_config);

    // Read data again from the dataset
    H5Dread(dset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, read_data);

    // Close dataset
    H5Dclose(dset_id);

    // Close the file
    H5Fclose(file_id);

    // Delete the file
    H5Fdelete(FILENAME, H5P_DEFAULT);

    return 0;
}