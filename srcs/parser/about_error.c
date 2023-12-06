/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:17:23 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/06 10:19:52 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int	ft_error(int error, t_tools *tools)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("syntax error: unexpected end of file\n",
			STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	parser_error(int error, t_tools *tools, t_lexer *lexer_list)
{
	ft_lexerclear(&lexer_list);
	ft_error(error, tools);
}

int	parser_token_error(t_tools *tools, t_lexer *lexer_list,
	t_tokens token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == GREAT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == GREAT_GREAT)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token == LESS)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == LESS_LESS)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	// else if (token == SEMICOLON)
	// 	ft_putstr_fd("';'\n", STDERR_FILENO);
	else if (token == AND_AND)
		ft_putstr_fd("'&&'\n", STDERR_FILENO);
	else if (token == OR_OR)
		ft_putstr_fd("'||'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	ft_lexerclear(&lexer_list);
	free_tools(tools);
	return (EXIT_FAILURE);
}

int	handle_operator_error(t_tools *tools, t_tokens token)
{
	if (token == PIPE)
	{
		parser_token_error(tools, tools->lexer_list,
			tools->lexer_list->token);
		return (EXIT_FAILURE);
	}
	if (!tools->lexer_list)
	{
		parser_error(0, tools, tools->lexer_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}