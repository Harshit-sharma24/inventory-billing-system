#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void addItem();
void viewInventory();
void showBillPreview(int n, int purchasedId[], char purchasedName[][50],
                     char purchasedCategory[][50], int purchasedQty[],
                     float purchasedPrice[], float purchasedTotal[],
                     float *grandTotal)
{
    int i;
    *grandTotal = 0;

    printf("\n----------- BILL PREVIEW -----------\n");
    printf("ID   Item   Category   Qty   Total\n");

    for (i = 0; i < n; i++)
    {
        if (purchasedId[i] != -1)
        {
            purchasedTotal[i] = purchasedQty[i] * purchasedPrice[i];
            *grandTotal += purchasedTotal[i];

            printf("%d   %s   %s   %d   %.2f\n",
                   purchasedId[i],
                   purchasedName[i],
                   purchasedCategory[i],
                   purchasedQty[i],
                   purchasedTotal[i]);
        }
    }

    printf("----------------------------------\n");
    printf("Grand Total: %.2f\n", *grandTotal);
}

void editItemQty(int n, int purchasedId[], int purchasedQty[])
{
    int id, newQty, i;

    printf("Enter Item ID to edit quantity: ");
    scanf("%d", &id);

    for (i = 0; i < n; i++)
    {
        if (purchasedId[i] == id)
        {
            printf("Enter new quantity: ");
            scanf("%d", &newQty);
            purchasedQty[i] = newQty;
            printf("Quantity updated successfully!\n");
            return;
        }
    }

    printf("Item not found in bill!\n");
}

void deleteItem(int n, int purchasedId[])
{
    int id, i;

    printf("Enter Item ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < n; i++)
    {
        if (purchasedId[i] == id)
        {
            purchasedId[i] = -1;
            printf("Item deleted from bill!\n");
            return;
        }
    }

    printf("Item not found!\n");
}

void generateBill();
int generateOrderId();

int main()
{
    int choice;
    do
    {   printf("\ninventory billing system\n");
        printf("1. Add Item\n");
        printf("2. View Inventory\n");
        printf("3. Generate Bill\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addItem();
            break;
        case 2:
            viewInventory();
            break;
        case 3:
            generateBill();
            break;
        case 0:
            printf("Program exited successfully.\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }

    } while (choice != 0);

    return 0;
}



void addItem()
{
    FILE *fp, *tempFp;
    int id, stock, found = 0;
    float price;
    char name[50], category[50];

    printf("\nEnter Item ID: ");
    scanf("%d", &id);

    printf("Enter Item Name: ");
    scanf("%s", name);

    printf("Enter Category: ");
    scanf("%s", category);

    printf("Enter Price: ");
    scanf("%f", &price);

    printf("Enter Stock: ");
    scanf("%d", &stock);

    fp = fopen("inventory.txt", "r");
    tempFp = fopen("temp.txt", "w");

    if (fp != NULL)
    {
        int tempId, tempStock;
        float tempPrice;
        char tempName[50], tempCategory[50];

        while(fscanf(fp, "%d %s %s %f %d", &tempId, tempName, tempCategory, &tempPrice, &tempStock) != EOF)
        {
            if(tempId == id)
            {
                
                tempStock += stock;    
                tempPrice = price;     
                strcpy(tempName, name);
                strcpy(tempCategory, category);
                found = 1;
            }
            fprintf(tempFp, "%d %s %s %.2f %d\n", tempId, tempName, tempCategory, tempPrice, tempStock);
        }

        fclose(fp);
        fclose(tempFp);

        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
    }

    if(!found) 
    {
        fp = fopen("inventory.txt", "a");
        if(fp != NULL)
        {
            fprintf(fp, "%d %s %s %.2f %d\n", id, name, category, price, stock);
            fclose(fp);
        }
    }

    printf("Item added/updated successfully!\n");
}

void viewInventory()
{
    FILE *fp;
    int id, stock;
    float price;
    char name[50], category[50];

    fp = fopen("inventory.txt", "r");
    if (fp == NULL)
    {
        printf("Inventory not found!\n");
        return;
    }

    printf("\nID   Name   Category   Price   Stock\n");
    printf("-------------------------------------\n");

    while (fscanf(fp, "%d %s %s %f %d",
                  &id, name, category, &price, &stock) != EOF)
    {
        printf("%d   %s   %s   %.2f   %d\n",
               id, name, category, price, stock);
    }

    fclose(fp);
}
#define MAX_ITEMS 100 
void generateBill()
{
    FILE *fp, *tempFp;
    int id, stock;
    int buyId, buyQty;
    int n, i, found;
    float price, total, grandTotal = 0;
    char name[50], category[50];

    int orderId = generateOrderId();

    fp = fopen("inventory.txt", "r");
    if (fp == NULL)
    {
        printf("Inventory not found!\n");
        return;
    }

    printf("How many different items you want to buy? ");
    scanf("%d", &n);

    int purchasedId[MAX_ITEMS], purchasedQty[MAX_ITEMS];
    char purchasedName[MAX_ITEMS][50], purchasedCategory[MAX_ITEMS][50];
    float purchasedPrice[MAX_ITEMS], purchasedTotal[MAX_ITEMS];

    for (i = 0; i < n; i++)
        purchasedId[i] = -1;

    for (i = 0; i < n; i++)
    {
        printf("\nEnter Item ID: ");
        scanf("%d", &buyId);
        printf("Enter Quantity: ");
        scanf("%d", &buyQty);

        rewind(fp);
        found = 0;

        while (fscanf(fp, "%d %s %s %f %d",
                      &id, name, category, &price, &stock) != EOF)
        {
            if (id == buyId)
            {
                found = 1;
                if (stock >= buyQty)
                {
                    purchasedId[i] = id;
                    purchasedQty[i] = buyQty;
                    strcpy(purchasedName[i], name);
                    strcpy(purchasedCategory[i], category);
                    purchasedPrice[i] = price;
                }
                else
                {
                    printf("Insufficient stock!\n");
                }
                break;
            }
        }

        if (!found)
            printf("Item not found!\n");
    }


    fclose(fp);

    /* ===== EDIT MENU ===== */
    int choice;
    do
    {
        showBillPreview(n, purchasedId, purchasedName,
                        purchasedCategory, purchasedQty,
                        purchasedPrice, purchasedTotal,
                        &grandTotal);

        printf("\n1. Edit Quantity");
        printf("\n2. Delete Item");
        printf("\n3. Confirm Bill");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            editItemQty(n, purchasedId, purchasedQty);
        else if (choice == 2)
            deleteItem(n, purchasedId);

    } while (choice != 3);

    /* ===== UPDATE INVENTORY ===== */
    fp = fopen("inventory.txt", "r");
    tempFp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %s %s %f %d",
                  &id, name, category, &price, &stock) != EOF)
    {
        for (i = 0; i < n; i++)
        {
            if (purchasedId[i] == id)
                stock -= purchasedQty[i];
        }
        fprintf(tempFp, "%d %s %s %.2f %d\n",
                id, name, category, price, stock);
    }

    fclose(fp);
    fclose(tempFp);
    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    printf("\n================= DELHI SHOP BILL =================\n");
printf("Order ID: %d\n", orderId);
printf("---------------------------------------------------\n");
printf("%-5s %-15s %-12s %-5s %-10s\n",
       "ID", "Item", "Category", "Qty", "Total");
printf("---------------------------------------------------\n");

for (i = 0; i < n; i++)
{
    if (purchasedId[i] != -1)
    {
        printf("%-5d %-15s %-12s %-5d %-10.2f\n",
               purchasedId[i],
               purchasedName[i],
               purchasedCategory[i],
               purchasedQty[i],
               purchasedTotal[i]);
    }
}

printf("---------------------------------------------------\n");
printf("%-39s %-10.2f\n", "GRAND TOTAL:", grandTotal);
printf("===================================================\n");
printf("Thank You! Visit Again\n");

}

int generateOrderId()
{
    FILE *fp;
    int orderId = 1000;

    fp = fopen("order_id.txt", "r");
    if (fp != NULL)
    {
        fscanf(fp, "%d", &orderId);
        fclose(fp);
    }

    orderId++;

    fp = fopen("order_id.txt", "w");
    fprintf(fp, "%d", orderId);
    fclose(fp);

    return orderId;
}
