#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gps.h>
#include <math.h>

#define SERVER_NAME         "localhost"
#define SERVER_PORT         "2947"

int main(void) 
{
    struct gps_data_t g_gpsdata;
    int ret;

    // 1) Try GPS open
    ret = gps_open(SERVER_NAME,SERVER_PORT, &g_gpsdata);
    if(ret != 0) {
        printf("[GPS] Can't open...bye!\r\n");
        return -1;
    }

    // 2) Enable the JSON stream - we enable the watch as well
    gps_stream(&g_gpsdata, WATCH_ENABLE | WATCH_JSON, NULL);

    // 3) Wait for data from GPSD
    while (gps_waiting(&g_gpsdata, 5000000)) {

        sleep(1);

        if (-1 == gps_read(&g_gpsdata, NULL, 0)) {
            printf("Read error!! Exiting...\n");
            break;
        }

        if (g_gpsdata.status != STATUS_FIX) {
            printf("Waiting for fix...\n");
            continue;
        }
        
        if(isfinite(g_gpsdata.fix.latitude) && isfinite(g_gpsdata.fix.longitude)) {
            printf("[GPS DATA] Time = %ld.%06ld, Latitude = %lf, Longitude = %lf, Used satellites = %d, Mode = %d\n", 
                    g_gpsdata.online.tv_sec, g_gpsdata.online.tv_nsec/1000, g_gpsdata.fix.latitude, 
                    g_gpsdata.fix.longitude, g_gpsdata.satellites_used, g_gpsdata.fix.mode);        
        }
        else {
            printf(".");
        }
    }

    // Close gracefully...
    gps_stream(&g_gpsdata, WATCH_DISABLE, NULL);
    gps_close(&g_gpsdata);
    return 0;
}