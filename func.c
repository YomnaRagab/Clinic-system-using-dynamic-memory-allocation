#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "proto.h"
extern tstrlist strlist;
tstrpatient *tmp=NULL;
resrve y[5]; // for reserved patients
u8 reservedTime[5]={1,2,3,4,5};
u8 i=0; //counter
u8 empty; //indication for the patient list
void Admin(void)
{
  u8 exitflag=1;
  enchoice adminChoice;
  printf("Hi Admin\n");
  do
  {
  printf("-----------------------------------------\nYour options:\n1)Add new patient record.\n2)Edit patient record\n3)Reserve a slot with the doctor\n4)Cancel reservation\n5)User mode\n*Press 0 to exit*\nYour choice: ");
  scanf("%d",&adminChoice);// choice is enum type
  switch (adminChoice)
  {
    case add:
      AddPatient();
     break;
    case edit:
      EditPatient();
    break;
    case reservation:
      ReservePatient();
      break;
    case cancelReservation:
      DeleteReservePatient();
      break;
    case userMode: //it's avaliable in admin mode reach the user mode otherwise user mode always will be empty ! as all data is here!
      User();
    case 0:
      exitflag=0;
      printf("BYE Admin :D");
      break;
    default:
    printf("Invalid choice\n");
    break;
  }
}while(exitflag==1);
}
void AddPatient (void)
{

  tstrpatient*ptrPatient=(tstrpatient*) malloc (sizeof(tstrpatient));
  printf("Enter patient ID: "); //  scan the name , age , gender and ID from the user and save them is a struct variable in dynamic memory allocation.
  scanf("%d",&(ptrPatient->ID));
  printf("Name: ");
  scanf("%s",(ptrPatient->name));
  printf("Gender: ");
  scanf("%s",(ptrPatient->gender));
  printf("Age: ");
  scanf("%d",&(ptrPatient->age));
  printf("%d\n",(ptrPatient->ID));
  printf("%s\n",(ptrPatient->name));
  printf("%s\n",(ptrPatient->gender));
  printf("%d\n",(ptrPatient->age));

  SearchPatient(ptrPatient->ID); // after the scan it's gonna search for the existation of the ID
  while (tmp!=NULL) // if the ID is exist it will loop until it's not
  {
    printf("ID must be unique: ");
    scanf("%d",&ptrPatient->ID);
    SearchPatient(ptrPatient->ID); // it will search again for it
  }
  if(strlist.liststart==NULL) // if The patient is the first one in the element then
  {
    strlist.liststart=strlist.listend=ptrPatient; // the list start and end it will be it
    ptrPatient->nextpatient=ptrPatient->prevpatient=NULL; // and the next of the patient and the previous of it , will be null
  }
  else // if it's not the first patient to add then
  {
    strlist.listend->nextpatient=ptrPatient; //the next of the list end**which refers to the previous patient** will be the new patient
    ptrPatient->prevpatient=strlist.listend; // the previous of the new patient will be the old list end
    ptrPatient->nextpatient=NULL; // the next of the new patient will be null as it's the end of the list
    strlist.listend=ptrPatient; // the new end will be the new patient!
  }

}
void SearchPatient (u32 ID) // it taked ID to search
{ if (strlist.liststart != NULL) // check if the list is empty or no , if yes temp will take oxoo , if no it will start to search
  {
    tmp=strlist.liststart; // start from the list start
  while ((tmp->nextpatient!=NULL)&&(tmp->ID!=ID)) // if temp next not null *it's not the last node* and temp ID not the searched one then
  {
    tmp=tmp->nextpatient; // it will jump to the next element of the list
  }
  if (tmp->nextpatient != NULL ) //As if ID already was founded , it doesn't needed to check the last node
  {
    tmp=tmp;

  }
  else if ((tmp->nextpatient==NULL)&&(tmp->ID==ID)) // if temp is the last node and it conatins the same ID then it's not empty
  {
    tmp=tmp;
  }
  else // the next of temp is null but its ID is not equal to searched one
  {
    tmp=NULL;
  }
  empty=0;
}
else
{
  tmp=NULL;
  empty=1; //it is just indication for another function to know if it's empty or no

}
}
void EditPatient(void)
{
  u32 ID;
  printf("Please enter the ID to edit: "); // scan from the user the desired ID to edit
  scanf("%d",&ID);
  SearchPatient(ID); // search for it
  if (tmp==NULL) // if tmp is null that's meaning it's not existing
  {
    printf("It doesn't exist\n");
  }
  else // otherwise
  {
    printf("Patient infromation\n"); // it's gonna show the patient information to know which one admin wanna change
    printf("Patient ID %d\n",tmp->ID);
    printf("patient name %s\n",tmp->name);
    printf("patient gender %s\n",tmp->gender);
    printf("patient age %d\n",tmp->age);
    printf("- - - - - - - -\n");
    printf("You can edit the name , gender and age\n"); // of course it's not allowed to change the ID ! otherwise he/she can add patient from the start !
    printf("Enter patient name: ");
    scanf("%s",(tmp->name));
    printf("Gender: ");
    scanf("%s",(tmp->gender));
    printf("Age: ");
    scanf("%d",&(tmp->age));
    printf("Current Data are:"); // it's gonna show the changed data
    printf("ID:%d\n",(tmp->ID));
    printf("Name:%s\n",(tmp->name));
    printf("Gender:%s\n",(tmp->gender));
    printf("Age:%d\n",(tmp->age));

  }
}
void ReservePatient (void)
{
  u8 ii; // it's just a counter
  if((reservedTime[0]==0)&&(reservedTime[1]==0)&&(reservedTime[2]==0)&&(reservedTime[3]==0)&&(reservedTime[4]==0)) // check for avaliablity of reservation*complete or no**
  {
    printf("Reservation is complete, see u tomorrow.\n");
  }
  else
  {
  printf("1)2pm to 2:30pm\n2)2:30pm to 3pm\n3)3pm to 3:30pm\n4)4pm to 4:30pm\n5)4:30pm to 5pm\n"); // there are 5 slots to Reserve
  printf("Allowed choices are:\n");
  for(ii=0; ii<5; ii++)
  {
    printf("%d ",reservedTime[ii]); //array carries the allowed choices from the slots, it's array of 5
  }
  printf("\nYour choice: ");
  scanf("%d",&(y[i].reservedTime)); //scan the choice in array of 5 element each one from type struct one from the ID and another for the slot
  for(ii=0; ii<5;ii++ )
    {
      if (y[i].reservedTime==0) //it's not allowed to choice 0 as it's meaning this slot is reseerved
      {
        printf("INVALID choice\n");
        break;
      }
      else if(y[i].reservedTime==reservedTime[ii]) //if the admin choice is one from the allowed choice which saved in specific array
      {
        printf("please enter patient ID: "); // then it's gonna take the ID to put it in the same element of the array
        scanf("%d",&(y[i].ID));
        printf("slot: %d ID: %d\n",y[i].reservedTime,y[i].ID); // it's gonna print the slot and its ID
        reservedTime[ii]=0; //make this slot by 0 which meaning it's not avaliable
        i++;// increase the counter of array which saved the ID and its slot
        break; // break the loop
      }
      else if(((y[i].reservedTime)!=reservedTime[ii])&&(ii==4)) // if the choice is not one of the allowed choices in the array and counter get on the last elemnt of it , it's meaning not allowed choice
      {
        printf("INVALID choice\n");
      }
    }
}
}
void DeleteReservePatient (void) //deleting a reservation
{
  u8 j; //counter
  u32 ID; //ID for scannin
  printf("Enter patient ID to cancel the reservation: ");//scan the specific ID to delete the reservation
  scanf("%d",&ID);
  for(j=0; j<i; j++)
  {
    if((y[j].ID)==ID) //if the ID is one of the reservation array
    {
      printf("ID: %d , reservedTime was choice number: %d were deleted\n",y[j].ID,y[j].reservedTime); //it's gonna show the ID and its slot
      y[j].ID=0; //put the ID =0
      reservedTime[(y[j].reservedTime)-1]=y[j].reservedTime; //put this slot again in slots array as each element number -1 equals its value
      y[j].reservedTime=0; //put the ID slot by 0
      break; // break the loop
    }
    else if ((j==i-1) && (ID!=y[j].ID)) // if the ID doesn't equale any elemnt of the reservation array and the counter reached to the end of the list it's meaning it's not valid
    {
      printf("Invalid ID\n");
    }
  }
}
void User(void) //User mode
{
  enpatientchoice patientchoice; //enum type for patient choices *user mode*
  u8 exitflag=1;
  printf("USER MODE\n***********HELLO***********\n");
  while (exitflag==1) //while loop until the user chooce to exit!
  {
    printf("Your options:\n1)View patient record.\n2)View today reservation.\n**To exit press 0**\n  Your choice: ");
    scanf("%d",&patientchoice);
    switch(patientchoice) // switch on patient mode
    {
      case viewRecord:
        PatientViewRecord ();
        break;
      case viewReservation:
        PatientViewReservation ();
        break;
      case 0:
        exitflag=0;
        break;
      default:
      printf("Invalid choice\n");
    }
  }

}
void PatientViewRecord (void)
{
  u32 ID;
  printf("Enter patient ID: ");
  scanf("%d",&ID); //scan the ID to show its data
  SearchPatient(ID); //search the entered  ID
  if(empty==1) //if empty ==1 ! that's indication of empty list
  {
    printf("LIST is EMPTY\n");
  }
  else if(tmp!=NULL) // if tmp isn't equale to NULL that's meaning it exist
  {
    printf("Patient ID %d\n",tmp->ID); // will print the ID data
    printf("patient name %s\n",tmp->name);
    printf("patient gender %s\n",tmp->gender);
    printf("patient age %d\n",tmp->age);

  }
  else //if the list is nt empty and tmp is not equal to null meanings the ID doesn't exist ! incorrect one
  {
    printf("ID is incorrect\n");
  }

}
void PatientViewReservation (void)
{
  u8 count; //a counter
  if(i>0) //if i<0 that's meaning the reservation array*list* is empty
  {
    printf("1)2pm to 2:30pm\n2)2:30pm to 3pm\n3)3pm to 3:30pm\n4)4pm to 4:30pm\n5)4:30pm to 5pm\n");
    printf("Today's reservation:\n");
    for (count=0; count<i; count++)
    {
      if((y[count].ID!=0)&&(y[count].reservedTime!=0)) //it's the deleted reservation ID equals 0 and slot also
        printf("Patient ID: %d , reservation slot number: %d\n",y[count].ID, y[count].reservedTime);
    }
}
else
{
  printf("reservation list is empty\n");
}
}
