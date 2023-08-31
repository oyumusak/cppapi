#include "42lib.h"

char*   ft_system(char *command)
{
    char *ret = NULL;
    int fd[2], status;
    int error_log = open("error.log", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (error_log == -1)
        return NULL;

    if (dup2(error_log, 2) == -1)
        return NULL;

    if (pipe(fd) == -1)
       return NULL;
    
    int pid = fork();

    if (pid == 0)
    {
        if (dup2(fd[1], 1) == -1)
		{
			close(error_log);
			exit(EXIT_FAILURE);
		}
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
		{
			close(error_log);
			exit(EXIT_FAILURE);
		}
		if (system(command) == -1)
		{
			close(error_log);
			exit(EXIT_FAILURE);
		}
        exit(EXIT_SUCCESS);
    }
    if (close(fd[1]) == -1)
    {
        close(error_log);
        return NULL;
    }
    waitpid(pid, &status, 0);
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
		exit(EXIT_FAILURE);
	if (read_res == -1)
		exit(EXIT_FAILURE);
    close(error_log);
	return ret;
}
