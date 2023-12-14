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

#define BUF_FLUSH '\0'
#define HIST_FILE ".history"
#define HIST_MAX 4096

#define CONVERT_UNSIGNED (1 << 0)
#define CONVERT_LOWERCASE (1 << 1)

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\0'

typedef struct list_s {
    char *str;
    int num;
    struct list_s *next;
} list_t;

typedef struct info {
    char *arguments;
    char **argument_vector;
    char *path_string;
    char *file_name;
    int argument_count;
    list_t *environment;
    list_t *history_list;
    list_t *alias_list;
    char **environ;
    char **command_buffer;
    int read_file_descriptor;
    int histcount;
} info_t;

typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

typedef struct info_s
{
	list_t *env;
	char **environ;
	int env_changed;
} info_t;

typedef struct list_s {
    char *str;
    int num;
    struct list_s *next;
} list_t;

typedef struct shell_info {
    char *arguments;
    char **argument_vector;
    char *path_string;
    char *file_name;
    int argument_count;
    list_t *environment;
    list_t *history_list;
    list_t *alias_list;
    char **environ;
    char **command_buffer;
    int read_file_descriptor;
} shell_info_t;

typedef struct list_s
{
	int index;
	char *data;
	struct list_s *next;
} list_t;

typedef struct info {
    /* Add any necessary members here */
    list_t *env;
    int env_changed;
    char **environ;
} info_t;

typedef struct list {
    char *str;
    int num;
    struct list *next;
} list_t;

typedef struct list {
    char *str;
    int num;
    struct list *next;
} list_t;

int set_environment_variable(info_t *info_data, char *variable, char *value);
int remove_environment_variable(info_t *info_data, char *variable);
char **fetch_environment(info_t *info_data);
void init_shell_info(shell_info_t *shell_info);
void configure_shell_info(shell_info_t *shell_info, char **argument_vector);
void release_shell_info(shell_info_t *shell_info, int free_all);
int read_from_history(info_t *info_data);
int write_to_history(info_t *info_data);
int build_history_list(info_t *info_data, char *buffer, int line_count);
int renumber_history(info_t *info_data);
char *obtain_history_file(info_t *info_data);
char *convert_number_str(long int num, int base, int flags);
void print_error_msg(info_t *info_data, char *error_str);
int print_integer(int input, int fd);
int _str_to_int(char *str);
void replace_comments(char *buf);
list_t *add_node_to_end(list_t **head, const char *data, int index);
list_t *add_node_to_start(list_t **head, const char *data, int index);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list_nodes(list_t **head);
size_t print_data_only(const list_t *node);
int set_environment_variable(info_t *info_data, char *variable, char *value);
int remove_environment_variable(info_t *info_data, char *variable);
char **fetch_environment(info_t *info_data);
char **convert_list_to_strings(list_t *head);
size_t display_list(const list_t *list);
ssize_t find_node_index(list_t *head, list_t *node);
list_t *find_node_with_prefix(list_t *node, char *prefix, char c);
int print_alias_string(list_t *node);
int define_alias(info_t *info_data, char *str);
int display_history(info_t *info_data);
int manage_alias(info_t *info_data);
int remove_alias(info_t *info_data, char *str);
int _eputchar(char character);
int _puts_fd(char *input_str, int fd);
void _eputs(char *input_str);
int _put_fd(char character, int fd);
char *_character_find(char *string, char character);
char *_string_copy(char *destination, char *source, int count);
char *_string_concatenate(char *destination, char *source, int count);
int convert_to_integer(char *str);
int is_alphabetic(int character);
int check_interactive(info_t *info_data);
int is_separator(char character, char *separator_str);


#endif /* NEW_SHELL_H */
