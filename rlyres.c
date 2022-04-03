#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"conio2.h"
#include"rlyres.h"
int enterchoice()
{
    int choice,i;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("-");
    printf("\nSelect an option");
    printf("\n1-View Trains");
    printf("\n2-Book Ticket");
    printf("\n3-View Ticket");
    printf("\n4-Search Ticket No");
    printf("\n5-View All Bookings");
    printf("\n6-View Train Bookings");
    printf("\n7-Cancel Ticket");
    printf("\n8-Cancel Train");
    printf("\n9-Quit");
    printf("\n\nEnter Choice:");
    scanf("%d",&choice);
    return choice;
}
void add_trains()
{
    Train alltrains[4]={
              {"123","BPL","GWA",2100,1500},
              {"546","BPL","DEL",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360},
              };
   FILE *fp=fopen("d:\\C PROJECT\\myproject\\alltrains.dat","rb");
   if(fp==NULL)
   {
       fp=fopen("d:\\C PROJECT\\myproject\\alltrains.dat","wb");
       fwrite(alltrains,4*sizeof(Train),1,fp);
       printf("File created and saved!\n");
   }
   else
    printf("File already present\n");
   fclose(fp);

}
void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
    for(i=1;i<=80;i++)
        printf("-");
    FILE *fp=fopen("d:\\C PROJECT\\myproject\\alltrains.dat","rb");
    Train tr;

    while(fread(&tr,sizeof(tr),1,fp)==1)
    printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    printf("\n\n\n\n");
fclose(fp);
}

int check_train_no(char *trainno)
{
    FILE *fp=fopen("d:\\C PROJECT\\myproject\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
          if(strcmp(tr.train_no,trainno)==0)
          {
                  fclose(fp);
                  return 1;
          }

    }
fclose(fp);
return 0;
}
int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
       while(*p_mob!='\0')
      {
           if(isdigit(*p_mob)==0)
               return 0;
        p_mob++;
     }
      return 1;
}


Passenger * get_passenger_details()
{
    clrscr();

    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    static Passenger psn;
    printf("Enter passenger name:");
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *pos;
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
    if(strcmp(psn.p_name,"0")==0)
        {
          textcolor(LIGHTRED);
          gotoxy(1,25);
          printf("Reservation Cancelled!");
          getch();
          textcolor(YELLOW);
          return NULL;
        }
    int valid;
    printf("Enter gender(M/F):");
    do
        {
            valid=1;
            fflush(stdin);
            scanf("%c",&psn.gender);
            if(psn.gender=='0')
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            if(psn.gender!='M' && psn.gender!='F')
            {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Gender should be M or F (in uppercase)");
            valid=0;
            getch();
            gotoxy(19,2);
            printf(" \b");
            textcolor(YELLOW);
            }
    }
            while(valid==0);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,3);
            printf("Enter train number:");
            do
            {
                fflush(stdin);
                scanf("%s",psn.train_no);
                if(strcmp(psn.train_no,"0")==0)
                  {
                    textcolor(LIGHTRED);
                    gotoxy(1,25);
                    printf("\t\t\t\t\t\t\t");
                    gotoxy(1,25);
                    printf("Reservation Cancelled!");
                    getch();
                    textcolor(YELLOW);
                    return NULL;
                  }
                 valid=check_train_no(psn.train_no);
                if(valid==0)
                  {
                    textcolor(LIGHTRED);
                    gotoxy(1,25);
                    printf("Error! Invalid Train No");
                    getch();
                    gotoxy(20,3);
                    printf("\t\t\t\t\t\t");
                    gotoxy(20,3);
                    textcolor(YELLOW);
                 }
            }
            while(valid==0);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,4);
            printf("Enter travelling class(First AC-F,Second AC-S):");
            do
            {
               valid=1;
               fflush(stdin);
            scanf("%c",&psn.p_class);
            if(psn.p_class=='0')
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            if(psn.p_class!='F' && psn.p_class!='S')
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error! Travelling class should be F or S (in uppercase)");
                valid=0;
                getch();
                gotoxy(48,4);
                printf(" \b");
                textcolor(YELLOW);
            }
          }
            while(valid==0);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,5);
            printf("Enter address:");
            fflush(stdin);
            fgets(psn.address,20,stdin);
            pos=strchr(psn.address,'\n');
            *pos='\0';
            if(strcmp(psn.address,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            printf("Enter age:");
            do
            {
              valid=1;
              fflush(stdin);
            scanf("%d",&psn.age);
            if(psn.age==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            if(psn.age<=0)
            {
               textcolor(LIGHTRED);
               gotoxy(1,25);
               printf("Error! Age should be positive");
               valid=0;
               getch();
               gotoxy(11,6);
               printf("\t\t\t\t\t\t\t");
               gotoxy(11,6);
               textcolor(YELLOW);
            }
           }
            while(valid==0);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,7);
            printf("Enter mobile number:");
            do
            {
               fflush(stdin);
               fgets(psn.mob_no,12,stdin);
               pos=strchr(psn.mob_no,'\n');
            if(pos!=NULL)
             *pos='\0';
            if(strcmp(psn.mob_no,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            valid=check_mob_no(psn.mob_no);
            if(valid==0)
            {
               textcolor(LIGHTRED);
               gotoxy(1,25);
               printf("Error! Invalid Mobile No");
               getch();
               gotoxy(21,7);
               printf("\t\t\t\t\t\t");
               gotoxy(21,7);
               textcolor(YELLOW);
            }
            }
            while(valid==0);
            return &psn;
}

  int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp=fopen("d:\\C PROJECT\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc)
            ++count;
    }
    fclose(fp);
    return count;
}
int last_ticket_no()
{
    FILE *fp=fopen("d:\\C PROJECT\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    fseek(fp,-1*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}
int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==30)
    {
        textcolor(LIGHTRED);
        printf("All seats full in train no %s in %c class!\n",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no()+1;
    p.ticketno=ticket_no;
    FILE * fp=fopen("d:\\C PROJECT\\myproject\\allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}
int accept_ticket_no()
{
printf("Enter ticket no:");
int valid;
int ticket_no;
do
{
 valid=1;
 scanf("%d",&ticket_no);
 if(ticket_no==0)
 {
   textcolor(LIGHTRED);
   gotoxy(1,25);
   printf("\t\t\t\t\t\t\t");
   gotoxy(1,25);
   printf("Cancelling Input. . .!");
   textcolor(YELLOW);
   return 0;
}
if(ticket_no<0)
{
   textcolor(LIGHTRED);
   gotoxy(1,25);
   printf("Error! Ticket number should be positive");
   valid=0;
   getch();
   gotoxy(11,1);
   printf("\t\t\t\t\t\t\t");
   gotoxy(11,1);
   textcolor(YELLOW);
}
} while(valid==0);
return ticket_no;
}

void view_ticket(int ticket_no)
{
    int i;
    FILE *fp=fopen("d:\\C PROJECT\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
        return;
    }

    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
    if(pr.ticketno==ticket_no)
    {

       printf("\nNAME: %s\nGENDER: %c\nTRAIN NO: %s\nCLASS: %c\nADDRRESS: %s\nAGE: %d\nMOBILE NO: %s\nTICKET NO: %d\n",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
       printf("\n\n");
      found=1;
      break;
    }
    }
    if(!found)
    {
        textcolor(LIGHTRED);
        printf("\nNo details of ticket no %d found!",ticket_no);

    }
fclose(fp);
}

char* accept_mob_no()
{
static char mob_no[11];
char *pos;
int valid;
printf("Enter mobile number:");
do
{
fflush(stdin);
fgets(mob_no,11,stdin);
pos=strchr(mob_no,'\n');
if(pos!=NULL)
   *pos='\0';
if(strcmp(mob_no,"0")==0)
{
  textcolor(LIGHTRED);
  gotoxy(1,25);
  printf("\t\t\t\t\t\t\t");
  gotoxy(1,25);
  printf("Cancelling Input. . .!");
  getch();
  textcolor(YELLOW);
  return NULL;
}
valid=check_mob_no(mob_no);
if(valid==0)
  {
   textcolor(LIGHTRED);
   gotoxy(1,25);
   printf("Error! Invalid Mobile No");
   getch();
   gotoxy(21,1);
   printf("\t\t\t\t\t\t");
   gotoxy(21,1);
   textcolor(YELLOW);
  }
 }while(valid==0);
clrscr();
return mob_no;
}
int* get_ticket_no(char *p_mob_no)
{
   int count=0;
   FILE *fp=fopen("d:\\C PROJECT\\myproject\\allbookings.dat","rb");
   if(fp==NULL)
    {
        return NULL;
    }
   Passenger pr;
   while(fread(&pr,sizeof(pr),1,fp)==1)
    {
      if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
   }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
      if(strcmp(pr.mob_no,p_mob_no)==0)
      {
          *(p+i)=pr.ticketno;
            i++;
      }
    }
*(p+i)=-1;
fclose(fp);
return p;
}
void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! No tickets booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress any key to go back to the main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets booked for mobile no %s",pmob_no);
    int i;
    printf("\n\nTICKET NO\n");
    printf("---------");
    for(i=0;*(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
textcolor(WHITE);
printf("\n\nPress any key to go back to the main screen");
textcolor(YELLOW);
getch();
}
 char* accept_train_no()
{
	gotoxy(60,1);
 	textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(WHITE);
    static char trainno[10];
    int valid;
    printf("Enter train number:");
    do
    {
        valid=1;
        fflush(stdin);
        textcolor(YELLOW);
        fgets(trainno,20,stdin);
        char* pos=strchr(trainno,'\n');
        if(pos!=NULL)
        *pos='\0';

        if(strcmp(trainno,"0") == 0)
        {
        gotoxy(1,25);
        textcolor(RED);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("Cancelling Input");
        textcolor(YELLOW);
        return NULL;
        }
        valid=check_train_no(trainno);
        if(valid == 0)
        {
            textcolor(RED);
            gotoxy(1,25);
            printf("Error!Invalid train number");
            getch();
            gotoxy(20,1);
            printf("\t\t\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);
        }
    }while(valid == 0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t");
    clrscr();
    return trainno;
}

void view_booking(char* trainno)
{
    clrscr();
    textcolor(YELLOW);
    FILE* fp=fopen("d:\\C PROJECT\\myproject\\allbookings.dat","rb");
    if(fp == NULL)
    {
        textcolor(RED);
        printf("No bookings done yet");
        return;
    }
    Passenger pr;
    int found=0;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(int i=0;i<80;i++)
    {
        printf("-");
    }
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        textcolor(6);
        if(strcmp(pr.train_no,trainno) == 0)
        {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found=1;
        }
    }
    if(found == 0)
    {
        clrscr();
        textcolor(RED);
        gotoxy(1,24);
        printf("No details of bookings in train no %s found",trainno);
    }
    textcolor(WHITE);
    printf("\nPress any key to go back to the main screen");
    fclose(fp);
    return;
}

int cancel_ticket(int ticket_no)
{
	FILE* fp;
	fp=fopen("d:\\C PROJECT\\myproject\\allbookings.dat","rb");
	if(fp == NULL)
	{
		textcolor(RED);
		printf("\nNo bookings done yet");
		return -1;
	}
	FILE* sp;
	sp=fopen("d:\\C PROJECT\\myproject\\temp.dat","wb");
	Passenger pr;
	int found=0;
	while(fread(&pr,sizeof(pr),1,fp) == 1)
	{
		if(pr.ticketno == ticket_no)
			found=1;
		else
			fwrite(&pr,sizeof(pr),1,sp);
    }
	fclose(fp);
    fclose(sp);
	int result;
	if(found == 0)
	{
        remove("d:\\C PROJECT\\myproject\\temp.dat");
	}
    else
    {
        result=remove("d:\\C PROJECT\\myproject\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("d:\\C PROJECT\\myproject\\temp.dat","d:\\C PROJECT\\myproject\\allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}

void view_all_bookings()
{
    clrscr();
    FILE* fp;
    fp=fopen("d:\\C PROJECT\\myproject\\allbookings.dat","rb");
    if(fp == NULL)
    {
        textcolor(RED);
        printf("No bookings done yet!");
        return;
    }
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(int i=0;i<80;i++)
    {
        printf("-");
    }
    Passenger pr;
    textcolor(6);
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        printf("%d->%s\t\t%c\t%s",pr.ticketno,pr.train_no,pr.p_class,pr.p_name);
        gotoxy(41,row);
        printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
        row++;
    }
    fclose(fp);
}


int cancel_train(char* trainno)
{
    FILE* fp=fopen("d:\\C PROJECT\\myproject\\alltrains.dat","rb");
    if(fp == NULL)
    {
        textcolor(RED);
        printf("No trains are Running");
        return -1;
    }
    Train tp;
    int found=0;
    while(fread(&tp,sizeof(tp),1,fp)==1)
    {
        if(strcmp(tp.train_no,trainno) == 0)
            found=1;
    }
    fclose(fp);
    if(!found)
    {
        return found;
    }
    else
    {
        FILE* fp=fopen("d:\\C PROJECT\\myproject\\allbookings.dat","rb");
        FILE* sp=fopen("d:\\C PROJECT\\myproject\\temp1.dat","wb");
        Passenger pr;
        int result=0;
        while(fread(&pr,sizeof(pr),1,fp) == 1)
        {
            if(strcmp(trainno,pr.train_no) == 0)
                result=1;
            else
                fwrite(&pr,sizeof(pr),1,sp);
        }
        fclose(fp);
        fclose(sp);
        if(!result)
        {
            remove("d:\\C PROJECT\\myproject\\temp1.dat");
        }
        else
        {
            result=remove("d:\\C PROJECT\\myproject\\allbookings.dat");
            if(result!=0)
                return 2;
            result=rename("d:\\C PROJECT\\myproject\\temp1.dat","d:\\C PROJECT\\myproject\\allbookings.dat");
            if(result!=0)
                return 2;
        }
    }
    return found;
}





