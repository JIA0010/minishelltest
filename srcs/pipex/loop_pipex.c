/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 09:23:37 by toshota           #+#    #+#             */
/*   Updated: 2023/12/04 12:51:11 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// cat infile,|,cat,|,cat,|,cat,|,cat,;,echo -n wow,;,pwd
// pwd,&&,b.out,||,echo wow
int	loop_pipex(char **argv, t_env **env)
{
	char	***splitted_argv;
	char	**splitter;
	int		ret;

	if (is_splitter_exist(argv) == false)
		return (pipex(argv, env));
	get_loop_pipex(argv, &splitted_argv, &splitter);
	ret = do_loop_pipex(splitted_argv, splitter, env);
	return (end_loop_pipex(splitted_argv, splitter), ret);
}
