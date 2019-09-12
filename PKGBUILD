# Maintainer: Luca Weiss <luca (at) z3ntu (dot) xyz>
# Contributor: Gabriele Musco <emaildigabry@gmail.com>

pkgbase=openrazer
pkgname=('aero15kbd-driver-dkms')
pkgver=0.1.0
pkgrel=1
pkgdesc="An entirely open source driver and user-space daemon that allows you to manage your Razer peripherals on GNU/Linux."
arch=('any')
url="https://github.com/openrazer/openrazer"
license=('GPL2')
makedepends=('python-setuptools')
source=("https://github.com/openrazer/openrazer/releases/download/v$pkgver/openrazer-$pkgver.tar.xz")
sha256sums=('cf473a1956a00d1fd17138860e002d9ef90297a67daa7a7713b8ab9019795bac')

package_aero15kbd-driver-dkms() {
  pkgdesc="Kernel driver for Aero15 Keyboard device (DKMS-variant)"
  depends=('dkms' 'udev')
  install=openrazer-driver-dkms.install

  cd "$pkgbase-$pkgver"
  make DESTDIR="$pkgdir" setup_dkms udev_install
}

