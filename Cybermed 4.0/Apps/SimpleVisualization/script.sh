cd ..
cd ..
cd code
./packmanager.sh uninstall all
./packmanager.sh clean all
./packmanager.sh install utils core view
cd ..
cd Apps
cd SimpleVisualization
make clean
make
