# Lab_Network
# TFTP Client in C

This is a simple TFTP client implemented in C that supports file upload (`puttftp`) and download (`gettftp`) operations.

## Features

- **gettftp:** Download a file from the TFTP server.
- **puttftp:** Upload a file to the TFTP server.

## Prerequisites

- C compiler (e.g., gcc)
- Unix-like environment (Linux, macOS)

## How to Use

1. **Compile the Code:**

   ```bash
   gcc puttftp.c -o puttftp
   gcc gettftp.c -o gettftp
