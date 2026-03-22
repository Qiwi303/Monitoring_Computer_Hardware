#!/bin/bash

BUILD_PATH="./project/build"

cmake --build "$BUILD_PATH"

if ! pgrep -x "producer" > /dev/null; then
"$BUILD_PATH/producer" &

echo "producer start working"

fi

"$BUILD_PATH/ftxui-starter"


