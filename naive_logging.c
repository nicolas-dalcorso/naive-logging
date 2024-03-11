/*
    Implements the necessary structures and functions for a simple logging system

    The logging system is based on the following principles:
    - The log messages are written to a file
    - The log messages are timestamped
    - The log messages have a level of importance

    The log levels are:
    - DEBUG
    - INFO
    - WARNING
    - ERROR
    - FATAL

    The log messages are written to a file in the following format:
        `[l=level | dt=timestamp] message`

    
    ---

    nrdc
    2021-08-10
    v0.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//  Constants definitions
char* DEFAULT_LOG_FILE      = "./log/psdb_interface.log";
#define LOG_LEVEL_DEBUG     1
#define LOG_LEVEL_INFO      2
#define LOG_LEVEL_WARNING   3
#define LOG_LEVEL_ERROR     4
#define LOG_LEVEL_FATAL     5

/*
    Naive logging implementation
*/
char* DEFAULT_LOG_SESSION_INIT_STR = "Logging session started at %s\n";
char* DEFAULT_LOG_SESSION_FINISH_STR = "Logging session finished at %s\n";
char* DEFAULT_LOG_MESSAGE_STR = "[l=%d | dt=%s] %s\n";

/*
    Function: existsLogFile
    ----------------------------
    Checks if a log file exists.

    logFile: the file to check

    returns: 1 if the file exists, 0 otherwise
*/
int existsLogFile(char* logFile){
    FILE *file = fopen(logFile, "r");
    if (file == NULL){
        return 0;
    }
    fclose(file);
    return 1;
}

int mklogfile(char* logFile){
    if(!existsLogFile(logFile)){
        FILE *file = fopen(logFile, "w");
        if (file == NULL){
            return 0;
        }
        fclose(file);
    }
    return 1;
}

/*
    Function: setLoggingStrings
    ----------------------------
    Sets the default logging strings for the logging system.

    session_init: the string to be used when initializing the logging session
    session_end: the string to be used when finishing the logging session
    message_format: the string to be used when formatting the log message
*/
void setLoggingStrings(char* session_init, char* session_end, char* message_format){
    strcpy(DEFAULT_LOG_SESSION_INIT_STR, session_init);
    strcpy(DEFAULT_LOG_SESSION_FINISH_STR, session_end);
    strcpy(DEFAULT_LOG_MESSAGE_STR, message_format);
}


/*
    Function: getTimestampNow
    ----------------------------
    Returns a pointer to a string with the current timestamp by calling the time() function.
*/
char* getTimestampNow(){
    //  Allocate memory for the timestamp
    char* timestamp  = (char*)malloc(32);

    //  Get the current time
    time_t ltime;
    ltime=time(NULL);
    struct tm *tm;
    tm=localtime(&ltime);

    //  Format the timestamp
    sprintf(timestamp, "%d-%d-%d %d:%d:%d", tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);


    return timestamp;
};

/*  
    Function: initializeLoggingSession
    ----------------------------
    Initializes the logging session by opening the log file
    and inserting the current timestamp.
*/
void initializeLoggingSession(){
    mklogfile(DEFAULT_LOG_FILE);

    FILE *file = fopen(DEFAULT_LOG_FILE, "a");

    if (file == NULL){
        printf("Error opening file!\n");
        exit(1);
    }

    char* timestamp  = getTimestampNow();
    fprintf(file, "Logging session started at %s\n", timestamp);
    free(timestamp);

    fclose(file);
};

/*
    * Function: finishLoggingSession
    * ----------------------------
    * Finishes the logging session by opening the log file
    * and inserting the current timestamp.
    * 
*/
void finishLoggingSession(){
    FILE *file = fopen(DEFAULT_LOG_FILE, "a");

    if (file == NULL){
        printf("Error opening file!\n");
        exit(1);
    }

    char* timestamp  = getTimestampNow();
    fprintf(file, "Logging session finished at %s\n", timestamp);
    free(timestamp);

    fclose(file);
};

/*
    * Function: logMessage
    * ----------------------------
    * Logs a message to a file.
    *
    *   message: the message to be logged
    *   logFile: the file to log the message
*/
void logMessage(char* message, char* logFile){
    FILE *file = fopen(logFile, "a");

    if (file == NULL){
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(file, "%s\n", message);

    fclose(file);
};

/*
    * Function: getLogMessage
    * ----------------------------
    * Returns a pointer to a string with the log message.
    *
    *   level: the level of the message
    *   message: the message to be logged
    *
    *   returns: a pointer to a string with the log message
*/
char* getLogMessage(int level, char* message){
    char* logMessage = (char*)malloc(1000);
    char* timestamp  = getTimestampNow();

    sprintf(logMessage, "[l=%d | dt=%s] %s", level, timestamp,message);

    free(timestamp);

    return logMessage;
};


/*
    * Function: debug
    * ----------------------------
    * Logs a debug message to the default log file.
    *
    *   message: the message to be logged
*/
void debug(char* message){
    logMessage(getLogMessage(LOG_LEVEL_DEBUG, message), DEFAULT_LOG_FILE);
};

/*
    * Function: info
    * ----------------------------
    * Logs an info message to the default log file.
    *
    *   message: the message to be logged
*/
void info(char* message){
    logMessage(getLogMessage(LOG_LEVEL_INFO, message), DEFAULT_LOG_FILE);
};


/*
    * Function: error
    * ----------------------------
    * Logs an error message to the default log file.
    *
    *   message: the message to be logged
*/
void error(char* message){
    logMessage(getLogMessage(LOG_LEVEL_ERROR, message), DEFAULT_LOG_FILE);
};

/*
    * Function: warning
    * ----------------------------
    * Logs a warning message to the default log file.
    *
    *   message: the message to be logged
*/
void warning(char* message){
    logMessage(getLogMessage(LOG_LEVEL_WARNING, message), DEFAULT_LOG_FILE);
};

/*
    * Function: fatal
    * ----------------------------
    * Logs a fatal message to the default log file.
    *
    *   message: the message to be logged
*/
void fatal(char* message){
    logMessage(getLogMessage(LOG_LEVEL_FATAL, message), DEFAULT_LOG_FILE);
};

// NAIVE_LOGGING_C
// Path: modules/psdb_interface.c


//  Usage
int main(){
    char* logFile = "./log/logs.log";
    setLoggingStrings("Logging session started at %s", "Logging session finished at %s", "[l=%d | dt=%s] %s");
    initializeLoggingSession();


    debug("Debug message");
    info("Info message");
    error("Error message");
    warning("Warning message");
    fatal("Fatal message");

    
    finishLoggingSession();
    return 0;
}