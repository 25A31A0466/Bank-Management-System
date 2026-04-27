#include <stdio.h>
#include <stdlib.h>
struct Bank {
    int accNo;
    char name[50];
    float balance;
};
void createAccount() {
    struct Bank b;
    FILE *fp = fopen("account.dat", "ab");

    printf("Enter Account Number: ");
    scanf("%d", &b.accNo);
    printf("Enter Name: ");
    scanf("%s", b.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &b.balance);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("Account Created Successfully!\n");
}
void displayAll() {
    struct Bank b;
    FILE *fp = fopen("account.dat", "rb");

    while (fread(&b, sizeof(b), 1, fp)) {
        printf("\nAccount No: %d", b.accNo);
        printf("\nName: %s", b.name);
        printf("\nBalance: %.2f\n", b.balance);
    }
    fclose(fp);
}
void modifyAccount(int accNo, int option) {
    struct Bank b;
    FILE *fp = fopen("account.dat", "rb+");
    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.accNo == accNo) {
            float amt;
            if (option == 1) {
                printf("Enter amount to deposit: ");
                scanf("%f", &amt);
                b.balance += amt;
            } else if (option == 2) {
                printf("Enter amount to withdraw: ");
                scanf("%f", &amt);
                if (amt <= b.balance)
                    b.balance -= amt;
                else
                    printf("Insufficient Balance!\n");
            }
            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);
            printf("Transaction Successful!\n");
            break;
        }
    }

    fclose(fp);
}
int main() {
    int choice, accNo;
    do {
        printf("\n\n=== BANK MANAGEMENT SYSTEM ===");
        printf("\n1. Create Account");
        printf("\n2. Display All Accounts");
        printf("\n3. Deposit");
        printf("\n4. Withdraw");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                printf("Enter Account No: ");
                scanf("%d", &accNo);
                modifyAccount(accNo, 1);
                break;
            case 4:
                printf("Enter Account No: ");
                scanf("%d", &accNo);
                modifyAccount(accNo, 2);
                break;
            case 5:
                printf("Thank you!\n");
                break;
            default:
                printf("Invalid choice!");
        }

    } while (choice != 5);

    return 0;
}
