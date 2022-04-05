/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:44:03 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 11:33:42 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include "../libft/libft.h"

static char	*get_current_line(int rv, char **str)
{
	char	*newline;
	char	*temp;
	char	*line;

	newline = ft_strchr(*str, '\n');
	line = NULL;
	if (newline)
	{
		line = ft_strtrimchr(*str, '\n');
		if (*(newline + 1))
			temp = ft_strdup(newline + 1);
		else
			temp = NULL;
		free(*str);
		*str = temp;
	}
	else if (rv == 0 && *str)
	{
		line = ft_strdup(*str);
		free(*str);
		*str = NULL;
	}
	return (line);
}

static char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	int			rv;

	if (fd < 0)
		return (NULL);
	buffer = malloc((4 * sizeof(char)) + 1);
	if (!buffer)
		return (NULL);
	rv = 1;
	while (rv > 0 && !ft_strchr(str, '\n'))
	{
		rv = read(fd, buffer, 4);
		buffer[rv] = 0;
		if (rv >= 0)
			str = ft_strupdate(str, buffer);
		if (!str)
			rv = -1;
	}
	free(buffer);
	buffer = NULL;
	return (get_current_line(rv, &str));
}

int	here_doc(t_subprocess *subprocess)
{
	int		pipe_fds[2];
	char	*line;

	pipe(pipe_fds);
	ft_print_pipe(subprocess->commands_len - 1);
	line = get_next_line(0);
	while (ft_strlen(line) != ft_strlen(subprocess->delim)
		|| ft_strncmp(line, subprocess->delim, ft_strlen(subprocess->delim)))
	{
		if (!line)
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			free(line);
			ft_print_error("zsh: ", 1, 0, 1);
		}
		write(pipe_fds[1], line, ft_strlen(line));
		write(pipe_fds[1], "\n", 1);
		free(line);
		ft_print_pipe(subprocess->commands_len - 1);
		line = get_next_line(0);
	}
	free(line);
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

void	pipex_bonus(t_subprocess *subprocess)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	while (i < subprocess->commands_len - 1)
	{
		if (pipe(subprocess->pipes + (2 * i++)) < 0)
			ft_print_error("zsh: ", 1, 0, 1);
	}
	i = -1;
	if (subprocess->here_doc)
		move_fd(here_doc(subprocess), 0);
	else
		i += move_fd(ft_open(subprocess->infile, O_RDONLY), 0);
	while (++i < subprocess->commands_len)
	{
		pid = fork();
		if (pid < 0)
			ft_print_error("zsh: ", 1, 0, 1);
		else if (pid == 0 && subprocess->here_doc)
			execute_command(subprocess, i, O_WRONLY | O_CREAT | O_APPEND);
		else if (pid == 0)
			execute_command(subprocess, i, O_WRONLY | O_CREAT | O_TRUNC);
	}
	close_pipes(subprocess);
	while (wait(&status) > 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_subprocess	*subprocess;

	if (argc < 5)
		ft_print_error("Please provide commands and paths...", 0, 0, 1);
	subprocess = malloc(sizeof(t_subprocess));
	subprocess->infile = argv[1];
	subprocess->outfile = argv[argc - 1];
	subprocess->paths = get_paths(envp);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		argc -= 1;
		argv += 1;
		subprocess->delim = argv[1];
		subprocess->here_doc = 1;
	}
	subprocess->pipes = malloc((argc - 3) * 2 * sizeof(int));
	subprocess->commands_len = argc - 3;
	subprocess->commands = get_commands(argv + 2, argc - 3);
	subprocess->envp = envp;
	pipex_bonus(subprocess);
	ft_freestrs(subprocess->paths);
	ft_freestrarrs(subprocess->commands);
	free(subprocess->pipes);
	free(subprocess);
	return (ft_print_error("zsh: ", 1, argv[1], 0));
}
