#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void getFilesInDirectory(char *path, char **files) {
  DIR *d;
  struct dirent *dir;
  d = opendir(path);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..") &&
          dir->d_name[0] != '.') {
        printf("%s\n", dir->d_name);
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
