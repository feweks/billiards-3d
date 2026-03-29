#include "game/trace.hpp"

#include <raylib.h>
#include <string>

void trace_log(TraceLogLevel lvl, const std::string &msg) { TraceLog(lvl, msg.c_str()); }
