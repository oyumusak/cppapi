#include "executelib.h"
#include "utils.h"

static void	free_double(char **str)
{
	size_t idx = 0;

	while (str[idx] != NULL)
	{
		free(str[idx]);
		++idx;
	}
	free(str);
}

char*	ft_exec(char* command, char **envp)
{
	int	status, fd[2];
	char *ret = NULL, **d_array;

	if (command == NULL) // || envp == NULL
		return NULL;

	int error_log = open("error.log", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (error_log == -1)
        return NULL;

    if (dup2(error_log, 2) == -1)
        return NULL;

	d_array = ft_split(command, ' ');

	if (pipe(fd) == -1)
	{
		if (d_array != NULL)
			free_double(d_array);
		close(error_log);
		return NULL;
	}
	
	int pid = fork();

	if (pid == 0)
	{
		if (dup2(fd[1], 1) == -1)
		{
			perror("Error: dup2: ");
			free_double(d_array);
			close(error_log);
			exit(EXIT_FAILURE);
		}
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
		{
			perror("Error: close: ");
			free_double(d_array);
			close(error_log);
			exit(EXIT_FAILURE);
		}
		if (execve(d_array[0], d_array, envp) == -1)
		{
			perror("Error: execve: ");
			free_double(d_array);
			close(error_log);
			exit(EXIT_FAILURE);
		}
	}
	if (close(fd[1]) == -1)
	{
		free_double(d_array);
		close(error_log);
		return NULL;
	}
	waitpid(pid, &status, 0);
	free_double(d_array);
	if (WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_FAILURE))
	{
		close(error_log);
		return NULL;
	}
	int read_res = 0;
	char a;
	while ((read_res = read(fd[0], &a, 1)) > 0)
	{
		ret = add_char(ret, a);
		if (ret == NULL)
		{
			close(error_log);
			return NULL;
		}
	}
	if (close(fd[0]) == -1)
	{
		close(error_log);
		return NULL;
	}
	if (read_res == -1)
	{
		close(error_log);
		return NULL;
	}
	close(error_log);
	return ret;
}
