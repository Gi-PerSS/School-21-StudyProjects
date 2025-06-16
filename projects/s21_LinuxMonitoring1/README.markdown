# Linux Monitoring v1.0

A set of Bash scripts for system and filesystem monitoring on Ubuntu Server 20.04 LTS.

## Features
- **Script 1**: Takes one text parameter, outputs it, errors if parameter is a number.
- **Script 2**: Displays system info (hostname, timezone, user, OS, date, uptime, IP, memory, disk space) and optionally saves to a timestamped file.
- **Script 3**: Enhances Script 2 with colored output (4 parameters for background/font colors, 1-6: white, red, green, blue, purple, black).
- **Script 4**: Extends Script 3, reads colors from a config file, uses defaults if unset, displays color scheme.
- **Script 5**: Analyzes a directory (path as parameter), outputs folder/file counts, top 5 largest folders, top 10 largest files, top 10 executables with MD5 hashes, and execution time.

## Technical Details
- Scripts in `src/0x` folders, main script named `main.sh`.
- Decomposed into multiple files, with input validation.
- Run on Ubuntu Server 20.04 LTS VM.
- Color validation ensures non-matching font/background.

[Русская версия README](README_RUS.md)