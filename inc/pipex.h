/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:38:15 by yboumlak          #+#    #+#             */
/*   Updated: 2024/05/09 17:42:26 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/Libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	int		idx;
	int		argc;
	char	**args;
	int		pipe_fd[2];
	int		prev_fd;
	int		in_fd;
	int		out_fd;
	char	*cmd;
	char	**envp;
	int		input_fd;
}			t_pipe;

char		*is_path_valid(char *cmd, char **env_vars);

char		**split_cmd(char *s);

void		execute_pipe(t_pipe *p);

void		error(char *error_msg);
void		print_usage(void);

#endif