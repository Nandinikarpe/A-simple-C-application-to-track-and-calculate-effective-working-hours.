# A-simple-C-application-to-track-and-calculate-effective-working-hours.
# Work Hours Tracker

A simple C application to track and calculate effective working hours.

## Features

- Start and end work sessions
- Record descriptions for each work session
- Calculate total work hours
- Persist data between program executions

## Compilation

### Windows

You have several options to compile this program on Windows:

#### Option 1: Using MinGW (GCC for Windows)
1. Download and install [MinGW](https://mingw-w64.org/downloads/) or [MSYS2](https://www.msys2.org/)
2. Add MinGW bin directory to your PATH
3. Compile with:
   ```
   gcc -Wall -o work_hours_tracker work_hours_tracker.c
   ```

#### Option 2: Using Visual Studio
1. Open a Developer Command Prompt for Visual Studio
2. Navigate to the project directory
3. Compile with:
   ```
   cl work_hours_tracker.c
   ```

#### Option 3: Using an online compiler
1. Copy the code from `work_hours_tracker.c`
2. Paste it into an online C compiler like [OnlineGDB](https://www.onlinegdb.com/)
3. Compile and run online (note: file saving functionality won't work in online compilers)

### Linux/macOS

To compile the program, use the provided Makefile:

```
make
```

Or compile directly with:

```
gcc -Wall -o work_hours_tracker work_hours_tracker.c
```

To clean the compiled files:

```
make clean
```

## Usage

Run the program:

```
./work_hours_tracker    # On Linux/macOS
work_hours_tracker.exe  # On Windows
```

### Menu Options

1. **Start new work session**: Records the current time as the start of a work session and allows you to enter a description.
2. **End current work session**: Records the current time as the end of the latest work session and calculates the duration.
3. **View total work hours**: Displays a list of all work sessions and calculates the total effective working hours.
4. **Exit**: Exits the program.

## Data Storage

Work session data is stored in a file named `work_sessions.dat` in the current directory. This allows your work sessions to persist between program executions. 
