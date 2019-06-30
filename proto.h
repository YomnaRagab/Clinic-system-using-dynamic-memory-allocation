#ifndef proto
#define proto
#include "types.h"
typedef enum
{
  admin=0,
  patient=1,
}mode;
typedef enum
{
  add=1,
  edit=2,
  reservation=3,
  cancelReservation=4,
  userMode=5,
}enchoice;
typedef enum
{
  viewRecord=1,
  viewReservation=2,
}enpatientchoice;
typedef struct
{
  u32 ID;
  u8 reservedTime;
}resrve;
struct patient
{
  u16 age;
  u32 ID;
  u16 gender[10];
  u16 name[20];
  struct patient *nextpatient;
  struct patient *prevpatient;
};
typedef struct patient tstrpatient;

typedef struct
{
   tstrpatient *liststart;
   tstrpatient *listend;
}tstrlist;
void Admin(void);
void User(void);
void AddPatient(void);
void SearchPatient (u32);
void EditPatient(void);
void ReservePatient (void);
void DeleteReservePatient (void);
void PatientViewRecord (void);
void PatientViewReservation (void);
#endif
