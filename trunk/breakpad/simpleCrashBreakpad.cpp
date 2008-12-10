#include <cstdio>
 
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/linux_thread.h"
 
 
using namespace google_breakpad;
 
// Callback when minidump written.
static bool MinidumpCallback(const char *dump_path,
                             const char *minidump_id,
                             void *context,
                             bool succeeded) {
  printf("%s is dumped\n", minidump_id);
  printf("%s is dumped\n", minidump_id);
  printf("%s is dumped\n", minidump_id);
  printf("%s is dumped\n", minidump_id);
  printf("%s is dumped\n", minidump_id);
  printf("%s is dumped\n", minidump_id);
  printf("%s is dumped\n", minidump_id);
  printf("%s is dumped\n", minidump_id);
 
  return succeeded;
}

void callMe() {
  int* foo = NULL;
  *foo = 42;
} 


void callMeFoo() {
  callMe();
}

int main(int argc, char *argv[]) {
  ExceptionHandler handler_process(".", NULL, MinidumpCallback,
                           NULL, true);
  
  callMeFoo();
  return 0;
} 

