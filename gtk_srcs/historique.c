/*
** historique.c for historique in /home/kersale/Dropbox/myirc/PSU_2013_myirc/src_client
** 
** Made by Elliot Kersale
** Login   <kersale@ubuntu>
** 
** Started on  Wed Apr 16 18:25:07 2014 Elliot Kersale
** Last update Wed Apr 23 17:02:39 2014 Elliot Kersale
*/

#include		"my_irc.h"

extern GtkWidget	*text;

int			open_historique(GdkFont *fixed_font)
{
  FILE *infile;
  char buffer[1024];
  int nchars;

  if ((infile = fopen(".histo", "a+")) != NULL)
    {
      while (1)
	{
	  memset(buffer, 0, 1024);
	  nchars = fread(buffer, 1, 1024, infile);
	  gtk_text_insert (GTK_TEXT (text), fixed_font, NULL,
			   NULL, buffer, nchars);
	  
	  if (nchars < 1024)
	    break;
	}
      fclose (infile);
      return (0);
    }
  return (1);
}
