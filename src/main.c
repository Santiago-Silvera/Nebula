#include "core.h"
#include <stdlib.h>

void init();
void cleanup();

int main() {

  #ifdef DEBUG
    NINFO("Running in debug mode.\n")
  #else
    NINFO("Running in release mode.\n")
  #endif

  EngineContext ctx = initEngine();

  mainLoop(ctx);

  cleanupEngine(ctx);
  return 0;
}

