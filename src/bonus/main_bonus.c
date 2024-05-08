/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:21:30 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/08 12:03:15 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

	p.argc = argc;
	p.args = argv;
	p.envp = envp;
	if (argc > 5)
	{
		if (is_here_doc(p.args))
		{
			p.idx = 3;
			p.is_here_doc = true;
		}
		else
		{
			p.idx = 2;
			p.out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (p.out_fd < 0)
			{
				perror("Error opening output file");
				return (1);
			}
		}
		execute_pipe(&p);
	}
	else
		perror("ghayerha");
}
