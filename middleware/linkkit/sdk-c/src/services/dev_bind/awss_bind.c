/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */
#include <stdio.h>
#include "iot_import.h"
#include "awss_cmp.h"
#include "awss_notify.h"
#include "awss_bind_statis.h"

#ifdef WIFI_PROVISION_ENABLED
#include "awss_statis.h"
#endif

#ifdef DEVICE_MODEL_ENABLED
#include "awss_reset.h"
#endif

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

static void *awss_bind_mutex = NULL;

int awss_report_cloud()
{
    if (awss_bind_mutex == NULL) {
        awss_bind_mutex = HAL_MutexCreate();
        if (awss_bind_mutex == NULL)
            return -1;
    }

    HAL_MutexLock(awss_bind_mutex);

    awss_cmp_online_init();
#ifdef DEVICE_MODEL_ENABLED
    awss_check_reset();
#endif
    awss_report_token();

    awss_cmp_local_init();
    awss_dev_bind_notify_stop();
    awss_dev_bind_notify();
#ifdef WIFI_PROVISION_ENABLED
#ifndef AWSS_DISABLE_REGISTRAR
    extern void awss_registrar_init(void);
    awss_registrar_init();
#endif
    AWSS_DISP_STATIS();
#endif
    AWSS_DB_DISP_STATIS();
    HAL_MutexUnlock(awss_bind_mutex);
    return 0;
}

int awss_bind_deinit()
{
    if (awss_bind_mutex)
        HAL_MutexLock(awss_bind_mutex);

#ifdef DEVICE_MODEL_ENABLED
    awss_stop_report_reset();
#endif
    awss_stop_report_token();
    awss_cmp_online_deinit();

    awss_dev_bind_notify_stop();

    awss_cmp_local_deinit(1);
#ifdef WIFI_PROVISION_ENABLED
#ifndef AWSS_DISABLE_REGISTRAR
    extern void awss_registrar_deinit(void);
    awss_registrar_deinit();
#endif
    AWSS_CLEAR_STATIS();
#endif
    AWSS_DB_CLEAR_STATIS();

    if (awss_bind_mutex) {
        HAL_MutexUnlock(awss_bind_mutex);
        HAL_MutexDestroy(awss_bind_mutex);
    }

    awss_bind_mutex = NULL;

    return 0;
}

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif