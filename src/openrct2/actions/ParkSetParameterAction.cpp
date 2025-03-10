/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "ParkSetParameterAction.h"

#include "../GameState.h"
#include "../interface/Window.h"
#include "../ride/ShopItem.h"
#include "../util/Util.h"
#include "../world/Park.h"

using namespace OpenRCT2;

ParkSetParameterAction::ParkSetParameterAction(ParkParameter parameter, uint64_t value)
    : _parameter(parameter)
    , _value(value)
{
}

void ParkSetParameterAction::AcceptParameters(GameActionParameterVisitor& visitor)
{
    visitor.Visit("parameter", _parameter);
    visitor.Visit("value", _value);
}

uint16_t ParkSetParameterAction::GetActionFlags() const
{
    return GameAction::GetActionFlags() | GameActions::Flags::AllowWhilePaused;
}

void ParkSetParameterAction::Serialise(DataSerialiser& stream)
{
    GameAction::Serialise(stream);
    stream << DS_TAG(_parameter) << DS_TAG(_value);
}

GameActions::Result ParkSetParameterAction::Query() const
{
    if (_parameter >= ParkParameter::Count)
    {
        return GameActions::Result(
            GameActions::Status::InvalidParameters, STR_ERR_INVALID_PARAMETER, STR_ERR_VALUE_OUT_OF_RANGE);
    }

    auto res = GameActions::Result();
    res.ErrorTitle = _ErrorTitles[EnumValue(_parameter)];
    return res;
}

GameActions::Result ParkSetParameterAction::Execute() const
{
    auto& gameState = GetGameState();
    switch (_parameter)
    {
        case ParkParameter::Close:
            if (gameState.ParkFlags & PARK_FLAGS_PARK_OPEN)
            {
                gameState.ParkFlags &= ~PARK_FLAGS_PARK_OPEN;
                WindowInvalidateByClass(WindowClass::ParkInformation);
            }
            break;
        case ParkParameter::Open:
            if (!(gameState.ParkFlags & PARK_FLAGS_PARK_OPEN))
            {
                gameState.ParkFlags |= PARK_FLAGS_PARK_OPEN;
                WindowInvalidateByClass(WindowClass::ParkInformation);
            }
            break;
        case ParkParameter::SamePriceInPark:
            gameState.SamePriceThroughoutPark = _value;
            WindowInvalidateByClass(WindowClass::Ride);
            break;
        default:
            return GameActions::Result(
                GameActions::Status::InvalidParameters, STR_ERR_INVALID_PARAMETER, STR_ERR_VALUE_OUT_OF_RANGE);
    }

    auto res = GameActions::Result();
    res.ErrorTitle = _ErrorTitles[EnumValue(_parameter)];
    return res;
}
