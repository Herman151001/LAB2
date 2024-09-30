#include <stdio.h>
#include <stdlib.h>

void displaysales(int productCount, int quantitiesSold[], int productID[], int manufacturePrice[], int retailPrice[], int commands[], int commandCount);
void selectionSort(int arr[], int size, int sortedIDs[], int originalIndices[]);
int binarySearch(int arr[], int size, int target);

int main() {
    const int MAX_PRODUCTS = 50000;
    const int MAX_COMMANDS = 10000;

    int quantitiesSold[MAX_PRODUCTS];
    int productID[MAX_PRODUCTS];
    int manufacturePrice[MAX_PRODUCTS];
    int retailPrice[MAX_PRODUCTS];
    int sortedProductID[MAX_PRODUCTS];
    int originalIndices[MAX_PRODUCTS];
    int productCount = 0;

    if (scanf("%d", &productCount) != 1 || productCount <= 0 || productCount > MAX_PRODUCTS) {
        printf("Invalid input\n");
        return 1;
    }
    
    for (int i = 0; i < productCount; i++) {
        scanf("%d %d %d", &productID[i], &manufacturePrice[i], &retailPrice[i]);
        originalIndices[i] = i;
    }

    // Sort products by ID
    selectionSort(productID, productCount, sortedProductID, originalIndices);
    
    int commands[MAX_COMMANDS];
    int commandCount = 0;

    while (1) {
        
        int userChoice;
        scanf("%d", &userChoice);
        
        if (userChoice == -2) {
            commands[commandCount++] = userChoice;
            displaysales(productCount, quantitiesSold, productID, manufacturePrice, retailPrice, commands, commandCount);
            break; 
        } else if (userChoice == -1) {
            commands[commandCount++] = userChoice; // Store the -1 command
            displaysales(productCount, quantitiesSold, productID, manufacturePrice, retailPrice, commands, commandCount);
        } else {
            int index = binarySearch(sortedProductID, productCount, userChoice);
            if (index != -1) {
                quantitiesSold[originalIndices[index]]++;
               // printf("Recorded sale for product ID %d. Quantity sold: %d\n", userChoice, quantitiesSold[originalIndices[index]]);
                commands[commandCount++] = userChoice; // Store the valid product ID
            } else {
                
            }
        }
    }

    return 0;
}

void selectionSort(int arr[], int size, int sortedIDs[], int originalIndices[]) {
    for (int i = 0; i < size; i++) {
        sortedIDs[i] = arr[i];
    }

    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (sortedIDs[j] < sortedIDs[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int tempID = sortedIDs[i];
            sortedIDs[i] = sortedIDs[minIndex];
            sortedIDs[minIndex] = tempID;

            int tempIndex = originalIndices[i];
            originalIndices[i] = originalIndices[minIndex];
            originalIndices[minIndex] = tempIndex;
        }
    }

    
    
    
}

int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
    
        if (arr[mid] == target) {
       
            return mid;
        }
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    return -1; // Not found
}



void recordSale(int productIndex, int quantitiesSold[]) {
    quantitiesSold[productIndex] += 1; // Increment quantity for the product
   
}




void displaysales(int productCount, int quantitiesSold[], int productID[], int manufacturePrice[], int retailPrice[], int commands[], int commandCount) {
    printf("\nSales:\n");
    printf("+-------+----------------+--------+---------------+\n");
    printf("| ID    | Quantity Sold  | Profit | GM            |\n");
    printf("+-------+----------------+--------+---------------+\n");

    
    int lastQuantities[productCount];
    for (int i = 0; i < productCount; i++) {
        lastQuantities[i] = 0; 
    }

    
    for (int i = 0; i < commandCount; i++) {
        if (commands[i] == -1) {
            break; 
        }
        int productIndex = -1;
        for (int j = 0; j < productCount; j++) {
            if (productID[j] == commands[i]) {
                productIndex = j;
                break; 
            }
        }

        if (productIndex != -1) {
            lastQuantities[productIndex] = quantitiesSold[productIndex]; 
        }
    }

  
    for (int i = 0; i < productCount; i++) {
        if (lastQuantities[i] > 0) {
            int quantity = lastQuantities[i];
            int profit = (retailPrice[i] - manufacturePrice[i]) * quantity;
            float profitMargin = (float)(retailPrice[i] - manufacturePrice[i]) / retailPrice[i] * 100;

            printf("| %d | %d            | %d      | %.2f          |\n", productID[i], quantity, profit, profitMargin);
        }
    }

     printf("\nSales:\n");
    printf("+-------+----------------+--------+---------------+\n");
    printf("| ID    | Quantity Sold  | Profit | GM            |\n");
    printf("+-------+----------------+--------+---------------+\n");
    for (int i = 0; i < productCount; i++) {
        if (quantitiesSold[i] > 0) {
            int quantity = quantitiesSold[i];
            int profit = (retailPrice[i] - manufacturePrice[i]) * quantity;
            float profitMargin = (float)(retailPrice[i] - manufacturePrice[i]) / retailPrice[i] * 100;

            printf("| %d | %d            | %d      | %.2f          |\n", productID[i], quantity, profit, profitMargin);
        }
    }

    printf("+-------+----------------+--------+---------------+\n");
}
