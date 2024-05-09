/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:21:30 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/09 19:32:10 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

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
			error("Error opening output file");
		execute_pipe(&p);
		close(p.in_fd);
		close(p.out_fd);
	}
	else
		print_usage();
}
