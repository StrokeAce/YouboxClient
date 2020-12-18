#!/bin/sh

#第一个参数是cpu架构

if  [ ! -n "$1" ] ;then
	echo "Please specify arg1 is amd64 or arm64 or mips64 or sw64"
else
	PLATFORM=$1

	sudo rm -rf ${PLATFORM}_deb_build
	
	mkdir -p ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient	
	mkdir -p ${PLATFORM}_deb_build/DEBIAN
	
	cp ${PLATFORM}/control ${PLATFORM}_deb_build/DEBIAN/
	cp ${PLATFORM}/info ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/
	cp -rf ${PLATFORM}/files ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/
	cp -rf entries ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/
	cp -rf pub/* ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/files/
	
	if [[ $1 = 'py64' ]];then
	  mkdir -p ${PLATFORM}_deb_build/usr/share/applications
		cp entries/applications/youboxclient.desktop ${PLATFORM}_deb_build/usr/share/applications/
		chmod +x ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/entries/applications/youboxclient.desktop
	else
	  chmod +x ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/entries/applications/com.whsrc.youboxclient.desktop
	fi

	chmod +x ${PLATFORM}_deb_build/opt/apps/com.whsrc.youboxclient/files/*	
	chmod -R 755 ${PLATFORM}_deb_build/DEBIAN/
	sudo dpkg -b ${PLATFORM}_deb_build/ com.whsrc.youboxclient_2.0.0_${PLATFORM}.deb

fi






