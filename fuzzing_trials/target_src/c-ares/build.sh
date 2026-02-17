#!/bin/bash -eu
# Copyright 2016 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
################################################################################

cd $SRC/googletest
mkdir build
cd build
cmake ..
make -j$(nproc)
make install

cd $SRC/c-ares

# Build the project.
./buildconf
./configure --enable-debug --enable-tests
make clean
make -j$(nproc) V=1 all


# afl + any approach other than liberator: include main and don't link in libfuzzer
# afl + liberator: don't include main and link in libfuzzer
# libfuzzer + any approach: don't include main and link in libfuzzer

# test 1: make sure libfuzzer builds work
# test 2: include main for liberator

# Liberator requires linking against the fuzzing engine library  to access LLVMFuzzerMutate functions
if [[ "$FUZZING_ENGINE" == "afl" && "$APPROACH" != "liberator" ]]; then
  CFLAGS="$CFLAGS -DINC_MAIN"
  CXXFLAGS="$CXXFLAGS -DINC_MAIN"
fi

# libfuzzer requires compilation flags for itself, liberator requires libfuzzer stubs for fuzzing as well
if [[ "$FUZZING_ENGINE" == "libfuzzer" || "$APPROACH" == "liberator" ]]; then
  CFLAGS="$CFLAGS $LIB_FUZZING_ENGINE"
  CXXFLAGS="$CXXFLAGS $LIB_FUZZING_ENGINE"
fi

if [ "$SANITIZER" = "none" ]; then
  CFLAGS="$CFLAGS -pthread  -ldl"
  CXXFLAGS="$CXXFLAGS -pthread  -ldl"
fi

# Build the fuzzers.
$CC $CFLAGS -Iinclude -Isrc/lib -r /src/synthesized_driver/*.c* -o $WORK/ares-test-fuzz.o
$CXX $CXXFLAGS -std=c++11 $WORK/ares-test-fuzz.o \
    -o $OUT/ares_parse_reply_fuzzer \
    $SRC/c-ares/src/lib/.libs/libcares.a

cp $OUT/ares_parse_reply_fuzzer $OUT/fuzz_driver_$SANITIZER

# Archive and copy to $OUT seed corpus if the build succeeded.
zip -j $OUT/ares_parse_reply_fuzzer_seed_corpus.zip $SRC/c-ares/test/fuzzinput/*
zip -j $OUT/ares_create_query_fuzzer_seed_corpus.zip \
    $SRC/c-ares/test/fuzznames/*
