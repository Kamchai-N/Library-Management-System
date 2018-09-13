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
//	line_mainmenu();
	gotoxy(42,3);
	printf("Library Management System");
	gotoxy(25,5);
	printf("----------------------- MAIN MENU ----------------------------");
	gotoxy(30,7);
	printf("1. Add Books");
	gotoxy(30,9);
	printf("2. Delete books");
	gotoxy(30,11);
	printf("3. Search Books");
	gotoxy(30,13);
	printf("4. View Book list");
	gotoxy(30,15);
	printf("5. Close Application");
	gotoxy(30,18);
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
			break;
		}
		default :{
			gotoxy(50,22);
			printf("Warning");
			Sleep(3000);
			mainmenu();
			break;
		}
				
	}
}
void addbooks(){
	system("cls");
//	line_addbooks();
	gotoxy(42,3);
	printf("Library Management System");
	gotoxy(25,5);
	printf("--------------------- SELECT CATEGOIES ----------------------");
	gotoxy(30,7);
	printf("1. Computer");
	gotoxy(30,9);
	printf("2. Electronics");
	gotoxy(30,11);
	printf("3. Electrical");
	gotoxy(30,13);
	printf("4. Civil");
	gotoxy(30,15);
	printf("5. Mechanical");
	gotoxy(30,17);
	printf("6. ETC.");
	gotoxy(30,19);
	printf("7. Back to main menu");
	gotoxy(30,22);
	printf("Enter your choice: ");
	scanf("%d",&s);
	if(s == 7){
		mainmenu();
	}else if(s>7){
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
		gotoxy(25,22);printf("--------------------------------------------------------------"); // Top
		gotoxy(40,24);
		printf("The record is sucessfully saved");
		gotoxy(40,25);
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
//	line_getdata();
	gotoxy(42,3);
	printf("Library Management System");
	gotoxy(25,5);
	printf("------------------------- Add Books --------------------------");
	gotoxy(30,8);
	printf("Category:");
	gotoxy(40,8);
	printf("%s",catagories[s-1]);
	gotoxy(30,10);
	printf("Book ID:\t");
	gotoxy(40,10);
	scanf("%d",&t);
//	printf("%d",t);
	if(checkid(t) == 0)
	{
		gotoxy(40,13);
		printf("\aThe book id already exists\a");
		getch();
		mainmenu();
		return 0;
	}
	a.id=t;
	gotoxy(30,12);printf("Book Name:");
	gotoxy(40,12);scanf("%s",a.name);
	gotoxy(30,14);printf("Author:");
	gotoxy(40,14);scanf("%s",a.Author);
	gotoxy(30,16);printf("Quantity:");
	gotoxy(40,16);scanf("%d",&a.quantity);
	gotoxy(30,18);printf("Price:");
	gotoxy(50,18);printf("Baht");
	gotoxy(40,18);scanf("%f",&a.Price);
	gotoxy(30,20);printf("Rack No:");
	gotoxy(40,20);scanf("%s",&a.rackno);
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
//		line_deletebooks();
		gotoxy(42,3);
		printf("Library Management System");
		gotoxy(25,5);
		printf("------------------------- BOOK DELETE ------------------------");
        gotoxy(28,7);printf("Enter the Book ID to  delete:"); scanf("%d",&d);
        fp = fopen("data.txt","rb+");
        while(fread(&a,sizeof(a),1,fp)==1){
            if(a.id==d){
                gotoxy(28,11);printf("The book record is available");
                gotoxy(28,13);printf("Book name is %s",a.name);
                gotoxy(28,14);printf("Rack No. is %s",a.rackno);
                gotoxy(25,16);printf("--------------------------------------------------------------");
                findBook = 1;
                gotoxy(28,18);printf("Do you want to delete it?(Y/N):");
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
                    gotoxy(28,19);printf("The record is sucessfully deleted");
                }
            }
        }
        if(findBook == 0){
            gotoxy(28,11);printf("No record is found");
        }

        gotoxy(28,20);printf("Delete another record?(Y/N)");
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
	printf("*****************************************Book List***********************************");
	gotoxy(2,2);
	printf(" CATEGORY     ID    BOOK NAME                   AUTHOR        QTY   PRICE     RackNo ");
	j=4;
	fp=fopen("data.txt","rb");
	while(fread(&a,sizeof(a),1,fp)==1){
		gotoxy(3,j);
		printf("%s",a.cat);
		gotoxy(16,j);
		printf("%d",a.id);
		gotoxy(22,j);
		printf("%s",a.name);
		gotoxy(50,j);
		printf("%s",a.Author);
		gotoxy(65,j);
		printf("%d",a.quantity);
		gotoxy(70,j);
		printf("%.2f",a.Price);
		gotoxy(80,j);
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
//	line_searchbooks();
	gotoxy(42,3);
	printf("Library Management System");
	gotoxy(25,5);
	printf("------------------------- BOOK SEARCH ------------------------");
	gotoxy(35,8);
	printf(" 1. Search By ID");
	gotoxy(35,10);
	printf(" 2. Search By Name");
	gotoxy(35,12);
	printf(" 3. Back to Main Menu");
	gotoxy(35,14);
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
		case '3':{
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
//	line_searchbookby();
	gotoxy(42,3);
	printf("Library Management System");
	gotoxy(25,5);
	printf("------------------------- BOOK SEARCH ------------------------");
	gotoxy(30,6);
	printf("****Search Books By Id****");
	gotoxy(30,8);
	printf("Enter the book id:");
	scanf("%d",&d);
	gotoxy(35,9);
	printf("Searching........");
	while(fread(&a,sizeof(a),1,fp)==1){
        if(a.id==d){
        	Sleep(2);
        	gotoxy(35,11);
			printf("The Book is available");
			gotoxy(35,12);
			printf("ID:%d",a.id);printf("\n");
			gotoxy(35,13);
			printf("Name:%s",a.name);printf("\n");
			gotoxy(35,14);
			printf("Author:%s ",a.Author);printf("\n");
			gotoxy(35,15);
			printf("Qantity:%d ",a.quantity);printf("\n");
			gotoxy(35,16);
			printf("Price:%.2f",a.Price);printf("\n");
			gotoxy(35,17);
			printf("Rack No:%s ",a.rackno);printf("\n");
			gotoxy(35,18);
			findbook='f';
		}
	}
	if(findbook!='f'){
		gotoxy(22,9);
		printf("\aNo Record Found");
	}
	gotoxy(35,20);
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
//	line_searchbookby();
	gotoxy(42,3);
	printf("Library Management System");
	gotoxy(25,5);
	printf("------------------------- BOOK SEARCH ------------------------");
	gotoxy(30,6);
	printf("****Search Books By Name****");
	gotoxy(30,8);
	printf("Enter the book Name:");
	scanf("%s",s);
	int d = 0;
	gotoxy(35,9);
	printf("Searching........");
	while(fread(&a,sizeof(a),1,fp)==1){
        if(strcmp(a.name,(s))==0){
        	gotoxy(35,11);
			printf("The Book is available");
			gotoxy(35,12);
			printf("ID:%d",a.id);printf("\n");
			gotoxy(35,13);
			printf("Name:%s",a.name);printf("\n");
			gotoxy(35,14);
			printf("Author:%s ",a.Author);printf("\n");
			gotoxy(35,15);
			printf("Qantity:%d ",a.quantity);printf("\n");
			gotoxy(35,16);
			printf("Price:Rs.%.2f",a.Price);printf("\n");
			gotoxy(35,17);
			printf("Rack No:%s ",a.rackno);printf("\n");
			gotoxy(35,18);
			d++;
		}
	}
	if(d==0){
		gotoxy(22,9);
		printf("\aNo Record Found");
	}
	gotoxy(35,20);
	printf("Try another search?(Y/N)");
	if(getch()=='y'){
		searchbooks();
	}else{
		mainmenu();
	}	
}

