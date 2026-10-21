
/////////////////////////////////////////
//
//             Street Rod 3
//
// Copyright (C) Auxiliary Software 2002-2004
//
//
/////////////////////////////////////////
/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

/////////////////////////////////////////
// Street Rod 3 - Logging system
// Based on the original logger, 2002-2004
/////////////////////////////////////////

#include "defs.h"

FILE *fpLog = NULL;

// Write a timestamped log message.
void writeLog(char *fmt, ...)
{
    va_list arg;
    time_t now;
    struct tm *localTime;

    // Open the log on the first message.
    if(!fpLog) {
        fpLog = fopen("logfile.txt", "wt");
        if(fpLog == NULL)
            return;

        fprintf(fpLog,
                "Street Rod 3 Log file\n"
                "---------------------\n\n");
    }

    now = time(NULL);
    localTime = localtime(&now);

    if(localTime != NULL) {
        fprintf(fpLog,
                "[%04d-%02d-%02d %02d:%02d:%02d] ",
                localTime->tm_year + 1900,
                localTime->tm_mon + 1,
                localTime->tm_mday,
                localTime->tm_hour,
                localTime->tm_min,
                localTime->tm_sec);
    } else {
        fprintf(fpLog, "[time unavailable] ");
    }

    va_start(arg, fmt);
    vfprintf(fpLog, fmt, arg);
    va_end(arg);

    fflush(fpLog);
}

// Close the log file.
void closeLog(void)
{
    if(fpLog)
        fclose(fpLog);

    fpLog = NULL;
}
