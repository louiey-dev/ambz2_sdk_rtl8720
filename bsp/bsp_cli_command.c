/********************************************************************

   Created     :   2024.01.29.

   Author      : louiey.dev@gmail.com

   Description :  command line interface command handler

   History     :  // louiey, 2024.01.29. Basic code implemented

*********************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "bsp_cli.h"
#include "bsp_cli_command.h"

#include "bsp.h"

#define CLI_VERSION_INFO 	"RTL8720 CLI Version 0.1"

static Bool cliCommandInterpreter (int command, int argc, char** argv);
static const char *TAG = "cli";

extern BSP_ST gst_Bsp;

/**************************** PRIVATE FUNCTION DEFINITIONS *******************/
static CliJte cliCommandTable [] =
{
	{ "init",
      NULL,
      "Initialize",
      CLI_CMD_INITIALISE,
      1,
      NULL,
      0,
      &cliCommandInterpreter
    },
    { "ver",
      NULL,
      "Get version info",
      CLI_CMD_VERSION,
      1,
      NULL,
      0,
      &cliCommandInterpreter
    },
    { "set_prd",
      "set_prd 2000 // periodic duration value set to 2000ms",
      "Set periodic duration value",
      CLI_CMD_SET_PRD_DURATION,
      2,
      NULL,
      0,
      &cliCommandInterpreter
    },
    { "exit",
      NULL,
      "Quits the application",
      CLI_CMD_EXIT,
      1,
      NULL,
      0,
      &cliCommandInterpreter
    },
};



void cliCommandsInitialise (void)
{
    cliRegisterTable (pTableCli,
        "Cli commands",
        sizeof (cliCommandTable) / sizeof (cliCommandTable [0]),
        cliCommandTable
        );
}

static Bool cliCommandInterpreter (int command, int argc, char** argv)
{
    Bool result = TRUE; // Assume that we are going to process the command
    
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;

    // printf("cliCommandInterpreter cmd %d argc %d argv %s\n", command, argc, *argv);

    switch (command)
    {
        case CLI_CMD_INITIALISE:
        break;
		
        case CLI_CMD_VERSION:
        printf(TAG, "CLI Version %s", CLI_VERSION_INFO);
        break;

        case CLI_CMD_SET_PRD_DURATION:
        u16 = atoi(argv[1]);
        gst_Bsp.prdTickDuration = u16;
        gst_Bsp.prdTickCount = 0;
        printf("Periodic duration set to %d ms\n", u16);
        break;

        case CLI_CMD_EXIT:
        // Quit the program
        cliExit ();
        break;

    }

    return result;
}