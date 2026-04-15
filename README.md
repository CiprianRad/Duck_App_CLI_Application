A C++ application designed to manage swimming competitions. This project demonstrates the use of Object-Oriented Programming (OOP) principles—including inheritance, encapsulation, and polymorphism—to handle participants, events, and results.

## Features
Participant Management: Tracks athletes and their specific details.

Event Handling: Organizes various swimming styles and distances.

Result Processing: Calculates and displays rankings based on performance.

Modular Design: Built with clear separation between headers (.h) and implementation files (.cpp).

## Project Structure
The repository is organized into several key components:

main.cpp: The entry point of the application.

Participant.h / .cpp: Defines the base class for competition entries.

Proba.h / .cpp: Handles the logic for specific swimming events.

Concurs.h / .cpp: The orchestrator class that manages the overall flow of the competition.

## Getting Started
### Prerequisites
You will need a C++ compiler supporting at least C++11 (such as GCC, Clang, or MSVC).

### Compilation
To compile the project using G++, navigate to the root directory and run:

Bash
g++ -o natatie main.cpp Participant.cpp Proba.cpp Concurs.cpp
### Running the Application
After compilation, execute the generated binary:

Bash
./natatie
## Usage Example
Upon running the program, the system will typically:

Initialize a list of participants.

Assign participants to specific swimming events (e.g., 100m Freestyle).

Output the sorted results or specific participant details to the console.

## Technical Concepts Used
Classes and Objects: Modeling real-world entities.

Constructors/Destructors: Efficient memory and resource management.

Pointers and References: For handling dynamic data structures.

Standard Template Library (STL): Likely utilized for data storage (e.g., std::vector or std::string).

## License
This project is open-source. Feel free to use and modify it for educational purposes.
