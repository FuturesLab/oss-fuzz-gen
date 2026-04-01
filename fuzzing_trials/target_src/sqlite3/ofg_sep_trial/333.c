#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <stdlib.h>

extern int LLVMFuzzerTestOneInput_333(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract two integers
    if (size < sizeof(int) * 2) {
        return 0;
    }

    // Initialize sqlite3_index_info structure
    sqlite3_index_info indexInfo;
    struct sqlite3_index_constraint *aConstraint = malloc(sizeof(struct sqlite3_index_constraint));
    struct sqlite3_index_constraint_usage *aConstraintUsage = malloc(sizeof(struct sqlite3_index_constraint_usage));
    struct sqlite3_index_orderby *aOrderBy = malloc(sizeof(struct sqlite3_index_orderby));

    if (!aConstraint || !aConstraintUsage || !aOrderBy) {
        // Handle memory allocation failure
        free(aConstraint);
        free(aConstraintUsage);
        free(aOrderBy);
        return 0;
    }

    // Properly initialize the sqlite3_index_info structure
    indexInfo.nConstraint = 1;
    indexInfo.aConstraint = aConstraint;
    indexInfo.aConstraintUsage = aConstraintUsage;
    indexInfo.nOrderBy = 1;
    indexInfo.aOrderBy = aOrderBy;
    indexInfo.needToFreeIdxStr = 0;
    indexInfo.idxStr = NULL;
    indexInfo.estimatedCost = 0.0;
    indexInfo.estimatedRows = 0;
    indexInfo.idxNum = 0;
    indexInfo.orderByConsumed = 0;
    indexInfo.aConstraint[0].iColumn = 0;
    indexInfo.aConstraint[0].op = 0;
    indexInfo.aConstraint[0].usable = 1;
    indexInfo.aConstraint[0].iTermOffset = 0;
    indexInfo.aConstraintUsage[0].argvIndex = 1;
    indexInfo.aConstraintUsage[0].omit = 0;
    indexInfo.aOrderBy[0].iColumn = 0;
    indexInfo.aOrderBy[0].desc = 0;

    // Extract two integers from the data
    int op1 = *(const int *)(data);
    int op2 = *(const int *)(data + sizeof(int));

    // Validate the extracted integers to ensure they are within a valid range
    if (op1 >= 0 && op2 >= 0 && op1 < indexInfo.nConstraint && op2 < indexInfo.nOrderBy) {
        // Call the function under test with valid inputs
        sqlite3_vtab_in(&indexInfo, op1, op2);
    }

    // Free allocated memory
    free(aConstraint);
    free(aConstraintUsage);
    free(aOrderBy);

    return 0;
}