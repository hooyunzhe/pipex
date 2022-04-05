#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_subprocess
{
	pid_t	pid;
	int		*pipes;
	char	*infile;
	char	*outfile;
	char	**paths;
	int		here_doc;
	char	*delim;
	int		commands_len;
	char	***commands;
	char	**envp;
}			t_subprocess;

int		move_fd(int old_fd, int new_fd);
void	close_pipes(t_subprocess *subprocess);
char	**get_paths(char **envp);
char	***get_commands(char **args, int len);
void	execute_command(t_subprocess *subprocess, int index, int flags);

#endif