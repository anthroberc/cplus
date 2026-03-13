#!/bin/bash
set -e

REPO="sapirrior/cplus"
VERSION="v0.0.1"

OS_NAME="$(uname -s | tr '[:upper:]' '[:lower:]')"
ARCH_NAME="$(uname -m)"
IS_TERMUX=false

if [ -n "$PREFIX" ] && [ -d "$PREFIX/bin" ]; then
  IS_TERMUX=true
fi

case "$OS_NAME" in
  linux)
    if [ "$ARCH_NAME" = "aarch64" ] || [ "$ARCH_NAME" = "arm64" ]; then
      PLATFORM="linux-arm64"
    else
      PLATFORM="linux-x64"
    fi
    ;;
  darwin)
    PLATFORM="macos-universal"
    ;;
  *)
    echo "Unsupported operating system: $OS_NAME"
    exit 1
    ;;
esac

BINARY_NAME="${VERSION}-cplus-${PLATFORM}"
DOWNLOAD_URL="https://github.com/${REPO}/releases/download/${VERSION}/${BINARY_NAME}"

echo "Detected Platform: $OS_NAME ($ARCH_NAME) $( [ "$IS_TERMUX" = true ] && echo "[Termux Detected]" )"
echo "Downloading C+ $VERSION ($PLATFORM)..."

if ! curl -L --fail -o cplus "$DOWNLOAD_URL"; then
  echo "Error: Failed to download binary from $DOWNLOAD_URL"
  exit 1
fi

chmod +x cplus

if [ "$IS_TERMUX" = true ]; then
  INSTALL_DIR="$PREFIX/bin"
  USE_SUDO=false
else
  INSTALL_DIR="/usr/local/bin"
  USE_SUDO=true
fi

echo "Installing to $INSTALL_DIR/cplus..."

if [ "$USE_SUDO" = true ]; then
  if sudo mv cplus "$INSTALL_DIR/cplus"; then
    echo "Successfully installed C+!"
  else
    echo "Installation failed. Try moving the 'cplus' file to your PATH manually."
    exit 1
  fi
else
  if mv cplus "$INSTALL_DIR/cplus"; then
    echo "Successfully installed C+!"
  else
    echo "Installation failed. Make sure $INSTALL_DIR is writable."
    exit 1
  fi
fi

echo "You can now run it using: cplus"
