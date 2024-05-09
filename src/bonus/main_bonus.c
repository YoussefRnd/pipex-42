/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:21:30 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/09 19:31:01 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	init_pipe(t_pipe *p, int argc, char **argv, char **envp)
{
	p->argc = argc;
	p->args = argv;
	p->envp = envp;
	p->is_here_doc = false;
	p->in_fd = -1;
	p->out_fd = -1;
	p->idx = 0;
}

void	init_here_doc(t_pipe *p)
{
	p->idx = 3;
	p->is_here_doc = true;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

	init_pipe(&p, argc, argv, envp);
	if (argc > 5)
	{
		if (is_here_doc(p.args))
			init_here_doc(&p);
		else
		{
			p.idx = 2;
			p.in_fd = open(argv[1], O_RDONLY, 0777);
			if (p.in_fd < 0)
				error("Error opening input file");
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
