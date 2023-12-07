/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/06 14:23:14 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*check_malloc(void *ptr)
{
	if (ptr == NULL)
	{
		put_error("failed to malloc\n");
		exit(1);
	}
	return (ptr);
}

bool	check_open(int fd, char *file)
{
	struct stat	st;

	if (fd == -1)
	{
		if (stat(file, &st) < 0)
			return (false);
		else if (S_ISDIR(st.st_mode))
			return (put_error_w_file(file, "Is a directory"), false);
		if (file)
			put_file_error(NULL, file);
		else
			put_error("failed to open\n");
		return (false);
	}
	return (true);
}

bool	check_close(int ret)
{
	if (ret < 0)
	{
		put_error("failed to close\n");
		return (false);
	}
	return (true);
}

bool	check_pipe(int ret)
{
	if (ret < 0)
	{
		put_error("failed to create pipe\n");
		return (false);
	}
	return (true);
}

bool	check_fork(pid_t child_pid)
{
	if (child_pid < 0)
	{
		put_error("failed to fork\n");
		return (false);
	}
	return (true);
}
