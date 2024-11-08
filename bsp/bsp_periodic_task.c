

#include "FreeRTOS.h"
#include "task.h"
#include <platform/platform_stdlib.h>
#include <simple_ble_service.h>

#include "bsp.h"

extern BSP_ST gst_Bsp;
int64_t notifyCount = 0;
int32_t indicateCount = 0;

extern bool simp_ble_service_send_v4_indicate(uint8_t conn_id, T_SERVER_ID service_id, void *p_value,
                                     uint16_t length);
extern bool simp_ble_service_send_v3_notify(uint8_t conn_id, T_SERVER_ID service_id, void *p_value,
                                     uint16_t length);

static void bsp_periodic_task(void *arg)
{
    printf("bsp_periodic_task start");

    while (1) 
    {
        vTaskDelay(gst_Bsp.prdTickDuration);
        printf("%s Tick => %d\n", USER_FUNC, gst_Bsp.prdTickCount++);

        /* check bt status */ // louiey, 2024.05.17. 
        if( (gst_Bsp.isBtEnabled != 1) && (gst_Bsp.prdTickCount == 1) )
        {
            gst_Bsp.isBtEnabled = 1;
            ble_app_init();
        }

        if(gst_Bsp.isNotifyEnabled)
        {
            printf("[%s] notify %d, %d\n", __func__, gst_Bsp.prdTickCount + notifyCount, sizeof(gst_Bsp));
            notifyCount += 50;
            simp_ble_service_send_v3_notify(gst_Bsp.conn_id, gst_Bsp.service_id, &gst_Bsp, sizeof(gst_Bsp));

            // printf("[%s] notify %d\n", __func__, notifyCount++);
            // simp_ble_service_send_v3_notify(gst_Bsp.conn_id, gst_Bsp.service_id, &notifyCount, sizeof(notifyCount));
        }

        if(gst_Bsp.isIndicateEnabled)
        {
            printf("[%s] indicate %d\n", __func__, indicateCount++);
            simp_ble_service_send_v4_indicate(gst_Bsp.conn_id, gst_Bsp.service_id, &indicateCount, sizeof(indicateCount));
        }
    }
}

int8_t bsp_periodic_task_init(void* p)
{
    int8_t ret = 0;

    xTaskCreate(bsp_periodic_task, "bsp_periodic_task", 1024*1, NULL, configMAX_PRIORITIES, NULL);
    printf("bsp_periodic_task_init\n");

    return ret;
}
