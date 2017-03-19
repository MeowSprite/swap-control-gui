#! /bin/bash

INFO(){ echo -n "INFO: "; echo "$@" ;}
WARN(){ echo -n "WARN: "; echo "$@" ;}
ERRO(){ echo -n "ERRO: "; echo -n "$@" ; echo " Abort!"; exit 1;}

Depencence="libqt5core5a (>= 5.6.1), libqt5gui5 (>= 5.6.1), libqt5widgets5 (>= 5.6.1), libc6 (>= 2.14), systemd"

cd "$(dirname $0)"
VERSION=$(cat ./debian/version)
DEB_NAME=systemd-swap-gui${VERSION}
mkdir -p $DEB_NAME
./systemd-swap/install.sh PREFIX=$(pwd)/$DEB_NAME/
mkdir -p  $DEB_NAME/DEBIAN
chmod 755 $DEB_NAME/DEBIAN

install ./debian/postinst -Dm755 $DEB_NAME/DEBIAN/postinst
install ./debian/prerm -Dm755 $DEB_NAME/DEBIAN/prerm

if [ ! -e ./swap-control ]; then
    ERRO "No built swap-control, please make sure swap-control in the folder"
fi

install debian/swap-control-gui.desktop -Dm644 $DEB_NAME/usr/share/applications/swap-control-gui.desktop
install shell/listvalue.sh -Dm644 $DEB_NAME/usr/share/swap-control/shell/listvalue.sh
install ./swap-control -Dm755 $DEB_NAME/usr/share/swap-control/swap-control

mkdir -p $DEB_NAME/usr/share/swap-control/translations
cp translations/*.qm $DEB_NAME/usr/share/swap-control/translations/


echo "Package: systemd-swap-gui"    >  $DEB_NAME/DEBIAN/control
echo "Version: $VERSION"        >> $DEB_NAME/DEBIAN/control
echo "Section: custom"          >> $DEB_NAME/DEBIAN/control
echo "Priority: optional"       >> $DEB_NAME/DEBIAN/control
echo "Architecture: amd64"        >> $DEB_NAME/DEBIAN/control
echo "Essential: no"            >> $DEB_NAME/DEBIAN/control
echo "Installed-Size: 50"       >> $DEB_NAME/DEBIAN/control
echo "Maintainer: Wikyo_Roc@163.com" >> $DEB_NAME/DEBIAN/control
echo "Description: Combine with systemd-swap to manage zram, zswap and swap space" >> $DEB_NAME/DEBIAN/control
echo "Depends: $Depencence" >> $DEB_NAME/DEBIAN/control
dpkg-deb --build $DEB_NAME
