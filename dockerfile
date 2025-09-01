
# ============================
# Stage 1: Build the application
# ============================
FROM ubuntu:22.04 AS build

# Install CMake and other build dependencies
RUN apt-get update && apt-get install -y libasio-dev


RUN apt-get update && apt-get install -y \
    curl \
    git \
    g++ \
    make \
    tar \
    && rm -rf /var/lib/apt/lists/*

 
RUN git clone --branch v1.0+5 --depth 1 https://github.com/CrowCpp/crow.git /crow

# Install CMake 3.22.1
RUN curl -L https://github.com/Kitware/CMake/releases/download/v3.22.1/cmake-3.22.1-linux-x86_64.tar.gz \
    -o cmake.tar.gz \
    && tar -xzvf cmake.tar.gz \
    && mv cmake-3.22.1-linux-x86_64 /opt/cmake-3.22.1 \
    && ln -s /opt/cmake-3.22.1/bin/* /usr/local/bin/ \
    && rm cmake.tar.gz




# Set working directory
WORKDIR /app

# Copy only required build config and source files
COPY . .
# Create separate build folder and compile
RUN mkdir build

WORKDIR /app/build 

RUN cmake .. 
RUN make 

WORKDIR /app
# ============================
# Stage 2: Runtime image
# ============================
FROM ubuntu:22.04

WORKDIR /app

# Copy only the final binary from the build stage
COPY --from=build /app/build/cpp_rest_api .

# Expose application port
EXPOSE 8080

# Run application
CMD ["./cpp_rest_api"]
