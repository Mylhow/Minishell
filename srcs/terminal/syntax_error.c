#include "libft_mem.h"
#include "libft_string.h"
#include "syntax_error.h"

/*
** Check si la ligne est vide
** Return [int] 1 - Success
** Return [int] 0 - Failed
*/

static int	check_empty_line(char *input)
{
	int i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (!input[i])
		return (1);
	return (0);
}

/*
** Check le contenu des parentheses
** Return [char] 1 - Error Malloc
** Return [char] * - Call Syntax error
*/

static char	recursion_parenth(char *input, int length)
{
	int		i;
	char	*str_parenth;
	char	return_value;

	if (!(str_parenth = wrmalloc((length + 1) * sizeof(char))))
		return (MALLOC_ERROR);
	ft_strlcpy(str_parenth, input, length + 1);
	i = length - 2;
	while (i > 0 && (str_parenth[i] == ' ' || str_parenth[i] == '\t'))
		i--;
	str_parenth[length - 1] = (str_parenth[i] != ';') ? ';' : '\0';
	return_value = syntax_error(str_parenth);
	wrfree(str_parenth);
	return (return_value);
}

/*
** Check les parenthese ouverture et fermeture
** Return [char] 3 - Call syntax error
** Return [char] 2 - Call new line
** Return [char] * - Check le contenu des parentheses
*/

static char	syntax_parenth(char *input, int type, int *index)
{
	int		i;
	int		nbr_parenth;

	if (type == WORD)
		return (EXIT_SYNTAX_ERROR);
	i = 1;
	nbr_parenth = 1;
	while (input[i] && nbr_parenth)
	{
		if (ft_memchr("\'\"", input[i], 2))
		{
			if (pass_quotes(input, &i))
				return (NEW_LINE);
		}
		else if (input[i] == '(')
			nbr_parenth++;
		else if (input[i] == ')')
			nbr_parenth--;
		i += (nbr_parenth) ? 1 : 0;
	}
	if (nbr_parenth) //TODO add ; a la fin
		return (NEW_LINE);
	*index += i + 1;
	return (recursion_parenth(input + 1, i));
}

/*
** Verifie le dernier caractère et agis en fonction.
** Return [char] 3 - Error, call new command
** Return [char] 2 - Call new line
** Return [char] 0 - To execute
*/

static char	check_end_line(char *input)
{
	int i;

	i = 0;
	while (input[i])
		i++;
	i--;
	while (input[i] == ' ' || input[i] == '\t')
		i--;
	if (input[i] == '>' || input[i] == '<')
		return (EXIT_SYNTAX_ERROR);
	else if (input[i] == '\\' || input[i] == '|')
		return (NEW_LINE);
	else if (i > 0 && (!ft_strncmp("&&", input + i - 1, 2)))
		return (NEW_LINE);
	return (TO_EXECUTE);
}

/*
** Verifie la syntaxe de la commande
** Return [short] 0 - Can be executed
** Return [short] 1 - Error malloc
** Return [short] 2 - Add a new line
** Return [short] 3 - Ask a new command
** Return [short] 4 - Syntax error. New command
** Type : 0 Word, 1 Operator, 2 Parenthesis
*/

short		syntax_error(char *input)
{
	int		i;
	int		type;
	char	return_value;

	i = 0;
	type = OPERAT;
	if (check_empty_line(input))
		return (NEW_COMMAND);
	while (input[i])
	{
		if (input[i] == ')')
			return (EXIT_SYNTAX_ERROR);
		else if (input[i] == '(')
		{
			if ((return_value = syntax_parenth(input + i, type, &i)))
				return (return_value);
			type = PARENTH;
		}
		else if (!ft_strncmp(">>", input + i, 2)
		|| !ft_strncmp("&&", input + i, 2)
		|| !ft_strncmp("||", input + i, 2))
		{
			if (type == OPERAT)
				return (EXIT_SYNTAX_ERROR);
			type = OPERAT;
			i += 2;
		}
		else if (ft_memchr("<>|;", input[i], 4))
		{
			if (type == OPERAT)
				return (EXIT_SYNTAX_ERROR);
			type = OPERAT;
			i++;
		}
		else if (ft_memchr("\'\"", input[i], 2))
		{
			if (pass_quotes(input, &i))
				return (NEW_LINE);
			type = WORD;
			i++;
		}
		else if (ft_memchr(" \t\n", input[i], 3))
			pass_blank(input, &i);
		else
		{
			if (type == PARENTH)
				return (EXIT_SYNTAX_ERROR);
			type = WORD;
			i++;
		}
	}
	return (check_end_line(input));
}
