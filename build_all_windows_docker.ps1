docker build -f Dockerfile.windows -t windows_build .
docker create --name windows_build_container windows_build
docker cp windows_build_container:/usr/src/windows_build/bin/Fire.exe bin/
docker cp windows_build_container:/usr/src/windows_build/bin/RotoZoom.exe bin/
docker cp windows_build_container:/usr/src/windows_build/bin/Plasma.exe bin/
docker cp windows_build_container:/usr/src/windows_build/bin/DotTunnel.exe bin/
docker cp windows_build_container:/usr/src/windows_build/bin/Deformations.exe bin/
docker cp windows_build_container:/usr/src/windows_build/bin/Planes.exe bin/
docker cp windows_build_container:/usr/src/windows_build/bin/Geometry.exe bin/
docker cp windows_build_container:/usr/src/windows_build/bin/FinalDemo.exe bin/
docker rm windows_build_container
docker rmi windows_build