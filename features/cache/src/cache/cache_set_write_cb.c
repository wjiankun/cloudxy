#include "cache.h"
#include "hlfs_log.h"
int cache_set_write_cb(CACHE_CTRL *cache_ctrl, void *cb_func, void * cb_user_param)
{
    if(NULL == cache_ctrl || NULL == cb_func){
       HLOG_ERROR("--Error: Params error!--");
       return -1;
    }
	int ret = 0;
    if(NULL!=cache_ctrl->write_callback_func){
       HLOG_WARN("--cache write cb switch to new--");
    }
    cache_ctrl->write_callback_func = cb_func;
    cache_ctrl->write_callback_user_param = cb_user_param;
	return ret;
}