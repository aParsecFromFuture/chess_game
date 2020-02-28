#include <gtk/gtk.h>
#include <cairo.h>
#include "chess.h"

GtkBuilder *builder;
GtkWidget *window, *draw_area, *switch_label, *history_table;
GtkTextBuffer *buffer;

cairo_surface_t* icon[13];
chess_board board;
int from[2], to[2], is_picked = 0, depth = 1, opponent = BLACK, iteration = 1;
char notation[10] = {0};

gboolean on_board_draw(GtkWidget*, cairo_t*, gpointer);
gboolean on_button_press(GtkWidget*, GdkEventButton*, gpointer);
void on_switch_button_state_set(GtkSwitch*);
void on_scale_button_value_changed(GtkRange*);

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    
    builder = gtk_builder_new_from_file("main.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    draw_area = GTK_WIDGET(gtk_builder_get_object(builder, "draw_area"));
    switch_label = GTK_WIDGET(gtk_builder_get_object(builder, "switch_label"));
    history_table = GTK_WIDGET(gtk_builder_get_object(builder, "game_history_table"));
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(history_table));
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), 0);
    
    gtk_builder_connect_signals(builder, 0);
    
    icon[0] = 0;
    icon[1] = cairo_image_surface_create_from_png("../resource/w_pawn.png");
    icon[2] = cairo_image_surface_create_from_png("../resource/w_knight.png");
    icon[3] = cairo_image_surface_create_from_png("../resource/w_bishop.png");
    icon[4] = cairo_image_surface_create_from_png("../resource/w_rook.png");
    icon[5] = cairo_image_surface_create_from_png("../resource/w_queen.png");
    icon[6] = cairo_image_surface_create_from_png("../resource/w_king.png");
    icon[7] = cairo_image_surface_create_from_png("../resource/b_pawn.png");
    icon[8] = cairo_image_surface_create_from_png("../resource/b_knight.png");
    icon[9] = cairo_image_surface_create_from_png("../resource/b_bishop.png");
    icon[10] = cairo_image_surface_create_from_png("../resource/b_rook.png");
    icon[11] = cairo_image_surface_create_from_png("../resource/b_queen.png");
    icon[12] = cairo_image_surface_create_from_png("../resource/b_king.png");
    
    chess_init(board);
    
    gtk_widget_show(window);
    gtk_main();
	return 0;
}

gboolean on_board_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    int i, j, offset_x = 14, offset_y = 8;
    for(i = 0;i < 8;i++){
        for(j = 0;j < 8;j++){
            if(board[i][j] != EMPTY){
                cairo_set_source_surface(cr, icon[board[i][j]], i * 60 + offset_x, j * 60 + offset_y);
                cairo_paint(cr);            
            }
        }
    }
    if(is_picked){
        cairo_set_source_rgba(cr, 0, 0, 1, 0.15);
        cairo_rectangle(cr, 60 * from[0], 60 * from[1], 60, 60);
        for(i = 0;i < 8;i++){
            for(j = 0;j < 8;j++){
                to[0] = i;
                to[1] = j;
                chess_board tmp;
                chess_copy(board, tmp);
                if(chess_play_2(tmp, from[0], from[1], to[0], to[1])){
                    cairo_rectangle(cr, 60 * to[0], 60 * to[1], 60, 60);
                }
            }
        }
        cairo_fill(cr);
    }
    return 0;
}

gboolean on_button_press(GtkWidget *w, GdkEventButton *event, gpointer data)
{
    if(is_picked){
        to[0] = (int)(event->x / 60);
        to[1] = (int)(event->y / 60);
        chess_notation(board, from[0], from[1], to[0], to[1], LAST_MOVEMENT);
        if(chess_play_2(board, from[0], from[1], to[0], to[1])){
            switch(opponent){
                case WHITE :
                sprintf(notation, "%s\n",LAST_MOVEMENT);
                case BLACK :
                sprintf(notation, "%d. %s\t", iteration, LAST_MOVEMENT);
            }
            gtk_text_buffer_insert_at_cursor(buffer, notation, -1);
            
            chess_play_ai(board, opponent, depth);
            switch(opponent){
                case WHITE :
                sprintf(notation, "%d. %s\t", iteration, LAST_MOVEMENT);
                case BLACK :
                sprintf(notation, "%s\n",LAST_MOVEMENT);
            }
            gtk_text_buffer_insert_at_cursor(buffer, notation, -1);
            iteration++;
        }
        gtk_widget_queue_draw(draw_area);
        is_picked = 0;
    }else{
        from[0] = (int)(event->x / 60);
        from[1] = (int)(event->y / 60);
        if(color[board[from[0]][from[1]]] * opponent < 0){
            gtk_widget_queue_draw(draw_area);
            is_picked = 1;
        }
    }
    return TRUE;
}

void on_switch_button_state_set(GtkSwitch *s)
{
    switch(opponent){
        case WHITE :
        opponent = BLACK;
        gtk_label_set_text(GTK_LABEL(switch_label),(gchar*)"WHITE");
        chess_play_ai(board, opponent, depth);
        sprintf(notation, "%s\n",LAST_MOVEMENT);
        gtk_text_buffer_insert_at_cursor(buffer, notation, -1);
        break;
        case BLACK :
        opponent = WHITE;
        gtk_label_set_text(GTK_LABEL(switch_label),(gchar*)"BLACK");
        chess_play_ai(board, opponent, depth);
        sprintf(notation, "%d. %s\t",iteration, LAST_MOVEMENT);
        gtk_text_buffer_insert_at_cursor(buffer, notation, -1);
        break;
    }
    gtk_widget_queue_draw(draw_area);
}

void on_scale_button_value_changed(GtkRange *r)
{
    depth = (int)gtk_range_get_value(r);
}

