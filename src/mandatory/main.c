/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:21:30 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/08 18:15:38 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	leaks(void)
{
	system("leaks pipex");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

	// atexit(leaks);
	p.argc = argc;
	p.args = argv;
	p.envp = envp;
	if (argc == 5)
	{
		p.in_fd = open(argv[1], O_RDONLY);
		if (p.in_fd < 0)
		{
			perror("Error opening input file");
			return (1);
		}
		p.out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (p.out_fd < 0)
		{
			perror("Error opening output file");
			return (1);
		}
		execute_pipe(&p);
	}
	else
		perror("ghayerha");
}
