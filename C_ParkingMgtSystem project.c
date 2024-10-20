#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car {
    char brand[50];
    char model[50];
    char plate_number[20];
    char chassis_number[20];
    char owner[100];
};

void registerCar(FILE *file) {
    struct Car car;

    printf("Enter brand: ");
    scanf("%s", car.brand);

    printf("Enter model: ");
    scanf("%s", car.model);

    printf("Enter plate number: ");
    scanf("%s", car.plate_number);

    printf("Enter chassis number: ");
    scanf("%s", car.chassis_number);

    printf("Enter owner: ");
    scanf("%s", car.owner);

    fprintf(file, "%s %s %s %s %s\n", car.brand, car.model, car.plate_number, car.chassis_number, car.owner);
    printf("Car registered successfully!\n");
}

float pricing(int hours) {
    return hours * 5.0;
}

void searchCar(FILE *file, const char *plate_number) {
    struct Car car;
    int found = 0;

    // Rewind the file to the beginning
    rewind(file);

    while (fscanf(file, "%s %s %s %s %s", car.brand, car.model, car.plate_number, car.chassis_number, car.owner) != EOF) {
        if (strcmp(car.plate_number, plate_number) == 0) {
            printf("Car found!\n");
            printf("Brand: %s\n", car.brand);
            printf("Model: %s\n", car.model);
            printf("Plate Number: %s\n", car.plate_number);
            printf("Chassis Number: %s\n", car.chassis_number);
            printf("Owner: %s\n", car.owner);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Car not found with plate number: %s\n", plate_number);
    }
}

void updateCar(FILE *file, const char *plate_number) {
    struct Car car;
    long pos;
    int found = 0;

    // Rewind the file to the beginning
    rewind(file);

    while (fscanf(file, "%s %s %s %s %s", car.brand, car.model, car.plate_number, car.chassis_number, car.owner) != EOF) {
        if (strcmp(car.plate_number, plate_number) == 0) {
            pos = ftell(file) - strlen(car.plate_number) - 1; // consider space after plate_number
            found = 1;
            break;
        }
    }

    if (found) {
        fseek(file, pos, SEEK_SET);

        printf("Enter new brand: ");
        scanf("%s", car.brand);

        printf("Enter new model: ");
        scanf("%s", car.model);

        printf("Enter new chassis number: ");
        scanf("%s", car.chassis_number);

        printf("Enter new owner: ");
        scanf("%s", car.owner);

        fprintf(file, "%s %s %s %s %s\n", car.brand, car.model, car.plate_number, car.chassis_number, car.owner);
        printf("Car information updated successfully!\n");
    } else {
        printf("Car not found with plate number: %s\n", plate_number);
    }
}

int main() {
    FILE *file;
    int choice;
    char plate_number[20];

    file = fopen("parking_data.txt", "a+");

    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    do {
        printf("\nParking Management System\n");
        printf("1. Register Car\n");
        printf("2. Search Car\n");
        printf("3. Update Car Information\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerCar(file);
                break;
            case 2:
                printf("Enter plate number to search: ");
                scanf("%s", plate_number);
                searchCar(file, plate_number);
                break;
            case 3:
                printf("Enter plate number to update: ");
                scanf("%s", plate_number);
                updateCar(file, plate_number);
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    fclose(file);

    return 0;
}
