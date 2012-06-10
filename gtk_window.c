#include "cs32.h"

/*the cpu map*/
static GdkPixmap *pixmap = NULL; 
static GtkWidget *clocker;
GdkGC *my_gc_red;
GdkColor color;
float x = 0.0;  /*draw line x*/
float y = 0.0;  /*draw line y*/
float util = 0.0; /*cpu util info*/

long user2=0,system2=0,nice2=0,idle2=0,iowait2=0,irq2=0,softirq2=0; 
enum{      
    col_name = 0,
    col_stat,
    col_pid,
    col_ppid,
    col_nice,
     col_mem,
     n_cols1
};


void on_new_item_activate(GtkMenuItem *menuitem, gpointer user_data)
{
}

void on_open_item_activate(GtkMenuItem *menuitem,gpointer user_data)
{
}

void on_t_1_activate (GtkMenuItem *menuitem,gpointer user_data)
{
}

void on_c_1_activate(GtkMenuItem *menuitem,gpointer user_data)
{
}

void on_p_1_activate GtkMenuItem *menuitem, gpointer user_data)
{
}

void on_d_1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
}


void on_about1_activate (GtkMenuItem *menuitem,gpointer user_data)
{
}
/*to reboot the pc*/
void on_reboot_item_activate(GtkMenuItem *menuitem, gpointer user_data)
    system("reboot");
 }
/*to shut down the pc*/
void on_shutdown_item_activate(GtkMenuItem *menuitem, gpointer user_data) 
{
    system("halt");
}



/*
 * function : to kill a thread
 * parameter:a pid of a thread
 * return void
 * 2012 5 22
 */
void b_kill_thread( GtkWidget *widget,gpointer data){    
       char *s=(char *)malloc(2000*sizeof(char));
        char *t=data;
             
             strcpy(s,"kill -9 ");
             strcat(s,t);
             printf("%s",s);
             system(s);
}






/*
 * function : to look for detail info of a thread
 * parameter:a pid of a thread
 * return void
 * 2012 5 22
 */
void b_thread_detail( GtkWidget *widget,gpointer data){     
       GtkWidget *main_window;
       GtkWidget *label;
       GtkWidget *button,*vbox;
       char *entry_text=data;
       char path_status[50];
       int fd;
       char buf[200];
       main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
       g_signal_connect(G_OBJECT(main_window), "delete_event", G_CALLBACK(gtk_main_quit), NULL);
       gtk_window_set_title(GTK_WINDOW(main_window), "进程详细信息");
       gtk_window_set_default_size(GTK_WINDOW(main_window), 200,200);
       label=gtk_label_new(NULL);
       gtk_widget_show(label);
       button=gtk_button_new_with_label("结束进程");
       
       vbox=gtk_vbox_new(FALSE,10);
       gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 10);
       gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 10);
       gtk_container_add(GTK_CONTAINER(main_window), vbox);
       
       printf("entry_text=%s",entry_text);
       strcpy(path_status,"/proc/");
       strcat(path_status,entry_text);
       strcat(path_status,"/status");
        fd=open(path_status,O_RDONLY);
        read(fd,buf,200);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(b_kill_thread),entry_text);
        gtk_label_set_text(GTK_LABEL(label),buf);
        gtk_widget_show_all(main_window);
        gtk_main();
 }






/*
 * function : to search a thread by its pid
 * parameter:a pid of a thread
 * return void
 * 2012 5 22
 */

void b_find_thread_by_pid(GtkWidget *widget, gpointer data){     /*查询进程窗口*/
         GtkWidget *main_window; //主窗口对象
         GtkWidget *hbox, *button, *editor;
         char *entry_text;
         main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
         g_signal_connect(G_OBJECT(main_window), "delete_event", G_CALLBACK(gtk_main_quit), NULL);
         gtk_window_set_title(GTK_WINDOW(main_window), "查询进程");
         gtk_window_set_default_size(GTK_WINDOW(main_window), 100,50);
         button=gtk_button_new_with_label("查询");
         editor=gtk_entry_new();
         hbox = gtk_hbox_new(FALSE, 10);
         gtk_box_pack_start(GTK_BOX(hbox), editor, TRUE, TRUE, 10);
        gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 10);
        gtk_container_add(GTK_CONTAINER(main_window), hbox);
        entry_text = gtk_entry_get_text (GTK_ENTRY (editor));
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(b_thread_detail),entry_text);
        gtk_widget_show_all(main_window);
        gtk_main();
}




/*
 * function : create a detail window about the infomation
 * parameter:a pid of a thread
 * return void
 * 2012 5 22
 */
void  create_thread_window(gpointer data){    /*创建进程详细信息窗口*/
   GtkWidget *main_window;
   GtkWidget *vbox,*button1,*button2;
   char *pid=data;
       main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
       g_signal_connect(G_OBJECT(main_window), "delete_event", G_CALLBACK(gtk_main_quit), NULL);
       gtk_window_set_title(GTK_WINDOW(main_window),"进程选项" );
       gtk_window_set_default_size(GTK_WINDOW(main_window), 50,50);
       button1=gtk_button_new_with_label("进程详细信息");
       button2=gtk_button_new_with_label("结束进程");
       vbox=gtk_vbox_new(FALSE,10);
       gtk_box_pack_start(GTK_BOX(vbox), button1, TRUE, TRUE, 10);
       gtk_box_pack_start(GTK_BOX(vbox), button2, FALSE, FALSE, 10);
       gtk_container_add(GTK_CONTAINER(main_window), vbox);
       g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(b_thread_detail),pid);
       g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(b_kill_thread),pid);
       gtk_widget_show_all(main_window);
       gtk_main();
  }



/*
 * function : to see detasls in a thread
 * parameter: a list
 * return void
 * 2012 5 20
 */
gboolean view_selection_func (GtkTreeSelection *selection,
                     GtkTreeModel     *model,
                     GtkTreePath      *path,
                     gboolean          path_currently_selected,
                     gpointer          userdata)
{
   
  GtkTreeIter iter;
  char *pid;
  if (gtk_tree_model_get_iter(model, &iter, path))
  {
    
   gtk_tree_model_get(model, &iter, col_pid, &pid, -1);
   create_thread_window(pid);
   free(pid);}
   return TRUE; /* allow selection state to change */
}




/*
 * function : draw the cpu line
 * parameter: widget to draw
 * return void
 * 2012 5 20
 */
gint draw_cpu_util(GtkWidget *widget){    

     gdk_draw_line(pixmap,my_gc_red,x,y,x+10,util);
     gtk_widget_queue_draw_area(widget,x,util,10,util-y);
    
     x+=10;
     y=util;
     return 1;   
}



/*
 * function : show the cpu line lable
 * parameter: label to show
 * return void
 * 2012 5 20
 */

void show_label( GtkWidget *label){
            char *s=(char *)malloc(2000*sizeof(char));
            strcpy(s,"%0");
            strcat(s,"\n\n\n\n");
            strcat(s,"%100");
            gtk_label_set_text(GTK_LABEL(label),s);
  }   



/*
 * function : this is acting like a timer
 * parameter: widget to use and timer event 
 * return 0 if successful
 * 2012 5 20
 */

int timer_expose_event(GtkWidget *widget , GdkEventExpose *event , gpointer data)  
{
      gdk_draw_drawable(widget->window ,
              widget->style->fg_gc[GTK_WIDGET_STATE(widget)] ,
              pixmap , 0 , 0 , 0 , 0 ,
              widget->allocation.width ,
              widget->allocation.height);   
              gtk_timeout_add(2000,(GtkFunction)draw_cpu_util,widget);
      return 0;
}



/*
 * fuction: to draw the map when configuration changes
 * parameter: the widget to draw
 * return : 0 if successful
 * 2012 5 20 
 */
int cpu_configure_event(GtkWidget *widget , GdkEventConfigure *event)
{
      if(pixmap)
          g_object_unref(pixmap);
      pixmap = gdk_pixmap_new(widget->window ,
                  widget->allocation.width ,
                  widget->allocation.height ,
                  -1);
      gdk_draw_rectangle(pixmap , widget->style->white_gc ,
                  TRUE , 0 , 0 ,
                  widget->allocation.width ,
                  widget->allocation.height);

      my_gc_red = gdk_gc_new(widget->window);
      color.red = 30000;
      color.green = 0;
      color.blue = 30000;
      gdk_gc_set_rgb_fg_color(my_gc_red , &color);   

      return 0;
}



/*
 * fuction: to create the whole window and init all the widgets
 * parameter: void
 * return : the main window
 * 2012 5 20 
 */

GtkWidget* create_main_window(void)
{
  GtkWidget *window1;
  GtkWidget *vbox1;
  GtkWidget *menubar1;
  GtkWidget *menuitem1;
  GtkWidget *menu1;
  GtkWidget *new_item;
  GtkWidget *open_item;
  GtkWidget *menuitem2;
  GtkWidget *menu2;
  GtkWidget *t_1;
  GtkWidget *c_1;
  GtkWidget *p_1;
  GtkWidget *d_1;
  GtkWidget *menuitem3;
  GtkWidget *menu3;
  GtkWidget *menuitem4;
  GtkWidget *menu4;
  GtkWidget *about1;
  GtkWidget *menuitem5;
  GtkWidget *menu5;
  GtkWidget *reboot_item;
  GtkWidget *shutdown_item;
  GtkWidget *notebook1;
  GtkWidget *empty_notebook_page;
  GtkWidget *text;

  
  GtkWidget *label4;
  GtkWidget *frame1;
  GtkWidget *alignment1;
  GtkWidget *vbox2;
  GtkWidget *scrolledwindow1;
  GtkWidget *treeview1;

  GtkWidget *hbox1;
  GtkWidget *hbox2;
  GtkWidget *button3;
  GtkWidget *button2;
  GtkWidget *button1;

  GtkWidget *label5;
  GtkWidget *vbox3;
  GtkWidget *label6;
  GtkWidget *frame2;
  AtkObject *atko;
  GtkWidget *alignment2;
  GtkWidget *scrolledwindow2;
 GtkWidget *viewport1;
 GtkWidget *label32;
 GtkWidget *label29;
GtkWidget *label30;
GtkWidget *drawing_area;
  GtkWidget *label20;
  GtkWidget *label7;
GtkWidget *label35;
 GtkWidget*hbox3;
  GtkWidget *label_cpu;  /*the cpu info bar*/
  GtkTreeSelection *selection;
  /*int i,j;*/
  GtkAccelGroup *accel_group;
 
  

  accel_group = gtk_accel_group_new ();

  window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);        /*创建主窗口*/
  gtk_window_set_title (GTK_WINDOW (window1), "Linux Manager by HIT-CS32 牛舒媛");      
  gtk_window_set_default_size(GTK_WINDOW(window1), 500,500);
  g_signal_connect(G_OBJECT(window1),"delete_event",G_CALLBACK(gtk_main_quit),NULL);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (window1), vbox1);

  menubar1 = gtk_menu_bar_new ();
  gtk_widget_show (menubar1);
  gtk_box_pack_start (GTK_BOX (vbox1), menubar1, FALSE, FALSE, 0);

  menuitem1 = gtk_menu_item_new_with_mnemonic ("文件");                           /*菜单各项建立过程*/
  gtk_widget_show (menuitem1);
  gtk_container_add (GTK_CONTAINER (menubar1), menuitem1);

  menu1 = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem1), menu1);

  new_item = gtk_image_menu_item_new_from_stock ("gtk-new", accel_group);
  gtk_widget_show (new_item);
  gtk_container_add (GTK_CONTAINER (menu1), new_item);

 open_item = gtk_image_menu_item_new_from_stock ("gtk-open", accel_group);
  gtk_widget_show (open_item);
  gtk_container_add (GTK_CONTAINER (menu1), open_item);


  menuitem2 = gtk_menu_item_new_with_mnemonic ("编辑");
  gtk_widget_show (menuitem2);
  gtk_container_add (GTK_CONTAINER (menubar1), menuitem2);

  menu2 = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem2), menu2);

  t_1 = gtk_image_menu_item_new_from_stock ("gtk-cut", accel_group);
  gtk_widget_show (t_1);
  gtk_container_add (GTK_CONTAINER (menu2), t_1);

  c_1 = gtk_image_menu_item_new_from_stock ("gtk-copy", accel_group);
  gtk_widget_show (c_1);
  gtk_container_add (GTK_CONTAINER (menu2), c_1);

  p_1 = gtk_image_menu_item_new_from_stock ("gtk-paste", accel_group);
  gtk_widget_show (p_1);
  gtk_container_add (GTK_CONTAINER (menu2), p_1);

  d_1 = gtk_image_menu_item_new_from_stock ("gtk-delete", accel_group);
  gtk_widget_show (d_1);
  gtk_container_add (GTK_CONTAINER (menu2), d_1);

  menuitem3 = gtk_menu_item_new_with_mnemonic ("查看");
  gtk_widget_show (menuitem3);
  gtk_container_add (GTK_CONTAINER (menubar1), menuitem3);

  menu3 = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem3), menu3);

  menuitem4 = gtk_menu_item_new_with_mnemonic ("帮助");
  gtk_widget_show (menuitem4);
  gtk_container_add (GTK_CONTAINER (menubar1), menuitem4);

  menu4 = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem4), menu4);

  about1 = gtk_menu_item_new_with_mnemonic ("关于");
  gtk_widget_show (about1);
  gtk_container_add (GTK_CONTAINER (menu4), about1);
  
   menuitem5=gtk_menu_item_new_with_mnemonic("关机");
   gtk_widget_show(menuitem5);
   gtk_container_add(GTK_CONTAINER(menubar1),menuitem5);
   
   menu5=gtk_menu_new();
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem5),menu5);
   
   reboot_item=gtk_menu_item_new_with_mnemonic("重启");
   gtk_widget_show(reboot_item);
   gtk_container_add(GTK_CONTAINER(menu5),reboot_item);

  shutdown_item=gtk_menu_item_new_with_mnemonic("关机");
   gtk_widget_show(shutdown_item);
   gtk_container_add(GTK_CONTAINER(menu5),shutdown_item);    
   
  notebook1 = gtk_notebook_new ();                                              /*创建笔记本*/
  gtk_widget_show (notebook1);
  gtk_box_pack_start (GTK_BOX (vbox1), notebook1, TRUE, TRUE, 0);

  empty_notebook_page = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (empty_notebook_page);
  gtk_container_add (GTK_CONTAINER (notebook1), empty_notebook_page);
 
   text=gtk_label_new(NULL);                                  /*显示系统信息*/
   gtk_widget_show(text);
   gtk_box_pack_start(GTK_BOX(empty_notebook_page),text,TRUE,TRUE,0);
   show_sys_info(text);
   
  
   
                          


  label4 = gtk_label_new ("系统信息");                                  
  gtk_widget_show (label4);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 0), label4);


  frame1 = gtk_frame_new (NULL);
  gtk_widget_show (frame1);
  gtk_container_add (GTK_CONTAINER (notebook1), frame1);
  gtk_container_set_border_width (GTK_CONTAINER (frame1), 13);
  gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_NONE);

  alignment1 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment1);
  gtk_container_add (GTK_CONTAINER (frame1), alignment1);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment1), 0, 0, 12, 0);

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox2);
  gtk_container_add (GTK_CONTAINER (alignment1), vbox2);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox2), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_SHADOW_IN);

   treeview1 = gtk_tree_view_new ();            
   gtk_widget_show (treeview1);
   gtk_container_add (GTK_CONTAINER (scrolledwindow1), treeview1);
 
   arrange_tree_view1(treeview1);
   show_proc(treeview1);
   gtk_timeout_add(15000,(GtkFunction)show_proc,treeview1);
   selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview1));
   gtk_tree_selection_set_select_function(selection, view_selection_func, NULL, NULL);  

   
 


  hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox1, FALSE, FALSE, 0);

  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox2);
  gtk_box_pack_start (GTK_BOX (hbox1), hbox2, TRUE, TRUE, 0);

  button3 = gtk_button_new_with_mnemonic ("查看进程");
  gtk_widget_show (button3);
  gtk_box_pack_start (GTK_BOX (hbox2), button3, FALSE, FALSE, 0);
   g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(b_find_thread_by_pid),NULL);  


  button2 = gtk_button_new_with_mnemonic ("结束任务");
  gtk_widget_show (button2);
  gtk_box_pack_start (GTK_BOX (hbox1), button2, FALSE, FALSE, 0);

  button1 = gtk_button_new_with_mnemonic ("退出");
  gtk_widget_show (button1);
  gtk_box_pack_start (GTK_BOX (hbox1), button1, FALSE, FALSE, 0);
  g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(gtk_main_quit),NULL);;

  clocker = gtk_label_new (NULL);
  gtk_widget_show (clocker);
  gtk_frame_set_label_widget (GTK_FRAME (frame1),clocker);
  gtk_label_set_use_markup (GTK_LABEL (clocker), TRUE);
  gtk_timeout_add(1000,(GtkFunction)timeout_callback,clocker);

 

  label5 = gtk_label_new ("进程");
  gtk_widget_show (label5);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 1), label5);

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox3);
  gtk_container_add (GTK_CONTAINER (notebook1), vbox3);

label35=gtk_label_new("cpu性能");
  gtk_widget_show (label35);
  gtk_box_pack_start (GTK_BOX (vbox3), label35, FALSE, FALSE, 0);

  hbox3 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox3);
  gtk_box_pack_start (GTK_BOX (vbox3), hbox3, TRUE, TRUE, 0);

  label_cpu = gtk_label_new (NULL );
  gtk_widget_show (label_cpu);
  gtk_box_pack_start (GTK_BOX (hbox3), label_cpu, FALSE, FALSE, 0);
  show_label(label_cpu);

   drawing_area=gtk_drawing_area_new();                   
  gtk_widget_show(drawing_area);
  gtk_box_pack_start(GTK_BOX(hbox3),drawing_area,TRUE,TRUE,0);
 gtk_signal_connect(GTK_OBJECT(drawing_area),"expose_event",G_CALLBACK(timer_expose_event) , NULL);
  g_signal_connect(G_OBJECT(drawing_area) , "configure_event" ,
              G_CALLBACK(cpu_configure_event) , NULL);
  gtk_widget_set_events(drawing_area,GDK_EXPOSURE_MASK);
 

 label29 = gtk_label_new ("label29");
  gtk_widget_show (label29);
  gtk_box_pack_start (GTK_BOX (vbox3), label29, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label29, -1, 100);
 gtk_timeout_add(1000,(GtkFunction)get_cpu_util,label29); 

  label30 = gtk_label_new ("label30");
  gtk_widget_show (label30);
  gtk_box_pack_start (GTK_BOX (vbox3), label30, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label30, -1, 210);
   gtk_timeout_add(1000,(GtkFunction)show_mem_info,label30);



 label6 = gtk_label_new ("性能");
  gtk_widget_show (label6);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 2), label6);

 

  frame2 = gtk_frame_new (NULL);
  gtk_widget_show (frame2);
  gtk_container_add (GTK_CONTAINER (notebook1), frame2);
  gtk_container_set_border_width (GTK_CONTAINER (frame2), 9);
  gtk_frame_set_shadow_type (GTK_FRAME (frame2), GTK_SHADOW_NONE);

  alignment2 = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment2);
  gtk_container_add (GTK_CONTAINER (frame2), alignment2);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment2), 0, 0, 12, 0);

  scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow2);
  gtk_container_add (GTK_CONTAINER (alignment2), scrolledwindow2);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_SHADOW_IN);

  viewport1 = gtk_viewport_new (NULL, NULL);
  gtk_widget_show (viewport1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow2), viewport1);

  label32 = gtk_label_new (NULL);           
  gtk_widget_show (label32);
  gtk_container_add (GTK_CONTAINER (viewport1), label32);
  show_disk_info(label32);
  gtk_timeout_add(10000,(GtkFunction)show_disk_info,label32);   
              
  label20 = gtk_label_new ("文件系统");
  gtk_widget_show (label20);
  gtk_frame_set_label_widget (GTK_FRAME (frame2), label20);
  gtk_label_set_use_markup (GTK_LABEL (label20), TRUE);

  label7 = gtk_label_new ("文件系统");
  gtk_widget_show (label7);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook1), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook1), 3), label7);


  
       

  g_signal_connect ((gpointer) new_item, "activate",
                    G_CALLBACK (on_new_item_activate),
                    NULL);
  g_signal_connect ((gpointer)open_item, "activate",
                    G_CALLBACK (on_open_item_activate),
                    NULL);
  g_signal_connect ((gpointer)t_1, "activate",
                    G_CALLBACK (on_t_1_activate),
                    NULL);
  g_signal_connect ((gpointer) c_1, "activate",
                    G_CALLBACK (on_c_1_activate),
                    NULL);
  g_signal_connect ((gpointer) p_1, "activate",
                    G_CALLBACK (on_p_1_activate),
                    NULL);
  g_signal_connect ((gpointer) d_1, "activate",
                    G_CALLBACK (on_d_1_activate),
                    NULL);
  g_signal_connect ((gpointer) about1, "activate",
                    G_CALLBACK (on_about1_activate),
                    NULL);
 g_signal_connect((gpointer)reboot_item,"activate",G_CALLBACK(on_reboot_item_activate),NULL);
 g_signal_connect((gpointer)shutdown_item,"activate",G_CALLBACK(on_shutdown_item_activate),NULL); 

  atko = gtk_widget_get_accessible (frame2);
  atk_object_set_name (atko, "frame2");
 gtk_window_add_accel_group (GTK_WINDOW (window1), accel_group);
   
   return window1;
}





void model_data_new1(GtkTreeModel* store1, 
                    const gchar* name, const gchar* stat, const gchar  *pid,const gchar  *ppid,const gchar  *nice, const gchar *mem) {   
    GtkTreeIter iter;
    gtk_list_store_append(GTK_LIST_STORE(store1), &iter);
    gtk_list_store_set(GTK_LIST_STORE(store1), &iter,
                       col_name, name,
                       col_stat, stat,
                       col_pid, pid,
                       col_ppid,ppid,
                      col_nice,nice,
                       col_mem, mem,
                       
                       
                      -1);
}

GtkTreeModel* create_model1() {         
    GtkListStore  *store1;
    store1 = gtk_list_store_new (n_cols1,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
    return GTK_TREE_MODEL(store1);
}

void arrange_tree_view1(GtkWidget* view) {
    GtkCellRenderer* renderer;
    renderer = gtk_cell_renderer_text_new ();

    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(view), -1, "进程\t", renderer, "text", col_name, NULL);
    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(view), -1, "状态\t", renderer, "text", col_stat, NULL);
    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(view), -1, "pid\t", renderer, "text", col_pid, NULL);
    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(view), -1, "父进程\t", renderer, "text", col_ppid, NULL);
   gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(view), -1, "nice\t", renderer, "text", col_nice, NULL);
    gtk_tree_view_insert_column_with_attributes(
        GTK_TREE_VIEW(view), -1, "内存\t", renderer, "text", col_mem, NULL);
   
   
} 






