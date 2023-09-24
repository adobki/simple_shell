#include "simple_shell.h"

/**
 * save_paths - Parses the system PATH string in the
 *             current environment.
 *
 * @argv0: Command used to launch Simple Shell.
 * @env: Environment variables from the shell.
 *
 * Return: Array of paths from PATH on SUCCESS,
 *         NULL otherwise.
 */
char **save_paths(char *argv0, char **env)
{
	char **paths = NULL, *str = NULL, *delim = ":";
	int i = 0;

	/* Find PATH string in env */
	while ((str = env[i]))
	{
		if (str[0] == 'P' && str[1] == 'A' && str[2] == 'T' && str[3] == 'H')
			break;
		str = NULL, i++;
	}
	if (!str)
		return (NULL);

	/* Create string array to store paths */
	paths = malloc(sizeof(char **) * ARR_SIZE / 2);
	if (!paths)
		return (NULL);

	/* Copy all paths in PATH to paths array */
	paths[0] = argv0;
	i = 1, paths[i] = strtok(str + 5, delim);
	while (paths[i] && i++ < (ARR_SIZE / 4 - 1))
		paths[i] = strtok(NULL, delim);

	return (paths);
}

/**
 * chk_path - Checks for a file in PATH.
 *
 * @argv: List of arguments passed from the commandline
 * @paths: Paths from system PATH Environment variable.
 *
 * Return: Path to file on SUCCESS.
 *         NULL otherwise.
 */
char *chk_path(char **argv, char **paths)
{
	char *str, *errstr = ": not found\n";
	int i = 0;

	/* Check if given command exists in the current path */
	if (!find_file(argv[0]))
		return (argv[0]);

	/* Search for given command in PATH locations if PATH is found */
	i = 1; /* Offset 1 for argv0 command from save_paths function */
	while (paths[i])
	{
		str = _concat(paths[i++], argv[0]);
		if (!find_file(str))
			return (str);
		free(str);
	}

	/* Print error on not found */
	if (isatty(0))
		print(paths[0]), print(": 0: "), print(argv[0]), print(errstr);
	else
		print(paths[0]), print(": 1: "), print(argv[0]), print(errstr);

	return (NULL);
}

/**
 * find_file - Checks is a give file/path is valid
 *
 * @path: Path/file to be checked.
 *
 * Return: 0 on success (if found/valid),
 *         -1 otherwise.
 */
int find_file(char *path)
{
	struct stat buffer;

	return (stat(path, &buffer));
}
