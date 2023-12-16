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

#define BUF_FLUSH (-1)
#define HIST_FILE ".history"
#define HIST_MAX 4096
#define CONVERT_UNSIGNED (1 << 0)
#define CONVERT_LOWERCASE (1 << 1)
#define WRITE_BUF_SIZE 1024

/* Define constants */
#define CMD_AND 1
#define CMD_OR 2
#define CMD_CHAIN 3

/* Define structure for the list node */
typedef struct list_s
{
    char *str;
    struct list_s *next;
} list_t;

/* Define structure for information about the shell */
typedef struct info_s
{
    char **argv;
    int status;
    int cmd_buf_type;
    list_t *alias;
    list_t *env;
} info_t;

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

typedef struct {
    // Define your info_t structure members here
} info_t;

/**
 * struct info - holds shell information
 * @env: array of environment variables
 * @alias: linked list of aliases
 * @argv: array of command arguments
 * @arg: buffer for command input
 * @path: path of the command
 * @status: exit status
 * @lineCount: line count
 * @lineCountFlag: line count flag
 * @errNum: error number
 * @environ: copy of environment variables as strings
 */
typedef struct info
{
    char **env;
    list_t *alias;
    char **argv;
    char *arg;
    char *path;
    int status;
    ssize_t lineCount;
    int lineCountFlag;
    int errNum;
    char **environ;
    list_t *history;
} info_t;

/**
 * struct builtin - holds shell builtin command information
 * @type: command name
 * @func: corresponding function
 */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *infoData);
} builtin_table;

/**
 * struct list - linked list structure
 * @str: string data
 * @num: numeric data
 * @next: pointer to the next node
 */
typedef struct list
{
    char *str;
    ssize_t num;
    struct list *next;
} list_t;

/**
 * struct info_s - structure to hold shell information
 * @argv: argument vector
 * @env: environment variables
 * @status: exit status
 * @line_count: line count
 * @linecount_flag: flag for line count
 * @path: path
 */
typedef struct info_s
{
	char **argv;
	char **env;
	int status;
	int line_count;
	int linecount_flag;
	char *path;
} info_t;

/**
 * custom_strcpy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *custom_strcpy(char *destination, char *source);

/**
 * custom_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *custom_strdup(const char *str);

/**
 * custom_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void custom_puts(char *str);

/**
 * custom_putchar - writes the character c to stdout
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char character);

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av);

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin(info_t *info);

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info);

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info);
/**
 * _split_string - splits a string into words. Repeat delimiters are ignored
 * @input_str: the input string
 * @delimiter_str: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_split_string(char *input_str, char *delimiter_str);

/**
 * _split_string2 - splits a string into words
 * @input_str: the input string
 * @delimiter: the delimiter
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_split_string2(char *input_str, char delimiter);


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
int customFree(void **targetPtr);
int isExecutable(info_t *infoData, char *filePath);
char *duplicateSubstring(char *pathString, int start, int stop);
char *findCmdInPath(info_t *infoData, char *pathString, char *cmd);
char *_custom_memset(char *dest, char byte, unsigned int size);
void free_string_array(char **str_array);
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int custom_shell(info_t *infoData, char **arguments);
int find_builtin(info_t *infoData);
void find_command(info_t *infoData);
void fork_command(info_t *infoData);
int custom_strlen(char *str);
int custom_strcmp(char *str1, char *str2);
char *custom_starts_with(const char *haystack, const char *needle);
char *custom_strcat(char *destination, char *source);
int isChainDelimiter(info_t *info, char *buf, size_t *p);
void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replaceAliases(info_t *info);
int replaceVariables(info_t *info);
int replaceString(char **old, char *newStr);

#endif /* NEW_SHELL_H */
