// Copyright MFDGaming 2023

// This file is licensed under
// the GPLv2 license

// I take no responibility
// for any malicious use of
// this file, use it at your
// own risk

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/param.h>
#include <string.h>

#define ALL_USERS_PATH "/home/C/"

void list_dir(char *path) {
  struct dirent *d;
  DIR *dr = opendir(path);
  if (dr != NULL) {
    for(d = readdir(dr); d != NULL; d = readdir(dr)) {
      printf("%s\n", d->d_name);
    }
    closedir(dr);
  }
}

void priview_file(char *path) {
  FILE *fp = fopen(path, "r");
  fseek(fp, 0, SEEK_END);
  size_t len = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char *data = malloc(len + 1);
  data[len] = '\0';
  fread(data, sizeof(char), len, fp);
  fclose(fp);
  printf("%s\n", data);
  free(data);
}

int main(int argc, char **argv, char **envp) {
  printf("LIST ALL USERS? (y/n, default=y): ");
  char list_all_users = 'y';
  scanf("%c", &list_all_users);
  if (list_all_users == 'y' || list_all_users == '\n') {
    list_dir(ALL_USERS_PATH);
  }
  char user[9];
  user[8] = '\0';
  printf("INSERT USERNAME: ");
  scanf("%8s", user);
  int len = strlen(ALL_USERS_PATH) + strlen(user) + strlen("/programs/");
  char *programs = malloc(len + 1);
  strcpy(programs, ALL_USERS_PATH);
  strcat(programs, user);
  strcat(programs, "/programs/");
  programs[len] = '\0';
  list_dir(programs);
  printf("INSERT FILE NAME: ");
  char file[MAXPATHLEN];
  file[MAXPATHLEN-1] = '\0';
  scanf("%s", file);
  len += strlen(file);
  char *path = malloc(len + 1);
  path[len] = '\0';
  strcpy(path, programs);
  strcat(path, file);
  free(programs);
  puts("<------------------------------FILE START------------------------------>");
  priview_file(path);
  puts("<-------------------------------FILE END------------------------------->");
  free(path);
}
