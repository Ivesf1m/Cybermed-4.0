cd ..
cd ..
cd code
./packmanager.sh uninstall utils core view collision
./packmanager.sh clean utils core view collision
./packmanager.sh install utils core view collision
cd ..
cd Apps/OBBCollisionTest
make clean
make
