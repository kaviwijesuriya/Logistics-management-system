#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50

char cityName[MAX_CITIES][50];
int distanceMatrix[MAX_CITIES][MAX_CITIES];
int numOfCities = 0;

void addCity();
void renameCity();
void removeCity();
void inputDistance();
void displayDistance();
void handleDelivery();

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
            case 3: removeCity(); break;
            case 4: inputDistance(); break;
            case 5: displayDistance(); break;
            case 6: handleDelivery(); break;

        }
    } while (choice != 6);

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

void removeCity() {
    int idx;
    if (numOfCities == 0) {
        printf("No cities to remove.\n");
        return;
    }
    printf("Enter city index (0 to %d): ", numOfCities - 1);
    scanf("%d", &idx);
    if (idx < 0 || idx >= numOfCities) {
        printf("Invalid index.\n");
        return;
    }
    for (int i = idx; i < numOfCities - 1; i++) {
        strcpy(cityName[i], cityName[i + 1]);
        for (int j = 0; j < numOfCities; j++) {
            distanceMatrix[i][j] = distanceMatrix[i + 1][j];
            distanceMatrix[j][i] = distanceMatrix[j][i + 1];
        }
    }
    numOfCities--;
    printf("City removed successfully!\n");
}

void inputDistance() {
    if (numOfCities < 2) {
        printf("Need at least 2 cities.\n");
        return;
    }
    int i, j, d;
    printf("Enter source city index: "); scanf("%d", &i);
    printf("Enter destination city index: "); scanf("%d", &j);
    if (i < 0 || i >= numOfCities || j < 0 || j >= numOfCities || i == j) {
        printf("Invalid indices.\n");
        return;
    }
    printf("Enter distance between %s and %s (km): ", cityName[i], cityName[j]);
    scanf("%d", &d);
    distanceMatrix[i][j] = distanceMatrix[j][i] = d;
    printf("Distance updated.\n");
}

void displayDistance() {
    if (numOfCities == 0) {
        printf("No cities.\n");
        return;
    }

    printf("\nDistance Matrix:\n");
    printf("%12s", "");
    for (int j = 0; j < numOfCities; j++) {
        printf("%12s", cityName[j]);
    }
    printf("\n");

    for (int i = 0; i < numOfCities; i++) {
        printf("%12s", cityName[i]);
        for (int j = 0; j < numOfCities; j++) {
            printf("%12d", distanceMatrix[i][j]);
        }
        printf("\n");
    }
}

void handleDelivery() {
    if (numOfCities < 2) {
        printf("Add cities and distances first.\n");
        return;
    }

    int src, dest, vType;
    float weight;
    const float fuelPrice = 310;

    printf("Enter source city index: "); scanf("%d", &src);
    printf("Enter destination city index: "); scanf("%d", &dest);
    printf("Enter weight (kg): "); scanf("%f", &weight);

    printf("Select vehicle:\n1. Van\n2. Truck\n3. Lorry\n");
    scanf("%d", &vType);

    char vehicle[20];
    int rate, capacity, speed, eff;

    switch (vType) {
        case 1: strcpy(vehicle, "Van"); rate = 30; capacity = 1000; speed = 60; eff = 12; break;
        case 2: strcpy(vehicle, "Truck"); rate = 40; capacity = 5000; speed = 50; eff = 6; break;
        case 3: strcpy(vehicle, "Lorry"); rate = 80; capacity = 10000; speed = 45; eff = 4; break;
        default: printf("Invalid vehicle.\n"); return;
    }


}

