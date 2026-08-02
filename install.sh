compiler=""

echo "Checking for compiler..."

if command -v gcc >/dev/null 2>&1; then
    echo "gcc is installed"
    compiler="gcc"
else
    echo "gcc not found"
fi

if [ -z "$compiler" ]; then
    if command -v clang >/dev/null 2>&1; then
        echo "clang is installed"
        compiler="clang"
    else
        echo "clang not found"
    fi
fi

if [ -z "$compiler" ]; then
    if command -v cc >/dev/null 2>&1; then
        echo "cc is installed"
        compiler="cc"
    else
        echo "cc not found"
    fi
fi

if [ -z "$compiler" ]; then
    echo "Error: no compiler found."
    echo "The application will close..."
    exit 1
fi

echo "Using compiler: $compiler"

echo "Checking for root..."
if [ "$(id -u)" -eq 0 ]; then
    echo "Alredy rooted"
else
    sudo -k
    if sudo true; then
        echo "Correct password"
    else
        echo "Error: failed authentication, the application will close..."
        exit 1
    fi
fi

echo "Compiling asciiReference.c to executable..."
$compiler asciiReference.c -o ascii

echo "Moving ascii executable to path..."
sudo mv ascii /bin/
