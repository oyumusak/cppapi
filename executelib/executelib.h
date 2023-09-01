#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


char*   ft_exec(char* command, char** envp);
char*   ft_system(char *command);


