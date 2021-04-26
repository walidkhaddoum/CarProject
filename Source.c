#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>


typedef struct Vehicle
{
    int VehicleID;
    char Make[30];
    char Model[10];
    int Year;
    int Mileage;
    int Cost;
}Vehicle;

Vehicle vehicle[10];

int ReadFile(char* fileName);

void DisplayAllCars(char* fileName)
{
    int CarsNumbers;
    CarsNumbers = ReadFile(fileName);
    int i;
    printf("Vehicle-ID\tMake\tModel\tYear\tMileage\tCost\n");
    for (i = 0; i < CarsNumbers; i++)
    {
        printf("%d\t%s\t%s\t%d\t%d\t%d\n", vehicle[i].VehicleID, vehicle[i].Make, vehicle[i].Model, vehicle[i].Year, vehicle[i].Mileage, vehicle[i].Cost);
    }
}

void InsertaNewCar(int CarsNumbers, char* filename)
{
    int result;
    FILE* filePtr = NULL;
    int i;
    printf("Vehicle-ID : ");
    scanf("%d", &vehicle[CarsNumbers].VehicleID);
    result = SearchByVehicleID(CarsNumbers, vehicle[CarsNumbers].VehicleID);
        while(result==-1){
            result = -1;
            printf("This Vehicle ID already Exist\n");
            printf("Vehicle-ID : ");
            scanf("%d", &vehicle[CarsNumbers].VehicleID);
            for (i = 0; i <= CarsNumbers; i++)
            {
                if (vehicle[i].VehicleID == vehicle[CarsNumbers].VehicleID) {
                    result = i;
                }
            }
        }
    printf("\nMake : ");
    scanf("%s", &vehicle[CarsNumbers].Make);
    printf("\nModel : ");
    scanf("%s", &vehicle[CarsNumbers].Model);
    printf("\nYear : ");
    scanf("%d", &vehicle[CarsNumbers].Year);
    printf("\nMileage : ");
    scanf("%d", &vehicle[CarsNumbers].Mileage);
    printf("\nCost : $");
    scanf("%d", &vehicle[CarsNumbers].Cost);
    if ((filePtr = fopen(filename, "w")) == NULL)
    {
        printf("Error : Unable to open %s for reading\n", filename);
        exit(EXIT_FAILURE);
    }
    for (i = 0; i <= CarsNumbers; i++)
    {
        fprintf(filePtr, "%d\n", vehicle[i].VehicleID);
        fprintf(filePtr, "%s\n", vehicle[i].Make);
        fprintf(filePtr, "%s\n", vehicle[i].Model);
        fprintf(filePtr, "%d\n", vehicle[i].Year);
        fprintf(filePtr, "%d\n", vehicle[i].Mileage);
        fprintf(filePtr, "%d\n", vehicle[i].Cost);
    }
    fclose(filePtr);
    printf("Car with information : \nVehicle ID : %d\nMake : %s\nModel : %s\nYear : %d\nMileage : %d\nCost : $%d\nHas Inserted", vehicle[CarsNumbers].VehicleID, vehicle[CarsNumbers].Make, vehicle[CarsNumbers].Model, vehicle[CarsNumbers].Year, vehicle[CarsNumbers].Mileage, vehicle[CarsNumbers].Cost);
}

int SearchByVehicleID(int CarsNumbers, int VehicleSearch)
{
    int result = -1;
    int i;
    for (i = 0; i <= CarsNumbers; i++) {
        if (vehicle[i].VehicleID == VehicleSearch) {
            result = i;
            break;
        }
    }
    return result;
}

void UpdateaCar(int CarsNumbers, int VehicleSearch, char* filename)
{
    FILE* filePtr = NULL;
    int i;
    int VehicleUpdated = SearchByVehicleID(CarsNumbers, VehicleSearch);
    if (VehicleUpdated == -1)
    {
        printf("Not Found Please Try Again ... \n");
    }
    else {
        printf("\nYear : ");
        scanf("%d", &vehicle[VehicleUpdated].Year);
        printf("Cost : $");
        scanf("%d", &vehicle[VehicleUpdated].Cost);
        if ((filePtr = fopen(filename, "w")) == NULL)
        {
            printf("Error : Unable to open %s for reading\n", filename);
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < CarsNumbers; i++) {
            fprintf(filePtr, "%d\n", vehicle[i].VehicleID);
            fprintf(filePtr, "%s\n", vehicle[i].Make);
            fprintf(filePtr, "%s\n", vehicle[i].Model);
            fprintf(filePtr, "%d\n", vehicle[i].Year);
            fprintf(filePtr, "%d\n", vehicle[i].Mileage);
            fprintf(filePtr, "%d\n", vehicle[i].Cost);
        }
        fclose(filePtr);
    }

}

void DeleteaCar(int CarsNumbers, int VehicleSearch, char* filename) {
    FILE* filePtr = NULL;
    int i;
    int VehicleDeleted = SearchByVehicleID(CarsNumbers, VehicleSearch);
    if (VehicleDeleted == -1)
    {
        printf("Not Found Please Try Again ... \n");
    }
    else {
        for (i = VehicleDeleted; i < CarsNumbers; i++)
        {
            vehicle[i].VehicleID = vehicle[i + 1].VehicleID;
            strcpy(vehicle[i].Make, vehicle[i + 1].Make);
            strcpy(vehicle[i].Model, vehicle[i + 1].Model);
            vehicle[i].Year = vehicle[i + 1].Year;
            vehicle[i].Mileage = vehicle[i + 1].Mileage;
            vehicle[i].Cost = vehicle[i + 1].Cost;
        }
        CarsNumbers--;
        if ((filePtr = fopen(filename, "w")) == NULL)
        {
            printf("Error : Unable to open %s for reading\n", filename);
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < CarsNumbers; i++) {
            fprintf(filePtr, "%d\n", vehicle[i].VehicleID);
            fprintf(filePtr, "%s\n", vehicle[i].Make);
            fprintf(filePtr, "%s\n", vehicle[i].Model);
            fprintf(filePtr, "%d\n", vehicle[i].Year);
            fprintf(filePtr, "%d\n", vehicle[i].Mileage);
            fprintf(filePtr, "%d\n", vehicle[i].Cost);
        }
        fclose(filePtr);
    }
}

int Search(int typeSearch, int CarsNumbers, char* filename) {
    int result = -1;
    char car[20];
    int testing = 0;
    int i, VehicleSearch;
    if (typeSearch == 1) {
        scanf("%d", &VehicleSearch);
        result = SearchByVehicleID(CarsNumbers, VehicleSearch);
        if (result == -1) {
            printf("No car exist with this Vehicle-ID (%d)", VehicleSearch);
        }
        else {
            printf("Vehicle-ID\tMake\tModel\tYear\tMileage\tCost\n");
            for (i = 0; i <= CarsNumbers; i++)
            {
                if (vehicle[i].VehicleID == VehicleSearch)
                {
                    printf("%d\t%s\t%s\t%d\t%d\t%d\n", vehicle[i].VehicleID, vehicle[i].Make, vehicle[i].Model, vehicle[i].Year, vehicle[i].Mileage, vehicle[i].Cost);
                }
            }
        }
        result = -1;
    }
    if (typeSearch == 2) {
        scanf("%s", &car);
        result = 0;
        printf("Vehicle-ID\tMake\tModel\tYear\tMileage\tCost\n");
        for (i = 0; i < CarsNumbers; i++)
        {
            if (strcmp(_strlwr(car), _strlwr(vehicle[i].Make)) == 0)
            {
                printf("%d\t%s\t%s\t%d\t%d\t%d\n", vehicle[i].VehicleID, vehicle[i].Make, vehicle[i].Model, vehicle[i].Year, vehicle[i].Mileage, vehicle[i].Cost);
                result++;
            }
        }
        if (result == 0)
        {
            printf("No Car found (%s)", car);
        }
    }
    if (typeSearch == 3) {
        scanf("%d", &VehicleSearch);
        for (i = 0; i <= CarsNumbers; i++) {
            if (vehicle[i].Year == VehicleSearch) {
                result = i;
                break;
            }
        }
        if (result == -1) {
            printf("No car exist with this Year (%d)", VehicleSearch);
        }
        else {
            printf("Vehicle-ID\tMake\tModel\tYear\tMileage\tCost\n");
            for (i = 0; i <= CarsNumbers; i++)
            {
                if (vehicle[i].Year == VehicleSearch)
                {
                    printf("%d\t%s\t%s\t%d\t%d\t%d\n", vehicle[i].VehicleID, vehicle[i].Make, vehicle[i].Model, vehicle[i].Year, vehicle[i].Mileage, vehicle[i].Cost);
                }
            }
        }
        result = -1;
    }
    if (typeSearch == 4) {
        scanf("%d", &VehicleSearch);
        for (i = 0; i <= CarsNumbers; i++) {
            if (vehicle[i].Cost == VehicleSearch) {
                result = i;
                break;
            }
        }
        if (result == -1) {
            printf("No car exist with this Cost (%d)", VehicleSearch);
        }
        else {
            printf("Vehicle-ID\tMake\tModel\tYear\tMileage\tCost\n");
            for (i = 0; i <= CarsNumbers; i++)
            {
                if (vehicle[i].Cost == VehicleSearch)
                {
                    printf("%d\n%s\n%s\n%d\n%d\n%d\n", vehicle[i].VehicleID, vehicle[i].Make, vehicle[i].Model, vehicle[i].Year, vehicle[i].Mileage, vehicle[i].Cost);
                }
            }
        }
        result = -1;
    }
}


int main(int argc, char* argv[])
{
    int i;
    int carsNumber;
    char* fileName = "carList.txt";
    int Choice, ChoiceSearch;
    int VehicleSearch;
    carsNumber = ReadFile(fileName);
    do
    {
        printf("\n\n");
        printf("\t1.Dispaly All Cars\n");
        printf("\t2.Insert a new car\n");
        printf("\t3.Update a car by Vehicle-ID\n");
        printf("\t4.Delete a car by Vehicle-ID\n");
        printf("\t5.Search\n");
        printf("\t6.Exit\n");
        printf("\n\n\tYour Choice :>");
        scanf("%d", &Choice);
        switch (Choice)
        {
        case 1:
            DisplayAllCars(fileName, carsNumber);
            break;
        case 2:
            InsertaNewCar(carsNumber, fileName);
            carsNumber++;
            break;
        case 3:
            printf("The car you are lookin for :> ");
            scanf("%d", &VehicleSearch);
            UpdateaCar(carsNumber, VehicleSearch, fileName);
            break;
        case 4:
            printf("\nThe vehicle you want to remove :> ");
            scanf("%d", &VehicleSearch);
            DeleteaCar(carsNumber, VehicleSearch, fileName);
            break;
        case 5:
            printf("\n5.1 Search by Vehicle-ID\n");
            printf("\n5.2 Search by Make\n");
            printf("\n5.3 Search for by year\n");
            printf("\n5.4 Search for by a Cost\n");
            printf("Your Choice :> ");
            scanf("%d", &ChoiceSearch);
            switch (ChoiceSearch)
            {
            case 1:
                printf("\nVehicle-ID :> ");
                Search(ChoiceSearch, carsNumber, fileName);
                break;
            case 2:
                printf("\nMake :> ");
                Search(ChoiceSearch, carsNumber, fileName);
                break;
            case 3:
                printf("\nYear :> ");
                Search(ChoiceSearch, carsNumber, fileName);
                break;
            case 4:
                printf("\nCost :> ");
                Search(ChoiceSearch, carsNumber, fileName);
                break;
            default:
                break;
            }
        }
    } while (Choice != 6);

    exit(EXIT_SUCCESS);
}

int ReadFile(char* fileName)
{
    FILE* filePtr = NULL;
    int  i = 0;

    if ((filePtr = fopen(fileName, "r")) == NULL)
    {
        printf("Error : Unable to open %s for reading\n", fileName);
        exit(EXIT_FAILURE);
    }
    while (fscanf(filePtr, "%d\n%[^\n]%*c%[^\n]%*c%d\n%d\n%d\n", &vehicle[i].VehicleID, &vehicle[i].Make, &vehicle[i].Model, &vehicle[i].Year, &vehicle[i].Mileage, &vehicle[i].Cost) != EOF)
    {
        i++;
    }

    fclose(filePtr);
    return i;
}