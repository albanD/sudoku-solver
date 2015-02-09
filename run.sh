#!/bin/bash

pushd build

#We need to set the build folder in the LD_LIBRARY_PATH to use the .so that is in there
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)

echo "####### Starting TestSudoku #######"
if ./TestSudoku; then
    echo "#######         Done        #######"
    echo "All test passing"
else
    echo "Program exited with error code"
fi


popd
