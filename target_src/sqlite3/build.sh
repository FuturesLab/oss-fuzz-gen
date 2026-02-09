mkdir bld
cd bld

export ASAN_OPTIONS=detect_leaks=0

# Limit max length of data blobs and sql queries to prevent irrelevant OOMs.
# Also limit max memory page count to avoid creating large databases.
export CFLAGS="$CFLAGS -DSQLITE_MAX_LENGTH=128000000 \
               -DSQLITE_MAX_SQL_LENGTH=128000000 \
               -DSQLITE_MAX_MEMORY=25000000 \
               -DSQLITE_PRINTF_PRECISION_LIMIT=1048576 \
               -DSQLITE_DEBUG=1 \
               -DSQLITE_MAX_PAGE_COUNT=16384"             
               
../configure --shared=0
make -j$(nproc)
make sqlite3.c

# To build batched harness, add this check for the fuzzing engine to decide whether to include main or not.
if [ "$FUZZING_ENGINE" = "afl" ]; then
  CFLAGS="$CFLAGS -DINC_MAIN"
fi

# use -r flag instead of -c to batch multiple .c files into one .o file
$CC $CFLAGS -I. -r /src/synthesized_driver/*.c \
    -o $SRC/sqlite3/test/ossfuzz.o

$CXX $CXXFLAGS \
    $SRC/sqlite3/test/ossfuzz.o -o $OUT/ossfuzz \
    $LIB_FUZZING_ENGINE -pthread  -ldl ./sqlite3.o

cp $SRC/*.options $SRC/*.dict $SRC/*.zip $OUT/