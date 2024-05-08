# CompanyPersonnelManager
This program manages a dynamic list of company personnel, including owners, managers, and laborers. It features advanced functionalities like searching, adding, removing, and calculating salary averages, demonstrating file I/O for data persistence.

# Company Personnel Manager

## Overview
This repository contains the source code for the Company Personnel Manager, a detailed program designed to handle different types of personnel in a company, such as owners, managers, and laborers. This project builds upon earlier work and includes additional functionalities to enhance data management and processing.

Output Screenshots: [Pg1](https://i.postimg.cc/tCYvWX9v/screenshot1.png) [Pg2](https://i.postimg.cc/260TLtMf/screenshot2.png) [Pg3](https://i.postimg.cc/W10nwzC8/screenshot3.png) [Pg4](https://i.postimg.cc/CxpC5Y5q/screenshot4.png) [Pg5](https://i.postimg.cc/zGpkc6DH/screenshot5.png)

## Features
- **Add Person**: Add new personnel to the system, categorizing them as laborers, managers, or owners with specific attributes.
- **Delete Person**: Remove a person from the system by their name.
- **Find Person**: Search for a person by name and display their detailed information.
- **Show All Persons**: Display information for all entries in the system.
- **Calculate Averages**: Compute and display the average earnings for each category of personnel.
- **Quit**: Safely exit the program and save all data to a file.

## File Structure
- `main.cpp`: The main application code includes the logic for menu options and handling of different personnel types.
- `Person.h`: Definition of the base class Person and derived classes (Laborer, Manager, Owner).
- `data.txt`: Data file where personnel information is stored and retrieved upon program startup.
