SYSTEM REQUIREMENTS
-------------------
- 32-bit version of Visual Studio 2010


INSTALLATION INSTRUCTIONS
-------------------------
This project depends on the usage of Win32 Pthreads, which is
NOT a standard library in Win32 systems. A 32-bit installation of
Visual Studio 2010 is required.

1. Copy the pthreadVCE2.dll file into
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin

2. For running AutoTester.exe, the pthreadVCE2.dll file needs to be in
in the same directory as the AutoTester.exe file. Simply copy the
pthreadVCE2.dll over to the directory where you house AutoTester.exe
or vice versa.

3. An spaconfig_sample.txt file is provided. Copy this file as
"spaconfig.txt" for a real SPA configuration file.

The spaconfig.txt file will allow you to configure
multithreading options. It must be present in the same directory
as the AutoTester binary to enable multithreading.
Multithreading is disabled by default and will be disabled if
an spaconfig.txt file is not found in the same directory as the
AutoTester binary.

The spaconfig.txt file has 2 keys, "ThreadsOn" and "MaxThreads".

ThreadsOn can be one of "Yes" or "No"
MaxThreads must be an integer, the default is 4. Maximum number of
threads that will be accepted is 8.