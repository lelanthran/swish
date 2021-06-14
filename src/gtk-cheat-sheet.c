
#include <stdio.h>

#include <gtk/gtk.h>

// #define INTERFACE_FILE ("test-scripts/gtk-cheat-sheet.gtk3-ui")
#define INTERFACE_FILE ("test-scripts/glade-test.glade")

void
button_clicked (GtkButton *button,
                gpointer   data)
{
  g_print ("Hello World from %p/%p\n", button, data);
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  // GtkWidget *window;
  GtkWindow *window2;
  GtkWidget *button;
  GtkButton *dialog_button;
  GtkButton *quit_button;
  GtkWidget *button_box;
  GtkBuilder *interface;

  interface = gtk_builder_new_from_file (INTERFACE_FILE);
  dialog_button = GTK_BUTTON (gtk_builder_get_object (interface, "dialog_button"));
  quit_button = GTK_BUTTON (gtk_builder_get_object (interface, "quit_button"));
  window2 = GTK_WINDOW (gtk_builder_get_object (interface, "FWindow"));

  printf ("interface gave us %p / %p\n", dialog_button, window2);

  // window = gtk_application_window_new (app);
  // gtk_window_set_title (GTK_WINDOW (window), "Window");
  // gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  // gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("MyButton");
  g_signal_connect (dialog_button, "clicked", G_CALLBACK (button_clicked), dialog_button);
  g_signal_connect (quit_button, "clicked", G_CALLBACK (button_clicked), quit_button);
  g_signal_connect_swapped (quit_button, "clicked", G_CALLBACK (gtk_widget_destroy), window2);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  // gtk_widget_show_all (window);
  gtk_application_add_window (app, window2);
  gtk_widget_show_all (GTK_WIDGET (window2));

  gtk_widget_destroy (interface);
  g_object_unref (interface);
}


int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
