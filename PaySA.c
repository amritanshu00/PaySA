#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
/*
Bank User ID: bank1234
Password: 1234bank
*/
struct Bank
{
char user[21];
char pass[21];
long unsigned int bal;
};
struct Name
{
char fname[21];
char lname[21];
};
struct request
{
long unsigned int amount;
char reason[31],date[11],from[11];
};
struct pb
{
long unsigned int amount;
char func[11];
struct Name name;
char number[11];
char date[11];
};
struct PaySa
{
struct Bank bank;
long unsigned int balance;
struct Name name;
struct pb passbook[100];
struct request req[10];
char mobile[11];
char email[31];
char pass[21];
int OTP;
char DOB[11];
int no;
int zr;
int zf;
};
void cscreen()
{
system("cls");
}
void construct(struct PaySa* x)
{
x->balance=0;
strcpy(x->DOB,"\0");
strcpy(x->email,"\0");
strcpy(x->mobile,"\0");
strcpy(x->pass,"\0");
x->OTP=0;
x->no=0;
x->zr=-1;
x->zf=-1;
x->bank.bal=0;
strcpy(x->bank.user,"\0");
strcpy(x->bank.pass,"\0");
strcpy(x->name.fname,"\0");
strcpy(x->name.lname,"\0");
int i;
for(i=0;i<10;i++)
{
x->req[i].amount=0;
x->passbook[i].amount=0;
strcpy(x->req[i].date,"\0");
strcpy(x->req[i].reason,"\0");
strcpy(x->req[i].from,"\0");
strcpy(x->passbook[i].func,"\0");
strcpy(x->passbook[i].number,"\0");
strcpy(x->passbook[i].date,"\0");
strcpy(x->passbook[i].name.fname,"\0");
strcpy(x->passbook[i].name.lname,"\0");
}
}
void genOTP(struct PaySa* x)
{
char s[21];
srand(time(0));
printf("Enter your PaySa password\n");
scanf("%s",s);
cscreen();
if(!(strcmp(s,x->pass)))
{
x->OTP=(rand()%(999-100+1))+100;
printf("Your OTP is %d\n",x->OTP);
getch();
}
else
{
printf("Wrong password\n");
getch();
genOTP(x);
}
}
void display(struct PaySa* x)
{
printf("First name\n%s\nLast name\n%s\nMobile number\n%s\nE-mail ID\n%s\nPaySa wallet balance\n%lu\n",x->name.fname,x->name.lname,x->mobile,x->email,x->balance);
}
void input(struct PaySa* x)
{
FILE *filep;
filep=fopen("PaySa.dat","ab");
if(filep==NULL)
{
printf("Cannot create file for input\n");
getch();
return;
}
int p,i;
for(i=0;i<100;i++)
{
cscreen();
printf("Enter your mobile number\n");
scanf("%s",x->mobile);
if(checkmobile(x))
break;
else
getch();
}
if(!checkmobile(x))
return;
for(i=0;i<100;i++)
{
cscreen();
printf("Enter your mobile number\n%s\n",x->mobile);
printf("Enter your E-mail ID\n");
scanf("%s",x->email);
if(checkemail(x))
break;
else
getch();
}
if(!checkemail(x))
return;
for(i=0;i<100;i++)
{
cscreen();
printf("Enter your mobile number\n%s\nEnter your E-mail ID\n%s\n",x->mobile,x->email);
printf("Create your PaySa password\n");
scanf("%s",x->pass);
if(strlen(x->pass)==0)
{
printf("PaySa password is neccesary for protecting your PaySa account\n");
getch();
}
else
break;
}
if(strlen(x->pass)==0)
return;
genOTP(x);
for(i=0;i<100;i++)
{
cscreen();
printf("Enter the One Time Password(OTP)\tTo resend OTP press 1\n");
scanf("%d",&p);
if(p==1)
genOTP(x);
else if(p!=x->OTP)
{
printf("Wrong OTP\n");
getch();
continue;
}
else
break;
}
if(p!=x->OTP)
return;
for(i=0;i<100;i++)
{
cscreen();
printf("Enter your full name[(first name) (last name)]\n");
scanf("%s",x->name.fname);
scanf("%s",x->name.lname);
if(strlen(x->name.fname)==0)
{
printf("Your name is neccesary information for creating your PaySa account\n");
getch();
}
else
break;
}
if(strlen(x->name.fname)==0)
return;
printf("Enter your date of birth(dd/mm/yyyy)\n");
scanf("%s",x->DOB);
for(i=0;i<100;i++)
{
cscreen();
printf("Enter your net banking username\n");
scanf("%s",x->bank.user);
if(strlen(x->bank.user)==0)
{
printf("Your net banking username is neccesary information for creating your PaySa account\n");
getch();
}
else
break;
}
if(strlen(x->bank.user)==0)
return;
for(i=0;i<100;i++)
{
cscreen();
printf("Enter your net banking username\n%s\n",x->bank.user);
printf("Enter your net banking password\n");
scanf("%s",x->bank.pass);
if(strlen(x->bank.pass)==0)
{
printf("Your net banking password is neccesary information for creating your PaySa account\n");
getch();
}
else
break;
}
if(strlen(x->bank.pass)==0)
return;
printf("Enter your bank balance\n");
scanf("%lu",&x->bank.bal);
fwrite(x,sizeof(struct PaySa),1,filep);
fclose(filep);
cscreen();
printf("\t\tYour PaySa account has been created succesfully\n");
display(x);
printf("To use your account login to PaySa\n");
getch();
}
int checkemail(struct PaySa* x)
{
int a=0;
FILE* filep;
filep=fopen("PaySa.dat","rb");
if(filep==NULL)
{
printf("Cannot open file for checking E-mail ID\n");
getch();
return 0;
}
if(strlen(x->email)!=0)
{
fseek(filep,0,SEEK_SET);
struct PaySa* e;
e=(struct PaySa*)malloc(sizeof(struct PaySa));
construct(e);
while(fread(e,sizeof(struct PaySa),1,filep))
{
if(!(strcmp(x->email,e->email)))
a++;
}
free(e);
fclose(filep);
if(a==1)
{
printf("Account associated with this E-mail ID already exists\n");
getch();
return 0;
}
else
return 1;
}
else
return 1;
}
int checkmobile(struct PaySa* x)
{
int a=0;
FILE* filep;
filep=fopen("PaySa.dat","rb");
if(filep==NULL)
{
printf("Cannot open file for checking mobile number\n");
getch();
return 0;
}
fseek(filep,0,SEEK_SET);
struct PaySa* e;
e=(struct PaySa*)malloc(sizeof(struct PaySa));
construct(e);
while(fread(e,sizeof(struct PaySa),1,filep))
{
if(!(strcmp(x->mobile,e->mobile)))
a++;
}
free(e);
fclose(filep);
if(a==1)
{
printf("Account linked to this number already exists\n");
getch();
return 0;
}
else if(strlen(x->mobile)!=10)
{
printf("Invalid mobile number\n");
getch();
return 0;
}
else
return 1;
}
void modify(struct PaySa* x)
{
int a,j;
char b,c,p[21],s[21];
do
{
cscreen();
printf("Enter your choice\n1. Change name\n2. Change E-mail ID\n3. Change password\n4. Change date of birth\n5. Exit\n");
scanf("%d",&a);
cscreen();
switch(a)
{
case 1:printf("Current name\n%s %s\nAre you sure you want to change your registered name?(y/n)\n",x->name.fname,x->name.lname);
       scanf("%c",&c);
       if(c=='n'||c=='N')
       break;
       getch();
       cscreen();
       printf("Enter new name [(first name) (last name)]\n");
       scanf("%s",x->name.fname);
       scanf("%s",x->name.lname);
       break;
case 2:printf("Current E-mail ID\n%s\nAre you sure you want to change your E-mail ID?(y/n)\n",x->email);
       scanf("%c",&c);
       if(c=='n'||c=='N')
       break;
       getch();
       cscreen();
       printf("Enter new E-mail ID\n");
       scanf("%s",x->email);
       break;
case 3:printf("Are you sure you want to change your PaySa password?(y/n)\n");
       scanf("%c",&c);
       if(c=='n'||c=='N')
       break;
       getch();
       for(j=0;j<100;j++)
       {
       cscreen();
       printf("Enter new password\n");
       scanf("%s",s);
       printf("Re-enter password\n");
       scanf("%s",p);
       if(strcmp(s,p))
       printf("Unseccessful, passwords do not match\n");
       else
       {
       strcpy(x->pass,s);
       break;
       }
       }
       break;
case 4:printf("Current date of birth\n%s\nAre you sure you want to change your registered date of birth?(y/n)\n",x->DOB);
       scanf("%c",&c);
       if(c=='n'||c=='N')
       break;
       getch();
       cscreen();
       printf("Enter new date of birth (dd/mm/yyyy))\n");
       scanf("%s",x->DOB);
       break;
case 5:return;
default:printf("Not a valid option\n");
}
cscreen();
printf("Do you want to modify other registered information?(y/n)\n");
scanf(" %c",&b);
}while(b=='y'||b=='Y');
}
void pay(struct PaySa* x)
{
int b,i;
long unsigned int a;
i=0;
cscreen();
printf("Enter amount to be paid\n");
scanf("%lu",&a);
if(a>x->balance)
{
printf("Transaction not possible (PaySa balance is low)\n");
getch();
return;
}
x->passbook[x->no].amount=a;
printf("Enter date(dd/mm/yyyy)\n");
scanf("%s",x->passbook[x->no].date);
printf("Enter mobile number of receiver\n");
scanf("%s",x->passbook[x->no].number);
FILE* filep,* filep1;
filep=fopen("PaySa.dat","rb");
if(filep==NULL)
{
printf("Cannot open file for checking receiver's number\n");
getch();
return;
}
fseek(filep,0,SEEK_SET);
struct PaySa* e;
e=(struct PaySa*)malloc(sizeof(struct PaySa));
construct(e);
filep1=fopen("temp.dat","wb");
if(filep1==NULL)
{
printf("Cannot open file for creating receiver's passbook\n");
getch();
return;
}
fseek(filep1,0,SEEK_SET);
while(fread(e,sizeof(struct PaySa),1,filep))
{
if(!(strcmp(x->passbook[x->no].number,e->mobile)))
{
cscreen();
strcpy(x->passbook[x->no].name.fname,e->name.fname);
strcpy(x->passbook[x->no].name.lname,e->name.lname);
strcpy(e->passbook[e->no].name.fname,x->name.fname);
strcpy(e->passbook[e->no].name.lname,x->name.lname);
e->passbook[e->no].amount=a;
strcpy(e->passbook[e->no].func,"Received from");
strcpy(e->passbook[e->no].date,x->passbook[x->no].date);
strcpy(e->passbook[e->no].number,x->mobile);
printf("Transfer to\n1. PaySa wallet\n2. Bank account\n");
scanf("%d",&b);
switch(b)
{
case 1:e->balance+=a;
       break;
case 2:e->bank.bal+=a;
       break;
default:printf("Invalid choice\n");
}
e->no++;
i++;
}
fwrite(e,sizeof(struct PaySa),1,filep1);
}
free(e);
fclose(filep);
fclose(filep1);
remove("PaySa.dat");
rename("temp.dat","PaySa.dat");
if(i==0)
{
printf("Account not found\n");
getch();
return;
}
strcpy(x->passbook[x->no].func,"Sent to");
cscreen();
printf("Rupees %lu have been sent to %s %s\n",a,e->name.fname,e->name.lname);
x->balance-=a;
x->no++;
}
void deposit(struct PaySa* x)
{
int b,s,i,t;
long unsigned int a;
char sa[21];
t=0;
cscreen();
printf("Enter amount to be added\n");
scanf("%lu",&a);
if(a>x->bank.bal)
{
printf("Transaction not possible (bank balance is low)\n");
getch();
return;
}
x->passbook[x->no].amount=a;
printf("Choose mode of payment\n1. Credit card\n2. Debit card\n3. Net banking\n4. Exit\n");
scanf("%d",&b);
cscreen();
switch(b)
{
case 1:strcpy(x->passbook[x->no].name.fname,"Credit");
       strcpy(x->passbook[x->no].name.lname,"card");
case 2:cscreen();
       printf("Enter card number (10 digits)\n");
       scanf("%s",x->passbook[x->no].number);
       printf("Enter date(dd/mm/yyyy)\n");
       scanf("%s",x->passbook[x->no].date);
       printf("Enter CVV/Security code\n");
       scanf("%s",sa);
       if(b==2)
       {
       strcpy(x->passbook[x->no].name.fname,"Debit");
       strcpy(x->passbook[x->no].name.lname,"card");
       }
	   genOTP(x);
       cscreen();
       for(i=0;i<100;i++)
       {
       cscreen();
       printf("Enter the One Time Password(OTP)\tTo resend OTP press 1\n");
       scanf("%d",&s);
       if(s==1)
       genOTP(x);
       else if(s!=x->OTP)
       {
       printf("Wrong OTP\n");
       getch();
       continue;
       }
       else
       break;
       }
       if(s==x->OTP)
       {
       x->balance+=a;
       if(b==2)
       x->bank.bal-=a;
       t=1;
       }
       break;
case 3:printf("Enter name of your bank\n");
       scanf("%s",x->passbook[x->no].name.fname);
       scanf("%s",x->passbook[x->no].name.lname);
       printf("Enter date(dd/mm/yyyy)\n");
       scanf("%s",x->passbook[x->no].date);
       printf("Enter username\n");
       scanf("%s",x->passbook[x->no].number);
       if(strcmp(x->passbook[x->no].number,x->bank.user))
       {
       printf("Incorrect username\n");
       getch();
       break;
       }
       printf("Enter password\n");
       scanf("%s",sa);
       if(strcmp(sa,x->bank.pass))
       {
       printf("Incorrect password\n");
       getch();
       break;
       }
       x->balance+=a;
       x->bank.bal-=a;
       t=1;
       break;
case 4:return;
default:printf("Invalid choice\n");
}
strcpy(x->passbook[x->no].func,"Added from");
cscreen();
if(t==1)
{
printf("Rupees %lu have been added to your PaySa wallet\n",a);
x->no++;
}
else
printf("Transaction unsuccessful\n");
}
void sortpb(struct PaySa* x)
{
struct pb j;
int i,k;
for(k=0;k<x->no-1;k++)
{
for(i=0;i<x->no-k-1;i++)
{
if(x->passbook[i].amount<x->passbook[i+1].amount)
{
j=x->passbook[i];
x->passbook[i]=x->passbook[i+1];
x->passbook[i+1]=j;
}
}
}
}
void viewpb(struct PaySa* x)
{
sortpb(x);
int pos,j,i;
for(i=0;i<x->no;i++)
{
if(x->passbook[i].amount==0||strcmp(x->passbook[i].func,"\0")==0||strcmp(x->passbook[i].name.fname,"\0")==0||strcmp(x->passbook[i].name.lname,"\0")==0||strcmp(x->passbook[i].number,"\0")==0||strcmp(x->passbook[i].date,"\0")==0)
{
pos=i;
x->no--;
for(j=pos;j<x->no;j++)
x->passbook[i]=x->passbook[i+1];
}
printf("%d. Rupees %lu\n   %s %s %s\n   ID: %s\n   On: %s\n",i+1,x->passbook[i].amount,x->passbook[i].func,x->passbook[i].name.fname,x->passbook[i].name.lname,x->passbook[i].number,x->passbook[i].date);
printf("\n");
}
}
int dequeue(struct PaySa* x)
{
if(x->zf==-1)
{
printf("No requests to be shown\n");
getch();
return 0;
}
printf("Request:\nFor: Rs.%lu\nFrom: %s\nReason: Payment for %s\nOn: %s\n",x->req[x->zf].amount,x->req[x->zf].from,x->req[x->zf].reason,x->req[x->zf].date);
if(x->zr==x->zf)
x->zr=x->zf=-1;
else
x->zf=((x->zf+1)%10);
return 1;
}
int enqueue(struct PaySa* x,char mobile[11])
{
cscreen();
if((x->zr==9&&x->zf==0)||(x->zf==x->zr+1))
{
printf("Cannot make request, receiver's inbox is currently full\n");
getch();
return 0;
}
else if(x->zf==-1)
x->zf=0;
x->zr=((x->zr+1)%10);
printf("Enter amount to be requested\n");
scanf("%lu",&x->req[x->zr].amount);
printf("Enter date (dd/mm/yyyy)\n");
scanf("%s",x->req[x->zr].date);
strcpy(x->req[x->zr].from,mobile);
printf("Payment requested for\n");
scanf("%s",x->req[x->zr].reason);
printf("Request sent\n");
return 1;
}
void request(struct PaySa* x)
{
int i=0;
int j=1;
char m[11];
printf("Enter mobile number to request money from\n");
scanf("%s",m);
FILE* filep,* filep1;
filep=fopen("PaySa.dat","rb");
if(filep==NULL)
{
printf("Cannot open file for request\n");
getch();
return;
}
fseek(filep,0,SEEK_SET);
struct PaySa* e;
e=(struct PaySa*)malloc(sizeof(struct PaySa));
construct(e);
filep1=fopen("temp.dat","wb");
if(filep1==NULL)
{
printf("Cannot open file for request\n");
getch();
return;
}
fseek(filep1,0,SEEK_SET);
while(fread(e,sizeof(struct PaySa),1,filep))
{
if(!(strcmp(m,e->mobile)))
{
j=enqueue(e,x->mobile);
i=1;
}
fwrite(e,sizeof(struct PaySa),1,filep1);
}
free(e);
fclose(filep);
fclose(filep1);
remove("Paysa.dat");
rename("temp.dat","PaySa.dat");
if(j==0)
return;
if(i==0)
{
printf("Account not found\n");
getch();
return;
}
}
void viewr(struct PaySa* x)
{
char ch;
int j;
printf("Once viewed, requests will be deleted from your inbox\nDo you want to continue viewing requests?(y/n)\n");
scanf(" %c",&ch);
while(ch=='y'||ch=='Y')
{
cscreen();
j=dequeue(x);
if(j==0)
return;
getch();
cscreen();
printf("Do you want to continue viewing requests?(y/n)\n");
scanf(" %c",&ch);
}
}
void deactivate(struct PaySa* x)
{
genOTP(x);
int p,i;
for(i=0;i<100;i++)
{
cscreen();
printf("Enter the One Time Password(OTP)\tTo resend OTP press 1\n");
scanf("%d",&p);
if(p==1)
genOTP(x);
else if(p!=x->OTP)
{
printf("Wrong OTP\n");
getch();
continue;
}
else
break;
}
if(p!=x->OTP)
return;
struct PaySa* e;
e=(struct PaySa*)malloc(sizeof(struct PaySa));
construct(e);
FILE* filep,* filep1;
filep=fopen("PaySa.dat","rb");
if(filep==NULL)
{
printf("Cannot open file for deactivation of account\n");
getch();
return;
}
filep1=fopen("temp.dat","wb");
if(filep1==NULL)
{
printf("Cannot open file for deactivation of account\n");
getch();
return;
}
x->bank.bal+=x->balance;
x->balance=0;
fseek(filep,0,SEEK_SET);
fseek(filep1,0,SEEK_SET);
while(fread(e,sizeof(struct PaySa),1,filep))
{
if(strcmp(x->mobile,e->mobile))
{
fwrite(e,sizeof(struct PaySa),1,filep1);
}
}
free(e);
fclose(filep1);
fclose(filep);
remove("PaySa.dat");
rename("temp.dat","PaySa.dat");
cscreen();
printf("Account deactivated\n");
}
void tbank(struct PaySa* x)
{
long unsigned int a;
cscreen();
printf("Enter amount to be transferred\n");
scanf("%lu",&a);
if(a>x->balance)
{
printf("Transaction not possible (PaySa balance is low)\n");
getch();
return;
}
x->passbook[x->no].amount=a;
printf("Enter date(dd/mm/yyyy)\n");
scanf("%s",x->passbook[x->no].date);
strcpy(x->passbook[x->no].number,x->mobile);
strcpy(x->passbook[x->no].name.fname,x->name.fname);
strcpy(x->passbook[x->no].name.lname,x->name.lname);
strcpy(x->passbook[(x->no)+1].name.fname,x->name.fname);
strcpy(x->passbook[(x->no)+1].name.lname,x->name.lname);
x->passbook[(x->no)+1].amount=a;
strcpy(x->passbook[(x->no)+1].func,"Received from");
strcpy(x->passbook[(x->no)+1].date,x->passbook[x->no].date);
strcpy(x->passbook[(x->no)+1].number,x->mobile);
strcpy(x->passbook[x->no].func,"Sent to");
cscreen();
printf("Rupees %lu have been transferred to your bank account\n",a);
x->balance-=a;
x->bank.bal+=a;
x->no+=2;
}
void updatebankbalance()
{
char c[9];
cscreen();
printf("Enter User ID\n");
scanf("%s",c);
if(strcmp(c,"bank1234"))
{
printf("Incorrect User ID\n");
getch();
return;
}
printf("Enter password\n");
scanf("%s",c);
if(strcmp(c,"1234bank"))
{
printf("Incorrect Password\n");
getch();
return;
}
struct PaySa* e;
e=(struct PaySa*)malloc(sizeof(struct PaySa));
construct(e);
FILE* filep,* filep1;
filep=fopen("PaySa.dat","rb");
if(filep==NULL)
{
printf("Cannot open file for updation of bank balance\n");
getch();
return;
}
filep1=fopen("temp.dat","wb");
if(filep1==NULL)
{
printf("Cannot open file for updation of bank balance\n");
getch();
return;
}
fseek(filep,0,SEEK_SET);
fseek(filep1,0,SEEK_SET);
while(fread(e,sizeof(struct PaySa),1,filep))
{
cscreen();
printf("Enter updated bank balance of %s %s (Netbanking User ID: %s)\n",e->name.fname,e->name.lname,e->bank.user);
scanf("%lu",&e->bank.bal);
fwrite(e,sizeof(struct PaySa),1,filep1);
}
free(e);
fclose(filep1);
fclose(filep);
remove("PaySa.dat");
rename("temp.dat","PaySa.dat");
cscreen();
printf("Updation complete\n");
}
int main()
{
struct PaySa* v,* e;
v=(struct PaySa*)malloc(sizeof(struct PaySa));
e=(struct PaySa*)malloc(sizeof(struct PaySa));
construct(v);
construct(e);
int b,i,t,f,g,h,q;
char c[31],p[21],ch,cha;
FILE* filep,* filep1;
do
{
cscreen();
printf("Enter your choice\n1. Login to PaySa\n2. Sign Up\n3. Login as bank representative (Update bank balance of registered users)\n4. Exit\n");
scanf("%d",&b);
switch(b)
{
case 1:cscreen();
	   printf("Enter E-mail ID/mobile number\n");
       scanf("%s",c);
       filep=fopen("PaySa.dat","rb");
       if(filep==NULL)
       {
       printf("Cannot open file for login\n");
       getch();
       break;
       }
       t=0;
       fseek(filep,0,SEEK_SET);
       while(fread(v,sizeof(struct PaySa),1,filep))
       {
       if(!(strcmp(c,v->email))||!(strcmp(c,v->mobile)))
       {
       t=1;
       break;
       }
       }
       fclose(filep);
       if(t==0)
       {
       printf("E-mail/mobile number not found\n");
       break;
       }
       printf("Enter your PaySa password\n");
       scanf("%s",p);
       if(strcmp(p,v->pass))
       {
       printf("Incorrect password\n");
       break;
       }
       else
       {
	   do	
       {	
       cscreen();
       printf("What do you want to do?\n1.  Add money to your PaySa wallet\n2.  Pay or Send\n3.  Request money\n4.  Check requests\n5.  Access Passbook\n6.  Modify your registered information\n7.  Transfer money from your PaySa wallet to your bank account\n8.  Check your current PaySa wallet balance\n9.  Check your current bank balance\n10. Deactivate your PaySa account\n11. Exit\n");
       scanf("%d",&f);
       cscreen();
       switch(f)
       {
       case 1:deposit(v);
	      break;
       case 2:pay(v);
	      break;
       case 3:request(v);
	      break;
       case 4:viewr(v);
	      break;
       case 5:viewpb(v);
	      break;
       case 6:modify(v);
	      break;
	   case 7:tbank(v);
	      break;
       case 8:printf("Your current PaySa wallet balance is: %lu",v->balance);
       	  break;
       case 9:printf("Your current bank balance is: %lu",v->bank.bal);
          break;
	   case 10:deactivate(v);
	   case 11:return;
       default:printf("Invalid choice\n");
       }
       filep=fopen("PaySa.dat","rb");
       if(filep==NULL)
       {
       printf("Cannot open file for login functions\n");
       getch();
       break;
       }
       filep1=fopen("temp.dat","wb");
       if(filep1==NULL)
       {
       printf("Cannot open file for login functions\n");
       getch();
       break;
       }
       fseek(filep,0,SEEK_SET);
       fseek(filep1,0,SEEK_SET);
       while(fread(e,sizeof(struct PaySa),1,filep))
       {
       if(!(strcmp(e->mobile,v->mobile)))	
       fwrite(v,sizeof(struct PaySa),1,filep1);
       else
       fwrite(e,sizeof(struct PaySa),1,filep1);
       }
       fclose(filep);
       fclose(filep1);
       remove("PaySa.dat");
       rename("temp.dat","PaySa.dat");
       getch();
       cscreen();
       printf("Do you want to continue using your PaySa account?(y/n)\n");
	   scanf(" %c",&cha);
       }while(cha=='y'||cha=='Y');
       }
       break;
case 2:input(v);
       break;
case 3:updatebankbalance();
       break;
case 4:return;
default:printf("Invalid choice\n");
}
getch();
cscreen();
printf("Do you want to continue using PaySa?(y/n)\n");
scanf(" %c",&ch);
}while(ch=='y'||ch=='Y');
free(e);
free(v);
getch();
return 0;
}