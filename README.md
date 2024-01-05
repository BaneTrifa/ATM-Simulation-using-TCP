
# Simulating ATM using TCP

The goal of this project is to simulate ATM (client-server model) using TCP and SQLite.

## Prerequisite

                1. Installing sqlite3: 
                            sudo apt update
                            sudo apt upgrade
                            sudo aptinstall sqlite3
                2. Install SQLite C library that implements an SQL database engine: 
                            sudo apt-get install libsqlite3-dev


## Description
    
In the project, 2 sides are implemented, server-side and client-side. The idea is for each side to run on a separate workstation, but for testing purposes, they can be run on the same workstation.
In this case, the server-side simulates a bank server where client data and their accounts are stored. Meanwhile, the client-side simulates an ATM.

## Run applications
    SERVER SIDE:
          1. Position yourself to /server/src/ directory
          2. Open terminal and run 'make' command
          3. Run ./server 
    CLIENT SIDE:
          1. Position yourself to /client/src/ directory
          2. Open terminal and run 'make' command
          3. Run ./client

## Demonstration of functionalities  
    0. When you run client side, on server terminal by ATM number will be flag "1".
    
![1asd](https://github.com/BaneTrifa/ATM-Simulation-using-TCP/assets/88882867/5b350a20-aa07-4b0e-9829-d59783d81616)

    1. Logging in: You can log in with either your username or card number. 
       If you enter an incorrect password, a log for the incorrect password attempt is printed on the server side.
       The server is located in the upper-right window, while clients are in the other three windows.
       
![2sds](https://github.com/BaneTrifa/ATM-Simulation-using-TCP/assets/88882867/bfb2b01e-7016-4295-8493-e1c97bf47553)

    2. Optinios: After successful login, options offered by the ATM are displayed.
       I won't reveal any of the options here; I'll leave that for you to discover :)
    
![3sdfsd](https://github.com/BaneTrifa/ATM-Simulation-using-TCP/assets/88882867/36c1a29d-df54-4439-844c-867eb1a32333)



## Author

- [@BrankoTrifkovic](https://www.linkedin.com/in/branko-trifkovic/)


