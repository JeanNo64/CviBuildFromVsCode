#include <userint.h>
#include <ansi_c.h>
#include <cvirte.h>
#include "uir.h"

static int panelHandle;
static int numButtonPresses = 0;
static char msgString[100];

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;    /* out of memory */
    panelHandle = LoadPanel (0, "uir.uir", PANEL);
    if(panelHandle <0) {
        MessagePopup("Error", "Unable to load myuir.uir, make sure it\nis in the same directory as this executable.");
        return 1;
    }
    DisplayPanel (panelHandle);
    RunUserInterface ();
    return 0;
}


int CVICALLBACK TestCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    switch (event) {
        case EVENT_COMMIT:
            numButtonPresses++;
            sprintf(msgString, "Working: button pressed %d times\n", numButtonPresses);
            SetCtrlVal (panelHandle, PANEL_STATUS_STRING, msgString);
            break;
    }
    return 0;
}

int CVICALLBACK QuitCallback (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
    switch (event) {
        case EVENT_COMMIT:
            QuitUserInterface (0);
            break;
    }
    return 0;
}
