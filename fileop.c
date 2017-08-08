#include "fileop.h"
#include <stdio.h>
#include <stdlib.h>

 void CreateFile()
 {
 printf("creat Done\n");
 }

 void OpenFile()
 {
 printf("open Done\n");
 }

 void SaveFile()
 {
 printf("save Done\n");
 }

 void Exit()
 {
 printf("exit Done\n");
 exit(0);
 }

 static CmdEntry cmdArray[10] = {
 {&CreateFile, "create file"},
 {&OpenFile, "open file"},
 {&SaveFile, "save file"},
 {&Exit, "exit"},
 // <?? 1>?????????
 {0, 0} // ??
 };


 void showHelp()
 {

 for (int i = 0; (i < 10) && cmdArray[i].pfuncmd; i++){
 printf("%d\t%s\n", i, cmdArray[i].cHelp);
 }
 }

 int main(void)
 {
 int iCmdNum;
 char cTmp1[256];

 while (1){
 showHelp();
 printf("Select item \n");
 iCmdNum = getchar() - '0'; 
 gets(cTmp1); //
 if (iCmdNum >= 0 && iCmdNum < 10 && cmdArray[iCmdNum].pfuncmd){
 cmdArray[iCmdNum].pfuncmd();
 }
 else{
	 printf("Inlegal No,please re-select\n");
	 }
 }
}
