/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:51:33 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/07 17:41:10 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_to_char(t_tokens token)
{
	if (token == PIPE)
		return ("|");
	else if (token == GREAT)
		return (">");
	else if (token == GREAT_GREAT)
		return (">>");
	else if (token == LESS)
		return ("<");
	else if (token == LESS_LESS)
		return ("<<");
	else if (token == SEMICOLON)
		return (";");
	else if (token == AND_AND)
		return ("&&");
	else if (token == OR_OR)
		return ("||");
	else
		return ("");
}

void	nodefirst_ver_simple_cmds(t_simple_cmds **node)
{
	if (node == NULL || *node == NULL)
		return ;
	while ((*node)->prev != NULL)
		*node = (*node)->prev;
}

// char	**change_to_array(t_tools *tools)
// {
// 	char **tmparray;
// 	char *tmpstr;
// 	int i;
// 	int k;
// 	t_simple_cmds *tmp;

// 	i = 0;
// 	k = 0;
// 	tmp = tools->simple_cmds;
// 	while (tmp)
// 	{
// 		if (tmp->str)
// 			i++;
// 		if (tmp->redirections)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	nodefirst_ver_simple_cmds(&tmp);
// 	tmparray = check_malloc((char **)malloc(sizeof(char *) * (i + 1)));
// 	i = 0;
// 	tmp = tools->simple_cmds;
// 	while (tmp)
// 	{
// 		k = 0;
// 		tmpstr = ft_strdup("");
// 		if (tmp->str && tmp->str[k])
// 		{
// 			while (tmp->str[k])
// 			{
// 				// if(tmpstr && tmp->redirections->token != 1)
// 					tmparray[i] = ft_strjoin(tmpstr, tmp->str[k]);
// 				if (tmp->str[k + 1])
// 					tmparray[i] = ft_strjoin(tmparray[i], " ");
// 				// if(tmpstr)
// 				// 	free(tmpstr);//これがないと、パイプが現れない問題
// 				tmpstr = ft_strdup(tmparray[i]);
// 				k++;
// 			}
// 			if (tmpstr)
// 				free(tmpstr);
// 			i++;
// 		}
// 		if (tmp->redirections)
// 		{
// 			while (tmp->redirections && tmp->redirections->token != 1)
// 			{
// 				tmparray[i++] = ft_strdup(token_to_char(tmp->redirections->token));
// 				if(!tmp->redirections->str)

// 				tmparray[i++] = ft_strdup(tmp->redirections->str);
// 				tmp->redirections = tmp->redirections->next;
// 			}
// 			if (tmp->redirections && tmp->redirections->token == 1)
// 			{
// 				tmparray[i++] = ft_strdup(token_to_char(tmp->redirections->token));
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	tmparray[i] = NULL;
// 	nodefirst_ver_simple_cmds(&tmp);
// 	return (tmparray);
// }

char	**allocate_tmparray(int size)
{
	char	**tmparray;

	tmparray = check_malloc((char **)malloc(sizeof(char *) * (size + 1)));
	return (tmparray);
}

char	*process_str_concat(char *tmpstr, char *str)
{
	char	*result;

	result = ft_strjoin(tmpstr, str);
	return (result);
}

char	*ft_malloced_strjoin(const char *s1, const char *s2, char **dest)
{
	char	*tmp;

	tmp = *dest;
	*dest = check_malloc(ft_strjoin(s1, s2));
	// printf("dest = %p\n", *dest);
	free(tmp);
	return (*dest);
}

int	process_str(char **tmparray, t_simple_cmds *tmp, int i)
{
	int		k;
	char	*tmpstr;

	k = 0;
	tmpstr = NULL;
	if (tmp->str && tmp->str[k])
	{
		while (tmp->str[k])
		{
			tmparray[i] = process_str_concat(tmpstr, tmp->str[k]);
			if (tmp->str[k + 1])
				tmparray[i] = ft_malloced_strjoin(tmparray[i], " ",
						&tmparray[i]);
			free(tmpstr);
			tmpstr = ft_strdup(tmparray[i]);
			free(tmparray[i]);
			k++;
		}
		free(tmpstr);
		i++;
	}
	return (i);
}

//t_simple_cmds	*tmp;
//process_redirections(tmparray, tmp, i);
int	process_redirections(char **tmparray, t_simple_cmds *tmp, int i)
{
	while (tmp->redirections && tmp->redirections->token != PIPE
		&& tmp->redirections->token != AND_AND
		&& tmp->redirections->token != OR_OR
		&& tmp->redirections->token != SEMICOLON)
	{
		tmparray[i++] = ft_strdup(token_to_char(tmp->redirections->token));
		if (tmp->redirections->str)
			tmparray[i++] = ft_strdup(tmp->redirections->str);
		tmp->redirections = tmp->redirections->next;
	}
	if (tmp->redirections && (tmp->redirections->token == PIPE
			|| tmp->redirections->token == AND_AND
			|| tmp->redirections->token == OR_OR
			|| tmp->redirections->token == SEMICOLON))
	{
		tmparray[i++] = ft_strdup(token_to_char(tmp->redirections->token));
	}
	return (i);
}

int	fill_tmparray(t_tools *tools, char **tmparray)
{
	int				i;
	t_simple_cmds	*tmp;

	i = 0;
	tmp = tools->simple_cmds;
	while (tmp)
	{
		i = process_str(tmparray, tmp, i);
		i = process_redirections(tmparray, tmp, i);
		tmp = tmp->next;
	}
	return (i);
}

int	count_elements(t_tools *tools)
{
	int				count;
	t_simple_cmds	*tmp;

	count = 0;
	tmp = tools->simple_cmds;
	while (tmp)
	{
		if (tmp->str)
			count++;
		if (tmp->redirections)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**change_to_array(t_tools *tools)
{
	char	**tmparray;
	int		i;

	i = count_elements(tools);
	tmparray = allocate_tmparray(i);
	i = fill_tmparray(tools, tmparray);
	tmparray[i] = NULL;
	return (tmparray);
}
