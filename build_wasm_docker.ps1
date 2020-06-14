docker build -f Dockerfile.wasm -t fire .
docker create --name fire_container fire
docker cp fire_container:/usr/src/wasm/bin/Fire.html binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Fire.js binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Fire.wasm binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Plasma.html binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Plasma.js binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Plasma.wasm binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/DotTunnel.html binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/DotTunnel.js binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/DotTunnel.wasm binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/RotoZoom.html binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/RotoZoom.js binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/RotoZoom.wasm binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Deformations.html binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Deformations.js binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Deformations.wasm binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Geometry.html binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Geometry.js binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Geometry.wasm binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/FinalDemo.html binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/FinalDemo.js binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/FinalDemo.wasm binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Planes.html binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Planes.js binaries/lin/wasm
docker cp fire_container:/usr/src/wasm/bin/Planes.wasm binaries/lin/wasm
docker rm fire_container
docker rmi fire