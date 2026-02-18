Docker

- used in CD/CI, GH Actions
- virtualization: take small parts of the host's hardware to run a completly separate machine (VM) which has its own OS
- hypervisor: the thing that controlls VM's. VMWare, VirtualBox
- containerization: instruct certain processes to run in isolation without touching anything outside of the container. setting up something like this manually is pretty hard. this is where Docker comes in.
- Docker: set up containers
- docker file: the text file that acts as instruction s oh how to build a docker image
- docker image: the blueprint for a docker container. built using a docker file
- docker container: the running instance of a docker image
- docker hub: like github but for docker images. public and private repos

- in a project folder:
    - create a docker file
    - docker build -t <image-name> .
    - docker run -d -p 8080:80 <image-name>
    - go to localhost:8080