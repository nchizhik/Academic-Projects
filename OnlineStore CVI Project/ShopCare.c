#include <formatio.h>
#include <ansi_c.h>
#include <utility.h>
#include <rs232.h>
#include <cvirte.h>		
#include <userint.h>
#include "ShopCare.h"

void update_stock_file(); 
static int panelHandle, panelHandle_Manager,panelHandle_Oostk,panelHandle_Graph;
int SendCom = 1;
int RecvCom = 2;
int Err;
int LineNum = 0;
int x[2000];
static int pic;
/*********************************************************************/   
void MyPolling ()
{
char RecBuff[100];
int Recv_Num;
int N;
	N = ComRdTerm (RecvCom, RecBuff, 100, 0);
	RecBuff[N] = 0;  //Buffer becomes a string 
	InsertTextBoxLine (panelHandle_Manager, PANEL_MGMT_RCVR, -1, RecBuff);
	SetCtrlAttribute (panelHandle_Manager, PANEL_MGMT_RCVR, ATTR_FIRST_VISIBLE_LINE, LineNum++);
	
	//changing string to int:
	sscanf (RecBuff, "%d", &Recv_Num);

	//changing to negative value because taking stock out
	Recv_Num*=-1;
	
	//update stock
	SetCtrlAttribute (panelHandle_Manager, PANEL_MGMT_NUMERIC_NEW_STOCK, ATTR_CTRL_VAL, Recv_Num);
	update_stock_file();   

	
	return;
}
/*********************************************************************/   
void MyPolling2 ()
{
char RecBuff[100];
int Recv_Num;
int N;
	N= ComRdTerm (SendCom, RecBuff, 100, 0);
	RecBuff[N] = 0;
	
	sscanf (RecBuff, "%d", &Recv_Num);
	
	if (Recv_Num==1)

		DisplayPanel (panelHandle_Oostk);

	return;
}
/*********************************************************************/ 
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "ShopCare.uir", PANEL)) < 0)
		return -1;
	if ((panelHandle_Manager = LoadPanel (0, "ShopCare.uir", PANEL_MGMT)) < 0)
		return -1;
	if ((panelHandle_Oostk = LoadPanel (0, "ShopCare.uir", PANEL_OSTK)) < 0)
		return -1;
	if ((panelHandle_Graph = LoadPanel (0, "ShopCare.uir", PANEL_GRPH)) < 0)
		return -1;
	
	
	DisplayPanel (panelHandle);
	DisplayPanel (panelHandle_Manager);

	RunUserInterface ();
	DiscardPanel (panelHandle);
	DiscardPanel (panelHandle_Manager); 
	DiscardPanel (panelHandle_Oostk);
	DiscardPanel (panelHandle_Graph);

	Err = CloseCom (SendCom);
	Err = CloseCom (RecvCom);
	
	
	return 0;
}
/*********************************************************************/   
int CVICALLBACK quit (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			DeleteGraphPlot (panelHandle_Graph, PANEL_GRPH_GRAPH, -1, VAL_IMMEDIATE_DRAW);

			QuitUserInterface (0);
			break;
	}
	return 0;
}

/*********************************************************************/   
int CVICALLBACK Config (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			Err = OpenComConfig (SendCom, "", 9600, 0, 7, 1, 512, 512);
			Err = OpenComConfig (RecvCom, "", 9600, 0, 7, 1, 512, 512);
		
				SetCtrlAttribute (panelHandle_Manager, PANEL_MGMT_TIMER, ATTR_ENABLED, 1);
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
				SetCtrlAttribute (panelHandle, PANEL_AMOUNT, ATTR_DIMMED, 0);
				
				break;
	}
	return 0;
}
/*********************************************************************/   
int CVICALLBACK SendString_dataupdate (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
char SendBuff[100];
int Len;
	switch (event)
	{
		case EVENT_COMMIT:
			
			SetCtrlAttribute (panelHandle, PANEL_PICTURE_2, ATTR_VISIBLE, 1);
			pic=1;
			//forward data to COM
			GetCtrlVal (panelHandle, PANEL_AMOUNT, SendBuff);
			Len = strlen(SendBuff);
			ComWrt (SendCom, SendBuff, Len+1);
			Delay(0.1);
			
			
			break;
	}
	return 0;
}
/*********************************************************************/   
int CVICALLBACK RecTimer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int N;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			N = GetInQLen (RecvCom);	 
			if (!N)  return(0);			   
			MyPolling ();
			
			if (pic==1)
			{
				SetCtrlAttribute (panelHandle, PANEL_PICTURE_2, ATTR_PICT_BGCOLOR, VAL_WHITE);
				Delay(0.8);
				SetCtrlAttribute (panelHandle, PANEL_PICTURE_2, ATTR_PICT_BGCOLOR, VAL_DK_RED);
				Delay(0.8);
			}
			break;
	}
	return 1;
}
/*********************************************************************/   
int CVICALLBACK RecTimer2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
int N;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			N = GetInQLen (SendCom);	 
			if (!N)  return(0);			  //check if we got a message (empty/valid port) 
			MyPolling2 ();
			break;
	}
	return 1;
}
/*********************************************************************/
void CVICALLBACK manager_window (int menuBar, int menuItem, void *callbackData,
								 int panel)
{ 
	DisplayPanel (panelHandle_Manager);    

}
/*********************************************************************/   
int CVICALLBACK print_stock (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{   int first_amount;
	FILE* fp;
	FILE* fp2; 
	
switch (event)
	{
		case EVENT_COMMIT:
			
	    GetCtrlVal (panelHandle_Manager, PANEL_MGMT_NUMERIC_FIRST, &first_amount);
		SetCtrlAttribute (panelHandle_Manager, PANEL_MGMT_NUMERIC_FIRST, ATTR_DIMMED, 1);
		SetCtrlAttribute (panelHandle_Manager, PANEL_MGMT_APPLY_FIRST_STOCK, ATTR_DIMMED, 1);
		
		SetCtrlAttribute (panelHandle_Manager, PANEL_MGMT_NUMERIC_NEW_STOCK, ATTR_DIMMED, 0);
		SetCtrlAttribute (panelHandle_Manager, PANEL_MGMT_APPLY_NEW_STOCK, ATTR_DIMMED, 0);
		
			fp = fopen ("Stock Data list.txt", "w");
			fp2= fopen ("Stock Data Value.txt", "w"); 
			fprintf(fp,"%d\n",first_amount);  
			fprintf(fp2,"%d",first_amount);
			
			fclose (fp);
		 	fclose (fp2);

			break;
	}
	return 0;
}
/*********************************************************************/
int CVICALLBACK print_value (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		
		  update_stock_file();

			break;
	
	}
	return 0;
}
/*********************************************************************/
void update_stock_file()

{	FILE* fp;
	FILE* fp2;
	char Out_of_stock_buff[100];
   	int new_amount, final_amount,Present_Stock,Len; 
	
	GetCtrlVal (panelHandle_Manager, PANEL_MGMT_NUMERIC_NEW_STOCK, &new_amount);    	

			fp2 = fopen ("Stock Data Value.txt", "r");
			//check amount
			fscanf(fp2,"%d" ,&Present_Stock);
			
			//calc
			final_amount= new_amount+Present_Stock;
			
			
			//end of Stock check -> turn on led please and show banner
			if (final_amount<=0)
			{	
				SetCtrlVal (panelHandle_Manager, PANEL_MGMT_LED_OUT_OF_STOCK, 1);
				GetCtrlVal (panelHandle, PANEL_OUT_OF_STK, Out_of_stock_buff);
				Len = strlen(Out_of_stock_buff);  
				ComWrt (RecvCom, Out_of_stock_buff , Len+1); 
				Delay(0.1);
			}
			else
			{
				SetCtrlVal (panelHandle_Manager, PANEL_MGMT_LED_OUT_OF_STOCK, 0);
				fp = fopen ("Stock Data list.txt", "a");
				fp2= fopen ("Stock Data Value.txt", "w"); 
				fprintf(fp,"%d\n", final_amount);  
				fprintf(fp2,"%d", final_amount);
	
				fclose (fp);
		 		fclose (fp2);
			}		
}

/*********************************************************************/

int CVICALLBACK exit_out_of_stock (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				HidePanel (panelHandle_Oostk); 
				HidePanel (panelHandle_Graph); 
				DeleteGraphPlot (panelHandle_Graph, PANEL_GRPH_GRAPH, -1, VAL_IMMEDIATE_DRAW);

			break;
	}
	return 0;
}
/*********************************************************************/
void CVICALLBACK stock_chart (int menuBar, int menuItem, void *callbackData,
							  int panel)
{

			 
			DisplayPanel (panelHandle_Graph);
	
}

 /*********************************************************************/

void CVICALLBACK Client_panel (int menuBar, int menuItem, void *callbackData,
							   int panel)
{		   	
	DisplayPanel (panelHandle);
	
}
/*********************************************************************/

int CVICALLBACK show (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	   	char len;
		FILE* fp;
		
	switch (event)
	{
		case EVENT_COMMIT:
			
		
				fp= fopen ("Stock Data list.txt", "r");
				
				for(len=0;!feof(fp);len++)
				fscanf(fp,"%d",x+len);
				
				
				PlotY (panelHandle_Graph, PANEL_GRPH_GRAPH, x, len, VAL_UNSIGNED_INTEGER, VAL_FAT_LINE, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1,
					   VAL_RED);
				
			
			  	fclose(fp);	
			break;
	}
	return 0;
}
