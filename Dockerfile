# Stage 1: Build the application
FROM debian:latest as builder

# Set working directory
WORKDIR /app

# Copy source code
COPY src/ /app/src/
COPY bin/ /app/bin/

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    default-mysql-server \
    default-libmysqlclient-dev \
    libsqlite3-dev

# Build the application
RUN cd src && cmake . && make

# Stage 2: Create the final image
FROM debian:latest as runtime

# Set working directory
WORKDIR /app

# Copy built application from the builder stage
COPY --from=builder /app/bin/expense_tracker /app/expense_tracker

# Install runtime dependencies (if any)
RUN apt-get update && apt-get install -y \
    libsqlite3-dev \
    sqlite3 

# Copy libsqlite3.so.0 to /usr/local/lib/
# COPY --from=builder /usr/lib64/libsqlite3.so.0 /usr/local/lib/libsqlite3.so

# Expose the application port
EXPOSE 8080

# Run the application
CMD ["./expense_tracker"]

