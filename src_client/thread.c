/*
** thread.c for myirc in /home/kersal_e/Dropbox/myirc/irc_tmp/src_client
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Tue Apr 29 18:51:06 2014 Elliot Kersale
** Last update Tue Apr 29 22:04:24 2014 Elliot Kersale
*/

#include	"client.h"

void		lock_mutex(pthread_mutex_t *mutex)
{
  pthread_mutex_lock(mutex);
}

void		unlock_mutex(pthread_mutex_t *mutex)
{
  pthread_mutex_unlock(mutex);
}

pthread_t	init_thread(t_lib *shared, void *(*routine) (void *))
{
  pthread_t	thread;

  if (pthread_create(&thread, NULL, routine, shared) < 0)
    {
      perror("pthread_create()");
      return (0);
    }
  return (thread);
}

void		join_thread(pthread_t *thread)
{
  pthread_join(*thread, NULL);
}

void		init_mutex(pthread_mutex_t *mutex)
{
  pthread_mutex_init(mutex, NULL);
}
