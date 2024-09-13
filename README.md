# PrimeFinder Application

[![Build](https://github.com/mitchcamza/PrimeFinder/actions/workflows/build.yml/badge.svg)](https://github.com/mitchcamza/PrimeFinder/actions/workflows/build.yml)

## Overview

**PrimeFinder** is a multithreaded Qt application that finds prime numbers within a user-defined range. The user can specify the range of numbers to search for primes, as well as the number of threads that will perform the task concurrently. This project demonstrates manual thread management in Qt using `QThread` and worker objects (`PrimeFinder`).

The application also allows users to stop the threads mid-execution, and it handles proper cleanup and thread management upon completion or interruption.

---

## Features

- **Multithreaded Prime Calculation**: The application supports up to 4 concurrent threads to divide the task of finding prime numbers over a user-specified range.
- **Customizable Input**: Users can specify the starting number, ending number, and the number of threads.
- **Real-Time Output**: The application displays primes found by each thread in its respective output window.
- **Stop Functionality**: Users can stop the execution of threads mid-process, and the application ensures proper cleanup.
- **Thread Management**: Threads are created, started, and managed manually using `QThread` and custom worker objects (`PrimeFinder`).
- **Cross-Platform**: Built with Qt, the application runs on Windows, macOS, and Linux.

![alt text](<Screenshot 2024-09-08 at 15.19.15.png>)
---

## How It Works

1. **Start the Application**: Specify the starting number, ending number, and the number of threads.
2. **Display Results**: Each thread is assigned a portion of the range and outputs the prime numbers it finds in real-time.
3. **Stop Threads**: At any point, the user can press the "Stop" button to halt the execution of all threads.
4. **Automatic Cleanup**: The application ensures that all threads are stopped and resources are properly cleaned up when the application is closed or stopped.

---

## Installation & Build

To build and run this application, follow these steps:

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/your-username/PrimeFinder.git
    cd PrimeFinder
    ```

2. **Install Dependencies**:
   Ensure that you have the Qt framework installed. If not, you can download it from the official Qt website.

3. **Build the Project**:
   Open the project in Qt Creator, or use the following commands to build it using CMake:
   
   ```bash
   mkdir build
   cd build
   cmake ..
   make

4. **Run the Application**:
    ```bash 
    ./PrimeFinder
    ```

## Usage

### Interface
- **Start Number**: Specify the number from which to begin the search for primes.
- **End Number**: Specify the last number in the range to search for primes.
- **Number of Threads**: Choose the number of threads to use (1 to 4).
- **Start Button**: Begins the prime number search.
- **Stop Button**: Stops the threads before they finish naturally.

### Example
1.	Enter the range (e.g., Start: 1, End: 1000).
2.	Select the number of threads (e.g., 2).
3.	Click **Start** to begin finding prime numbers.
4.	The results will appear in the text boxes, with each thread displaying its results in a separate window.
5.	Press **Stop** to halt execution early.

## Project Structure
The repository is organized as follows:
```
PrimeFinder/
│
├── src/
│   ├── main.cpp
│   ├── widget.cpp
│   ├── widget.h
│   ├── primefinder.cpp
│   └── primefinder.h
│
├── CMakeLists.txt
└── README.md
```

## License
This project is licensed under the MIT License. See the [LICENSE](https://github.com/mitchcamza/PrimeFinder/blob/main/LICENSE) file for details.

## Author
Mitch Campbell

[LinkedIn](https://www.linkedin.com/in/mitch-campbell-93b18919b/)
