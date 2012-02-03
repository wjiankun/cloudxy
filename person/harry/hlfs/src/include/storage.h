#ifndef _HLFS_STORAGE_H_
#define _HLFS_STORAGE_H_


#include <stdint.h>
#include "glib.h"
#include "comm_define.h"
//#include "bs_local.h"

#define BS_READONLY 0
#define BS_WRITEABLE 1

typedef void* bs_file_t;
typedef void* bs_fs_t;


typedef struct file_info{
  const char name[SEGMENT_FILE_NAME_MAX];
  char       is_dir;
  uint64_t   size;
  uint64_t   lmtime;
}bs_file_info_t;

struct back_storage   
{   
   char* storage_name;
   const char* uri;
//   const char* fs_location;
   char* user;
   uint32_t port;
   bs_fs_t     fs_handler;
   int        (*bs_fs_connect)(struct back_storage *storage,const char* uri); 
   int        (*bs_fs_disconnect)(struct back_storage *storage); 
   bs_file_t  (*bs_file_open) (struct back_storage *storage ,const char* path,int flags); 
   int        (*bs_file_close)(struct back_storage *storage ,bs_file_t file);
   int        (*bs_file_is_exist)(struct back_storage *storage,const char *path);
   uint64_t   (*bs_file_tell)(struct back_storage *storage,bs_file_t file);
   int        (*bs_file_append)(struct back_storage *storage,bs_file_t file,const char *write_buff,uint32_t write_len);
   int        (*bs_file_pread)(struct back_storage *storage ,bs_file_t file,const char *read_buff,uint32_t read_len,uint64_t pos);
   int        (*bs_file_flush)(struct back_storage *storage ,bs_file_t file);
   int        (*bs_file_delete)(struct back_storage *storage ,const char *path);
   bs_file_t  (*bs_file_create)(struct back_storage *storage,const char *path);
   int        (*bs_file_mkdir)(struct back_storage *storage,const char *path);
   bs_file_info_t*
              (*bs_file_info)(struct back_storage *storage,const char *path);
   bs_file_info_t*
              (*bs_file_list_dir)(struct back_storage *storage,const char * dir,uint32_t* num_entries);};
#endif 

