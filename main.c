#include "libs/fileManager.h"
#include <linux/limits.h>
#include <stdio.h>

int main() {

  char** files;
  char path[PATH_MAX];
  getCallerPath(path);

  getFilesInDirectory(path, files);

  return 1;
}
