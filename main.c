#include<stdio.h>
#include<string.h>
#include<math.h>


//template for booking
struct Booking
{
    int bookingId;
    int customerId;
    char from;
    char to;
    int pickupTime;
    int dropTime;
    int amount;
    char* taxiName;
};

//template for taxi
struct Taxi{
 char name[10];
 int earned;
 char location;
 int dropTime;
};


//Initialized with 5 taxis
struct Taxi taxis[5]={
{ "Taxi-1",0,'A',-1},
{ "Taxi-2",0,'A',-1},
{ "Taxi-3",0,'A',-1},
{ "Taxi-4",0,'A',-1},
{ "Taxi-5",0,'A',-1}
};



//Storing booking history
struct Booking history[10];
int historyLength=0;
//calculating the distance between the points
 int calculateDistance(char from, char to) {
        int fromInt = from;
        int toInt = to;
        return abs(fromInt - toInt) * 15;
}
//Calculating the amount for the distance
   int calculateAmount(int distance) {
        return distance * 10;
    }


//Calculating the nearest taxi available
    struct Taxi* findTaxi(char from, int pickupTime) {
    struct Taxi* availableTaxi;
    struct Taxi* minTaxi[5];
    int minTaxiLength =0;
    int minimumDistance = -1;
//Choosing the closest taxis
        for(int i=0;i<5;i++) {
                struct Taxi* taxi = &taxis[i];
                if(pickupTime>=taxi->dropTime){
                int distance = calculateDistance(from, taxi->location);
                if (minimumDistance == -1) {
                    minTaxi[minTaxiLength++]=taxi;
                    minimumDistance = distance;
                } else if (minimumDistance > distance) {
                    minTaxiLength = 0;
                    minimumDistance = distance;
                    minTaxi[minTaxiLength++]=taxi;
                } else if (minimumDistance == distance) {
                    minTaxi[minTaxiLength++]=taxi;
                }
                }
        }
//Choosing the taxi with minimum earnings
availableTaxi = minTaxi[0];
        if (minTaxiLength > 1) {
            int earned = availableTaxi->earned;
            for (int i = 1; i < minTaxiLength; i++) {
               struct Taxi* taxi = minTaxi[i];
                if (earned > taxi->earned) {
                    availableTaxi = taxi;
                    earned = taxi->earned;
                }
            }
        }
        return availableTaxi;
    }


//Booking a new taxi
void bookTaxi(char from, char to, int pickupTime) {

        int bookingId = historyLength + 1;
        int customerId =historyLength + 1;

        int distance = calculateDistance(from, to);
       int dropTime = pickupTime+distance;
        int amount = calculateAmount(distance);

        struct Taxi* taxi = findTaxi(from, pickupTime);
        taxi->location = to;
        taxi->dropTime = dropTime;
        taxi->earned += amount;
        char* taxiName = taxi->name;


        struct Booking booking = {
                bookingId,
                customerId,
                from,
                to,
                pickupTime,
                dropTime,
                amount,
                taxiName
        };
        history[historyLength++]=booking;

       printf("Booking ID: %d\n",bookingId);
       printf("Allotted Taxi: %s\n", taxiName);
    }

//Viewing the history of the particular taxi
    void historyOf(char taxiName[10]) {

        for(int i=0;i<historyLength;i++)
        {
          struct Booking booking = history[i];
            if (booking.taxiName[5] == taxiName[5]) {
                printf("%d %c %c %d:%d %d:%d %d\n",
                                booking.customerId ,
                                booking.from ,
                                booking.to ,
                                booking.pickupTime/60,
                                booking.pickupTime%60,
                                booking.dropTime/60,
                                booking.dropTime%60,
                                booking.amount
                );
            }
        }
    }



void main()
{

    int hr,min;
    char start;
    char to;
    int a=1,b;
    char c[10];
    while(a){
            printf("1 - Booking Taxi\n");
            printf("2 - Viewing History\n");
            printf("3 - quit\n");
            printf("Enter your choice: ");
            scanf("%d",&b);
            switch(b){
            case 1:
                printf("Enter start point: ");
                scanf("%s",&to);
                printf("Enter end point: ");
                scanf("%s",&start);
                printf("\nEnter the pickup time :");
                scanf("%d.%d",&hr,&min);
                int time = (hr*60)+min;
                printf("\ntime : %d.%d\t",hr,min);
                bookTaxi(to,start,time);
                break;
            case 2:
                scanf("%s",c);
                historyOf(c);
                break;
            case 3:
                a=0;
                break;
            default:
                printf("invalid");
    }
}
}






