#include "../lib/server.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <string>

size_t ft_strlen(const char *s)
{
	size_t idx = 0;

	while (s && s[idx] != '\0')
		++idx;
	return idx;
}

char*	add_char(char *str, char a)
{
	size_t i = 0;
	size_t len = ft_strlen(str);
	char *tmp = (char *)malloc(sizeof(char) * (len + 2));
	if (!tmp)
		return (NULL);
	for (i = 0; i < len; i++)
		tmp[i] = str[i];
	tmp[i] = a;
	tmp[++i] = '\0';
	free(str);
	return (tmp);
}

static int	count_words(const char *str, char c)
{
	int i;
	int trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char*	word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char**	ft_split(char const* s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	if (!s || !(split = (char **)malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}


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

	if (command == NULL)
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

std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Dosya açılamadı: " << filename << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));

    file.close();
    return content;
}


int reqCount = 0;

std::string alp(client cliData)
{
    reqCount++;

    std::string val(ft_exec((char *)"./bins/alp", NULL));

    return (val);
}

std::string users(client cliData)
{
    std::string val(ft_exec((char *)"./bins/index", NULL));

    return (val);  
}

std::string python(client cliData)
{
    std::string val(ft_system("ls"));
    return (val);
}

std::string desktopInfo(client cliData)
{
    std::string fileContent = "bash ./bash/desktop.sh " + cliData.queryString;

    fileContent = ft_system((char *)fileContent.c_str());

    return (fileContent);
}

std::string desktophtml(client cliData)
{
    std::string fileContent = readFileToString("./html/index.html");
    return (fileContent);
}

int main()
{
    server mysw;

    mysw.handleGet("/desktop", desktophtml);
    mysw.handleGet("/desktopinfo", desktopInfo);
    mysw.handleGet("/index", users);
    mysw.handleGet("/alp", alp);
    mysw.handleGet("/python", python);

    mysw.createServer(2626);
}