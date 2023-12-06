/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_file_ok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/30 16:12:35 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_file_exist(char *file)
{
	return (!access(file, F_OK));
}

bool	is_file_readable(char *file)
{
	return (!access(file, R_OK));
}

bool	is_file_writable(char *file)
{
	return (!access(file, W_OK));
}

bool	is_file_exectable(char *file)
{
	return (!access(file, X_OK));
}
