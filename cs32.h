#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <dirent.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>


#define MAX_THREAD 200

/*the data struct of a thread */
struct Thread{    
        char  pid[5];
        char comm[20];
        char state[20];
        char mem[20];
        char ppid[20];;
        char nice[20];
       };

extern long user2,system2,nice2,idle2,iowait2,irq2,softirq2;
extern GdkGC *my_gc_red;
extern GdkColor color;

extern float x;  /*draw line x*/
extern float y;  /*draw line y*/
extern float util; /*cpu util info*/

extern struct Thread pro[MAX_THREAD]; //

/*function to create the main window*/
GtkWidget* create_main_window(void);
void b_kill_thread( GtkWidget *widget,gpointer data);
void show_sys_info(GtkWidget * text);
void b_thread_detail( GtkWidget *widget,gpointer data);
void b_find_thread_by_pid(GtkWidget *widget, gpointer data);
void  create_thread_window(gpointer data);
gboolean view_selection_func (GtkTreeSelection *selection,
                     GtkTreeModel     *model,
                     GtkTreePath      *path,
                     gboolean          path_currently_selected,
                     gpointer          userdata);
gint draw_cpu_util(GtkWidget *widget);
void show_label( GtkWidget *label);
int timer_expose_event(GtkWidget *widget , GdkEventExpose *event , gpointer data);
int cpu_configure_event(GtkWidget *widget , GdkEventConfigure *event);
void model_data_new1(GtkTreeModel* store1, 
                    const gchar* name, const gchar* stat, const gchar *pid,const gchar  *ppid,const gchar  *nice, const gchar *mem);
void arrange_tree_view1(GtkWidget* view);
GtkTreeModel* create_model1();

/*function for func.c*/

int select_name(char name[]);
gint show_proc(GtkWidget *treeview1);
int show_pro_info(void);
gint get_cpu_util(GtkWidget *label29);
gint timeout_callback(GtkWidget *clocker);
gint show_mem_info(GtkWidget *label30);
void show_sys_info(GtkWidget * text);
gint show_disk_info(GtkWidget * label32);



