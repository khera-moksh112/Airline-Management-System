#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_FLIGHTS 200
#define MAX_PASSENGERS 500
#define MAX_STAFF 100

// ================= STRUCTURES =================

typedef struct {
    int flightID;
    char flightName[50];
    char source[50];
    char destination[50];
    char date[20];
    char time[10];
    int totalSeats;
    int availableSeats;
    float ticketPrice;
} Flight;

typedef struct {
    int passengerID;
    char name[50];
    char gender[10];
    int age;
    int flightID;
    char seatNumber[10];
    float farePaid;
} Passenger;

typedef struct {
    int staffID;
    char name[50];
    char role[30];
    char contact[15];
} Staff;

// ================= GLOBAL DATA =================

Flight flights[MAX_FLIGHTS];
Passenger passengers[MAX_PASSENGERS];
Staff staffs[MAX_STAFF];

int flightCount = 0;
int passengerCount = 0;
int staffCount = 0;

// ================= UTILITIES =================

void pressEnter() {
    printf("\nPress Enter to continue...");
    getchar();
}

void generateSeat(char *seat) {
    char row = 'A' + rand() % 6;
    int num = 1 + rand() % 30;
    sprintf(seat, "%c%d", row, num);
}

// case-insensitive string compare (STANDARD C)
int compareIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower(*a) != tolower(*b))
            return 0;
        a++;
        b++;
    }
    return *a == *b;
}

// ================= FILE HANDLING =================

void saveFlights() {
    FILE *fp = fopen("flights.dat", "wb");
    if (!fp) return;
    fwrite(&flightCount, sizeof(int), 1, fp);
    fwrite(flights, sizeof(Flight), flightCount, fp);
    fclose(fp);
}

void loadFlights() {
    FILE *fp = fopen("flights.dat", "rb");
    if (!fp) return;
    fread(&flightCount, sizeof(int), 1, fp);
    fread(flights, sizeof(Flight), flightCount, fp);
    fclose(fp);
}

void savePassengers() {
    FILE *fp = fopen("passengers.dat", "wb");
    if (!fp) return;
    fwrite(&passengerCount, sizeof(int), 1, fp);
    fwrite(passengers, sizeof(Passenger), passengerCount, fp);
    fclose(fp);
}

void loadPassengers() {
    FILE *fp = fopen("passengers.dat", "rb");
    if (!fp) return;
    fread(&passengerCount, sizeof(int), 1, fp);
    fread(passengers, sizeof(Passenger), passengerCount, fp);
    fclose(fp);
}

void saveStaffs() {
    FILE *fp = fopen("staff.dat", "wb");
    if (!fp) return;
    fwrite(&staffCount, sizeof(int), 1, fp);
    fwrite(staffs, sizeof(Staff), staffCount, fp);
    fclose(fp);
}

void loadStaffs() {
    FILE *fp = fopen("staff.dat", "rb");
    if (!fp) return;
    fread(&staffCount, sizeof(int), 1, fp);
    fread(staffs, sizeof(Staff), staffCount, fp);
    fclose(fp);
}

// ================= FLIGHTS =================

void addFlight() {
    Flight f;
    f.flightID = flightCount + 1;

    printf("Flight Name: ");
    scanf("%s", f.flightName);
    printf("Source: ");
    scanf("%s", f.source);
    printf("Destination: ");
    scanf("%s", f.destination);
    printf("Date (DD-MM-YYYY): ");
    scanf("%s", f.date);
    printf("Time (HH:MM): ");
    scanf("%s", f.time);
    printf("Total Seats: ");
    scanf("%d", &f.totalSeats);
    f.availableSeats = f.totalSeats;
    printf("Ticket Price: ");
    scanf("%f", &f.ticketPrice);

    flights[flightCount++] = f;
    saveFlights();
    printf("Flight added successfully!\n");
}

void viewFlights() {
    if (flightCount == 0) {
        printf("No flights available.\n");
        return;
    }

    for (int i = 0; i < flightCount; i++) {
        printf("%d %s %s->%s %s %s Seats:%d Price:%.2f\n",
               flights[i].flightID,
               flights[i].flightName,
               flights[i].source,
               flights[i].destination,
               flights[i].date,
               flights[i].time,
               flights[i].availableSeats,
               flights[i].ticketPrice);
    }
}

void searchFlight() {
    char src[50], dest[50];
    int found = 0;

    printf("Source: ");
    scanf("%s", src);
    printf("Destination: ");
    scanf("%s", dest);

    for (int i = 0; i < flightCount; i++) {
        if (compareIgnoreCase(flights[i].source, src) &&
            compareIgnoreCase(flights[i].destination, dest)) {
            printf("ID:%d %s %s %s %.2f Seats:%d\n",
                   flights[i].flightID,
                   flights[i].flightName,
                   flights[i].date,
                   flights[i].time,
                   flights[i].ticketPrice,
                   flights[i].availableSeats);
            found = 1;
        }
    }

    if (!found)
        printf("No flights found.\n");
}

// ================= BOOKINGS =================

void bookTicket() {
    int id;
    Passenger p;

    printf("Enter Flight ID: ");
    scanf("%d", &id);
    getchar();

    if (id <= 0 || id > flightCount || flights[id - 1].availableSeats == 0) {
        printf("Invalid or full flight.\n");
        return;
    }

    p.passengerID = passengerCount + 1;
    p.flightID = id;

    printf("Passenger Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("Age: ");
    scanf("%d", &p.age);
    printf("Gender: ");
    scanf("%s", p.gender);

    generateSeat(p.seatNumber);
    p.farePaid = flights[id - 1].ticketPrice;

    flights[id - 1].availableSeats--;
    passengers[passengerCount++] = p;

    savePassengers();
    saveFlights();

    printf("Booking successful. Seat: %s\n", p.seatNumber);
}

void viewBookings() {
    if (passengerCount == 0) {
        printf("No bookings found.\n");
        return;
    }

    for (int i = 0; i < passengerCount; i++) {
        printf("%d %s Flight:%d Seat:%s Fare:%.2f\n",
               passengers[i].passengerID,
               passengers[i].name,
               passengers[i].flightID,
               passengers[i].seatNumber,
               passengers[i].farePaid);
    }
}

void cancelBooking() {
    int id;
    printf("Passenger ID: ");
    scanf("%d", &id);

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].passengerID == id) {
            flights[passengers[i].flightID - 1].availableSeats++;
            for (int j = i; j < passengerCount - 1; j++)
                passengers[j] = passengers[j + 1];
            passengerCount--;
            savePassengers();
            saveFlights();
            printf("Booking cancelled.\n");
            return;
        }
    }
    printf("Passenger not found.\n");
}

// ================= STAFF =================

void addStaff() {
    Staff s;
    s.staffID = staffCount + 1;

    printf("Name: ");
    scanf("%s", s.name);
    printf("Role: ");
    scanf("%s", s.role);
    printf("Contact: ");
    scanf("%s", s.contact);

    staffs[staffCount++] = s;
    saveStaffs();
    printf("Staff added.\n");
}

void viewStaff() {
    for (int i = 0; i < staffCount; i++) {
        printf("%d %s %s %s\n",
               staffs[i].staffID,
               staffs[i].name,
               staffs[i].role,
               staffs[i].contact);
    }
}

// ================= MENUS =================

void adminMenu() {
    int ch;
    do {
        printf("\n1 Add Flight\n2 View Flights\n3 Add Staff\n4 View Staff\n5 Back\nChoice: ");
        scanf("%d", &ch);
        getchar();

        if (ch == 1) addFlight();
        else if (ch == 2) viewFlights();
        else if (ch == 3) addStaff();
        else if (ch == 4) viewStaff();

        pressEnter();
    } while (ch != 5);
}

void customerMenu() {
    int ch;
    do {
        printf("\n1 Search\n2 Book\n3 View\n4 Cancel\n5 Back\nChoice: ");
        scanf("%d", &ch);
        getchar();

        if (ch == 1) searchFlight();
        else if (ch == 2) bookTicket();
        else if (ch == 3) viewBookings();
        else if (ch == 4) cancelBooking();

        pressEnter();
    } while (ch != 5);
}

void staffMenu() {
    int ch;
    do {
        printf("\n1 View Flights\n2 View Passengers\n3 Back\nChoice: ");
        scanf("%d", &ch);
        getchar();

        if (ch == 1) viewFlights();
        else if (ch == 2) viewBookings();

        pressEnter();
    } while (ch != 3);
}

// ================= MAIN =================

int main() {
    srand(time(NULL));
    loadFlights();
    loadPassengers();
    loadStaffs();

    int ch;
    while (1) {
        printf("\n1 Admin\n2 Customer\n3 Staff\n4 Exit\nChoice: ");
        scanf("%d", &ch);
        getchar();

        if (ch == 1) adminMenu();
        else if (ch == 2) customerMenu();
        else if (ch == 3) staffMenu();
        else if (ch == 4) break;
    }
    return 0;
}
