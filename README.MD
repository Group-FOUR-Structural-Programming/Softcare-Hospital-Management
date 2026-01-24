# SMARTCARE HOSPITAL MANAGEMENT SYSTEM

## Overview

SMARTCARE is a comprehensive hospital management system that combines a command-line interface (CLI) backend written in C with a web-based patient portal built using Node.js and Express. The system enables efficient management of hospital operations, including patient registration, staff management, appointments, medical records, and billing.

## Features

### C Backend (CLI)
- **Patient Management**: Register, view, update, and delete patient records
- **Staff Management**: Manage hospital staff information and credentials
- **Appointments**: Schedule and manage patient appointments
- **Medical Records**: Add, view, and update patient medical history with costs
- **Billing System**: Track and manage patient charges and payments
- **Authentication**: Secure login system for staff access

### Node.js Web Frontend (Patient Portal)
- **Patient Registration**: Self-registration for new patients
- **Patient Login**: Secure authentication for existing patients
- **Dashboard**: View personal profile, appointments, and medical records
- **Profile Management**: Update personal information and change passwords
- **Real-time Data**: Access to current charges and medical history

## Architecture

### System Connection
The C and Node.js programs are seamlessly connected through shared data files stored in the `C source files` directory. Both applications read from and write to the same text-based data files, ensuring data consistency across the entire system:

- **`patients.txt`**: Stores patient information (name, age, gender, contact, username, password, totalDueCharges)
- **`appointments.txt`**: Contains appointment details (username, date, time, doctor)
- **`medical_records.txt`**: Holds medical history (username, diagnosis, treatment, cost) - uses pipe (|) delimiter for multi-word entries
- **`staff.txt`**: Staff credentials and information
- **`users.txt`**: Additional user data

This shared file approach allows:
- **Data Synchronization**: Changes made in the C CLI are immediately reflected in the web portal
- **No Database Dependency**: Simple file-based storage for easy deployment and backup
- **Cross-Platform Compatibility**: Text files work across different operating systems
- **Concurrent Access**: Both applications can access data simultaneously (with appropriate file locking considerations)

### Frontend Scope
The web frontend is exclusively a **patient's portal** designed for patient self-service. It does NOT provide administrative functions or staff access. Patients can:
- Create accounts and manage their profiles
- View their medical information and appointment history
- Access billing information
- Update contact details and passwords

All administrative and management tasks must be performed through the C CLI application by authorized hospital staff.

## Technologies Used

- **Backend**: C programming language
- **Web Server**: Node.js with Express.js
- **Frontend**: HTML5, CSS3, JavaScript (Vanilla JS with Fetch API)
- **Data Storage**: Text files (space-separated and pipe-separated formats)
- **Build System**: GCC compiler for C code
- **Package Management**: npm for Node.js dependencies

## Installation and Setup

### Prerequisites
- GCC compiler (for C code compilation)
- Node.js (version 14 or higher)
- npm (comes with Node.js)

### Setup Steps

1. **Clone or Download the Project**
   ```
   cd path/to/your/projects
   # Place the smartcare_system folder here
   ```

2. **Compile C Code**
   ```
   cd smartcare_system
   gcc -o smartcare *.c
   ```

3. **Setup Node.js Web Server**
   ```
   cd "Web Front"
   npm install
   ```

4. **Run the Applications**
   - **C CLI**: `./smartcare` (Linux/Mac) or `smartcare.exe` (Windows)
   - **Web Portal**: `npm start` then open http://localhost:3000

## Usage

### For Hospital Staff
1. Run the C executable
2. Login with staff credentials
3. Use the menu system to manage patients, appointments, records, and billing

### For Patients
1. Open web browser to http://localhost:3000
2. Register a new account or login with existing credentials
3. Access dashboard to view personal information
4. Use profile page to update information

## Data File Formats

### patients.txt
```
Name Age Gender Contact Username Password TotalDueCharges
```

### appointments.txt
```
Username Date Time Doctor
```

### medical_records.txt
```
Username|Diagnosis|Treatment|Cost
```

## Security Considerations

- Passwords are stored in plain text (consider hashing for production)
- File-based storage may have concurrency issues with multiple simultaneous writes
- No session management in web portal (basic implementation)
- Access control is minimal - enhance for production use

## Future Enhancements

- Database integration (SQLite/PostgreSQL)
- User authentication with JWT tokens
- Role-based access control
- Encrypted data storage
- RESTful API improvements
- Mobile-responsive design
- Email notifications for appointments

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make changes and test thoroughly
4. Ensure data consistency between C and web components
5. Submit a pull request

## License

This project is for educational purposes. Please ensure compliance with local data protection regulations when handling patient information.

## Support

For issues or questions:
- Check data file formats and permissions
- Ensure both C and Node.js applications have read/write access to data files
- Verify file paths in source code match your system structure
