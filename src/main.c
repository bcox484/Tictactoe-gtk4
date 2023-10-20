/*
 * This file is part of Tictactoe-gtk4.
 * Copyright (C) 2023 Benjamin Cox
 *
 * Tictactoe-gtk4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tictactoe.h"

static void activate(GtkApplication *app, gpointer user_data) {
    GtkBuilder *bd = gtk_builder_new();
    GtkWidget *buttons[9];
    GtkWidget *restart_button, *close_button;
    /* Stores GtkWidgets for images and the application window so they can
     * be passed to other functions through G_CALLBACK */
    ImageContainer *container = calloc(1, sizeof(ImageContainer));
    gtk_builder_add_from_resource(bd, "/tictactoe/src/tictactoe.ui", NULL);

    container->window = GTK_WIDGET(gtk_builder_get_object(bd, "window"));
    gtk_window_set_application(GTK_WINDOW(container->window), app);

    /* Initializes the 9 buttons and images for the tictactoe board */
    for (int i = 0; i < 9; i++) {
        char string_num[10];
        snprintf(string_num, sizeof(string_num), "%d", i + 1);
        container->images[i] =
            GTK_WIDGET(gtk_builder_get_object(bd, string_num));

        snprintf(string_num, sizeof(string_num), "button%d", i + 1);
        buttons[i] = GTK_WIDGET(gtk_builder_get_object(bd, string_num));
        g_signal_connect(buttons[i], "clicked", G_CALLBACK(make_move),
                         container);
    }

    restart_button = GTK_WIDGET(gtk_builder_get_object(bd, "restart"));
    close_button = GTK_WIDGET(gtk_builder_get_object(bd, "close"));

    g_signal_connect(close_button, "clicked", G_CALLBACK(quit_application),
                     container->window);

    g_signal_connect(restart_button, "clicked", G_CALLBACK(restart_game),
                     container);

    /* Free ImageContainer when application window is destroyed */
    g_signal_connect(container->window, "destroy", G_CALLBACK(free_image_ptr),
                     container);

    gtk_window_present(GTK_WINDOW(container->window));
    g_object_unref(bd);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    app = gtk_application_new("tic.tac.toe", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
