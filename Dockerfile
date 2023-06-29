# Run using $ sudo docker-compose build and $ sudo docker-compose up -d
# Base image
FROM debian:latest

# Set working directory
WORKDIR /app

# Copy source code
COPY src/ /app/src/
COPY bin/ /app/bin/

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    cmake \
    default-mysql-server \
    default-libmysqlclient-dev

# Clean up packages
RUN apt-get autoremove -y && apt-get clean

# Build the application
RUN cd src && cmake . && make

# Expose the application port
EXPOSE 8080

# Run the application
CMD ["./app/bin/expense_tracker"]

# Delete containers by running $ sudo docker ps -a and $ sudo docker stop <container_id> and $ sudo docker rm <container_id>
# and $ sudo docker images and $ sudo docker rmi <image_id>
# can also delete images by using the -f force command i.e. $ sudo docker rmi -f <image_id>
