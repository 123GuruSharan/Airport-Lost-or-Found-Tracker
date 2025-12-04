FROM ubuntu:22.04

RUN apt update && apt install -y \
    g++ \
    cmake \
    make \
    libboost-all-dev

WORKDIR /app
COPY backend/ .

RUN mkdir build && cd build && cmake .. && make

ENV PORT=8080
EXPOSE 8080

CMD ["./build/app"]
