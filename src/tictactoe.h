#ifndef TIC_TAC_TOE
#define TIC_TAC_TOE

#include <gtk/gtk.h>

#define UNOCCUPIED 0
#define O_OCCUPIED_POS 1
#define X_OCCUPIED_POS 2

typedef struct {
    GtkWidget *images[9];
    GtkWidget *window;
} ImageContainer;

extern bool g_finished;
extern bool g_turn;
extern int g_moves[9];

void quit_application(GtkWidget *btn, gpointer window);
void end_game(ImageContainer *container);
void restart_game(GtkWidget *btn, gpointer container);
void change_picture(GtkWidget *image, char turn);
void make_move(GtkWidget *btn, gpointer imgs);
bool check_win();
bool full_board();
bool check_tie();
bool check_game();
bool repeat_move(int move);
void free_image_ptr(GtkWidget *btn, gpointer imgs);

#endif
