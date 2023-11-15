#include "tokens.h"

const char	*get_tag_name(t_tag tag)
{
	const	char *(tag_table[100]) = {\
		[T_DOUBLE_QUOTE] = "Double Quote", \
		[T_SINGLE_QUOTE] = "Single Quote", \
		[T_REDIRECT_IN] = "Redirect In", \
		[T_REDIRECT_OUT] = "Redirect Out", \
		[T_PIPE] = "Pipe", \
		[T_APPEND] = "Append", \
		[T_HERE_DOC] = "Heredoc", \
		[T_EQUALS] = "Equals", \
		[T_EXPANSION] = "Expansions", \
		[T_SEMICOLUMN] = "Semi column", \
		[T_COMMAND] = "Command/Argument", \
		[T_NONE] = "None", \
	};

	if (!tag_table[tag])
		return ("Unrecognized token");
	return (tag_table[tag]);
}
