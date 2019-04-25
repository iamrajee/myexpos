#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "simulator.h"

#include "disk_file.h"

static
xsm_options _options;

/* By default, assign 20 ticks. */
static
const int XSM_TIMER_DURATION = 20;

static
const int XSM_DISK_DURATION = 20;

static
const int XSM_CONSOLE_DURATION = 20;

int
simulator_run ()
{
	disk_init (XSM_DEFAULT_DISK);

	/* On your marks! */
	if (!machine_init (&_options))
		return XSM_FAILURE;

	/* Fire! */
	if (!machine_run ())
		return XSM_FAILURE;

	printf ("Machine is halting.\n");

	/* A little housekeeping. */
	machine_destroy ();
	disk_close ();
	return XSM_SUCCESS;
}

int
simulator_parse_args(int argc, char **argv)
{
	int val;

	argv++;
	argc --;

	/* Initialize with default values. */
	_options.timer = XSM_TIMER_DURATION;
	_options.console = XSM_CONSOLE_DURATION;
	_options.disk = XSM_DISK_DURATION;

	while (argc > 0)
	{
		if (!strcmp (*argv, "--debug"))
		{
			_options.debug = TRUE;

			argv ++;
			argc --;
		}
		else if (!strcmp(*argv, "--timer"))
		{
			argv ++;
			argc --;

			val = atoi(*argv);
            if (val < 0 || val > 1024)
            {
                printf("--timer takes value in the range 0-1024\n");
                exit(0);
            }
			_options.timer = val + 1;
			if(val == 0)
				_options.timer = 0;

			argv++;
			argc --;
		}
		else if (!strcmp(*argv, "--console"))
		{
			argv ++;
			argc --;

			val = atoi(*argv);
            if (val < 20 || val > 1024)
            {
                printf("--console takes value in the range 20-1024\n");
                exit(0);
            }
			_options.console = val + 1;

			argv++;
			argc--;
		}
		else if (!strcmp(*argv, "--disk"))
		{
			argv++;
			argc --;

			val = atoi(*argv);
            if (val < 20 || val > 1024)
            {
                printf("--disk takes value in the range 20-1024\n");
                exit(0);
            }
			_options.disk = val + 1;

			argv++;
			argc--;
		}
		else
		{
			/* Unrecognised option. */
			return XSM_FAILURE;
		}
	}

	return XSM_SUCCESS;
}
