# Minitalk

## Overview

**Minitalk** is a client-server communication system that uses UNIX signals to transmit messages. The objective is to send strings from a client to a server, one character at a time, using `SIGUSR1` and `SIGUSR2` signals. The server receives and decodes these signals to reconstruct and display the message.

---

## Features

- **Signal-Based Communication:** Uses `SIGUSR1` and `SIGUSR2` to send each bit of a character.
- **Client-Server Model:**
  - **Server:** Starts, displays its PID, and waits for signals to decode and print messages.
  - **Client:** Sends a message to the server by converting each character into a series of signals.
- **Bonus Features:**
  - **Acknowledgment:** Server sends a confirmation signal back to the client.
  - **Unicode Support:** Handles extended characters.
- **Error Handling:** Manages invalid PIDs, empty messages, and other edge cases.
- Outputs the received message on the server side.
- **Libft Submodule:** Utilizes the `libft` library for string and memory manipulation functions.

---

## How It Works

### **Server**

1. The server starts and prints its Process ID (PID).
2. It uses `sigaction` to set up signal handlers for `SIGUSR1` and `SIGUSR2`.
3. When signals are received, it decodes them bit by bit (8 bits per character) to reconstruct the message.
4. The message is printed as it is received.

### **Client**

1. Takes two command-line arguments:
   - The server's PID.
   - The message to send.
2. Converts each character of the message into 8 bits.
3. Sends each bit as a signal:
   - `SIGUSR1` for 1.
   - `SIGUSR2` for 0.
4. Sends a null character (`\0`) to indicate the end of the message.

### **Communication**

- Each character is sent as a sequence of 8 signals (one for each bit).
- The server collects these signals, reconstructs the character, and prints it.
- `usleep` is used in the client to add a delay between signals, ensuring the server processes them correctly.

---

## Bonus Features

- **Acknowledgment:** The server sends a signal back to the client to confirm message receipt.
- **Unicode Support:** The system can handle extended characters for broader compatibility.

---

## Code Overview

- **server.c:** Sets up signal handlers using `sigaction`, decodes incoming signals, and prints the message.
- **client.c:** Converts the message into bits and sends them as signals using `kill()`.
- **server_bonus.c:** Includes acknowledgment and Unicode support.
- **client_bonus.c:** Handles acknowledgment from the server.
- **Key Functions:**
  - `sigaction`: Configures signal handlers.
  - `kill`: Sends signals to the server’s PID.
  - `pause`: Makes the client wait for acknowledgment signals.
  - `usleep`: Ensures signals are sent at a manageable pace.
- **Libft:** A submodule providing utility functions for string manipulation, memory management, and more.

---

## How to Use

### Prerequisites

- A C compiler (e.g., `gcc`).
- GNU Make.
- Git (to clone the repository and initialize the `libft` submodule).

### Setup

1. Clone the repository and initialize the `libft` submodule:

```bash
git clone --recursive https://github.com/hetzwaard/minitalk.git
```

Alternatively, if you already cloned the repository:

```bash
git submodule init
git submodule update
```

### Compilation

To compile the project, run:

```bash
make
```

For bonus features:

```bash
make bonus
```

### Usage

1. Start the server:

```bash
./server
```

Example Output: `Server PID: 12345`

2. In another terminal, run the client with the server’s PID and a message:

```bash
./client 12345 "Hello, World!"
```

The server will print: `Hello, World!`

---

## Testing

Test the program with various inputs:

```bash
./client 12345 "Test message"
./client 12345 ""  # Empty message
./client 12345 "Hello 😊"  # Unicode characters (bonus)
```

To simulate edge cases:

- Use an invalid PID.
- Send long messages to test performance.

---

## Notes

- The program assumes valid input (e.g., a correct PID and a string message).
- The server reconstructs characters by counting 8 bits and stops when it receives a null character (`\0`).
- Ensure the `libft` submodule is properly initialized before compilation.

---

## Acknowledgments

Special thanks to the 42 Network, Codam College (42 Amsterdam), and its community for inspiring this project.
