#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>
#include <direct.h>
#include <sys/stat.h>

struct accounts
{
    char name[30];
    char C_account_number[10];
    int password;
    int account_number;
    int money;
};

struct accounts all_accounts[100];
int number_of_accounts = 0;
int account_numbers[100];

void Account_Activities();
void Create_account();
void Main_menu();
void Show_account();
int search_account();
void Deposit_money();
void Withdraw_money();
void Send_money();
char* Find_account_activities();
void Create_Account_Activities();
void count_account_activities();
int generate_account_number();
void update_money();

int main()
{
    srand(time(NULL));
    int choice;
    struct stat st = {0};
    if (stat("user_story", &st) == -1)
        system("mkdir account_activities");
    count_account_activities();
    while (true)
    {
        Main_menu();
        printf("What would you like to do?\n=");
        scanf("%d",&choice);
        switch (choice)
        {  
            case 1:
                Create_account();
                break;
            case 2:
                Show_account();
                break;
            case 3:
                int temp1;
                printf("Your account number: ");
                scanf("%d",&temp1);
                if (search_account(temp1) == -1)
                    printf("There are no accounts that are using this account number. Please try again\n");
                else
                    Deposit_money(search_account(temp1));
                break;
            case 4:
                int temp2;
                printf("Your account number: ");
                scanf("%d",&temp2);
                if (search_account(temp2) == -1)
                    printf("There are no accounts that are using this account number. Please try again\n");   
                else
                    Withdraw_money(search_account(temp2));
                break;
            case 5:
                int temp3;
                printf("Your account number: ");
                scanf("%d",&temp3);
                int temp101 = search_account(temp3);
                if (temp101 == -1)
                    printf("There are no accounts that are using this account number. Please try again\n");
                else
                    Send_money(temp101);
                break;
            case 6:
                printf("We hope you come again :)\n");
                return 0;
                break;
            default:
                printf("Please select a valid option\n");
                break;
        }
    }
}

void Main_menu()
{
    printf("\n1. Create a new account\n");
    printf("2. Show account\n");
    printf("3. Deposit money\n");
    printf("4. Withdraw money\n");
    printf("5. Send money\n");
    printf("6. Exit\n");
    printf("--------------------------------\n");
    
}

void Create_account()
{
    printf("\n\nYour name: ");
    getchar();
    fgets(all_accounts[number_of_accounts].name,30,stdin);
    int length = strlen(all_accounts[number_of_accounts].name);
    if (length > 0 && all_accounts[number_of_accounts].name[length - 1] == '\n')
        all_accounts[number_of_accounts].name[length - 1] = '\0';
    all_accounts[number_of_accounts].account_number = generate_account_number(number_of_accounts);
    printf("Your account number is %d dont forget that.\n",all_accounts[number_of_accounts].account_number);
    sprintf(all_accounts[number_of_accounts].C_account_number,"%d",all_accounts[number_of_accounts].account_number);
    printf("Password: ");
    scanf("%d", &all_accounts[number_of_accounts].password);
    printf("Your account has been succesfully created :)\n\n");
    number_of_accounts++;
    char select;
    all_accounts[number_of_accounts-1].money = 0;
    Create_Account_Activities(number_of_accounts-1);
    printf("You have %d money right now want to deposit some?(Y/N): ",all_accounts[number_of_accounts-1].money);
    getchar();
    scanf("%c",&select);
    while (toupper(select) != 'Y' && toupper(select) != 'N')
    {
        printf("Please enter Y or N: ");
        getchar();
        scanf("%c",&select);
    }
    if (toupper(select) == 'Y')
        return Deposit_money(number_of_accounts-1);
    return;
}

void Show_account()
{
    int TEMP;
    printf("\nYour account number: ");
    scanf("%d",&TEMP);
    int index = search_account(TEMP);
    if (index == -1)
    {
        printf("There are no accounts that are using this account number. Please try again\n");
    }
    else
    {
        printf("\nYour name: %s\n",all_accounts[index].name);
        printf("Your account number: %d\n",all_accounts[index].account_number);
        printf("Your money: %d\n",all_accounts[index].money);
        printf("\n\n");
        getchar();
    }
    return;
}

int search_account(int index)
{
    for (int i = 0; i < number_of_accounts; i++)
    {
        if (index == all_accounts[i].account_number)
        {
            return i;
        }
    }
    return -1;
}

void Deposit_money(int index_of_customer)
{
    int pass,depositing_money;
    printf("How much money you want to deposit: ");
    scanf("%d",&depositing_money);
    printf("Your password: ");
    getchar();
    scanf("%d",&pass);
    if (all_accounts[index_of_customer].password == pass)
    {
        all_accounts[index_of_customer].money += depositing_money;
        update_money(all_accounts[index_of_customer].C_account_number,index_of_customer);
        printf("Your money has been deposited :)\n");
        char *The_file = Find_account_activities(all_accounts[index_of_customer].C_account_number);
        FILE *pF = fopen(The_file,"a");
        printf("\n%s\n",The_file);
        if (pF == NULL)
            printf("This transaction was not recorded in account transactions\n");
        else
        {
            fprintf(pF,"$%d has been deposited into the account\n",depositing_money);
        }
        fclose(pF);
    }
    else
        printf("Your password is wrong please try again.\n");
    
    return;
}
void Withdraw_money(int index_of_customer)
{
    int pass,Withdrawing_money;
    printf("How much money you want to withdraw: ");
    scanf("%d",&Withdrawing_money);
    if (Withdrawing_money > all_accounts[index_of_customer].money)
    {
        printf("You dont have this much money on your account. Please try again.\n");
        return;
    }
    printf("Your password: ");
    getchar();
    scanf("%d",&pass);
    if (all_accounts[index_of_customer].password == pass)
    {
        all_accounts[index_of_customer].money -= Withdrawing_money;
        update_money(all_accounts[index_of_customer].C_account_number,index_of_customer);
        printf("Your have been withdrawed some money :)\n");
        char *The_file = Find_account_activities(all_accounts[index_of_customer].C_account_number);
        FILE *pF = fopen(The_file,"a");
        if (pF == NULL)
            printf("This transaction was not recorded in account transactions\n");
        else
            fprintf(pF,"$%d was withdrawn from the account\n",Withdrawing_money);
        fclose(pF);
    }
    else
    {
        printf("Your password is wrong please try again.\n");
    }
    return;
}

void Send_money(int index_of_customer)
{
    int person,pass,Sending_money;
    printf("What is the account number that you are sending money to: ");
    scanf("%d",&person);
    int person_index = search_account(person);
    if (person_index == -1)
    {
        printf("There are no accounts that are using this account number. Try again\n");
        return;
    }
    printf("How much money you want to send: "); 
    getchar();
    scanf("%d",&Sending_money);
    if (Sending_money > all_accounts[index_of_customer].money)
    {
        printf("You dont have this much money on your account. Please try again.\n");
        return;
    }
    printf("Your password: ");
    getchar();
    scanf("%d",&pass);
    if (all_accounts[index_of_customer].password == pass)
    {
        all_accounts[index_of_customer].money -= Sending_money;
        update_money(all_accounts[index_of_customer].C_account_number,index_of_customer);
        all_accounts[person_index].money += Sending_money;
        update_money(all_accounts[person_index].C_account_number,person_index);
        printf("You have been succesfully sended money\n");                    
        
        char *The_file1 = Find_account_activities(all_accounts[index_of_customer].C_account_number);
        FILE *pFile = fopen(The_file1,"a");
        if (pFile == NULL)
            printf("This transaction was not recorded in account transactions\n");
        else
            fprintf(pFile,"$%d transferred to %d person\n",Sending_money,person);
        fclose(pFile);

        char *The_file2 = Find_account_activities(all_accounts[person_index].C_account_number);
        pFile = fopen(The_file2,"a");
        if (pFile == NULL)
            printf("This transaction was not recorded in account transactions\n");
        else
            fprintf(pFile,"%d sent you $%d\n",all_accounts[index_of_customer].account_number,Sending_money);
        fclose(pFile);
    }
    else
    {
        printf("Your password is wrong please try again.\n");
    }
    return;
}

void Create_Account_Activities(int Account_number_of_customer)
{
    char path[150]= "account_activities\\";
    sprintf(path,"%s%s.txt",path,all_accounts[Account_number_of_customer].C_account_number);
    printf("\n%s\n",path);
    FILE *pFile = fopen(path,"w");
    if (pFile == NULL)
        printf("Error\n");
    fprintf(pFile,"name: %s\npassword: %d\naccount number: %d\nmoney: %d\n-----------------------\n\n",all_accounts[Account_number_of_customer].name,all_accounts[Account_number_of_customer].password,all_accounts[Account_number_of_customer].account_number,all_accounts[Account_number_of_customer].money);
    fclose(pFile);
    return;
}

char* Find_account_activities(char Account_number_of_customer[]) 
{
    char *The_file1 = malloc(sizeof(char)*100);
    sprintf(The_file1,"account_activities\\%s.txt",Account_number_of_customer);
    return The_file1;
}

void count_account_activities()
{
    FILE *pF;
    char path[100] = "account_activities\\";
    char txt[15];
    for (int i = 100; i < 1000; i++)
    {
        sprintf(path,"account_activities\\");
        sprintf(txt,"%d.txt",i);
        strcat(path,txt);
        pF = fopen(path,"r");
        if (pF != NULL)
        {
            fscanf(pF,"name: %s\npassword: %d\naccount number: %d\nmoney: %d",&all_accounts[number_of_accounts].name,&all_accounts[number_of_accounts].password,&all_accounts[number_of_accounts].account_number,&all_accounts[number_of_accounts].money);
            account_numbers[number_of_accounts] = all_accounts[number_of_accounts].account_number;
            sprintf(all_accounts[number_of_accounts].C_account_number,"%d",all_accounts[number_of_accounts].account_number);
            number_of_accounts++;
            fclose(pF);
        }
    }
}

int generate_account_number(int index)
{
    int an = (rand() % 900) + 100;
    for (int i = 0;account_numbers[i] != 0; i++)
        if (account_numbers[i] == an)
            return generate_account_number(index);
    return an;
}

void update_money(char C_index[],int index)
{
    FILE *pF;
    char path[100] = "account_activities\\";
    sprintf(path,"%s%d.txt",path,all_accounts[index].account_number);
    pF = fopen(path,"r+");
    fprintf(pF,"name: %s\npassword: %d\naccount number: %d\nmoney: %d\n-----------------------",all_accounts[index].name,all_accounts[index].password,all_accounts[index].account_number,all_accounts[index].money);
    fclose(pF);
}