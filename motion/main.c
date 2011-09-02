/*
 *  UniMotion - Unified Motion detection for Apple portables.
 *
 *  Copyright (c) 2007 Lincoln Ramsay. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "unimotion.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum {
    raw,
    calibrated,
    real,
    bytes,
    scaled
} disp_t;

void usage()
{
    int type;
    char *name;

    printf("Usage:  motion [-f|-r|-b|-s] [ms]\n\n");
    printf("-f  Print real (foating point) values (calibrated machines report 1G as 1.0)\n");
    printf("-r  Print raw values (exactly as the SMS returns)\n");
    printf("-c  Print calibrated values (raw + offset calibration)\n");
    printf("-b  Print raw bytes (exactly as the SMS returns)\n");
    printf("-s  Print scaled values (calibrated + 1G = around 250)\n");
    printf("ms continue to output every ms miliseconds\n");
    printf("Note that calibrated output is the default\n");
    printf("\n");

    type = detect_sms();
    switch ( type ) {
        case powerbook:
            name = "powerbook";
            break;
        case ibook:
            name = "ibook";
            break;
        case highrespb:
            name = "highrespb";
            break;
        case macbookpro:
            name = "macbookpro";
            break;
        default:
            name = "???";
            break;
    }
    printf("Detected SMS type %d (%s)\n", type, name);
}

int main( int argc, char **argv )
{
    int type;
    int x, y, z;
    double fx, fy, fz;
    int loop = 0;
    int i = 1;
    disp_t disp = calibrated;

    if ( argc >= i+1 ) {
        if ( strcmp(argv[i], "-f") == 0 ) {
            i++;
            disp = real;
        } else if ( strcmp(argv[i], "-r") == 0 ) {
            i++;
            disp = raw;
        } else if ( strcmp(argv[i], "-c") == 0 ) {
            i++;
            disp = calibrated;
        } else if ( strcmp(argv[i], "-b") == 0 ) {
            i++;
            disp = bytes;
        } else if ( strcmp(argv[i], "-s") == 0 ) {
            i++;
            disp = scaled;
        } else if ( strcmp(argv[i], "-h") == 0 ) {
            usage();
            return 0;
        }
    }
    if ( argc >= i+1 )
        loop = atoi(argv[i]);

    type = detect_sms();
    if ( type == unknown ) {
        fprintf(stderr, "Could not detect an SMS\n");
        return 1;
    }

    do {
        int ok = 0;
        switch ( disp ) {
            case raw:
                ok = read_sms_raw(type, &x, &y, &z);
                if ( ok )
                    printf("%d %d %d\n", x, y, z);
                break;
            case calibrated:
                ok = read_sms(type, &x, &y, &z);
                if ( ok )
                    printf("%d %d %d\n", x, y, z);
                break;
            case real:
                ok = read_sms_real(type, &fx, &fy, &fz);
                if ( ok )
                    printf("%.2f %.2f %.2f\n", fx, fy, fz);
                break;
            case scaled:
                ok = read_sms_scaled(type, &x, &y, &z);
                if ( ok )
                    printf("%d %d %d\n", x, y, z);
                break;
            case bytes:
                {
                    uint8_t *buffer;
                    int size;
                    int i;

                    buffer = read_sms_raw_bytes( type, &size );
                    if ( !buffer )
                        break;
                    printf("%d bytes:\n", size);
                    for ( i = 0; i < size; i++ ) {
                        printf("%02x ", buffer[i]);
                        if ( i % 8 == 7 )
                            printf("\n");
                    }
                    if ( i % 8 > 0 )
                        printf("\n");
                    free(buffer);
                }
            default:
                return -2;
        }
        fflush(stdout);
        if ( !ok )
            fprintf(stderr, "no co-ordinates!\n");
        if ( loop ) usleep(loop*1000);
    } while ( loop );

    return 0;
}
