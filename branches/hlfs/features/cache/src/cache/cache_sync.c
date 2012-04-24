#include <string.h>
#include "cache.h"
#include "cache_helper.h"
#include "hlfs_log.h"

int cache_sync(CACHE_CTRL *cache_ctrl)
{
	HLOG_DEBUG("--Entering func :%s", __func__);
	int ret = 0;
    uint32_t free_size;
#if 1
    g_mutex_lock(cache_ctrl->cache_mutex);
    //g_cond_signal(cache_ctrl->flush_waken_cond);
    while ((free_size =__get_cache_free_size(cache_ctrl)) != cache_ctrl->cache_size) {
           HLOG_DEBUG("--sync all block--:free size:%d,total size:%d",free_size,cache_ctrl->cache_size);
           g_message("free_size:%d", free_size);
		   g_cond_signal(cache_ctrl->flush_waken_cond);
		   g_message("run here");
           HLOG_DEBUG("--signal flush again over--");
           g_cond_wait(cache_ctrl->writer_waken_cond, cache_ctrl->cache_mutex);
		   g_message("run here");
           HLOG_DEBUG("--sync to check again--");
           g_usleep(100);
		   //g_cond_signal(cache_ctrl->flush_waken_cond);
    }
    g_mutex_unlock(cache_ctrl->cache_mutex);
#endif
	HLOG_DEBUG("--leaving func :%s", __func__);
	return ret;
}
