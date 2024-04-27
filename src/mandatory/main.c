/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:21:30 by yboumlak          #+#    #+#             */
/*   Updated: 2024/04/26 17:15:31 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	char	**processed_data;

	if (argc == 5)
	{
		// TODO make a function to parce the args.
		processed_data = parse(argv);
		// TODO make a fucntion that will execute the commands.
		execute(processed_data);
	}
	return (0);
}
