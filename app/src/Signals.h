#pragma once

#include "spark.h"
#include "engine/ecs/Signal.h"

namespace se::ecs
{
    SPARK_INSTANTIATE_TEMPLATE(Signal, )
    SPARK_INSTANTIATE_TEMPLATE(Signal, std::string)
}
