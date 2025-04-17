#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SESSIONS 100
#define FILENAME "work_sessions.dat"

typedef struct {
    time_t start_time;
    time_t end_time;
    char description[100];
} WorkSession;

WorkSession sessions[MAX_SESSIONS];
int session_count = 0;

// Function to save sessions to file
void save_sessions() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Error: Could not open file for saving data.\n");
        return;
    }
    
    fwrite(&session_count, sizeof(int), 1, file);
    fwrite(sessions, sizeof(WorkSession), session_count, file);
    fclose(file);
    printf("Sessions saved successfully.\n");
}

// Function to load sessions from file
void load_sessions() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("No previous sessions found. Starting fresh.\n");
        return;
    }
    
    fread(&session_count, sizeof(int), 1, file);
    fread(sessions, sizeof(WorkSession), session_count, file);
    fclose(file);
    printf("Loaded %d previous sessions.\n", session_count);
}

// Function to start a new work session
void start_session() {
    if (session_count >= MAX_SESSIONS) {
        printf("Error: Maximum number of sessions reached.\n");
        return;
    }
    
    sessions[session_count].start_time = time(NULL);
    sessions[session_count].end_time = 0; // Not finished yet
    
    printf("Enter a brief description for this work session: ");
    scanf(" %[^\n]", sessions[session_count].description);
    
    printf("Work session started at %s", ctime(&sessions[session_count].start_time));
    session_count++;
    save_sessions();
}

// Function to end the current work session
void end_session() {
    if (session_count == 0) {
        printf("No active sessions to end.\n");
        return;
    }
    
    int latest_session = session_count - 1;
    
    // Check if the session is already ended
    if (sessions[latest_session].end_time != 0) {
        printf("The latest session is already completed.\n");
        return;
    }
    
    sessions[latest_session].end_time = time(NULL);
    printf("Work session ended at %s", ctime(&sessions[latest_session].end_time));
    
    double duration = difftime(sessions[latest_session].end_time, sessions[latest_session].start_time);
    printf("Session duration: %.2f hours (%.0f minutes)\n", duration / 3600, duration / 60);
    
    save_sessions();
}

// Function to calculate and display total work hours
void display_total_hours() {
    if (session_count == 0) {
        printf("No work sessions recorded yet.\n");
        return;
    }
    
    double total_seconds = 0;
    printf("\n%-4s %-20s %-20s %-10s %s\n", "No.", "Start Time", "End Time", "Hours", "Description");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < session_count; i++) {
        char start_str[30], end_str[30];
        double duration;
        
        strftime(start_str, sizeof(start_str), "%Y-%m-%d %H:%M:%S", localtime(&sessions[i].start_time));
        
        if (sessions[i].end_time == 0) {
            strcpy(end_str, "In progress");
            duration = 0;
        } else {
            strftime(end_str, sizeof(end_str), "%Y-%m-%d %H:%M:%S", localtime(&sessions[i].end_time));
            duration = difftime(sessions[i].end_time, sessions[i].start_time);
            total_seconds += duration;
        }
        
        printf("%-4d %-20s %-20s %-10.2f %s\n", i+1, start_str, end_str, duration / 3600, sessions[i].description);
    }
    
    printf("--------------------------------------------------------------------------------\n");
    printf("Total work hours: %.2f hours (%.0f minutes)\n", total_seconds / 3600, total_seconds / 60);
}

// Function to display the menu
void display_menu() {
    printf("\n--- Work Hours Tracker ---\n");
    printf("1. Start new work session\n");
    printf("2. End current work session\n");
    printf("3. View total work hours\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    
    printf("Welcome to Work Hours Tracker!\n");
    load_sessions();
    
    while (1) {
        display_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                start_session();
                break;
            case 2:
                end_session();
                break;
            case 3:
                display_total_hours();
                break;
            case 4:
                printf("Thank you for using Work Hours Tracker. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
} 