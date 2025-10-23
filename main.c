#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CITIES 30

char cityName[MAX_CITIES][50];
int numOfCities = 0;

void addCity();
void renameCity();

int main() {
    int choice;

    do {
        printf("\n===== Logistics Management System =====\n");
        printf("1. Add City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. Input Distance\n");
        printf("5. Display Distance\n");
        printf("6. Handle Delivery\n");
        printf("7. Show Reports\n");
        printf("8. Save and Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCity(); break;
            case 2: renameCity(); break;

        }
    } while (choice != 2);

    return 0;
}

void addCity(){
    int i;
    printf("Enter the number of cities you are going to add:");
    scanf("%d",&numOfCities);

    if(numOfCities < MAX_CITIES){
        for(i=0;i<numOfCities;i++){
            printf("city %d:",i);

            printf("Enter city name:");
            scanf("%s",cityName[i]);
        }

        printf("City added successfully!\n");
    }
}


void renameCity() {
    int idx;
    if (numOfCities == 0) {
        printf("No cities available.\n");
        return;
    }
    printf("Enter city index (0 to %d): ", numOfCities - 1);
    scanf("%d", &idx);
    if (idx < 0 || idx >= numOfCities) {
        printf("Invalid index.\n");
        return;
    }
    printf("Enter new name for %s: ", cityName[idx]);
    scanf("%s", cityName[idx]);
    printf("City renamed successfully!\n");
}
