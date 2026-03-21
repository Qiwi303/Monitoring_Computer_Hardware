#!/bin/bash

BUILD_PATH="./project/build"

cmake --build "$BUILD_PATH"

"$BUILD_PATH/producer" &
"$BUILD_PATH/ftxui-starter"


