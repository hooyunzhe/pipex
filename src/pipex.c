/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun-zhe <hyun-zhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:28:18 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/02/21 11:33:17 by hyun-zhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include "../libft/libft.h"

void	pipex(t_subprocess *subprocess)
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
	i = move_fd(ft_open(subprocess->infile, O_RDONLY), 0);
	while (i < subprocess->commands_len)
	{
		pid = fork();
		if (pid < 0)
			ft_print_error("zsh: ", 1, 0, 1);
		else if (pid == 0)
			execute_command(subprocess, i, O_WRONLY | O_CREAT | O_TRUNC);
		i++;
	}
	close_pipes(subprocess);
	while (wait(&status) > 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_subprocess	*subprocess;

	if (argc != 5)
		ft_print_error("Please provide commands and path...", 0, 0, 1);
	subprocess = malloc(sizeof(t_subprocess));
	subprocess->pipes = malloc((argc - 3) * 2 * sizeof(int));
	subprocess->infile = argv[1];
	subprocess->outfile = argv[argc - 1];
	subprocess->paths = get_paths(envp);
	subprocess->commands_len = argc - 3;
	subprocess->commands = get_commands(argv + 2, argc - 3);
	subprocess->envp = envp;
	pipex(subprocess);
	ft_freestrs(subprocess->paths);
	ft_freestrarrs(subprocess->commands);
	free(subprocess->pipes);
	free(subprocess);
	return (ft_print_error("zsh: ", 1, argv[1], 0));
}
