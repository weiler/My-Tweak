#include "cs32.h"


struct Thread pro[MAX_THREAD];


/*
 * function : to show the disk infomation
 * parameter: label to show
 * return void
 * 2012 5 27
 */
gint show_disk_info(GtkWidget * label32){        
      int fd;
      char *buf;
      buf=(char *)malloc(2000*sizeof(char));
      fd=open("/proc/partitions",O_RDONLY);
      read(fd,buf,1000);
      close(fd);
      gtk_label_set_text(GTK_LABEL(label32),buf);
      return 1;
}





/*
 * function : to show the system infomation
 * parameter: label to show
 * return void
 * 2012 5 27
 */
void show_sys_info(GtkWidget * text){ 
     int fd0;
     int fd1;
     int fd2;
     char *buf,*buf1;
     buf=(char *)malloc(2000*sizeof(char));
     buf1=(char *)malloc(2000*sizeof(char));
      strcat(buf,"\n主机名:");
     fd0=open("/proc/sys/kernel/hostname",O_RDONLY);
      read(fd0,buf1,2000);
     close(fd0);
     strcat(buf,buf1);
     strcat(buf,"\n系统版本号:");
     fd1=open("/proc/sys/kernel/osrelease",O_RDONLY);
     read(fd1,buf1,2000);
     close(fd1);
     strcat(buf,buf1);
     strcat(buf,"\ncpu型号和主频:");
     fd2=open("/proc/cpuinfo",O_RDONLY);
     read(fd2,buf1,165);
     close(fd2);
     strcat(buf,buf1);
      gtk_label_set_text(GTK_LABEL(text),buf);
      free(buf);
      free(buf1);
     }




/*
 * function : to show the memory information
 * parameter: label to show
 * return void
 * 2012 5 27
 */
gint show_mem_info(GtkWidget *label30){  
    int fd;
    char *buf;
    buf=(char *)malloc(500*sizeof(char));
    
     fd=open("/proc/meminfo",O_RDONLY);
     read(fd,buf,350);
     close(fd);
     gtk_label_set_text(GTK_LABEL(label30),buf);
     free(buf);
        
    return 1;
}




/*
 * function : to show the system time 
 * parameter: label to show
 * return void
 * 2012 5 27
 */
gint timeout_callback(GtkWidget *clocker){   
    int fd;
    int time_run;
    int hour,minute,second; 
    time_t now,timep;
     struct tm *l_time;
     char *buf,*buf1;
     buf=(char *)malloc(256*sizeof(char));
     buf1=(char *)malloc(256*sizeof(char));
     now=time((time_t*)NULL);
     l_time=localtime(&now);
     sprintf(buf,"现在时间:%d:%d:%d",l_time->tm_hour,l_time->tm_min,l_time->tm_sec);
     strcat(buf,"\n系统开启时间:");
     fd=open("/proc/uptime",O_RDONLY);
     read(fd,buf1,100);
     time_run=atoi(strtok(buf1,"."));
     time(&timep);
     timep-=time_run;
      strcat(buf,ctime(&timep));
      strcat(buf,"系统运行时间:");
      fd=open("/proc/uptime",O_RDONLY);
      read(fd,buf1,100);
      time_run=atoi(strtok(buf1,"."));
      hour=time_run/3600;
      minute=(time_run-hour*3600)/60;
      second=time_run%60;
      sprintf(buf1,"%d:%d:%d",hour,minute,second);
      strcat(buf,buf1);
     gtk_label_set_text(GTK_LABEL(clocker),buf);
     free(buf);
      free(buf1);
     return 1;
}




/*
 * function : get the current cpu usage information 
 * parameter: label to show
 * return void
 * 2012 5 27
 */
gint get_cpu_util(GtkWidget *label29){  
      int fp;
      char *buf,*name,*buf1;
      buf=(char *)malloc(256*sizeof(char));
      buf1=(char *)malloc(256*sizeof(char));
      name=(char *)malloc(256*sizeof(char));
      long user1,system1,nice1,idle1,iowait1,irq1,softirq1;
     
      long sum1,sum2;
      
     
      fp=open("/proc/stat",O_RDONLY);
      read(fp,buf,200);
      sscanf(buf,"%s %ld %ld %ld %ld %ld %ld %ld",name,&user1,&system1,&nice1,&idle1,&iowait1,&irq1,&softirq1);
      sum1=user1+nice1+system1+idle1+iowait1+irq1+softirq1;
      close(fp);
     sum2=user2+nice2+system2+idle2+iowait2+irq2+softirq2;
  
      util=(float)100.0*(user2-user1+system2-system1)/(sum2-sum1);
      
      user2=user1;system2=system1;nice2=nice1;idle2=idle1;iowait2=iowait1;irq2=irq1;softirq2=softirq1;
      printf("%f",util);
      sprintf(buf1,"cpu使用率:%f %%\n\n\n\n\n内存信息:",util);
      
      
      close(fp);
     
     gtk_label_set_text(GTK_LABEL(label29),buf1);
    
      free(buf);
     free(buf1);
     free(name);
      return 1;
} 



int show_pro_info(void){   
     DIR *dir;
     struct dirent *ptr;
     int fd,tt;
     int i=0;
     int j;
     int total=0;
     char path_statm[50];
     char path_status[50];
     char path_stat[50];
     char buffer[100];
     char buf[100];
     dir=opendir("/proc");
     
     while((ptr=readdir(dir))!=NULL){
          if(select_name(ptr->d_name)){
            strcpy(pro[i].pid,ptr->d_name);
            i++;
            total++;
      }
   }
   closedir(dir);
    for(i=0;i<total;i++){
      strcpy(path_statm,"/proc/");
      strcpy(path_status,"/proc/");
      strcat(path_statm,pro[i].pid);
      strcat(path_statm,"/statm");
      strcat(path_status,pro[i].pid);
      strcat(path_status,"/status");
      strcpy(path_stat,"/proc/");
      strcat(path_stat,pro[i].pid);
      strcat(path_stat,"/stat"); 
       fd=open(path_status,O_RDONLY);
       tt=read(fd,buffer,100);
       strtok(buffer,":");
       strcpy(pro[i].comm,strtok(NULL,"\n"));
       strtok(NULL,":");
        strcpy(pro[i].state,strtok(NULL,"\n"));
        strtok(NULL,":");
        strtok(NULL,"\n");
        strtok(NULL,":");
        strtok(NULL,"\n");
        strtok(NULL,":");
        strtok(NULL,"\n");
        strtok(NULL,":");
        strcpy(pro[i].ppid,strtok(NULL,"\n"));
        close(fd);
       fd=open(path_statm,O_RDONLY);
        tt=read(fd,buf,100);
       strcpy(pro[i].mem,strtok(buf," "));
       strcat(pro[i].mem,"kb");
       close(fd); 
       fd=open(path_stat,O_RDONLY);
       tt=read(fd,buf,100);
       strtok(buf," ");
      for(j=0;j<17;j++){
         strtok(NULL," ");
       }
       strcpy(pro[i].nice,strtok(NULL," "));
        close(fd);
      
       }
      
       return total;
    }



gint show_proc(GtkWidget *treeview1){     
   int i,num;
    GtkTreeModel *store = create_model1();
  
   gtk_tree_view_set_model ( GTK_TREE_VIEW(treeview1),  store);
   num=show_pro_info();
  /*if(num) gtk_list_store_clear(GTK_LIST_STORE(store));*/
   
   for(i=0;i<num;i++)
          model_data_new1(store,pro[i].comm,pro[i].state,pro[i].pid,pro[i].ppid,pro[i].nice,pro[i].mem);  //
g_object_unref( store );
return 1;      
}


int select_name(char name[])  
{   int i;
    for(i=0;name[i]!=0;i++)
        if(isalpha(name[i])||name[i]=='.')
              return 0;
    return 1;
 }  



