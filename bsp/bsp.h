
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define USER_FUNC   __func__

#define LOGD					printf

#if 0
#define MSG(fmt, args...)     	LOGD("MSG [%s] "fmt"", ## args);
#define LOG(fmt, args...)     	LOGD("LOG [%s] "fmt"", ## args);
#define ERR(fmt, args...)     	LOGD("ERR [%s] [%s:%d] "fmt"", __FUNCTION__, __LINE__, ## args);
#define API(fmt, args...)     	LOGD("API [%s] [%s] "fmt"", __FUNCTION__, ## args);
#define TODO(fmt, args...)     	LOGD("TODO : "fmt"", ## args);
#endif

#define BSP_BUFF_LEN    32*3

typedef struct
{
	bool isBspInit;								///< true when tcp ip message is ready from host
    uint32_t prdTickDuration;
    int16_t prdTickCount;

    bool isBtEnabled;       // 

    bool isNotifyEnabled;
    bool isIndicateEnabled;

    uint8_t conn_id;
    uint8_t service_id;

    uint8_t buf[BSP_BUFF_LEN];
}__attribute__ ((packed)) BSP_ST;


/* BSP APIs */
int8_t bsp_init(void* p);

void cliInit(void);
void cliCommandsInitialise (void);
void cliLineParser(char* str);

int8_t bsp_periodic_task_init(void* p);
/***********************************************************/