#include	<pthread.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"common.h"
#include	"my_irc.h"

void            display(int argc, char ***argv);

void		*routine_com(void *args)
{
  t_share	*shared;

  shared = (t_share *)args;
  puts("Routine com init");
  send_cmd(shared->pipefd[0]);
  return (NULL);
}

void		*routine_graph(void *args)
{
  t_share	*shared;

  shared = (t_share *)args;
  puts("Routine graph init");
  display(shared->ac, &shared->av);
  //  send_cmd(shared->pipefd[0]);
  puts("Routine graph end");
  return (NULL);
}
