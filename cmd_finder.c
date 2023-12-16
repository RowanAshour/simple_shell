#include "new_shell.h"

/**
 * findCmdInPath - finds this cmd in the PATH string
 * @infoData: the info struct
 * @pathString: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *findCmdInPath(info_t *infoData, char *pathString, char *cmd)
{
    int i = 0, currPos = 0;
    char *path;

    if (!pathString)
        return NULL;
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (isExecutable(infoData, cmd))
            return cmd;
    }
    while (1)
    {
        if (!pathString[i] || pathString[i] == ':')
        {
            path = duplicateSubstring(pathString, currPos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (isExecutable(infoData, path))
                return path;
            if (!pathString[i])
                break;
            currPos = i;
        }
        i++;
    }
    return NULL;
}

/**
 * duplicateSubstring - duplicates characters from start to stop in pathString
 * @pathString: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicateSubstring(char *pathString, int start, int stop)
{
    static char buffer[1024];
    int k = 0;

    for (int i = start; i < stop; i++)
        if (pathString[i] != ':')
            buffer[k++] = pathString[i];
    buffer[k] = '\0';
    return buffer;
}



/**
 * isExecutable - determines if a file is an executable command
 * @infoData: the info struct
 * @filePath: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExecutable(info_t *infoData, char *filePath)
{
    struct stat fileStat;

    (void)infoData;
    if (!filePath || stat(filePath, &fileStat))
        return 0;

    if (fileStat.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

