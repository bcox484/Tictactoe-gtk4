/*
 * This file is part of Tictactoe-gtk4.
 * Copyright (C) 2023 Benjamin Cox
 *
 * *program name* is free software: you can redistribute it and/or modify
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

bool g_finished = false; /* Determines if game is over */
bool g_turn = true;      /* Determines whos turn it is, true for O */

/* Representation of tictactoe board as an array */
int g_moves[9] = {UNOCCUPIED};

void quit_application(GtkWidget *btn, gpointer window) {
    gtk_window_close(GTK_WINDOW(window));
}

void restart_game(GtkWidget *btn, gpointer container) {
    ImageContainer *con = (ImageContainer *)container;
    for (int i = 0; i < 9; i++) {
        gtk_image_clear(GTK_IMAGE(con->images[i]));
        g_moves[i] = UNOCCUPIED;
    }
    g_finished = false;
}

void end_game(ImageContainer *container) {
    g_finished = true;

    for (int i = 0; i < 9; i++) {
        gtk_image_clear(GTK_IMAGE(container->images[i]));
    }

    if (!check_tie()) {
        if (g_turn) {
            gtk_image_set_from_resource(GTK_IMAGE(container->images[1]),
                                        "/tictactoe/images/O.png");
            gtk_image_set_from_resource(GTK_IMAGE(container->images[3]),
                                        "/tictactoe/images/W.png");
            gtk_image_set_from_resource(GTK_IMAGE(container->images[4]),
                                        "/tictactoe/images/I.png");
            gtk_image_set_from_resource(GTK_IMAGE(container->images[5]),
                                        "/tictactoe/images/N.png");
        } else {
            gtk_image_set_from_resource(GTK_IMAGE(container->images[1]),
                                        "/tictactoe/images/X.png");
            gtk_image_set_from_resource(GTK_IMAGE(container->images[3]),
                                        "/tictactoe/images/W.png");
            gtk_image_set_from_resource(GTK_IMAGE(container->images[4]),
                                        "/tictactoe/images/I.png");
            gtk_image_set_from_resource(GTK_IMAGE(container->images[5]),
                                        "/tictactoe/images/N.png");
        }
    } else {
        gtk_image_set_from_resource(GTK_IMAGE(container->images[3]),
                                    "/tictactoe/images/T.png");
        gtk_image_set_from_resource(GTK_IMAGE(container->images[4]),
                                    "/tictactoe/images/I.png");
        gtk_image_set_from_resource(GTK_IMAGE(container->images[5]),
                                    "/tictactoe/images/E.png");
    }
    g_turn = true;
}

void change_picture(GtkWidget *image, char g_turn) {
    char file_path[50];
    snprintf(file_path, sizeof(file_path), "/tictactoe/images/%c.png", g_turn);
    gtk_image_set_from_resource(GTK_IMAGE(image), file_path);
}

bool check_win() {
    /* Checks all win conditions */
    int move;
    if (g_turn) {
        move = O_OCCUPIED_POS;
    } else {
        move = X_OCCUPIED_POS;
    }

    bool win = false;
    if (g_moves[0] == move && g_moves[1] == move && g_moves[2] == move) {
        win = true;

    } else if (g_moves[0] == move && g_moves[3] == move && g_moves[6] == move) {
        win = true;

    } else if (g_moves[0] == move && g_moves[4] == move && g_moves[8] == move) {
        win = true;

    } else if (g_moves[1] == move && g_moves[4] == move && g_moves[7] == move) {
        win = true;

    } else if (g_moves[2] == move && g_moves[5] == move && g_moves[8] == move) {
        win = true;

    } else if (g_moves[2] == move && g_moves[4] == move && g_moves[6] == move) {
        win = true;

    } else if (g_moves[3] == move && g_moves[4] == move && g_moves[5] == move) {
        win = true;

    } else if (g_moves[6] == move && g_moves[7] == move && g_moves[8] == move) {
        win = true;
    }
    return win;
}

bool full_board() {
    /* Checks if every position on the board is occupied */
    bool full = true;
    for (int i = 0; i < 9; i++) {
        if (g_moves[i] == UNOCCUPIED) {
            full = false;
        }
    }
    return full;
}

bool check_tie() {
    if (full_board() && !(check_win()))
        return true;
    return false;
}

bool check_game() {
    bool end = false;
    if (check_win() || check_tie()) {
        end = true;
    }
    return end;
}

bool repeat_move(int move) {
    /* Ensures that player cannot make multiple moves in one position */
    bool repeat = false;
    if (g_moves[move] != UNOCCUPIED) {
        repeat = true;
    }
    return repeat;
}

void make_move(GtkWidget *btn, gpointer imgs) {
    ImageContainer *images = (ImageContainer *)imgs;

    /* Determines which button is clicked from button label */
    const char *label = gtk_button_get_label(GTK_BUTTON(btn));
    int move = atoi(label) - 1;

    /* Sets move, adds image to correct square, checks game*/
    if (g_turn && !(repeat_move(move)) && !g_finished) {
        g_moves[move] = O_OCCUPIED_POS;
        change_picture(images->images[move], 'O');
        if (check_game()) {
            end_game(images);
            return;
        }
        g_turn = false;

    } else if (!(repeat_move(move)) && !g_finished) {
        g_moves[move] = X_OCCUPIED_POS;
        change_picture(images->images[move], 'X');
        if (check_game()) {
            end_game(images);
            return;
        }
        g_turn = true;
    }
}

void free_image_ptr(GtkWidget *btn, gpointer imgs) { free(imgs); }
