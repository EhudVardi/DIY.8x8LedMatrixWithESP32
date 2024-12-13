#ifndef APPLICATION_PROPERTIES_H
#define APPLICATION_PROPERTIES_H

#include <Arduino.h>

const String APP_NAME_TEXT = "LED MATRIX DISPLAY";
const String APP_VERSION_TEXT = "1.0.0";

const std::string APP_TITLE_STRING = std::string(APP_NAME_TEXT.c_str()) + ". VERSION" + std::string(APP_VERSION_TEXT.c_str()); 

#endif // APPLICATION_PROPERTIES_H