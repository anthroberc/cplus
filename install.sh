#!/bin/bash
set -e

REPO_URL="https://github.com/sapirrior/cplus.git"
REPO="sapirrior/cplus"

OS_NAME="$(uname -s | tr '[:upper:]' '[:lower:]')"
IS_TERMUX=false
if [ -n "$PREFIX" ] && [ -d "$PREFIX/bin" ]; then
  IS_TERMUX=true
fi

# 1. Detect Compiler
if command -v clang++ &> /dev/null; then
  CXX="clang++"
elif command -v g++ &> /dev/null; then
  CXX="g++"
else
  echo "Error: No C++ compiler found (clang++ or g++)."
  if [ "$IS_TERMUX" = true ]; then
    echo "Please run: pkg install clang git -y"
  else
    echo "Please install a C++ compiler and git."
  fi
  exit 1
fi

if ! command -v git &> /dev/null; then
  echo "Error: git is not installed."
  exit 1
fi

# 2. Build Process
echo "Modern Source-Based Installer for C+"
echo "Compiler Detected: $CXX"
echo "Operating System: $OS_NAME"

TMP_DIR=$(mktemp -d)
echo "Cloning latest source to $TMP_DIR..."
git clone --depth 1 "$REPO_URL" "$TMP_DIR"

cd "$TMP_DIR"
echo "Building C+ natively (C++20)..."
if ! $CXX -std=c++20 src/main.cpp src/environment/*.cpp src/lexer/*.cpp src/parser/*.cpp src/ast/*.cpp -I src/ -o cplus; then
  echo "Compilation failed! Check your compiler version (C++20 required)."
  exit 1
fi

# 3. Installation Strategy
if [ "$IS_TERMUX" = true ]; then
  INSTALL_PATH="$PREFIX/bin/cplus"
  CMD="mv cplus $INSTALL_PATH"
else
  INSTALL_PATH="/usr/local/bin/cplus"
  if [ -w "/usr/local/bin" ]; then
    CMD="mv cplus $INSTALL_PATH"
  else
    CMD="sudo mv cplus $INSTALL_PATH"
  fi
fi

echo "Attempting to install to $INSTALL_PATH..."
if eval "$CMD"; then
  echo "Successfully installed C+ globally!"
  echo "You can now run it using: cplus"
else
  echo "Global installation failed (permissions?)."
  echo "Moving binary to $HOME/cplus instead..."
  mv cplus "$HOME/cplus"
  chmod +x "$HOME/cplus"
  echo "Done! Run it locally using: ~/cplus"
  echo "To make it global, move ~/cplus to a directory in your PATH."
fi

# 4. Cleanup
cd - > /dev/null
rm -rf "$TMP_DIR"
