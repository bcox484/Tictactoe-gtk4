#ifndef TIC_TAC_TOE
#define TIC_TAC_TOE

#include <gtk/gtk.h>

#define UNOCCUPIED 0
#define O_OCCUPIED_POS 1
#define X_OCCUPIED_POS 2

typedef struct {
    GtkWidget *images[9];
} ImageContainer;

void random_unoccupied_space(unsigned int *random_move);
void button_handler(GtkWidget *btn, gpointer container);
void quit_application(GtkWidget *btn, gpointer window);
void end_game(ImageContainer *container);
void restart_game(GtkWidget *btn, gpointer container);
void change_picture(GtkWidget *image, char turn);
void make_move(ImageContainer *images, int move);
bool check_win();
bool full_board();
bool check_tie();
bool check_game();
bool repeat_move(int move);
void human_enable(GtkWidget *btn);
void pc_enable(GtkWidget *btn, gpointer container);
void free_image_ptr(GtkWidget *btn, gpointer imgs);
void computer_move(gpointer container);
void clear_images(ImageContainer *images);
int computer_random_num();

#endif
