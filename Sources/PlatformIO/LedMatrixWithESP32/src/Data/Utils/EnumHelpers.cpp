#include "EnumHelpers.h"

namespace EnumHelpers {

    EnumHelper<LogType> logTypeHelper({
        { LogType::INFO, "INFO" },
        { LogType::DEBUG, "DEBUG" },
        { LogType::ERROR, "ERROR" },
        }, LogType::ERROR); // last valid state

}