#include "../funcs/ignoreFunctionality.h"
#include "fileManager.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

int isArgumentAFlag(char *argument) { return argument[0] == '-'; }

void tryToCreateProject() {
  char path[PATH_MAX];
  getCallerPath(path);

  int isProjectInited = checkForDSVCProject(path);

  if (!isProjectInited) {
    initDSVCProject(path);
  }
}

void filterOutIgnored(char **files, int numberOfFiles,
                      char ignoredFiles[300][300], int numberOfIgnoredFiles,
                      char outputFies[300][300], int *numberOfFilteredFiles) {

  int index = 0;
  int indexIgnored = 0;
  int shouldIgnore = 0;

  while (index < numberOfFiles) {
    char *fileName = files[index];
    while (indexIgnored < numberOfIgnoredFiles) {
      char *ignoreFile = ignoredFiles[indexIgnored];
      if (strcmp(fileName, ignoreFile) == 0) {
        shouldIgnore = 1;
      }
      indexIgnored++;
    }
    if (shouldIgnore == 0) {
      strcpy(outputFies[*numberOfFilteredFiles], fileName);
      (*numberOfFilteredFiles)++;
    }
    shouldIgnore = 0;
    indexIgnored = 0;
    index++;
  }
}

void handleListingFiles() {
  char caller_path[PATH_MAX];
  char *files[PATH_MAX];
  char ignoredFiles[300][300];
  char filteredFiles[300][300];
  int numberOfFiles = 0;
  int numberOfIgnoredFiles = 0;
  int numberOfFilteredFiles = 0;
  int index = 0;

  getCallerPath(caller_path);
  checkForDSVCIgnore(ignoredFiles, &numberOfIgnoredFiles);
  getFilesInDirectory(caller_path, files, &numberOfFiles);

  filterOutIgnored(files, numberOfFiles, ignoredFiles, numberOfIgnoredFiles,
                   filteredFiles, &numberOfFilteredFiles);

  while (index < numberOfFilteredFiles) {
    printf("%s \n", filteredFiles[index]);
    index++;
  }
}

void whichFlag(char *argument) {
  if (strcmp(argument, "-l") == 0) {
    handleListingFiles();
    return;
  }
  if (strcmp(argument, "-i") == 0) {
    tryToCreateProject();
    return;
  }
  printf("Unsuported flag");
}

void getFlags(char **arguments, int argumentsSize) {
  int index = 1;

  if (index > argumentsSize - 1) {
    tryToCreateProject();
  }

  while (index < argumentsSize) {
    char *argument = arguments[index];
    int isFlag = isArgumentAFlag(argument);
    if (isFlag) {
      whichFlag(argument);
    }
    index++;
  }
}
