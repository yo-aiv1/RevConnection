<div align="center">
  <h1>RevLink</h1>
</div>
RevConnection is an undetectable reverse shell written in C for Windows. It uses sockets to establish a connection to the attacker. And for evading detection I used the PEB structure to get the base of NTDLL and resolve the needed functions during runtime. I also used some other AV-evading techniques such as string encoding and API hashing.

<img src="assets/screenshot.png" alt="My cool logo" width="70%"/>


**Prerequisites:**
-   Python (Make sure you have a recent version installed. You can check by running `python --version` in your terminal)
-   C++ compiler (For Linux C++ cross compiler x86_64-w64-mingw32-g++)

#### Linux
1.  Clone the repository.
1.  Open a terminal in the project directory.
2.  Run the following command, replacing `<port>` with the desired port number and `<ip address>` with the IP address to bind to:
```
make port=<port> ip=<ip address>

```
This will compile the project and create an executable in the "bin" folder.

#### Windows
1.  Download and install the GNU Compiler Collection (GCC) for Windows from [winlibs]([https://gcc.gnu.org/install/](https://winlibs.com/#download-release)). Make sure to add the installation directory to your system path environment variable during installation.
2.  Open a command prompt in the project directory.
3.  Run the following command, replacing `<port>` with the desired port number and `<ip address>` with the IP address to bind to:
```
win.bat <port> <ip address>

```

This will compile the project and create an executable in the "bin" folder.

## Project Ideas & Contributions

Pull requests are welcome. For any changes.
