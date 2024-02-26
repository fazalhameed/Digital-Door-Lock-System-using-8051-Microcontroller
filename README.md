# Digital-Door-Lock-System-using-8051-Microcontroller



## OverView
Welcome to the Digital Door Lock System project! This advanced security system employs a keypad for secure password entry and an LCD for clear status updates. The project is designed to offer a sophisticated, user-friendly solution for access control, leveraging EEPROM memory to retain password integrity and servo motors for physical engagement of the lock mechanism. Our goal is to enhance security measures and provide peace of mind through a reliable and efficient digital door lock system.

## Introduction
This digital door lock system is an innovative security solution that combines convenience and reliability. It is designed to offer a secure method of access control for residential and commercial settings. The system features a keypad for password entry, an LCD for displaying status messages, and a servo motor to actuate the locking mechanism.

## Features
 Automatic Password Initialization: Upon first use, the system generates a unique 6-digit password using the rand() function, which is then printed on the product package and stored in EEPROM to ensure consistency.

 Interactive LCD Display: The LCD prompts users to “Enter password” and displays the input in real-time, providing clear feedback during operation.

 Servo Motor Door Control: A correct password entry triggers the servo motor to rotate from 0 to 180 degrees, unlocking the door, while a countdown timer indicates the time until relocking.

 Security Countermeasures: The system tracks incorrect password attempts and disables input after five consecutive errors, requiring factory intervention to reset.
 
 Password Customization: A long press of the ON/C key allows users to change their password after verifying the old one, enhancing security and user control.

## Operational States
The system’s logic is governed by a state machine with states including NEW_DEVICE, ENTER_PASS, DISABLED, and NEW_PASS. This approach ensures a structured and manageable codebase.

## Security and Recovery
To maintain security, the system does not transmit new passwords externally. In case of a system reset or power loss, the EEPROM preserves the password, and a reserved memory location in the microcontroller’s flash memory helps identify if the device is new or has been previously programmed.
