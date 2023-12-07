/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:54:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/07 15:25:19 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	all_free_tab(char **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	all_free_int(int **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

bool	end_pipex(t_pipex *pipex)
{
	all_free_tab(pipex->cmd_absolute_path);
	all_free_tab(pipex->cmd_absolute_path_with_parameter);
	all_free_int(pipex->pipe_fd);
	if (is_file_exist(HERE_DOC_FILE_PATH))
		if (check_unlink(unlink(HERE_DOC_FILE_PATH)) == false)
			return (false);
	return (true);
}
