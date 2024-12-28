#include "../managers/fileManager.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>

void readIgnoreFile(char *path, char arrayOfIgnores[300][300], int* numberOfIngoredFiles) {
  FILE *file;
  file = fopen(strcat(path, "/.dsvcignore"), "r");
  char line[30];

  while (fscanf(file, "%s", line) == 1) {
    strcpy(arrayOfIgnores[*numberOfIngoredFiles], line);
    (*numberOfIngoredFiles)++;
  }

  fclose(file);
}

void checkForDSVCIgnore(char ignoreFiles[300][300], int* numberOfIngoredFiles) {
  char caller_path[PATH_MAX];
  char *files[PATH_MAX];
  int numberOfFiles;
  int index = 0;

  getCallerPath(caller_path);
  getFilesInDirectory(caller_path, files, &numberOfFiles);

  while (index < numberOfFiles) {
    if (strcmp(files[index], ".dsvcignore") == 0) {
      readIgnoreFile(caller_path, ignoreFiles, numberOfIngoredFiles);
    }
    index++;
  }


}
