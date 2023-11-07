/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_QUIT                       2       /* control type: command, callback function: quit */
#define  PANEL_AMOUNT                     3       /* control type: string, callback function: SendString_dataupdate */
#define  PANEL_CONFIG                     4       /* control type: command, callback function: Config */
#define  PANEL_PICTURE                    5       /* control type: picture, callback function: (none) */
#define  PANEL_TEXTMSG                    6       /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_4                  7       /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_3                  8       /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  9       /* control type: textMsg, callback function: (none) */
#define  PANEL_OUT_OF_STK                 10      /* control type: string, callback function: (none) */
#define  PANEL_TIMER                      11      /* control type: timer, callback function: RecTimer2 */
#define  PANEL_PICTURE_2                  12      /* control type: picture, callback function: (none) */

#define  PANEL_GRPH                       2
#define  PANEL_GRPH_EXIT                  2       /* control type: command, callback function: exit_out_of_stock */
#define  PANEL_GRPH_GRAPH                 3       /* control type: graph, callback function: (none) */
#define  PANEL_GRPH_SHOW_GRPH             4       /* control type: command, callback function: show */

#define  PANEL_MGMT                       3
#define  PANEL_MGMT_QUIT                  2       /* control type: command, callback function: quit */
#define  PANEL_MGMT_TEXTMSG_2             3       /* control type: textMsg, callback function: (none) */
#define  PANEL_MGMT_TEXTMSG               4       /* control type: textMsg, callback function: (none) */
#define  PANEL_MGMT_RCVR                  5       /* control type: textBox, callback function: (none) */
#define  PANEL_MGMT_TIMER                 6       /* control type: timer, callback function: RecTimer */
#define  PANEL_MGMT_NUMERIC_NEW_STOCK     7       /* control type: numeric, callback function: (none) */
#define  PANEL_MGMT_NUMERIC_FIRST         8       /* control type: numeric, callback function: (none) */
#define  PANEL_MGMT_APPLY_FIRST_STOCK     9       /* control type: command, callback function: print_stock */
#define  PANEL_MGMT_LED_OUT_OF_STOCK      10      /* control type: LED, callback function: (none) */
#define  PANEL_MGMT_APPLY_NEW_STOCK       11      /* control type: command, callback function: print_value */

#define  PANEL_OSTK                       4
#define  PANEL_OSTK_EXIT                  2       /* control type: command, callback function: exit_out_of_stock */
#define  PANEL_OSTK_TEXTMSG               3       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU2_2                  2
#define  MENUBAR_MENU2_2_ITEM6            3
#define  MENUBAR_MENU2                    4
#define  MENUBAR_MENU2_ITEM1              5

#define  MENUBAR1                         2
#define  MENUBAR1_1                       2
#define  MENUBAR1_1_ITEM3                 3       /* callback function: Client_panel */
#define  MENUBAR1_MENU                    4
#define  MENUBAR1_MENU_MENU1              5       /* callback function: stock_chart */
#define  MENUBAR1_MENU2                   6
#define  MENUBAR1_MENU2_ITEM1_3           7
#define  MENUBAR1_MENU3                   8
#define  MENUBAR1_MENU3_ITEM1_2           9


     /* Callback Prototypes: */

void CVICALLBACK Client_panel(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Config(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK exit_out_of_stock(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK print_stock(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK print_value(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RecTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RecTimer2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SendString_dataupdate(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK show(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK stock_chart(int menubar, int menuItem, void *callbackData, int panel);


#ifdef __cplusplus
    }
#endif
