<div align="center">
  <h1>RevLink</h1>
</div>
RevLink is simple reverse shell (for now) written in C, it uses winsock to establish a connection to the attacker, it access the PEB to get the base of NTDLL and resolves the needed functions during runtime. also it uses another know AV evading techniques which is string encoding/hashing.

## Usage
### Linux
make sure you have python and the GNU C++ compiler\
(x86_64-w64-mingw32-g++) installed, you can compile it using the Makefile as shown below:
```
make port=<port> ip=<ip address>
```
### Windows
make sure you have python and the GNU C++ compiler\
(x86_64-w64-mingw32-g++) installed, you can compile it using the batch file as shown below:
```
win.bat <port> <ip address>
```
\
the final executable can be found in the bin folder.
\
## Project Ideas & Contributions

Pull requests are welcome. For any changes.