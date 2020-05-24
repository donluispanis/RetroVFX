FROM trzeci/emscripten

# Setting up timezone so tzdata con be downloaded

COPY . /usr/src/Fire
WORKDIR /usr/src/Fire

RUN emmake make fire_lin

CMD ["./Fire"]

LABEL Name=fire Version=0.0.1