#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

unsigned char month_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid syntax!\n");
        printf(" Usage: %s IP_DEST PORT_DEST\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(atoi(argv[2]));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    socklen_t l = sizeof(server);

    char request;
    sendto(c, &request, sizeof(request), 0, (struct sockaddr *) &server, sizeof(server));

    int val = 0;
    recvfrom(c, &val, sizeof(val), 0, (struct sockaddr *) &server, &l);

    val = ntohl(val); // val = number of seconds from 1 ianuarie 1970, 00:00
    
    printf("Value from the server: %d\n", val);
    printf(" Timezone: Romania (GMT+3)\n");
    val += 3 * 3600; // GMT+3
    int sec = val % 60;
    val /= 60;
    int min = val % 60;
    val /= 60;
    int hour = val % 24;
    val /= 24;
    
    char hour_form[10];
    char buf[4];
    memset(hour_form, '\0', sizeof(hour_form));
    sprintf(buf, "%d:", hour);
    if (hour < 10) {
        strcpy(hour_form, "0");
    }
    strcat(hour_form, buf);
    
    sprintf(buf, "%d:", min);
    if (min < 10) {
        strcat(hour_form, "0");
    }
    strcat(hour_form, buf);

    sprintf(buf, "%d", sec);
    if (sec < 10) {
        strcat(hour_form, "0");
    }
    strcat(hour_form, buf);

    printf("Current hour: %s\n", hour_form);

    int days = val; // the number of days since 1 January 1970
    int aprox_year = 1970 + days / 365; // the year without counting the leap years
    
    int leap_years = (aprox_year - 1972) / 4 - (aprox_year - 1972) / 100 + (aprox_year - 1972) / 400; // an leap year could be divisible by 4, but not by 100, or it could be divisible by 400

    int curr_year = 1970 + (days - leap_years) / 365; // we substract from the days the value of the leap years since 1970 to get the current year
    int day_of_year = ((days - leap_years) % 365) + 1; // the day of the current year

    if ((curr_year % 4 == 0 && curr_year % 100 != 0) || curr_year % 400 == 0) {
        month_days[1] = 29;
    }

    int curr_month, temp_days = 0;
    for (curr_month = 0; curr_month < 12; ++curr_month) {
        temp_days += month_days[curr_month];
        if (temp_days >= day_of_year) {
            break;
        }
    }

    int curr_day = day_of_year - temp_days + month_days[++curr_month]; // 

    printf("Current day: %d/%d/%d\n", curr_day, curr_month, curr_year);

    close(c);
}
