docker build -f Dockerfile.wasm -t fire .
docker create --name fire_container fire
docker cp fire_container:/usr/src/Fire/bin/Fire.html binaries/lin/wasm
docker cp fire_container:/usr/src/Fire/bin/Fire.js binaries/lin/wasm
docker cp fire_container:/usr/src/Fire/bin/Fire.wasm binaries/lin/wasm
docker cp fire_container:/usr/src/Fire/bin/Plasma.html binaries/lin/wasm
docker cp fire_container:/usr/src/Fire/bin/Plasma.js binaries/lin/wasm
docker cp fire_container:/usr/src/Fire/bin/Plasma.wasm binaries/lin/wasm
docker rm fire_container
docker rmi fire