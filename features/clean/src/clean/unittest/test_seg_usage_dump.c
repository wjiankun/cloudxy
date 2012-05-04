#include <glib.h>
#include <stdlib.h>
#include "clean_helper.h"
#include "clean.h"

#include "comm_define.h"

typedef struct {
     struct back_storage *storage;
} Fixture;

/* 
 * case1 setup: Build the environment for hlfs_take_snapshot().
 * Include:
 * --Format HLFS;
 * --Write something to HLFS;
 * --init and open hlfs readonly;
 */
Fixture fixture;

void case_setup()
{
	system("rm -rf /tmp/testenv");
	system("mkdir /tmp/testenv -p");
	//system("cd ../../../../ && ./output/bin/mkfs.hlfs -u local:///tmp/testenv/testfs -b 8192 -s 67108864 -m 1024 ");
	//system("cd -");
	char * uri = "local:///tmp/testenv/testfs";
	fixture->storage = init_storage_handler(uri);
    g_assert(NULL != fixture->storage);
}

/*
 * case1 test:
 * --call the function hlfs_take_snapshot with the arguments ctrl & "test_snapshot";
 *   The return value should be a minus.
 */

/*  write trigger wb*/
void test_seg_usage2text()
{
	int ret = 0;
	SEG_USAGE_T seg_usage;
	seg_usage->segno = 10;
	strcpy(seg_usage->up_sname,"test_snapshot",strlen("test_snapshot"));
	seg_usage->block_num = 64;
	seg_usage->inode_addr = 10101010;
	seg_usage->log_num = 8;
	seg_usage->timestamp = get_current_time();
	seg_usage->alive_block_num = 10;
	seg_usage->bitmap = g_malloc0(sizeof(int)*100);
	char textbuf[4096];
	memset(textbuf,4096,0);
    ret = seg_usage2text(&seg_usage,textbuf);
	g_assert(ret > 0);
	g_free(seg_usage->bitmap);
}


/*
 * case1 teardown:
 * --close hlfs;
 * --deinit hlfs;
 * --free the structure case1_fixture;
 * --rm hlfs root directory;
 */
void case_teardown()
{
	deinit_storage_handler(fixture->storage);
}

int main(int argc, char **argv) {
	if (log4c_init()) {
		g_message("log4c init error!");
	}
	g_test_init(&argc, &argv, NULL);
#if 1
	g_test_add("/misc/test_seg_usage2text", 
				Fixture, 
				NULL,
				case_setup, 
				test_seg_usage2text, 
				case_teardown);
#endif
#if 0
	g_test_add("/misc/cache_flush_work_2", 
				Fixture, 
				NULL,
				case_setup, 
				test_case_cache_flush_2, 
				case_teardown);
#endif 
#if 0
    g_test_add("/misc/cache_flush_work_3", 
				Fixture, 
				NULL,
				case_setup, 
				test_case_cache_flush_3, 
				case_teardown);
#endif
#if 0
    g_test_add("/misc/cache_flush_work_4", 
				Fixture, 
				NULL,
				case_setup, 
				test_case_cache_flush_4, 
				case_teardown);
#endif

	return g_test_run();
}

