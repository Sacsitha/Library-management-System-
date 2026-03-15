#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//---------All the structure---------
struct User{
    char UserId[50];
    char Password[100];
};
struct Catergory{
    int catergoryId;
    char name[50];
};
struct Book{
    int BookId;
    char Title[100];
    int YearofPublication;
    float Price;
    char Author[100];
    int NumberOfCopies;
    char catergory[100];
};
struct Member{
    int MemberId;
    char Name[100];
    char Phone[20];
};
struct Issue{
    int IssueId;
    int BookId;
    int MemberId;
    char IssueDate[20];
    char ReturnDate[20];
    int returned; // 0 = not returned , 1 = returned
};
//-----------Global Variables---------
struct User users[50]={
    {"Admin","Admin001"}
};
int user_count=1;
struct Book Books[50]={
    {1,"C Language ",2015,1500.00,"Dennis Ritchie ",10,"Programming "},
    {2,"Java Programming ",2018,2000.00,"James Gosling ",8,"Programming "},
    {3,"Database Systems",2017,1800.00,"Elmasri ",6,"Database"},
    {4,"Computer Networks ",2016,1700.00,"Andrew Tanenbaum ",5,"Networking "},
    {5,"Operating Systems ",2019,2200.00,"Silberschatz ",7,"Systems "}
};
int book_count=5;
struct Member members[50]={
    {1,"Kamal ","0771234567"},
    {2,"Nimal ","0712345678"},
    {3,"Saman ","0759876543"},
    {4,"Sunil ","0762223333"},
    {5,"Amal ","0704445555"}
};
int member_count = 5;
struct Issue issues[50]={
    {1,1,1,"2026-03-01","2026-03-10",0},
    {2,2,2,"2026-03-02","2026-03-09",1},
    {3,3,3,"2026-03-05","2026-03-12",0},
    {4,4,4,"2026-03-06","2026-03-13",0},
    {5,5,5,"2026-03-07","2026-03-14",1},
    {6,1,2,"2026-03-08","2026-03-15",0},
    {7,2,3,"2026-03-09","2026-03-16",1},
    {8,3,4,"2026-03-10","2026-03-17",0},
    {9,4,5,"2026-03-11","2026-03-18",0},
    {10,5,1,"2026-03-12","2026-03-19",1}
};
int issue_count = 10;
//----------Functions-----------
void AddBook();
void UpdateBook();
void DeleteBook();
void SearchBook();
void DisplayBooks();
void AddMember();
void AddIssue();
void NotReturnedBooks();
void OverdueBooks();
void Menu();
void Login();
int ConvertToDays(char date[]);
int CalculateFine(char returnDate[], char today[]);
int GetAvailableCopies(int bookId);
void AvailableBooks();
void ReturnBook();
//----------Main Function------------
int main(){
    printf("------Welcome to Library Management System------ \n");
    Login();
}
//Add Book
void AddBook(){
    system("cls");
    printf("-----Add Book----\n");
    if(book_count>50){
        printf("Storage Full\n CANNOT ADD ANYMORE BOOKS\n");
        return;
    }
    Books[book_count].BookId=book_count;
    getchar();
    printf("Enter Title : ");
    fgets(Books[book_count].Title,100,stdin);
    Books[book_count].Title[strcspn(Books[book_count].Title,"\n")] = 0;
    printf("Enter Author : ");
    fgets(Books[book_count].Author,100,stdin);
    Books[book_count].Author[strcspn(Books[book_count].Author,"\n")] = 0;
    printf("Enter Year of Publication : ");
    scanf("%d",&Books[book_count].YearofPublication);
    printf("Enter Price : ");
    scanf("%f",&Books[book_count].Price);
    printf("Enter Number of Copies : ");
    scanf("%d",&Books[book_count].NumberOfCopies);
    getchar();
    printf("Enter Category : ");
    fgets(Books[book_count].catergory,100,stdin);
    Books[book_count].catergory[strcspn(Books[book_count].catergory,"\n")] = 0;
    book_count++;
    printf("\n Book Added Successfully \n");
}
//Add Member
void AddMember(){
    system("cls");
    printf("-----Add Member----\n");
    if(member_count>50){
        printf("Storage Full\n CANNOT ADD ANYMORE MEMBERS\n");
        return;
    }
    members[member_count].MemberId = member_count + 1;
    getchar();
    printf("Enter Member Name : ");
    fgets(members[member_count].Name,100,stdin);
    members[member_count].Name[strcspn(members[member_count].Name,"\n")] = 0;
    printf("Enter Phone Number : ");
    fgets(members[member_count].Phone,20,stdin);
    members[member_count].Phone[strcspn(members[member_count].Phone,"\n")] = 0;
    member_count++;
    printf("\n Member Added Successfully \n");
}
//Add issue
void AddIssue(){
    printf("-----Add Issue----\n");
    system("cls");
    if(issue_count>50){
        printf("Storage Full\n CANNOT ADD ANYMORE ISSUES \n");
        return;
    }
    int bookId;
    int memberId;
    printf("Enter Book ID : ");
    scanf("%d",&bookId);
    int available = GetAvailableCopies(bookId);
    if(available == -1){
        printf("Book ID not found.\n");
        return;
    } else if(available <= 0){
        printf("No available copies for this book.\n");
        return;
    }
    printf("Enter Member ID : ");
    scanf("%d",&memberId);
    int memberIndex = -1;
    for(int i=0;i<member_count;i++){
        if(members[i].MemberId == memberId){
            memberIndex = i;
            break;
        }
    }
    if(memberIndex == -1){
        printf("Member ID not found .\n");
        return;
    }
    issues[issue_count].IssueId = issue_count + 1;
    issues[issue_count].BookId = bookId;
    issues[issue_count].MemberId = memberId;
    printf("Enter Issue Date (YYYY-MM-DD) : ");
    scanf("%s",issues[issue_count].IssueDate);
    printf("Enter Return Date (YYYY-MM-DD) : ");
    scanf("%s",issues[issue_count].ReturnDate);
    issues[issue_count].returned = 0;
    issue_count++;
    printf("Book Issued Successfully \n");
    printf("Available Copies Left : %d\n", available - 1);
}
//Update Book
void UpdateBook(){
    system("cls");
    printf("-----Modify Book----\n");
    int id;
    int found = 0;
    printf("Enter Book ID to update : ");
    scanf("%d",&id);
    for(int i=0;i<book_count;i++){
        if(Books[i].BookId == id){
            getchar();
            printf("Enter New Title : ");
            fgets(Books[i].Title,100,stdin);
            Books[i].Title[strcspn(Books[i].Title,"\n")] = 0;
            printf("Enter New Author : ");
            fgets(Books[i].Author,100,stdin);
            Books[i].Author[strcspn(Books[i].Author,"\n")] = 0;
            printf("Enter New Year : ");
            scanf("%d",&Books[i].YearofPublication);
            printf("Enter New Price : ");
            scanf("%f",&Books[i].Price);
            printf("Enter New Copies : ");
            scanf("%d",&Books[i].NumberOfCopies);
            getchar();
            printf("Enter New Category : ");
            fgets(Books[i].catergory,100,stdin);
            Books[i].catergory[strcspn(Books[i].catergory,"\n")] = 0;
            printf("\nBook Updated Successfully\n");
            found = 1;
            break;
        }
    }

    if(found == 0){
        printf("Book not found \n");
    }
}
//Display all Book
void DisplayBooks(){
    system("cls");
    if(book_count == 0){
        printf("No books available\n");
        return;
    }
    printf("------------------------------------Library Books--------------------------------------------------\n");
    printf("\n-------------------------------------------------------------------------------------------------\n");
    printf("%-5s %-25s %-20s %-6s %-10s %-8s %-15s\n",
           "ID","Title","Author","Year","Price","Copies","Category");
    printf("-------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<book_count;i++){
        printf("%-5d %-25s %-20s %-6d %-10.2f %-8d %-15s\n",
               Books[i].BookId,
               Books[i].Title,
               Books[i].Author,
               Books[i].YearofPublication,
               Books[i].Price,
               Books[i].NumberOfCopies,
               Books[i].catergory);
    }
    printf("-------------------------------------------------------------------------------------------------\n");
}
//Delete Book
void DeleteBook(){
    system("cls");
    printf("-----Delete Book----\n");
    int id;
    int found = 0;
    printf("Enter Book ID to delete : ");
    scanf("%d",&id);
    for(int i=0;i<book_count;i++){
        if(Books[i].BookId == id){
            found = 1;
            for(int j=i;j<book_count-1;j++){
                Books[j] = Books[j+1];
            }
            book_count--;
            printf("Book deleted successfully\n");
            break;
        }
    }
    if(found == 0){
        printf("Book not found\n");
    }
}
//Search Book
void SearchBook(){
    system("cls");
    printf("-----Search Book----\n");
    int id;
    int found = 0;
    printf("Enter Book ID to search : ");
    scanf("%d",&id);
    for(int i=0;i<book_count;i++){
        if(Books[i].BookId == id){
            printf("\nBook Found\n");
            printf("ID: %d\n",Books[i].BookId);
            printf("Title: %s\n",Books[i].Title);
            printf("Author: %s\n",Books[i].Author);
            printf("Year: %d\n",Books[i].YearofPublication);
            printf("Price: %.2f\n",Books[i].Price);
            printf("Copies: %d\n",Books[i].NumberOfCopies);
            printf("Category: %s\n",Books[i].catergory);
            found = 1;
            break;
        }
    }
    if(found == 0){
        printf("Book not found\n");
    }
}
void NotReturnedBooks(){
    system("cls");
    printf("\n---------------------------------- Books Issued but Not Returned ----------------------------------\n");
    printf("%-6s %-25s %-10s %-20s %-15s %-15s\n",
           "BID","Title","MID","Member Name","Issue Date","Return Date");
    printf("-----------------------------------------------------------------------------------------------\n");
    for(int i=0;i<issue_count;i++){
        if(issues[i].returned == 0){
            char title[100];
            char memberName[100];
            for(int j=0;j<book_count;j++){
                if(Books[j].BookId == issues[i].BookId){
                    strcpy(title, Books[j].Title);
                }
            }
            for(int k=0;k<member_count;k++){
                if(members[k].MemberId == issues[i].MemberId){
                    strcpy(memberName, members[k].Name);
                }
            }
            printf("%-6d %-25s %-10d %-20s %-15s %-15s\n",
                   issues[i].BookId,
                   title,
                   issues[i].MemberId,
                   memberName,
                   issues[i].IssueDate,
                   issues[i].ReturnDate);
        }
    }
    printf("-----------------------------------------------------------------------------------------------\n");
}
//Overdue books
void OverdueBooks(){
    system("cls");
    char today[20];
    printf("Enter Today's Date (YYYY-MM-DD) : ");
    scanf("%s", today);
    int todayDays = ConvertToDays(today);
    printf("\n--------------------------------------- Overdue Books ---------------------------------------\n");
    printf("%-6s %-25s %-10s %-20s %-15s %-15s\n",
           "BID","Title","MID","Member Name","Issue Date","Return Date");
    printf("---------------------------------------------------------------------------------------------\n");
    for(int i=0;i<issue_count;i++){
        if(issues[i].returned == 0){
            int returnDays = ConvertToDays(issues[i].ReturnDate);
            if(todayDays > returnDays){
                char title[100];
                char memberName[100];

                for(int j=0;j<book_count;j++){
                    if(Books[j].BookId == issues[i].BookId){
                        strcpy(title, Books[j].Title);
                    }
                }
                for(int k=0;k<member_count;k++){
                    if(members[k].MemberId == issues[i].MemberId){
                        strcpy(memberName, members[k].Name);
                    }
                }
                printf("%-6d %-25s %-10d %-20s %-15s %-15s\n",
                       issues[i].BookId,
                       title,
                       issues[i].MemberId,
                       memberName,
                       issues[i].IssueDate,
                       issues[i].ReturnDate);
            }
        }
    }
    printf("---------------------------------------------------------------------------------------------\n");
}
//AvailableBooks
int GetAvailableCopies(int bookId){
    int issued = 0;
    for(int i=0;i<issue_count;i++){
        if(issues[i].BookId == bookId && issues[i].returned == 0){
            issued++;
        }
    }
    for(int i=0;i<book_count;i++){
        if(Books[i].BookId == bookId){
            return Books[i].NumberOfCopies - issued;
        }
    }
    return -1;
}
void AvailableBooks(){
    system("cls");
    printf("-----Check Book Availablity----\n");
    int id;
    printf("Enter Book ID: ");
    scanf("%d",&id);

    int available = GetAvailableCopies(id);

    if(available == -1){
        printf("Book not found \n");
    } else {
        printf("Available Copies : %d\n", available);
    }
}
//Calculate Fine
int ConvertToDays(char date[]){
    int y,m,d;

    sscanf(date,"%d-%d-%d",&y,&m,&d);

    return y*365 + m*30 + d;
}
int CalculateFine(char returnDate[], char today[]){

    int y1,m1,d1;
    int y2,m2,d2;

    sscanf(returnDate,"%d-%d-%d",&y1,&m1,&d1);
    sscanf(today,"%d-%d-%d",&y2,&m2,&d2);

    int returnDays = y1*365 + m1*30 + d1;
    int todayDays = y2*365 + m2*30 + d2;

    int overdue = todayDays - returnDays;

    if(overdue > 0){
        return overdue * 20;
    }

    return 0;
}
//Return Book
void ReturnBook(){
    system("cls");
    int memberId;
    int bookId;
    printf("-----Return Book----\n");
    printf("Enter Member ID: ");
    scanf("%d",&memberId);

    printf("Enter Book ID: ");
    scanf("%d",&bookId);

    for(int i=0;i<issue_count;i++){

        if(issues[i].MemberId == memberId &&
           issues[i].BookId == bookId &&
           issues[i].returned == 0){

            char today[20];

            printf("Enter Today's Date (YYYY-MM-DD) : ");
            scanf("%s",today);

            int fine = CalculateFine(issues[i].ReturnDate, today);
            if(fine > 0){
                printf("Overdue Fine : Rs %d\n",fine);
            }
            else{
                printf("No Fine\n");
            }

            issues[i].returned = 1;

            printf("Book Returned Successfully \n");

            return;
        }
    }

    printf("No active issue found for this member and book \n");
}
// Menu
void Menu(){
    printf("\n---Welcome to Library Management System---\n");
    while(1){
        int choice;
        printf("\n--------MENU--------\n");
        printf("\n1.Add Book ");
        printf("\n2.Display Book ");
        printf("\n3.Update Book ");
        printf("\n4.Delete Book ");
        printf("\n5.Search Book ");
        printf("\n6.Add Member");
        printf("\n7.Add Issue");
        printf("\n8.Not Returned Books");
        printf("\n9.Overdue Books");
        printf("\n10.Available Copies");
        printf("\n11.Return Book");
        printf("\n12.Exit");
        printf("\nPlease Enter your choice :");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            AddBook();
            break;
        case 2:
            DisplayBooks();
            break;
        case 3:
            UpdateBook();
            break;
        case 4:
            DeleteBook();
            break;
        case 5:
            SearchBook();
            break;
        case 6:
            AddMember();
            break;
        case 7:
            AddIssue();
            break;
        case 8:
            NotReturnedBooks();
            break;
        case 9:
            OverdueBooks();
            break;
        case 10:
            AvailableBooks();
            break;
        case 11:
            ReturnBook();
            break;
        case 12:
            system("cls");
            Login();
            break;
        default:
            printf("Invalid \nPLEAS TRY AGAIN\n");
        }
    }
}
//---Login
void Login(){
    char user_name[100];
    char password[100];
    getchar();
    printf("Enter Username:");
    fgets(user_name,sizeof(user_name),stdin);
    user_name[strcspn(user_name, "\n")] = 0;
    printf("Enter Password:");
    fgets(password,sizeof(password),stdin);
    password[strcspn(password, "\n")] = 0;

    for(int i=0;i<user_count;i++){
        if(strcmp(users[i].UserId, user_name) == 0){
            if(strcmp(users[i].Password, password) == 0){
                system("cls");
                printf("\nLogin Successful\n");
                Menu();
                return;
            }else{
                printf("\nIncorrect Password\n");
                return Login();
            }
        }
    }
    printf("\nUser Id not found\n");
    return Login();
}
