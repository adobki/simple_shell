#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

#define ARR_SIZE 100

int cmdloop(int argc, char **env, char **usr_str, char **paths);
int runcmd(char **argv, char **env, char **paths);
int find_file(char *path);
int print(char *str);
char **save_paths(char *argv0, char **env);
char *chk_path(char **argv, char **paths);
char *_concat(char *str1, char *str2);
int _strlen(char *str);
int _strcomp(char *str1, char *str2);

/*
 * -------------------- TODO --------------------
 * 1. Fix memory leaks (malloc/free).
 */

#endif /*_SIMPLE_SHELL_H_*/
