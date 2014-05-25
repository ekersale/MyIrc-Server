/*
** format_name.c for my_irc in /home/kersale/Dropbox/myirc/PSU_2013_myirc
** 
** Made by Elliot Kersale
** Login   <kersale@epitech.net>
** 
** Started on  Sat Apr 19 15:34:43 2014 Elliot Kersale
** Last update Tue Apr 29 21:13:04 2014 Elliot Kersale
*/

#include	<string.h>
#include	<stdlib.h>
#include	"serveur.h"

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

void		insert_valid_char(char *in, char *out)
{
  while (*in)
    {
      if (!is_in_base(*in, FORBIDDEN_CHAR))
	{
	  *out = *in;
	  out += 1;
	}
      in += 1;
    }
  *out = 0;
}

void		replace_char(char *out)
{
  while (*out)
    {
      if (is_in_base(*out, REPLACED_CHAR))
	*out = REPLACING_CHAR;
      out += 1;
    }
}

char		*format_name(char *in)
{
  char		*out;
  
  if (in == NULL)
    return (strdup("null"));
  if ((out = malloc(sizeof(char) * (strlen(in) + 1))) == NULL)
    return (NULL);
  insert_valid_char(in, out);
  replace_char(out);
  if (strlen(out) == 0)
    {
      free(out);
      return (NULL);
    }
  return (out);
}
