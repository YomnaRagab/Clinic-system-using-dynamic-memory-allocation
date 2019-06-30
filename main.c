#include <stdio.h>
#include "types.h"
#include "proto.h"
tstrlist strlist;
void main (void)
{
  strlist.liststart=strlist.listend=NULL;//the begining list is empty
  mode x; //mode is enum type for admin and user
  u8 i; //a counter
  u16 pass; //admin pass
  printf("Clinic Management System\n   ****Hello****\nFor Admin mode press 0\nFor patient mode press 1\nYour choice: ");
  scanf("%d",&x); //scan the Choice
  switch (x) //switch for it
  {
    case admin: //in case of admin choice then
      printf("Enter Admin pass: "); //admin must enter the pass
      for (i=0; i<3; i++) // there 's three traials
        {
          scanf("%d",&pass);
          if(pass !=1234 && i<2 ) //if the pass is wrong and the trials aren't finished yet then
            {
              printf("Wrong pass...\nTry again: "); // ask for the pass again
            }
          else if (pass==1234) //if the pass is right then it will go for admin func
            {
                Admin();
                break;
              }
          else //if the i>2 and pass is wrong that's meaning the trials are finished
          {
            printf("Your traials are finished");
            break;
          }
        }
      break;
    case patient: //case of patient mode it will open the func immediately
      User();
      break;
    default: // otherwise meaning INVALID choice
      printf("Invalid choice...");
  }

}
