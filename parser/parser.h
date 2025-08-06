/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:14:47 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/05 17:59:39 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

// parser.c
void	parser(t_shell *shell, char *input);
// parser_cmd.c
void	handle_cmd(t_shell_input *shell_input, char **envp);
// skip_space.c
void	skip_space(char **input);
// is_space.c
int		is_space(char c);
// grab_word.c
char	*grab_word(char **input);
char	*grab_word_with_env(char **input, char **envp);
// quote_handler.c
char	*grab_quoted_word(char **input, char **envp);
char	*grab_single_quoted_word(char **input);
int		has_unclosed_quotes(char *input);

#endif