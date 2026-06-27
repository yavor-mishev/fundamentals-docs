systemd is used to manage system and service processes on Linux operating systems. It is a suite of basic building blocks for a Linux system, providing a standard process for controlling what programs run when a Linux system boots up and during its operation. These processes are called units, and they can be services, sockets, devices, mounts, automounts, swap spaces, timers, and more.

We use systemctl, the command-line utility for controlling the systemd system and service manager, to manage these units. Here are some common commands:

- **Start a service**:
  ```bash
  sudo systemctl start <service-name>
  ```
- **Stop a service**:
  ```bash
  sudo systemctl stop <service-name>
  ```
- **Restart a service**:
  ```bash
  sudo systemctl restart <service-name>
  ```
- **Enable a service to start on boot**:
  ```bash
  sudo systemctl enable <service-name>
  ```
- **Disable a service from starting on boot**:
  ```bash
  sudo systemctl disable <service-name>
  ```
- **Check the status of a service**:
  ```bash
  sudo systemctl status <service-name>
  ```
- **List all active services**:
  ```bash
  sudo systemctl list-units --type=service --state=active
  ```

We can test these commands after installing apache web server:

```bash
sudo apt update
sudo apt install apache2 -y
```

On some distros like Debian/Ubuntu, the service name might be `apache2`, while on others like Fedora/Red Hat, it might be `httpd`. You should also use the correct package manager for your distribution (e.g., `yum`, `dnf`, `pacman`, etc.). Note that on some of these distros after installing the apache web server it starts automatically. You can stop it first before starting it again to test the commands.

```bash
sudo systemctl stop apache2      # Stop the apache2 service
sudo systemctl start apache2     # Start the apache2 service
sudo systemctl status apache2    # Check the status of the apache2 service
```

You can also enable or disable services which would indicate whether the service should start automatically on boot.

```bash
sudo systemctl disable apache2   # Disable apache2 from starting on boot
sudo systemctl enable apache2    # Enable apache2 to start on boot
```
