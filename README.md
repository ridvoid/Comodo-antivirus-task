# Comodo-antivirus-task



You need to develop simple malware detector.




## Scanner



Scanner is core component implemented as shared library (DLL). Scanner component must be able to:


* Scan file by path

* Scan array of bytes

* Load signatures file



Implement appropriate methods in the scanner interface.
 Malware detection algorithm is the following: 

if scanned file contains any of predefined byte sequences, it is considered infected.
The sequences are stored in the regular text file separated by newlines, in the following format: HexString.{GUID}




### Examples:



*01ABEDFF55.{ab306a70-0fd2-4b4b-84fe-f9ebd899d90f}*


*EE21DEAD827739ACCD028FFC.{5c34b10f-3f6d-4bbb-b9ec-2faa1ee07660}*



If appropriate sequence is found, scanner must return its GUID. Use file mapping to increase scanning performance.




## Client



Client is UI or console application. Client application must be able to:


* Uses Scanner component to recursively scan specific folder.

* Scanning progress must be displayed.
* Scanning must be performed in the thread pool (2 threads per CPU core).




## Bonus tasks (optional)



* Use modern C++11, C++14

* Implement Scanner and Client as separate processes with an IPC.

* Implement Scanner component as COM object in an in-process or out-of-process COM server using ATL. Use ATL classes in Client application.

* Unit tests for Scanner classes.

You are free to refer to any documentation/internet etc.

Task estimated time: 1 — 2 days.




# Implemented


* MS VC++ 2015

* STL

* NamedPipe
* IoCompletionPort

* Asynchrony and multithreading

* Mapped files




## Server


The Server.exe, Dll.dll, and Signatures.txt files must be in the same directory. 
The signature file must be in Ansi encoding.




## Client


To scan, you must pass the path to the directory when starting. Example: "Client.exe C:\Windows".



Files are scanned: exe, dll, sys, drv, ocx, bat, bin, cmd, com, cpl, inf, pif, vb, vbe, vbs, vbscript, ws, wsf, dat.




Implementation time two days.