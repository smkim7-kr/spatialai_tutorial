
# Common Docker Commands

## 1. `docker images`
The `docker images` command lists all Docker images that are currently available on your local machine. Each image is identified by a **repository name**, **tag**, and **image ID**.

### Usage:
```bash
docker images
```

### Output:
```bash
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
ubuntu              latest              94e814e2efa8        2 weeks ago         89.2MB
osrf/ros            noetic-desktop-full 398d3d073235        3 weeks ago         2.9GB
```

---

## 2. `docker ps`
The `docker ps` command lists all running containers on your system. It shows important information like the container ID, the image the container is running from, status, ports, and more.

### Usage:
```bash
docker ps
```

### Output:
```bash
CONTAINER ID   IMAGE                  COMMAND         STATUS         PORTS    NAMES
2fa1d49d829d   osrf/ros:noetic-desktop-full   "/ros_entrypoint.sh"   Up 12 hours           friendly_ros_container
```

To list both running and stopped containers, add the `-a` flag:
```bash
docker ps -a
```

---

## 3. `docker stop`
The `docker stop` command stops a running container gracefully, allowing it to complete ongoing operations before halting.

### Usage:
```bash
docker stop <container_id_or_name>
```

For example:
```bash
docker stop 2fa1d49d829d
```

---

## 4. `docker rm`
The `docker rm` command is used to remove stopped containers. Containers must be stopped before they can be removed.

### Usage:
```bash
docker rm <container_id_or_name>
```

For example:
```bash
docker rm 2fa1d49d829d
```

To remove multiple containers at once, list their IDs:
```bash
docker rm <container_id1> <container_id2>
```

---

## 5. `docker attach`
The `docker attach` command allows you to connect to a running container’s main process, similar to logging into a live terminal. This is useful for interacting with containers that are running in the foreground.

### Usage:
```bash
docker attach <container_id_or_name>
```

For example:
```bash
docker attach 2fa1d49d829d
```

---

## 6. `docker push`
The `docker push` command is used to upload (push) your Docker image to a remote Docker registry like Docker Hub. Before pushing, you need to **tag** the image properly with the format `username/repository:tag`.

### Usage:
```bash
docker push <username/repository:tag>
```

For example:
```bash
docker push username/my-robot-image:latest
```

---

## 7. `docker pull`
The `docker pull` command downloads (pulls) an image from a remote registry (e.g., Docker Hub) to your local machine.

### Usage:
```bash
docker pull <repository:tag>
```

For example:
```bash
docker pull osrf/ros:noetic-desktop-full
```

---

## 8. `docker rmi`
The `docker rmi` command is used to remove a Docker image from your local machine. You can remove images by specifying their **image ID** or **repository:tag**.

### Usage:
```bash
docker rmi <image_id_or_repository:tag>
```

For example:
```bash
docker rmi 398d3d073235
```

If you want to remove multiple images at once:
```bash
docker rmi <image_id1> <image_id2>
```

---

## 9. `docker run`
The `docker run` command is used to create and start a new container from a Docker image. It combines the `docker create` and `docker start` commands into a single step.

### Basic Usage:
```bash
docker run <image>
```

For example:
```bash
docker run -it ubuntu
```

### Flags Commonly Used with `docker run`:
- `-it`: Run in interactive mode and allocate a TTY (useful for accessing the container shell).
- `--rm`: Automatically remove the container when it exits.
- `-d`: Run the container in detached mode (in the background).
- `-p`: Map container ports to host machine ports.

### Example: Running a ROS Noetic Container
```bash
docker run -it --rm osrf/ros:noetic-desktop-full
```

This will:
- Run an interactive container with ROS Noetic installed.
- Automatically remove the container when it exits.

---

## 10. `docker exec`
The `docker exec` command allows you to run a new command in an already running container.

### Usage:
```bash
docker exec -it <container_id_or_name> <command>
```

For example, to open a shell inside a running container:
```bash
docker exec -it 2fa1d49d829d /bin/bash
```

---

## Summary of Key Commands

| Command                | Description                                                     |
|------------------------|-----------------------------------------------------------------|
| `docker images`         | List all locally available Docker images                        |
| `docker ps`             | List all running containers                                     |
| `docker stop`           | Gracefully stop a running container                             |
| `docker rm`             | Remove stopped containers                                       |
| `docker attach`         | Attach to a running container’s main process                    |
| `docker push`           | Push a Docker image to a remote registry                        |
| `docker pull`           | Pull a Docker image from a remote registry                      |
| `docker rmi`            | Remove a Docker image from the local system                     |
| `docker run`            | Create and start a new container from an image                  |
| `docker exec`           | Run a new command in a running container                        |
