# Scanner

A simple C++ project that scans files for potential viruses by comparing their MD5 hashes with a known database. The project uses OpenSSL to compute MD5 hashes and checks them against a CSV database of known malicious file hashes.  

The scanner helps quickly identify suspicious files based on hash matches, providing a lightweight

## Features

- Computes MD5 hashes of files using OpenSSL  
- Compares hashes with a CSV database of known malicious files  
- Lightweight and fast detection method  
- Cross-platform support (Linux, Windows) 

## Requirements

- C++20 or higher  
- CMake 3.16 or higher  
- Compiler: GCC, Clang, or MSVC  
- OpenSSL: 3.6.0 

## Installation
	mkdir build
	cd build
	cmake ..
	cmake --build .
## Usage
	Usage: scanner [--path <dir>] [--log <file>] [--base <file>]

Options:
  - -- **path** –   Path to directory to scan (recursive).
  - -- **log** –   Path to file where detected matches will be logged.
  - -- **base** –   Path to CSV database file with known malicious MD5 hashes.

## Example
Scan **/scan*** using database **data/malicious_hashes.csv** and write matches to **found.txt**:


scanner.exe --path /home/user/scan --base data/malicious_hashes.csv --log found.log
## CSV Database Format

The CSV file should contain MD5 hashes (optionally with metadata). Simple accepted formats:

d41d8cd98f00b204e9800998ecf8427e;unknown-malware
5d41402abc4b2a76b9719d911017c592;known-trojan

## Logging & Output

Each matched file is appended to the log file specified by --log.
A typical log:
Path of the detected virus : <path>
Hash                       : <hash>
Verdict                    : <verdict>

- **Path** – full path of the detected file  
- **Hash** – computed MD5 hash of the file  
- **Verdict** – status based on the hash comparison (e.g., Green, Red, etc.)

## Repository

The source code of this project is available on GitHub. 

**GitHub link:** [https://github.com/andsukhikh/scanner](https://github.com/andsukhikh/scanner)