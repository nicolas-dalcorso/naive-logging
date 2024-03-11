#ifndef NAIVE_LOGGING_H
#define NAIVE_LOGGING_H
/*
    Naive logging interface
*/

//  Function prototypes

/*
    Function: existsLogFile
    Check if a log file exists
    Parameters:
        char* logFile: the file to check
    Returns:
        int: 1 if the file exists, 0 otherwise
*/
int existsLogFile(char* logFile);

/*
    Function: mklogfile
    Create a log file
    Parameters:
        char* logFile: the file to create
    Returns:
        int: 1 if the file was created, 0 otherwise
*/
int mklogfile(char* logFile);

/*
    Function: setLoggingStrings
    Set the strings for the logging session
    Parameters:
        char* session_init: the string to log when the session starts
        char* session_end: the string to log when the session ends
        char* message_format: the format for the log messages
*/
void setLoggingStrings(char* session_init, char* session_end, char* message_format);




/*
    Function: getTimestampNow
    Get the current timestamp in the format "YYYY-MM-DD HH:MM:SS"
    Returns:
        char*: the current timestamp
*/
char* getTimestampNow();


/*
    Function: initializeLoggingSession
    Initialize the logging session
    Parameters:
        char* logFile: the file to log the messages
*/
void initializeLoggingSession(char* logFile);

/*
    Function: finishLoggingSession
    Finish the logging session
*/
void finishLoggingSession();

/*
    Function: getLogMessage
    Get the log message with the timestamp and the log level
    Parameters:
        int level: the log level
        char* message: the message to log
    Returns:
        char*: the log message
*/
char* getLogMessage(int level, char* message);

/*
    Function: logMessage
    Log a message to a file
    Parameters:
        char* message: the message to log
        char* logFile: the file to log the message
*/
void logMessage(char* message, char* logFile);

//  --------------------

/*
    Function: debug
    Log a debug message (LOG_LEVEL_DEBUG)
    Parameters:
        char* message: the message to log
*/
void debug(char* message);

/*
    Function: info
    Log an info message (LOG_LEVEL_INFO)
    Parameters:
        char* message: the message to log
*/
void info(char* message);

/*
    Function: error
    Log an error message (LOG_LEVEL_ERROR)
    Parameters:
        char* message: the message to log
*/
void error(char* message);

/*
    Function: warning
    Log a warning message (LOG_LEVEL_WARNING)
    Parameters:
        char* message: the message to log
*/
void warning(char* message);

/*
    Function: fatal
    Log a fatal message (LOG_LEVEL_FATAL)
    Parameters:
        char* message: the message to log
*/
void fatal(char* message);


#endif // NAIVE_LOGGING_H