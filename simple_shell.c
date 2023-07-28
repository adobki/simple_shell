#include "simple_shell.h"

/**
 * main - Entry point for the program
 *
 * @argv: List of arguments passed from the commandline
 * @argc: Number of arguments passed from the commandline
 * @env: Environment variables from the shell.
 *
 * Return: 0 on SUCCESS,
 *         1 otherwise.
 */
int main(int argc, char **argv, char **env)
{
	char **usr_str, **paths;
	size_t ret = 1;

	/* Store paths in system PATH environment variable */
	paths = save_paths(argv[0], env);
	if (!paths)
		return (1);

	/* Check if interactive mode was invoked */
	if (argc > 1)
		runcmd(++argv, env, paths), ret = 0;

	/* Create empty string for user command and arguments */
	usr_str = malloc(sizeof(char *) * 3);
	if (usr_str)
	{
		usr_str[0] = NULL, usr_str[1] = NULL, usr_str[2] = NULL;

		usr_str[0] = malloc(sizeof(char) * ARR_SIZE);
		if (!usr_str[0])
			ret = 0;
	}
	else
		ret = 0;

	/* Start command processing on successful initialisation */
	if (ret)
		cmdloop(argc, env, &*usr_str, &*paths);

	/* Free up allocated memmory and exit */
	free(paths), free(usr_str[0]), free(usr_str);

	return (0);
}

/**
 * cmdloop - Runs the interactive shell in a loop until exit.
 *
 * @argc: Number of arguments passed from the commandline
 * @env: Environment variables from the shell.
 * @usr_str: List of argument and parameters passed by the user.
 * @paths: List of paths from the PATH environment variable.
 *
 * Return: Always 0.
 */
int cmdloop(int argc, char **env, char **usr_str, char **paths)
{
	int i = 0;
	char *delim = " ", *prompt = "($) ";
	size_t str_size = ARR_SIZE, ret = 1;

	while (ret >= 1)
	{
		/* Print prompt if running in interactive mode */
		if (isatty(0))
			print(prompt);

		ret = getline(usr_str, &str_size, stdin);
		if ((int)ret < 1)
			break;
		if (*usr_str[0] < 33)
			continue;

		/* Remove trailing blanks from end of getline string*/
		i = _strlen(usr_str[0]);
		while (i-- && usr_str[0][i] < 33)
			usr_str[0][i] = '\0';

		/* Split command and parameters into an array */
		i = 0, usr_str[0] = strtok(usr_str[0], delim);
		while (usr_str[i] && i++ < (int)(str_size / 4 - 1))
			usr_str[i] = strtok(NULL, delim);

		/* Run given command */
		runcmd(usr_str, env, paths);
	}

	/* Print new line before exit if running in interactive mode */
	if (isatty(0) && argc < 2)
		print("\n");

	return (0);
}

/**
 * runcmd - Runs a command given to the shell
 *
 * @argv: List of arguments passed from the commandline
 * @env: Environment variables from the shell.
 * @paths: Paths from system PATH Environment variable.
 *
 * Return: 0 on SUCCESS,
 *         -1 otherwise.
 */
int runcmd(char **argv, char **env, char **paths)
{
	pid_t pid;
	int extcode = 0;
	char *path;

	/* Check if exit command was given */
	if (!_strcomp(argv[0], "exit"))
		free(paths), exit(0);

	/* Check if given command exits in PATH */
	path = chk_path(argv, paths);
	if (!path)
		return (-1);

	/* Create child process to run command */
	pid = fork();
	if (pid == -1)
		return (pid);

	/* Check if child or parent process from fork */
	if (!pid)
	{
		/* Run given command */
		if ((int)execve(path, argv, env))
			print(argv[0]), print(": command not found\n"),	extcode = -1;

		/* Exit child process */
		free(path), exit(extcode);
	}
	else
		wait(&extcode);

	return (0);
}
