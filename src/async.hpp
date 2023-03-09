#pragma once

#include "main.h"

#define Async(code) src::Actions::doAsync([]() code);

static constexpr uint32_t NUM_WORKERS = 3;