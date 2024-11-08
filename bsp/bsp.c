/********************************************************************

   Created     :   2024.05.13.

   Author      : louiey

   Description :

   History     :

*********************************************************************/

#include"bsp.h"


BSP_ST gst_Bsp = {0};

int8_t bsp_init(void* p)
{
    int8_t ret = 0;

    gst_Bsp.isBspInit = true;
    gst_Bsp.prdTickDuration = 10000;
    gst_Bsp.prdTickCount = 0;
    gst_Bsp.isNotifyEnabled = false;

    cliInit();
    
    return ret;
}
