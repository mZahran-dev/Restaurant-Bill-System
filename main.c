#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct items
{
    char item[20];
    float price;
    int qty;
};
struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

void GenerateHeader(char Name[50], char date[30])
{
    printf("\n\n");
    printf("\t    SWISSHOUSE.RESTAURANT");
    printf("\n\t     ===================");
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", Name);
    printf("\n");
    printf("=======================================\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total");
    printf("\n=======================================");
    printf("\n\n");
}
void GenerateBody(char item[30], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f", qty * price);
    printf("\n");
}

void GenerateFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, totalPrice = netTotal + 2 * cgst;
    printf("=======================================\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount %%10\t\t\t%.2f", dis);
    printf("\n\t\t\t\t=======");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST %%9\t\t\t\t%.2f", cgst);
    printf("\nSGST %%9\t\t\t\t%.2f", cgst);
    printf("\n=======================================");
    printf("\nTotal Price\t\t\t%.2f", totalPrice);
    printf("\n=======================================\n");
}

int main(void)
{
    int op, n;
    char savebill = 'y', c = 'y';
    FILE *fp;
    struct orders ord;
    struct orders order;
    char name[50];
    while (c == 'y')
    {
        int invoiceF = 0;
        float total = 0;
        printf("\t\t==========SWISSHOUSE.RESTAURANT==========\n\n");
        printf("1. Generate Invoice\n");
        printf("2. Show All Invoices\n");
        printf("3. Search Invoice\n");
        printf("4. Exit\n\n");
        printf("Please, Select Your Operation:   ");
        scanf("%d", &op);
        fgetc(stdin);
        switch (op)
        {
        case 1:
            system("cls");
            printf("\nPlease Enter the Name Of the Customer:\t");
            fgets(ord.customer, 50, stdin);
            ord.customer[strlen(ord.customer) - 1] = 0;
            strcpy(ord.date, __DATE__);
            printf("Please enter the numbers of items:\t");
            scanf("%d", &n);
            ord.numOfItems = n;
            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the Name of the  item %d: ", i + 1);
                fgets(ord.itm[i].item, 20, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                printf("\nPlease enter the quantity:\t");
                scanf("%d", &ord.itm[i].qty);
                printf("\nPlease enter the unit price:\t");
                scanf("%f", &ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }
            GenerateHeader(ord.customer, ord.date);
            for (int i = 0; i < ord.numOfItems; i++)
            {
                GenerateBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            GenerateFooter(total);

            printf("\nDo want to save the invoice: [y/n]\t");
            scanf("%s", &savebill);
            if (savebill == 'y')
            {
                fp = fopen("Restaurantbill.dat", "a+");
                fwrite(&ord, sizeof(struct orders), 1, fp);
                if (fwrite != 0)
                    printf("\nSuccessfuly saved");
                else
                    printf("\nError Saving");

                fclose(fp);
            }
            break;
        case 2:
            system("cls");
            fp = fopen("Restaurantbill.dat", "r");
            printf("\n  ***** Your Privious invoices *****\n");
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                GenerateHeader(order.customer, order.date);
                for (int i = 0; i < order.numOfItems; i++)
                {

                    GenerateBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    total += order.itm[i].qty * order.itm[i].price;
                }
                GenerateFooter(total);
            }
            fclose(fp);
            break;

        case 3:

            printf("\nEnter the name of the customer:\t");
            // fgetc(stdin);
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            system("cls");
            fp = fopen("Restaurantbill.dat", "r");
            printf("\n\t\tInvoice of ==>> %s\n", name);
            printf("\n\t\t ===================");
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                if (strcmp(order.customer, name))
                {
                    GenerateHeader(order.customer, order.date);
                    for (int i = 0; i < order.numOfItems; i++)
                    {
                        GenerateBody(order.itm[i].item, order.itm[i].qty,
                                     order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    GenerateFooter(tot);
                    invoiceF = 1;
                }
            }
            if (!invoiceF)
                printf("sorry the invoice for %s doesNot Exists", name);

            fclose(fp);
            break;

        case 4:
            printf("\n\t\t Bye Bye:)\n");
            exit(0);
            break;

        default:
            printf("Sorry Invalid option ");
            break;
        }

        printf("\nDo want to perform another Operation [y/n]\t");
        scanf("%s", &c);
    }
    printf("\n\n");
    return 0;
}
