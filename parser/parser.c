/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:59:16 by tafanasi          #+#    #+#             */
/*   Updated: 2025/05/28 12:55:56 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../minishell.h"

int is_space(char c)
{
    if(c == 32 ||
    ( c >= 9 && c <= 13)
    )
        return(c);
}

// @manipulates the "i"
void skip_whitespace(char *input, int *i)
{
    if(is_space(*input))
        *i++;
}

char **grab_word(char *input, int *i)
{
    char *word;
    int bytes;

    bytes = 0;
    // 1. count
    while(!is_space(*input))
        bytes++;
    word = malloc((bytes + 1) * sizeof(char));
    if(!word)
        return(NULL);
    // !!! YOU ARE HERE !!!
    word[bytes] = '\0';
    while(bytes > 0)
        // ???? 
    // increment i for N bytes
    *i += bytes;
        
}

void handle_word(char *input, int *i)
{
    if(input[*i] == '>' || '<'){
        // handle redirections
        // 1. >>, <<, >, <
        // 2. files
    } else {
        // handle the commmand
        // 1. cmd
        // 2. args
        
    }
}

int parser(char *input)
{
    t_shell_input parsed_input;
    parsed_input.is_valid = 1;
    int i;

    i = 0;
    while(input[i])
    {
        t_cmd command;
        
        // char *cmd_name;
        // char **args;
        // + redirects
        // parsed_input.cmds
        skip_whitespace(*input, &i);

        
    }
}