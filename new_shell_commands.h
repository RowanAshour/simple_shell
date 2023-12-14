#ifndef NEW_SHELL_COMMANDS_H
#define NEW_SHELL_COMMANDS_H

#include "new_shell.h"

int change_directory(info_t *info_data);
int display_help(info_t *info_data);
int exit_shell(info_t *info_data);
int set_environment(info_t *shell_info, const char *name, const char *value);
int my_environment(info_t *shell_info);
char *get_environment(info_t *shell_info, const char *name);


#endif /* NEW_SHELL_COMMANDS_H */

