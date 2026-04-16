#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "sqlite3.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static void write_dummy_file(const char *data, size_t size) {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_367(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Prepare a null-terminated string for sqlite3_complete
    char *sql = (char *)malloc(Size + 1);
    if (!sql) {
        return 0;
    }
    memcpy(sql, Data, Size);
    sql[Size] = '\0';

    // 1. Test sqlite3_complete
    int is_complete = sqlite3_complete(sql);

    // Since sqlite3_complete does not allocate memory, we should not free sql here
    // 2. Free the allocated memory for sql
    free(sql);

    // 3. Test sqlite3_close
    sqlite3 *db;
    int rc = sqlite3_open("./dummy_file", &db);
    if (rc == SQLITE_OK) {
        sqlite3_close(db);
    }

    // 4. Test sqlite3_memory_highwater
    sqlite3_int64 highwater = sqlite3_memory_highwater(0);

    // 5. Test sqlite3_memory_used
    sqlite3_int64 memory_used = sqlite3_memory_used();

    // 6. Test sqlite3_status
    int current, highwater_status;
    rc = sqlite3_status(SQLITE_STATUS_MEMORY_USED, &current, &highwater_status, 0);

    // 7. Test sqlite3_memory_used again
    memory_used = sqlite3_memory_used();

    // 8. Test sqlite3_hard_heap_limit64
    sqlite3_int64 previous_hard_limit = sqlite3_hard_heap_limit64(1024 * 1024);

    // 9. Test sqlite3_soft_heap_limit64
    sqlite3_int64 previous_soft_limit = sqlite3_soft_heap_limit64(512 * 1024);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_367(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
