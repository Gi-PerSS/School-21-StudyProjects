# Linux Monitoring v2.0

A project for real-time Linux system monitoring and log analysis using Bash scripts, GoAccess, Prometheus, and Grafana on Ubuntu Server 20.04 LTS.

## Features
- **Script 1**: Generates folders and files with specified names, sizes, and structure; logs details; stops at 1GB free space.
- **Script 2**: Creates folders/files across the filesystem (excluding bin/sbin) with random counts; logs details; stops at 1GB free space.
- **Script 3**: Cleans filesystem using logs, date/time range, or name mask.
- **Script 4**: Generates 5 nginx log files (combined format, 100-1000 daily entries) with random IPs, response codes, methods, URLs, and agents.
- **Script 5**: Parses nginx logs with awk, outputting sorted response codes, unique IPs, error requests, or error IPs based on parameter.
- **Script 6**: Uses GoAccess to analyze nginx logs, providing web interface output.
- **Script 7**: Sets up Prometheus and Grafana, monitors CPU, memory, disk, and I/O; tests with stress and script from Part 2.
- **Script 8**: Installs Node Exporter dashboard, tests disk, memory, CPU, and network load with iperf3 on a second VM.
- **Script 9 (Optional)**: Custom node_exporter script/program generating Prometheus-compatible HTML, updated every 3s, tested as in Part 7.

## Technical Details
- Scripts in `src/0x` folders, main script named `main.sh`.
- Decomposed, with input validation, run on Ubuntu Server 20.04 LTS VM.
- Logs and monitoring tools configured for real-time analysis.

[Русская версия README](README_RUS.md)