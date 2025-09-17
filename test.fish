echo "testing with no arguments"
./build/qtee
echo "testing an invalid argument"
./build/qtee "you can't see me"
echo "testing import.q"
./build/qtee tests/import.q