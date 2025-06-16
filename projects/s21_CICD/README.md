# Basic CI/CD

A simple CI/CD pipeline for the *SimpleBashUtils* project, handling build, test, and deployment of *s21_cat* and *s21_grep* utilities.

## Features
- Set up a GitLab Runner on an Ubuntu Server 20.04 LTS VM.
- CI stages:
  - Build: Compile *SimpleBashUtils* using Makefile, store artifacts for 30 days.
  - Style Test: Run *clang-format*, fail pipeline on style violations, display output.
  - Integration Tests: Run tests automatically if build and style pass, fail pipeline on test failures, display results.
- CD stage:
  - Deploy: Manually copy built artifacts to `/usr/local/bin` on a second Ubuntu VM using SSH/SCP, fail pipeline on errors.
- Optional: Telegram notifications via a bot reporting CI/CD stage success/failure.

## Technical Details
- Configured in `.gitlab-ci.yml`.
- Uses bash scripts for deployment.
- Saves VM image dumps (not stored in Git).

[Русская версия README](README_RUS.md)