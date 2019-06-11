// build protobuf-c-text library somewhat like this:
// CC=clang CXX=clang++ CFLAGS="-g -O2 -fsanitize=fuzzer-no-link,address -I${HOME}/fuzzing/build/include" CXXFLAGS="-g -O2 -fsanitize=fuzzer-no-link,address -I${HOME}/fuzzing/build/include" LDFLAGS="-L${HOME}/fuzzing/build/lib" ./configure --prefix=${HOME}/fuzzing/build
//
// then build this fuzz target binary like this:
// clang fuzz-c-parse.c addressbook.pb-c.c -I${HOME}/fuzzing/build/include -L${HOME}/fuzzing/build/lib -lprotobuf-c-text -lprotobuf-c -fsanitize=fuzzer,address -o fuzz-c-parse

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <protobuf-c/protobuf-c.h>
#include "protobuf-c/protobuf-c-text.h"
#include "addressbook.pb-c.h"

int LLVMFuzzerTestOneInput(uint8_t *Data, size_t Size)
{
  ProtobufCTextError tf_res;
  Tutorial__Short *shortmsg;

  /* filter all input that is too short or not null-terminated as it occludes fuzzing */
  if (Size<2 || Data[Size-1] != 0) return 0;

  shortmsg = (Tutorial__Short *)protobuf_c_text_from_string(
      &tutorial__short__descriptor,
      (char *)Data,
      &tf_res, NULL);
  if (tf_res.error_txt) {
    free(tf_res.error_txt);
  }
  if (shortmsg) {
    tutorial__short__free_unpacked(shortmsg, NULL);
  }

  return 0;
}
