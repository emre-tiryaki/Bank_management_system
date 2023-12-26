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

int main()
{
    srand(time(NULL));
    int choice;
    struct stat st = {0};
    if (stat("user_story", &st) == -1)
        system("mkdir user_story");
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
                FILE *pF;
                char *The_file;
                for (int i = 0; i <= number_of_accounts; i++)
                {
                    The_file = Find_account_activities(all_accounts[i].C_account_number);
                    if (remove(The_file) != 0)
                        printf("%s could not have been deleted.",The_file);
                }
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
    //all_accounts[number_of_accounts].name[strlen(all_accounts[number_of_accounts].name)] = '\0';
    all_accounts[number_of_accounts].account_number = (rand() % 900) + 100;
    printf("Your account number is %d dont forget that.\n",all_accounts[number_of_accounts].account_number);
    sprintf(all_accounts[number_of_accounts].C_account_number,"%d.txt",all_accounts[number_of_accounts].account_number);
    printf("Password: ");
    scanf("%d", &all_accounts[number_of_accounts].password);
    printf("Your account has been succesfully created :)\n\n");
    number_of_accounts++;
    char select;
    all_accounts[number_of_accounts-1].money = 0;
    Create_Account_Activities(all_accounts[number_of_accounts-1].C_account_number);
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
        Deposit_money(number_of_accounts-1);
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
        printf("\nYour name: %s",all_accounts[index].name);
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
        printf("Your money has been deposited :)\n");
        char *The_file = Find_account_activities(all_accounts[index_of_customer].C_account_number);
        FILE *pF = fopen(The_file,"a");
        if (pF == NULL)
            printf("This transaction was not recorded in account transactions\n");
        else
        {
            fprintf(pF,"$%d money has been deposited into the account\n",depositing_money);
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
        printf("Your have been withdrawed some money :)\n");
        char *The_file = Find_account_activities(all_accounts[index_of_customer].C_account_number);
        FILE *pF = fopen(The_file,"a");
        if (pF == NULL)
            printf("This transaction was not recorded in account transactions\n");
        else
        {
            fprintf(pF,"$%d money was withdrawn from the account\n",Withdrawing_money);
        }
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
        all_accounts[person_index].money += Sending_money;
        printf("You have been succesfully sended money\n");                    
        
        char *The_file1 = Find_account_activities(all_accounts[index_of_customer].C_account_number);
        FILE *pFile = fopen(The_file1,"a");
        if (pFile == NULL)
            printf("This transaction was not recorded in account transactions\n");
        else
            fprintf(pFile,"$%d money transferred to %d person\n",Sending_money,person);
        fclose(pFile);

        char *The_file2 = Find_account_activities(all_accounts[person_index].C_account_number);
        pFile = fopen(The_file2,"a");
        if (pFile == NULL)
            printf("This transaction was not recorded in account transactions\n");
        else
            fprintf(pFile,"%d person sent you $%d\n",all_accounts[index_of_customer].account_number,Sending_money);
        fclose(pFile);
    }
    else
    {
        printf("Your password is wrong please try again.\n");
    }
    return;
}

void Create_Account_Activities(char Account_number_of_customer[10])
{
    char path[150]= "C:\\Users\\User\\OneDrive\\Desktop\\projelerim(Denemeler)\\Bank_management_system\\C\\Bank_Management_System\\user_story\\";
    strcat(path,Account_number_of_customer);
    
    FILE *pFile = fopen(path,"w");
    if (pFile == NULL)
        printf("Error\n");
    fprintf(pFile,"-----------------------\n");
    fclose(pFile);
    return;
}

char* Find_account_activities(const char Account_number_of_customer[10]) {
    char* The_file = malloc(150);

    if (The_file == NULL)
        printf("Error");

    strcpy(The_file, "C:\\Users\\User\\OneDrive\\Desktop\\projelerim(Denemeler)\\Bank_management_system\\C\\Bank_Management_System\\user_story\\");
    strcat(The_file, Account_number_of_customer);

    return The_file;
}