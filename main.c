#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include <example_entry.h>

extern void console_init(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	/* Initialize log uart and at command service */
	console_init();

	/* pre-processor of application example */
	pre_example_entry();

	/* wlan initialization */
	wlan_network();

	/* Execute application example */
	example_entry();

	// louiey, 2024.05.13. 
	/* user func */
	bsp_init(NULL);
	bsp_periodic_task_init(NULL);	// louiey, 2024.10.30. 

	// ble_app_init();
	/*************************************/

	/* Enable Schedule, Start Kernel */
	vTaskStartScheduler();

	/* Should NEVER reach here */
	return 0;
}

