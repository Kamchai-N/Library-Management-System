#include<windows.h>
#include<stdio.h>
#include<conio.h>

void gotoxy (int x, int y);
void mainmenu(void);
void addbooks(void);
int checkid(int t);
int getdata(void);
void deletebooks(void);  
void viewbooks(void);
void returnfunc(void);
void searchbooks(void);
void searchbookbyid(void);
void searchbookbyname(void);

struct books{
	int id;
	char stname[20];
	char name[20];
	char Author[20];
	int quantity;
	float Price;
	int count;
	char rackno[20];
	char *cat;
//	struct meroDate issued;
//	struct meroDate duedate;
};
struct books a;
FILE *fp,*ft,*fs;
char catagories[][15]={"Computer","Electronics","Electrical","Civil","Mechnnical","ETC."};
int s,d; 
char findbook;

main(){
	mainmenu();
}
void gotoxy (int x, int y){
	COORD coord = {0, 0};
	coord.X = x; coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void mainmenu(){
	system("cls");
	gotoxy(20,3);
	printf("Library Management System");
	gotoxy(5,5);
	printf("----------------------- MAIN MENU ----------------------------");
	gotoxy(8,6);
	printf("1. Add Books");
	gotoxy(8,8);
	printf("2. Delete books");
	gotoxy(8,10);
	printf("3. Search Books");
	gotoxy(8,12);
	printf("4. View Book list");
	gotoxy(8,14);
	printf("5. Close Application");
	gotoxy(8,16);
	printf("Enter your choice: ");
	switch(getch()){
		case '1':
			addbooks();
		break;
		case '2':
			deletebooks();
		break;
		case '3':
			searchbooks();
		break;
		case '4':	
			viewbooks();
		break;
		case '5':{
			system("cls");
			gotoxy(16,3);
			printf("\tLibrary Management System");
			gotoxy(16,4);
			printf("\t\tThank You");
			gotoxy(16,8);
			printf("Exiting in 3 second...........");
			Sleep(3000);
			exit(0);
		}
		break;		
	}
}
void addbooks(){
	system("cls");
	gotoxy(20,3);
	printf("Library Management System");
	gotoxy(5,5);
	printf("----------------------- SELECT CATEGOIES ----------------------------");
	gotoxy(8,6);
	printf("1. Computer");
	gotoxy(8,8);
	printf("2. Electronics");
	gotoxy(8,10);
	printf("3. Electrical");
	gotoxy(8,12);
	printf("4. Civil");
	gotoxy(8,14);
	printf("5. Mechanical");
	gotoxy(8,14);
	printf("6. ETC.");
	gotoxy(8,16);
	printf("7. Back to main menu");
	gotoxy(8,18);
	printf("Enter your choice: ");
	scanf("%d",&s);
	if(s == 7){
		mainmenu();
	}
	system("cls");
	fp=fopen("data.txt","ab+"); 
	if(getdata()== 1)
	{
		a.cat=catagories[s-1];
		fseek(fp,0,SEEK_END);
		fwrite(&a,sizeof(a),1,fp);
		fclose(fp);
		gotoxy(21,14);
		printf("The record is sucessfully saved");
		gotoxy(21,15);
		printf("Save any more?(Y / N):");
		if(getch()=='n')
			mainmenu();
		else
			system("cls");
			addbooks();
	}
}
int getdata(){
	int t;
	gotoxy(20,3);
	printf("Enter the Information Below");
	gotoxy(21,5);
	printf("Category:");
	gotoxy(31,5);
	printf("%s",catagories[s-1]);
	gotoxy(21,6);
	printf("Book ID:\t");
	gotoxy(30,6);
	scanf("%d",&t);
//	printf("%d",t);
	if(checkid(t) == 0)
	{
		gotoxy(21,13);
		printf("\aThe book id already exists\a");
		getch();
		mainmenu();
		return 0;
	}
	a.id=t;
	gotoxy(21,7);
	printf("Book Name:");gotoxy(33,7);
	scanf("%s",a.name);
	gotoxy(21,8);
	printf("Author:");gotoxy(30,8);
	scanf("%s",a.Author);
	gotoxy(21,9);
	printf("Quantity:");gotoxy(31,9);
	scanf("%d",&a.quantity);
	gotoxy(21,10);
	printf("Price:");gotoxy(28,10);
	scanf("%f",&a.Price);
	gotoxy(21,11);
	printf("Rack No:");gotoxy(30,11);
	scanf("%s",&a.rackno);
	return 1;
}
int checkid(int t){
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
		return 0; 
		return 1;
}
void deletebooks(){
    system("cls"); 
    char another = 'y';
    int d,findBook = 0;
    while(another = 'y'){  
        gotoxy(25,7);printf("********BOOK DELETE********");
        gotoxy(10,9);printf("Enter the Book ID to  delete:"); scanf("%d",&d);
        fp = fopen("data.txt","rb+");
        while(fread(&a,sizeof(a),1,fp)==1){
            if(a.id==d){
                gotoxy(10,11);printf("The book record is available");
                gotoxy(10,13);printf("Book name is %s",a.name);
                gotoxy(10,14);printf("Rack No. is %d",a.rackno);
                findBook = 1;
                gotoxy(10,16);printf("Do you want to delete it?(Y/N):");
                if(getch()=='y'){
                    ft=fopen("test.txt","wb");  
                    rewind(fp);
                    while(fread(&a,sizeof(a),1,fp)==1){
                        if(a.id!=d){
                            fwrite(&a,sizeof(a),1,ft); 
                        }                              
                    }
                    fclose(fp);
                    fclose(ft);
                    remove("data.txt");
                    rename("test.txt","data.txt"); 
                    gotoxy(10,17);printf("The record is sucessfully deleted");
                }
            }
        }
        if(findBook == 0){
            gotoxy(10,11);printf("No record is found");
        }

        gotoxy(10,18);printf("Delete another record?(Y/N)");
        if(getch()=='y'){
            deletebooks();
        }else{
        	mainmenu();
		}
    }
}
void viewbooks(){
	int i=0,j;
	system("cls");
	gotoxy(1,1);
	printf("*********************************Book List*****************************");
	gotoxy(2,2);
	printf(" CATEGORY     ID    BOOK NAME     AUTHOR       QTY     PRICE     RackNo ");
	j=4;
	fp=fopen("data.txt","rb");
	while(fread(&a,sizeof(a),1,fp)==1){
		gotoxy(3,j);
		printf("%s",a.cat);
		gotoxy(16,j);
		printf("%d",a.id);
		gotoxy(22,j);
		printf("%s",a.name);
		gotoxy(36,j);
		printf("%s",a.Author);
		gotoxy(50,j);
		printf("%d",a.quantity);
		gotoxy(57,j);
		printf("%.2f",a.Price);
		gotoxy(69,j);
		printf("%s",a.rackno);
		printf("\n\n");
		j++;
		i=i+a.quantity;
	}
	gotoxy(3,25);
	printf("Total Books =%d",i);
	fclose(fp);
	gotoxy(35,25);
	returnfunc();
	
}
void returnfunc(){
	printf(" Press ENTER to return to main menu");
	if(getch()==13) {	
		mainmenu();
	}
}
void searchbooks(){
	system("cls");
	printf("*****************************Search Books*********************************");
	gotoxy(5,4);
	printf(" 1. Search By ID");
	gotoxy(5,6);
	printf(" 2. Search By Name");
	gotoxy(5,8);
	printf(" * Back to Main Menu");
	gotoxy(5,10);
	printf("Enter Your Choice : ");
	fp=fopen("data.txt","rb+"); 
	rewind(fp);
	switch(getch()){
		case '1':{
			searchbookbyid();
			break;
		}
		case '2':{
			searchbookbyname();
			break;
		}
		case '*':{
			mainmenu();
			break;
		}
		default :
			getch();
			searchbooks();
	}
	fclose(fp);
}
void searchbookbyid(){
	system("cls");
	gotoxy(25,4);
	printf("****Search Books By Id****");
	gotoxy(20,5);
	printf("Enter the book id:");
	scanf("%d",&d);
	gotoxy(20,7);
	printf("Searching........");
	while(fread(&a,sizeof(a),1,fp)==1){
        if(a.id==d){
        	Sleep(2);
        	gotoxy(20,7);
			printf("The Book is available");
			gotoxy(20,9);
			printf("ID:%d",a.id);printf("\n");
			gotoxy(20,10);
			printf("Name:%s",a.name);printf("\n");
			gotoxy(20,11);
			printf("Author:%s ",a.Author);printf("\n");
			gotoxy(20,12);
			printf("Qantity:%d ",a.quantity);printf("\n");
			gotoxy(20,13);
			printf("Price:Rs.%.2f",a.Price);printf("\n");
			gotoxy(20,14);
			printf("Rack No:%s ",a.rackno);printf("\n");
			gotoxy(20,15);
			findbook='f';
		}
	}
	if(findbook!='t'){
		gotoxy(22,9);
		printf("\aNo Record Found");
	}
	gotoxy(20,17);
	printf("Try another search?(Y/N): ");
	if(getch()=='y'){
		searchbooks();
	}else{
		mainmenu();
	}	
}
void searchbookbyname(){
	char s[15];
	system("cls");
	gotoxy(25,4);
	printf("****Search Books By Name****");
	gotoxy(20,5);
	printf("Enter the book Name:");
	scanf("%s",s);
	int d = 0;
	while(fread(&a,sizeof(a),1,fp)==1){
        if(strcmp(a.name,(s))==0){
        	gotoxy(20,7);
			printf("The Book is available");
			gotoxy(20,9);
			printf("ID:%d",a.id);printf("\n");
			gotoxy(20,10);
			printf("Name:%s",a.name);printf("\n");
			gotoxy(20,11);
			printf("Author:%s ",a.Author);printf("\n");
			gotoxy(20,12);
			printf("Qantity:%d ",a.quantity);printf("\n");
			gotoxy(20,13);
			printf("Price:Rs.%.2f",a.Price);printf("\n");
			gotoxy(20,14);
			printf("Rack No:%s ",a.rackno);printf("\n");
			gotoxy(20,15);
			d++;
		}
	}
	if(d==0){
		gotoxy(22,9);
		printf("\aNo Record Found");
	}
	gotoxy(20,17);
	printf("Try another search?(Y/N)");
	if(getch()=='y'){
		searchbooks();
	}else{
		mainmenu();
	}	
}
