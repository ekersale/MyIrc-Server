#include	<string.h>
#include	<stdlib.h>

#define		FORBIDDEN_CHAR	"/\n\\"
#define		REPLACED_CHAR	"\t "
#define		REPLACING_CHAR	'_'

int		is_in_base(char c, char *base)
{
  while (*base)
    {
      if (c == *base)
	return (1);
      base += 1;
    }
  return (0);
}

void		insert_valid_char(char *in, char *out, char *base)
{
  while (*in)
    {
      if (!is_in_base(*in, base))
	{
	  *out = *in;
	  out += 1;
	}
      in += 1;
    }
  *out = 0;
}

void		replace_char(char *out, char c, char *base)
{
  while (*out)
    {
      if (is_in_base(*out, base))
	*out = c;
      out += 1;
    }
}

char		*format_name(char *in)
{
  char		*out;

  if (!in)
    return (NULL);
  if ((out = malloc(sizeof(char) * (strlen(in) + 1))) == NULL)
    return (NULL);
  insert_valid_char(in, out, FORBIDDEN_CHAR);
  replace_char(out, REPLACING_CHAR, REPLACED_CHAR);
  if (strlen(out) == 0)
    {
      free(out);
      return (NULL);
    }
  return (out);
}

char		*format_msg(char *in)
{
  char		*out;


  if ((out = malloc(sizeof(char) * (strlen(in) + 1))) == NULL)
    return (NULL);
  insert_valid_char(in, out, "\b\a\r");
  replace_char(out, ' ', "\n\t\v\f");
  if (strlen(out) == 0)
    {
      free(out);
      return (NULL);
    }
  return (out);
}
