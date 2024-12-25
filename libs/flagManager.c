#include "fileManager.h"
#include <linux/limits.h>

int isArgumentAFlag(char *argument) { return argument[0] == '-'; }

void tryToCreateProject() {
  char path[PATH_MAX];
  getCallerPath(path);

  int isProjectInited = checkForDSVCProject(path);

  if (!isProjectInited) {
    initDSVCProject(path);
  }
}

void getFlags(char **arguments, int argumentsSize) {
  int index = 1;

  if (index > argumentsSize - 1) {
    tryToCreateProject();
  }

  while (index < argumentsSize) {
    char *argument = arguments[index];
    int isFlag = isArgumentAFlag(argument);
    index++;
  }
}
