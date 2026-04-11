#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <htslib/sam.h>
#include <htslib/hts.h>

// Function-under-test
int bam_next_basemod(const bam1_t *, hts_base_mod_state *, hts_base_mod *, int, int *);

// Remove extern "C" as this is not valid in C files
int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Initialize bam1_t structure
    bam1_t *bam_record = bam_init1();
    if (!bam_record) return 0;

    // Initialize hts_base_mod_state structure
    hts_base_mod_state *mod_state = hts_base_mod_state_alloc();
    if (!mod_state) {
        bam_destroy1(bam_record);
        return 0;
    }

    // Initialize hts_base_mod structure
    hts_base_mod mod;
    mod.modified_base = 'C';  // Example base modification
    mod.strand = 0;           // Example strand

    // Initialize other parameters
    int max_mods = 10;        // Example maximum number of modifications
    int n_mods = 0;           // Number of modifications found

    // Call the function-under-test
    int result = bam_next_basemod(bam_record, mod_state, &mod, max_mods, &n_mods);

    // Clean up
    hts_base_mod_state_free(mod_state);
    bam_destroy1(bam_record);

    return 0;
}