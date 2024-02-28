#ifndef _RIVE_NESTED_INPUT_HPP_
#define _RIVE_NESTED_INPUT_HPP_
#include "rive/animation/nested_state_machine.hpp"
#include "rive/generated/animation/nested_input_base.hpp"
#include <stdio.h>
namespace rive
{
class NestedInput : public NestedInputBase
{
public:
    StatusCode onAddedDirty(CoreContext* context) override
    {
        StatusCode result = Super::onAddedDirty(context);
        auto parent = this->parent();
        if (parent != nullptr && parent->is<NestedStateMachine>())
        {
            parent->as<NestedStateMachine>()->addNestedInput(this);
        }
        return result;
    }

    virtual void applyValue() {}

protected:
    SMIInput* input()
    {
        auto parent = this->parent();
        if (parent != nullptr && parent->is<NestedStateMachine>())
        {
            StateMachineInstance* smInstance =
                parent->as<NestedStateMachine>()->stateMachineInstance();
            auto inputInstance = smInstance->input(this->inputId());
            return inputInstance;
        }
        return nullptr;
    }
};
} // namespace rive

#endif