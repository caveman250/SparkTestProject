#pragma once

#include "spark.h"
#include "engine/asset/texture/Texture.h"
#include "engine/reflect/Object.h"
#include "engine/reflect/Reflect.h"

namespace se::ui::button
{
    class ButtonSubscription;
}

namespace se::ui::systems
{
    class ButtonSystem;
}

namespace se::ui::components
{
    struct ReactToButtonComponent : reflect::ObjectBase
    {
        DECLARE_SPARK_COMPONENT(ReactToButtonComponent)

        std::shared_ptr<button::ButtonSubscription> subscription;
    };
}
