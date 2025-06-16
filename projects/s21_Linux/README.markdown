# UNIX/Linux Basics

A project focused on installing and administering a Linux system (Ubuntu 20.04 Server LTS) with basic system administration tasks.

## Features
- Install Ubuntu 20.04 Server LTS (no GUI) on VirtualBox.
- Create a new user and add to `adm` group.
- Configure network: set hostname, timezone, static IP, gateway, DNS; verify with pings to 1.1.1.1 and ya.ru.
- Update system packages to the latest version.
- Enable `sudo` for the created user and change hostname.
- Set up automatic time synchronization.
- Install and use text editors (VIM + two others) to create/edit files.
- Configure SSHd service on port 2022 with autostart.
- Use `top` and `htop` to monitor system resources.
- Analyze disk info with `fdisk`, `df`, `du`, and `ncdu`.
- View system logs (`dmesg`, `syslog`, `auth.log`) and track SSHd restart.
- Schedule `uptime` command every 2 minutes with CRON and clean up tasks.

## Technical Details
- Report in `src/report.md` with screenshots and explanations for each task.
- Commands executed in terminal, adhering to Linux administration practices.
- No GUI; all tasks performed via CLI.

[Русская версия README](README_RUS.md)