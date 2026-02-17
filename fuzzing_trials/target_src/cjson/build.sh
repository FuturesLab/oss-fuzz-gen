#!/bin/bash -eu
# Copyright 2019 Google Inc.
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
# Run the OSS-Fuzz script in the project

mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=OFF -DENABLE_CJSON_TEST=OFF ..
make -j$(nproc)


# afl + any approach other than liberator: include main and don't link in libfuzzer
# afl + liberator: don't include main and link in libfuzzer
# libfuzzer + any approach: don't include main and link in libfuzzer

# Liberator requires linking against the fuzzing engine library  to access LLVMFuzzerMutate functions
if [[ "$FUZZING_ENGINE" = "afl" && "$APPROACH" != "liberator" ]]; then
  CFLAGS="$CFLAGS -DINC_MAIN"
  CXXFLAGS="$CXXFLAGS -DINC_MAIN"
fi

# libfuzzer requires compilation flags for itself, liberator requires libfuzzer stubs for fuzzing as well
if [[ "$FUZZING_ENGINE" = "libfuzzer" || "$APPROACH" = "liberator" ]]; then
  CFLAGS="$CFLAGS $LIB_FUZZING_ENGINE"
  CXXFLAGS="$CXXFLAGS $LIB_FUZZING_ENGINE"
fi

if [ "$SANITIZER" = "none" ]; then
  CFLAGS="$CFLAGS -pthread  -ldl"
  CXXFLAGS="$CXXFLAGS -pthread  -ldl"
fi

$CXX $CXXFLAGS /src/synthesized_driver/*.c* -I. \
    -o $OUT/cjson_read_fuzzer \
    $SRC/cjson/build/libcjson.a

cp $OUT/cjson_read_fuzzer $OUT/fuzz_driver_$SANITIZER

find $SRC/cjson/fuzzing/inputs -name "*" | \
     xargs zip $OUT/cjson_read_fuzzer_seed_corpus.zip

cp $SRC/cjson/fuzzing/json.dict $OUT/cjson_read_fuzzer.dict