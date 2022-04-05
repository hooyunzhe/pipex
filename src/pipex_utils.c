/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:23:10 by hyun-zhe          #+#    #+#             */
/*   Updated: 2021/12/14 16:24:10 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include "../libft/libft.h"

int	move_fd(int old_fd, int new_fd)
{
	if (old_fd > 0)
	{
		if (dup2(old_fd, new_fd) < 0)
			ft_print_error("zsh: ", 1, 0, 1);
		close(old_fd);
	}
	if (!access("temp.txt", F_OK))
		return (1);
	else
		return (0);
}

void	close_pipes(t_subprocess *subprocess)
{
	int	i;

	i = 0;
	while (i < (subprocess->commands_len - 1) * 2)
		close(subprocess->pipes[i++]);
}

char	**get_paths(char **envp)
{
	int		i;
	char	*path_line;
	char	**paths;

	i = 0;
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	path_line = ft_substr(*envp, 5, ft_strlen(*envp));
	paths = ft_split(path_line, ':');
	while (paths[i])
	{
		free(path_line);
		path_line = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strdup(path_line);
		i++;
	}
	free(path_line);
	return (paths);
}

char	***get_commands(char **args, int len)
{
	int		i;
	char	***commands;

	i = 0;
	commands = malloc(ft_strslen(args) * sizeof(char **));
	while (i < len)
	{
		if (!ft_strchr(args[i], '\'') && !ft_strchr(args[i], '"'))
			commands[i] = ft_split(args[i], ' ');
		else if ((ft_strchr(args[i], '\'') < ft_strchr(args[i], '"')
				&& ft_strchr(args[i], '\'')) || !ft_strchr(args[i], '"'))
			commands[i] = ft_split(args[i], '\'');
		else if ((ft_strchr(args[i], '\'') > ft_strchr(args[i], '"')
				&& ft_strchr(args[i], '"')) || !ft_strchr(args[i], '\''))
			commands[i] = ft_split(args[i], '"');
		if (ft_strchr(args[i], '\'') || ft_strchr(args[i], '"'))
			commands[i][0][ft_strlen(commands[i][0]) - 1] = 0;
		i++;
	}
	commands[i] = 0;
	return (commands);
}

void	execute_command(t_subprocess *subprocess, int index, int flags)
{
	int		i;
	char	*command;
	char	*full_command;

	if ((index > 0 && dup2(subprocess->pipes[(index - 1) * 2], 0) < 0)
		|| (index < subprocess->commands_len - 1
			&& dup2(subprocess->pipes[index * 2 + 1], 1) < 0))
		ft_print_error("zsh: ", 1, 0, 1);
	else if (index == subprocess->commands_len - 1)
		move_fd(ft_open(subprocess->outfile, flags), 1);
	close_pipes(subprocess);
	i = 0;
	command = subprocess->commands[index][0];
	while (subprocess->paths[i])
	{
		full_command = ft_strjoin(subprocess->paths[i], command);
		if (!access(full_command, X_OK))
			execve(full_command, subprocess->commands[index], subprocess->envp);
		free(full_command);
		i++;
	}
	ft_print_error("zsh: command not found", 0, command, 1);
}
