/*
** main.c for display in /home/kersal_e/projet_actuels/local_myirc/src
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.eu>
** 
** Started on  Mon Apr  7 14:05:53 2014 Elliot Kersale
** Last update Sun Apr 27 18:22:17 2014 Elliot Kersale
*/

#include			<gtk/gtktext.h>
#include			<gtk/gtk.h>
#include			<gdk/gdk.h>
#include			<string.h>
#include			<unistd.h>
#include			<X11/Xlib.h>
#include			"common.h"
#include			"thread.h"
#include			"my_irc.h"
#include			"thread.h"

GtkWidget			*text;
int				glob_cs;

void				display_str(char *str, t_color *color)
{
  /* GdkColormap   *cmap;
  GdkColor      colour;
  
  cmap = gdk_colormap_get_system();
  colour.red = color->red;   
  colour.green = color->green;
  colour.blue = color->blue;
  printf("%p\n%s\n", text, str);
  if (!gdk_color_alloc(cmap, &colour))
  g_error("couldn't allocate color");*/
  if (strlen(str) > 1)
    printf("%s\n", str);
  gtk_text_insert (GTK_TEXT(text), NULL, NULL, NULL, str, strlen(str));
}

static gpointer	       	send_cmd(gpointer null)
{
  t_client		client;
  fd_set		readfd;
  char			buff[4096];
  int			max;
  int			nblu;


  (void)null;
  gdk_threads_enter();
  while (1) 
      {
      	printf("flux : <%d>\n", glob_cs);
	if (glob_cs > 0)
	  {
	    FD_ZERO(&readfd);
	    FD_SET(glob_cs, &readfd);
	    if (select(glob_cs + 1, &readfd, NULL, NULL, NULL) == -1)
	      {
		perror("select()");
		return (EXIT_FAILURE);
	      }
	    if (FD_ISSET(glob_cs, &readfd))
	      {
		memset(buff, 0, 4096);
		printf("---1----\n");
		nblu = recv(glob_cs, buff, 4096, 0);
		if (nblu > 0)
		  {
		    printf("<%s>\nlength : %d\n", buff, strlen(buff));
		    t_color color;
		    
		    color.red = 0;
		    color.blue = 0;
		    color.green = 0;
		    if (strlen(buff) > 1)
		      display_str(buff, &color);
		    //display_normal(buff);
		  }
	      }
	  }
      } 
  gdk_threads_leave();
}

void		enter_callback( GtkWidget *widget,
				GtkWidget *entry)
{
  const gchar	*entry_text;
  char		tmp[4096];
  t_client	client;
  int	       	max;
  
  (void)widget;
  max = 0;
  if (memset(tmp, 0, 4096) == NULL)
    return ;
  entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
  sprintf(tmp, "%s", entry_text);
  gtk_entry_set_text (GTK_ENTRY (entry), "");
  if (strncmp(tmp, "/server", 7) == 0)
    {
      if (connect_client(strnncpy(tmp, 8, strlen(tmp)), &glob_cs) == -1)
	return ;
      if (max < glob_cs)
	max = glob_cs;
      if (glob_cs != -1)
	write_msg("Unknown", glob_cs);
    }
  else
    if (glob_cs != -1)
      write_msg(tmp, glob_cs);
}

void enter_login( GtkWidget *widget,
                     GtkWidget *entry )
{
  (void)widget;
  const gchar *entry_text;
  char		tmp[4096];

  memset(tmp, 0, 4096);
  entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
  sprintf(tmp, "/nick %s", entry_text);
  write(0, tmp, strlen(tmp));
}

void		display(int argc, char ***argv, int fd)
{
  GtkWidget	*window;
  GtkWidget	*box1;
  GtkWidget	*box2;
  GtkWidget	*button;
  GtkWidget	*entry;
  GtkWidget	*separator;
  GtkWidget	*table;
  GtkWidget	*vscrollbar;
  GdkFont	*fixed_font;

  gtk_init (&argc, argv);
  if( ! g_thread_supported() )
    g_thread_init(NULL);
  gdk_threads_init();
  gdk_threads_enter();
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_usize (window, 800, 500);
  gtk_window_set_policy (GTK_WINDOW(window), TRUE, TRUE, FALSE);  
  gtk_signal_connect (GTK_OBJECT (window), "destroy",
                      GTK_SIGNAL_FUNC(close_application),
                      NULL);
  gtk_window_set_title (GTK_WINDOW (window), "my_irc");
  gtk_container_set_border_width (GTK_CONTAINER (window), 0);  
  box1 = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), box1);
  gtk_widget_show (box1);
  box2 = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
  gtk_box_pack_start (GTK_BOX (box1), box2, TRUE, TRUE, 0);
  gtk_widget_show (box2);
  table = gtk_table_new (2, 2, FALSE);
  gtk_table_set_row_spacing (GTK_TABLE (table), 0, 2);
  gtk_table_set_col_spacing (GTK_TABLE (table), 0, 2);
  gtk_box_pack_start (GTK_BOX (box2), table, TRUE, TRUE, 0);
  gtk_widget_show (table);
  text = gtk_text_new (NULL, NULL);
  gtk_text_set_editable (GTK_TEXT (text), FALSE);
  gtk_table_attach (GTK_TABLE (table), text, 0, 1, 0, 1,
                    GTK_EXPAND | GTK_SHRINK | GTK_FILL,
                    GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
  gtk_widget_show (text);
  vscrollbar = gtk_vscrollbar_new (GTK_TEXT (text)->vadj);
  gtk_table_attach (GTK_TABLE (table), vscrollbar, 1, 2, 0, 1,
                    GTK_FILL, GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
  gtk_widget_show (vscrollbar);
  fixed_font = gdk_font_load ("");
  gtk_widget_realize (text);
  open_historique(fixed_font);
  gtk_text_freeze (GTK_TEXT (text));
  gtk_text_thaw (GTK_TEXT (text));
  box2 = gtk_vbox_new (FALSE, 10);
  //END DISPLAY INIT
  
  //ENTRY TEXT : SPEAK
  entry = gtk_entry_new_with_max_length (50);
  gtk_signal_connect(GTK_OBJECT(entry), "activate",
		     GTK_SIGNAL_FUNC(enter_callback),
		     entry);
  gtk_entry_set_text (GTK_ENTRY (entry), "Some text here...");
  gtk_entry_select_region (GTK_ENTRY (entry),
  0, GTK_ENTRY(entry)->text_length);
  gtk_box_pack_start (GTK_BOX (box2), entry, TRUE, TRUE, 0);
  gtk_widget_show (entry);
  //END ENTRY TEXT
  
  separator = gtk_hseparator_new ();
  gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 0);
  gtk_widget_show (separator);
  gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
  gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, TRUE, 0);
  gtk_widget_show (box2);

  //BUTTON CLOSE
  button = gtk_button_new_with_label ("close");
  gtk_signal_connect (GTK_OBJECT (button), "clicked",
                      GTK_SIGNAL_FUNC(close_application),
                      NULL);
  gtk_box_pack_start (GTK_BOX (box2), button, TRUE, TRUE, 0);
  GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default (button);
  gtk_widget_show (button);
  gtk_widget_show (window);
  gtk_main ();
  gdk_threads_leave();
}

int		main(int ac, char **av)
{
  pthread_t	com;
  pthread_t	graph;
  t_share	shared;
  GThread	*thread;


  XInitThreads();
  glob_cs = -1;
  if( ! g_thread_supported() )
    g_thread_init( NULL );
  thread = g_thread_create( send_cmd, NULL,
  			    FALSE, NULL );
  if( ! thread )
    {
      printf( "Error\n" );
      return( -1 );
    }
  display(ac, &av, shared.pipefd[0]);
  return (0);
}
