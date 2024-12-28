#include <dirent.h>
#include <sys/stat.h>
#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void getFilesInDirectory(char *path, char **files, int* numberOfFiles) {
  DIR *d;
  int index = 0;
  struct dirent *dir;
  d = opendir(path);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")) {
        files[index] = dir->d_name;
        index++;
        (*numberOfFiles)++;
      }
    }
    closedir(d);
  }
}

void getCallerPath(char *path) {
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    strcpy(path, cwd);
  } else {
    perror("getcwd() error");
  }
}

void initDSVCProject(char *path){
  int check = mkdir(strcat(path,"/.dsvc"), 0777);
  if (check == 0) {
    printf("DSVC Project has been created");
  }else {
    printf("Unable to start DSVC Project");
  }
}

int checkForDSVCProject(char *path){

  char *files[PATH_MAX];
  int numberOfFiles = 0;
  int index = 0;

  getFilesInDirectory(path, files, &numberOfFiles);


  while (index < numberOfFiles) {
    if (!strcmp(files[index], ".dsvc")) {
      return 1;
    }
    index++;
  }

  return 0;

}
