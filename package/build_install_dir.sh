#!/bin/sh

#第一个参数是cpu架构

if  [ ! -n "$1" ] ;then
	echo "Please specify arg1 is amd64 or arm64 or mips64 or sw64"
else
	PLATFORM=$1
	
	rm -rf ${PLATFORM}_deb_build
	
	mkdir -p ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient
	mkdir -p ${PLATFORM}_deb_build/DEBIAN
	
	cp ${PLATFORM}/control ${PLATFORM}_deb_build/DEBIAN/
	cp ${PLATFORM}/info ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/
	cp -rf ${PLATFORM}/files ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/
	cp -rf entries ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/
	cp -rf pub/* ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/files/
	cp -rf ../build/youboxclient ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/files/
	
	sudo chmod -R 755 ${PLATFORM}_deb_build/DEBIAN/
	dpkg -b ${PLATFORM}_deb_build/ com.whsrc.youboxclient_2.0.0_${PLATFORM}.deb

fi






