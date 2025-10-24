#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50

typedef struct {
    char source[50];
    char destination[50];
    char vehicle[20];
    int distance;
    float weight;
    float cost;
    float fuelCost;
    float totalCost;
    float profit;
    float charge;
    float time;
} Delivery;

char cityName[MAX_CITIES][50];
int distanceMatrix[MAX_CITIES][MAX_CITIES];
int numOfCities = 0;
Delivery deliveries[MAX_DELIVERIES];
int deliveryCount = 0;

void addCity();
void renameCity();
void removeCity();
void inputDistance();
void displayDistance();
void handleDelivery();
void showReports();

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
            case 7: showReports(); break;
        }
    } while (choice != 7);

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

    if (weight > capacity) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }
    if (src == dest) {
        printf("Source and destination must be different.\n");
        return;
    }

    int D = distanceMatrix[src][dest];
    if (D == 0) {
        printf("Distance not set between these cities.\n");
        return;
    }

    float cost = D * rate * (1 + weight / 10000.0);
    float fuelUsed = (float)D / eff;
    float fuelCost = fuelUsed * fuelPrice;
    float totalCost = cost + fuelCost;
    float profit = cost * 0.25;
    float charge = totalCost + profit;
    float time = (float)D / speed;

   printf("==================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("--------------------------------------------------\n");
    printf("From: %s\nTo: %s\nVehicle: %s\nDistance: %d km\nWeight: %.2f kg\n", cityName[src], cityName[dest], vehicle, D, weight);
    printf("--------------------------------------------------\n");
    printf("Base Cost: %.2f LKR\nFuel Cost: %.2f LKR\nOperational Cost: %.2f LKR\nProfit: %.2f LKR\nCustomer Charge: %.2f LKR\nEstimated Time: %.2f hours\n",
           cost, fuelCost, totalCost, profit, charge, time);
    printf("==================================================\n");

    // Save delivery record
    if (deliveryCount < MAX_DELIVERIES) {
        strcpy(deliveries[deliveryCount].source, cityName[src]);
        strcpy(deliveries[deliveryCount].destination, cityName[dest]);
        strcpy(deliveries[deliveryCount].vehicle, vehicle);
        deliveries[deliveryCount].distance = D;
        deliveries[deliveryCount].weight = weight;
        deliveries[deliveryCount].cost = cost;
        deliveries[deliveryCount].fuelCost = fuelCost;
        deliveries[deliveryCount].totalCost = totalCost;
        deliveries[deliveryCount].profit = profit;
        deliveries[deliveryCount].charge = charge;
        deliveries[deliveryCount].time = time;
        deliveryCount++;
    }
}

void showReports() {
    float totalDist = 0, totalProfit = 0, totalCharge = 0, totalTime = 0;
    int longest = 0, shortest = 100000;

    if (deliveryCount == 0) {
        printf("No deliveries yet.\n");
        return;
    }

    for (int i = 0; i < deliveryCount; i++) {
        totalDist += deliveries[i].distance;
        totalProfit += deliveries[i].profit;
        totalCharge += deliveries[i].charge;
        totalTime += deliveries[i].time;

        if (deliveries[i].distance > longest)
            longest = deliveries[i].distance;
        if (deliveries[i].distance < shortest)
            shortest = deliveries[i].distance;
    }

    printf("\n===== PERFORMANCE REPORT =====\n");
    printf("Total Deliveries Completed: %d\n", deliveryCount);
    printf("Total Distance Covered: %.2f km\n", totalDist);
    printf("Average Delivery Time: %.2f hours\n", totalTime / deliveryCount);
    printf("Total Revenue (Customer Charge): %.2f LKR\n", totalCharge);
    printf("Total Profit: %.2f LKR\n", totalProfit);
    printf("Longest Route: %d km\n", longest);
    printf("Shortest Route: %d km\n", shortest);
}
