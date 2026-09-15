#!/bin/bash

PACKAGE_ID="com.olie.testpp"
PREFIX="/usr/local"

if [ "$EUID" -ne 0 ]; then
    echo "Please run the uninstaller with sudo."
    exit 1
fi

if ! /usr/sbin/pkgutil --pkg-info "$PACKAGE_ID" >/dev/null 2>&1; then
    echo "Test++ is not installed."
    exit 0
fi

echo "Uninstalling Test++..."

# Remove everything generated/stored by Test++.
rm -rf "$PREFIX/run/testpp"

# Remove files installed by the package.
while IFS= read -r file; do
    path="$PREFIX/${file#./}"

    if [ -f "$path" ] || [ -L "$path" ]; then
        rm -f "$path"
    fi
done < <(/usr/sbin/pkgutil --files "$PACKAGE_ID")

# Remove empty directories left behind by Test++.
for dir in \
    "$PREFIX/lib/cmake/testpp" \
    "$PREFIX/include/testpp" \
    "$PREFIX/lib" \
    "$PREFIX/include" \
    "$PREFIX/bin"
do
    rmdir "$dir" 2>/dev/null || true
done

# Remove the package receipt.
pkgutil --forget "$PACKAGE_ID" >/dev/null

echo "Test++ has been uninstalled."