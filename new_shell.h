#ifndef NEW_SHELL_H
#define NEW_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define HIST_MAX 100
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


typedef struct list_t {
    char *str;
    int line_count;
    struct list_t *next;
} list_t;

typedef struct info_t {
    char **argv;
    char **environment;
    char *cmd_buffer;
    list_t *history;
    int histcount;
    int linecount_flag;
    int status;
    int line_count;
    int cmd_buf_type;
    char *path;
} info_t;

void remove_comments(char *buffer);
void delete_node_at_index(list_t **head, int index);
void _putsfd(char *str, int file_descriptor);
void _putfd(char c, int file_descriptor);
void _eputs(char *str);
void _eputchar(char c);
void print_integer(int input, int fd);
void print_error_msg(info_t *info_data, char *error_str);
void find_command(info_t *infoData);
void build_history_list(info_t *info_data, char *buffer, int line_count);
void renumber_history(info_t *info_data);
void display_help(info_t *info_data);
int write_to_history(info_t *info_data);
int display_help(info_t *info_data);
int build_history_list(info_t *info_data, char *buffer, int line_count);
int display_help(info_t *info_data);

#endif /* NEW_SHELL_H */
