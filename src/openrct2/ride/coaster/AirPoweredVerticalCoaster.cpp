/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "../../drawing/Drawing.h"
#include "../../interface/Viewport.h"
#include "../../paint/Paint.h"
#include "../../paint/support/WoodenSupports.h"
#include "../../paint/tile_element/Paint.TileElement.h"
#include "../../sprites.h"
#include "../../world/Map.h"
#include "../RideData.h"
#include "../TrackData.h"
#include "../TrackPaint.h"

enum
{
    SPR_REVERSE_FREEFALL_RC_FLAT_SW_NE = 22164,
    SPR_REVERSE_FREEFALL_RC_FLAT_NW_SE = 22165,

    SPR_AIR_POWERED_VERTICAL_RC_FLAT_SW_NE = 22226,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_NW_SE = 22227,
    SPR_AIR_POWERED_VERTICAL_RC_STATION_SW_NE = 22228,
    SPR_AIR_POWERED_VERTICAL_RC_STATION_NW_SE = 22229,
    SPR_AIR_POWERED_VERTICAL_RC_BRAKES_NW_SE = 22230,
    SPR_AIR_POWERED_VERTICAL_RC_BRAKES_SW_NE = 22231,

    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_SW_NE_SEQ_0 = 22236,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_NW_SE_SEQ_0 = 22237,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_NE_SW_SEQ_0 = 22238,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_SE_NW_SEQ_0 = 22239,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_SW_NE_SEQ_1 = 22232,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_NW_SE_SEQ_1 = 22233,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_NE_SW_SEQ_1 = 22234,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_SE_NW_SEQ_1 = 22235,

    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_SW_NE = 22334,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_NW_SE = 22335,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_NE_SW = 22336,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_SE_NW = 22337,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_RIGHT_BANK_SW_NE = 22338,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_RIGHT_BANK_NW_SE = 22339,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_RIGHT_BANK_NE_SW = 22340,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_RIGHT_BANK_SE_NW = 22341,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_SW_NE = 22342,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_NW_SE = 22343,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_NE_SW = 22344,
    SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_SE_NW = 22345,
    SPR_AIR_POWERED_VERTICAL_RC_LEFT_BANK_SW_NE = 22346,
    SPR_AIR_POWERED_VERTICAL_RC_LEFT_BANK_NW_SE = 22347,
    SPR_AIR_POWERED_VERTICAL_RC_LEFT_BANK_NE_SW = 22348,
    SPR_AIR_POWERED_VERTICAL_RC_LEFT_BANK_SE_NW = 22349,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_SW_NE_SEQ_1 = 22350,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_SW_NE_SEQ_0 = 22351,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_SW_NE_SEQ_3 = 22352,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_SW_NE_SEQ_2 = 22353,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_NW_SE_SEQ_1 = 22354,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_NW_SE_SEQ_0 = 22355,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_NW_SE_SEQ_3 = 22356,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_NW_SE_SEQ_2 = 22357,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_SUPPORT_SW_NE = 22358,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_SUPPORT_NW_SE = 22359,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_SUPPORT_NE_SW = 22360,
    SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_SUPPORT_SE_NW = 22361,

    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_0 = 22240,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_1 = 22241,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_2 = 22242,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_3 = 22243,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_4 = 22244,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_6 = 22245,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_0 = 22246,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_1 = 22247,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_2 = 22248,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_3 = 22249,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_4 = 22250,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_6 = 22251,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_0 = 22252,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_1 = 22253,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_2 = 22254,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_3 = 22255,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_4 = 22256,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_6 = 22257,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_0 = 22258,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_1 = 22259,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_2 = 22260,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_3 = 22261,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_4 = 22262,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_6 = 22263,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_0 = 22264,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_1 = 22265,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_2 = 22266,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_3 = 22267,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_4 = 22268,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_6 = 22269,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_5 = 22270,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_0 = 22271,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_1 = 22272,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_2 = 22273,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_3 = 22274,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_4 = 22275,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_6 = 22276,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_5 = 22277,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_0 = 22278,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_1 = 22279,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_2 = 22280,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_3 = 22281,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_4 = 22282,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_6 = 22283,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_5 = 22284,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_0 = 22285,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_1 = 22286,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_2 = 22287,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_3 = 22288,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_4 = 22289,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_6 = 22290,
    SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_5 = 22291,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SW_SE_PART_0 = 22292,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SW_SE_PART_1 = 22293,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SW_SE_PART_2 = 22294,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SW_SE_PART_3 = 22295,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SW_SE_PART_4 = 22296,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NW_SW_PART_0 = 22297,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NW_SW_PART_1 = 22298,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NW_SW_PART_2 = 22299,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NW_SW_PART_3 = 22300,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NW_SW_PART_4 = 22301,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NE_NW_PART_0 = 22302,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NE_NW_PART_1 = 22303,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NE_NW_PART_2 = 22304,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NE_NW_PART_3 = 22305,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NE_NW_PART_4 = 22306,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SE_NE_PART_0 = 22307,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SE_NE_PART_1 = 22308,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SE_NE_PART_2 = 22309,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SE_NE_PART_3 = 22310,
    SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SE_NE_PART_4 = 22311,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SW_SE_PART_0 = 22312,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SW_SE_PART_1 = 22313,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SW_SE_PART_2 = 22314,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SW_SE_PART_3 = 22315,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SW_SE_PART_4 = 22316,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NW_SW_PART_0 = 22317,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NW_SW_PART_1 = 22318,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NW_SW_PART_2 = 22319,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NW_SW_PART_3 = 22320,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NW_SW_PART_4 = 22321,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NE_NW_PART_0 = 22322,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NE_NW_PART_1 = 22323,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NE_NW_PART_2 = 22324,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NE_NW_PART_3 = 22325,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NE_NW_PART_4 = 22326,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SE_NE_PART_0 = 22327,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SE_NE_PART_1 = 22328,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SE_NE_PART_2 = 22329,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SE_NE_PART_3 = 22330,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SE_NE_PART_4 = 22331,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_FRONT_NW_SW_PART_4 = 22332,
    SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_FRONT_SE_NE_PART_0 = 22333,
};

/** rct2: 0x008AFAD4 */
static void AirPoweredVerticalRCTrackFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr uint32_t imageIds[4] = {
        SPR_AIR_POWERED_VERTICAL_RC_FLAT_SW_NE,
        SPR_AIR_POWERED_VERTICAL_RC_FLAT_NW_SE,
        SPR_AIR_POWERED_VERTICAL_RC_FLAT_SW_NE,
        SPR_AIR_POWERED_VERTICAL_RC_FLAT_NW_SE,
    };

    auto imageId = session.TrackColours.WithIndex(imageIds[direction]);
    PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });

    WoodenASupportsPaintSetupRotated(
        session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);

    PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_SQUARE_FLAT);

    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

static void AirPoweredVerticalRCTrackStation(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr uint32_t imageIds[4][2] = {
        { SPR_AIR_POWERED_VERTICAL_RC_STATION_SW_NE, SPR_STATION_BASE_B_SW_NE },
        { SPR_AIR_POWERED_VERTICAL_RC_STATION_NW_SE, SPR_STATION_BASE_B_NW_SE },
        { SPR_AIR_POWERED_VERTICAL_RC_STATION_SW_NE, SPR_STATION_BASE_B_SW_NE },
        { SPR_AIR_POWERED_VERTICAL_RC_STATION_NW_SE, SPR_STATION_BASE_B_NW_SE },
    };

    PaintAddImageAsParentRotated(
        session, direction, GetStationColourScheme(session, trackElement).WithIndex(imageIds[direction][1]),
        { 0, 0, height - 2 }, { { 0, 2, height }, { 32, 28, 1 } });
    PaintAddImageAsChildRotated(
        session, direction, session.TrackColours.WithIndex(imageIds[direction][0]), { 0, 0, height },
        { { 0, 6, height }, { 32, 20, 1 } });

    WoodenASupportsPaintSetupRotated(
        session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);

    TrackPaintUtilDrawNarrowStationPlatform(session, ride, direction, height, 5, trackElement);

    PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_SQUARE_FLAT);

    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

static void AirPoweredVerticalRCTrackRightQuarterTurn5(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr SpriteBb imageIds[4][5] = {
        {
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SW_SE_PART_0, { 0, 2, 0 }, { 0, 0, 0 }, { 32, 32, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SW_SE_PART_1, { 0, 16, 0 }, { 0, 0, 0 }, { 32, 16, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SW_SE_PART_2, { 0, 0, 0 }, { 0, 0, 0 }, { 16, 16, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SW_SE_PART_3, { 16, 0, 0 }, { 0, 0, 0 }, { 16, 32, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SW_SE_PART_4, { 2, 0, 0 }, { 0, 0, 0 }, { 32, 32, 2 } },
        },
        {
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NW_SW_PART_0, { 2, 0, 0 }, { 0, 0, 0 }, { 32, 32, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NW_SW_PART_1, { 16, 0, 0 }, { 0, 0, 0 }, { 16, 34, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NW_SW_PART_2, { 0, 16, 0 }, { 0, 0, 0 }, { 16, 16, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NW_SW_PART_3, { 0, 0, 0 }, { 0, 0, 0 }, { 32, 16, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NW_SW_PART_4, { 0, 2, 0 }, { 0, 0, 0 }, { 32, 27, 2 } },
        },
        {
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NE_NW_PART_0, { 0, 2, 0 }, { 0, 0, 0 }, { 32, 27, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NE_NW_PART_1, { 0, 0, 0 }, { 0, 0, 0 }, { 32, 16, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NE_NW_PART_2, { 16, 16, 0 }, { 0, 0, 0 }, { 16, 16, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NE_NW_PART_3, { 0, 0, 0 }, { 0, 0, 0 }, { 16, 32, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_NE_NW_PART_4, { 2, 0, 0 }, { 0, 0, 0 }, { 27, 32, 2 } },
        },
        {
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SE_NE_PART_0, { 2, 0, 0 }, { 0, 0, 0 }, { 27, 32, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SE_NE_PART_1, { 0, 0, 0 }, { 0, 0, 0 }, { 16, 32, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SE_NE_PART_2, { 16, 0, 0 }, { 0, 0, 0 }, { 16, 16, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SE_NE_PART_3, { 0, 16, 0 }, { 0, 0, 0 }, { 32, 16, 2 } },
            { SPR_AIR_POWERED_VERTICAL_RC_QUARTER_TURN_5_SE_NE_PART_4, { 0, 2, 0 }, { 0, 0, 0 }, { 32, 32, 2 } },
        },
    };

    TrackPaintUtilRightQuarterTurn5TilesPaint3(session, height, direction, trackSequence, session.TrackColours, imageIds);
    TrackPaintUtilRightQuarterTurn5TilesWoodenSupports(session, height, direction, trackSequence);
    TrackPaintUtilRightQuarterTurn5TilesTunnel(session, height, direction, trackSequence, TUNNEL_SQUARE_FLAT);

    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            break;
        case 1:
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
            break;
        case 2:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(SEGMENT_D0 | SEGMENT_C4 | SEGMENT_D4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_CC, direction),
                0xFFFF, 0);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_C4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_D0 | SEGMENT_D4,
                    direction),
                0xFFFF, 0);
            break;
        case 4:
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
            break;
        case 5:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(SEGMENT_D4 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C8, direction),
                0xFFFF, 0);
            break;
        case 6:
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            break;
    }

    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

static void AirPoweredVerticalRCTrackLeftQuarterTurn5(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    AirPoweredVerticalRCTrackRightQuarterTurn5(session, ride, trackSequence, (direction + 1) % 4, height, trackElement);
}

/** rct2: 0x008AFB74 */
static void AirPoweredVerticalRCTrackFlatToLeftBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr uint32_t imageIds[4][2] = {
        { SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_SW_NE, SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_SW_NE },
        { SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_NW_SE, SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_NW_SE },
        { SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_NE_SW, SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_NE_SW },
        { SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_SE_NW, SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_SE_NW },
    };

    auto imageId = session.TrackColours.WithIndex(imageIds[direction][0]);
    PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });

    if (direction == 0 || direction == 1)
    {
        imageId = session.TrackColours.WithIndex(imageIds[direction][1]);
        PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 27, height }, { 32, 1, 26 } });
    }

    WoodenASupportsPaintSetupRotated(
        session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);

    PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_SQUARE_FLAT);

    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

/** rct2: 0x008AFB84 */
static void AirPoweredVerticalRCTrackFlatToRightBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr uint32_t imageIds[4][2] = {
        { SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_RIGHT_BANK_SW_NE, SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_SW_NE },
        { SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_RIGHT_BANK_NW_SE, SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_NW_SE },
        { SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_RIGHT_BANK_NE_SW, SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_NE_SW },
        { SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_RIGHT_BANK_SE_NW, SPR_AIR_POWERED_VERTICAL_RC_FLAT_TO_LEFT_BANK_FRONT_SE_NW },
    };

    auto imageId = session.TrackColours.WithIndex(imageIds[direction][0]);
    PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });

    if (direction == 2 || direction == 3)
    {
        imageId = session.TrackColours.WithIndex(imageIds[direction][1]);
        PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 27, height }, { 32, 1, 26 } });
    }

    WoodenASupportsPaintSetupRotated(
        session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);

    PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_SQUARE_FLAT);

    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

static void AirPoweredVerticalRCTrackLeftBankToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    AirPoweredVerticalRCTrackFlatToRightBank(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AFBA4 */
static void AirPoweredVerticalRCTrackRightBankToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    AirPoweredVerticalRCTrackFlatToLeftBank(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

static void AirPoweredVerticalRCTrackBankedRightQuarterTurn5(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr SpriteBb imageIds[4][5] = {
        {
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SW_SE_PART_0, { 0, 0, 0 }, { 0, 6, 0 }, { 32, 20, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SW_SE_PART_1, { 0, 0, 0 }, { 0, 16, 0 }, { 32, 16, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SW_SE_PART_2, { 0, 0, 0 }, { 0, 0, 0 }, { 16, 16, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SW_SE_PART_3, { 0, 0, 0 }, { 16, 0, 0 }, { 16, 32, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SW_SE_PART_4, { 0, 0, 0 }, { 6, 0, 0 }, { 20, 32, 3 } },
        },
        {
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NW_SW_PART_0, { 0, 0, 0 }, { 6, 0, 0 }, { 20, 32, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NW_SW_PART_1, { 0, 0, 0 }, { 16, 0, 0 }, { 16, 32, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NW_SW_PART_2, { 0, 0, 0 }, { 0, 16, 0 }, { 16, 16, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NW_SW_PART_3, { 0, 0, 0 }, { 0, 0, 0 }, { 32, 16, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NW_SW_PART_4, { 0, 0, 0 }, { 0, 6, 0 }, { 32, 20, 3 } },
        },
        {
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NE_NW_PART_0, { 0, 0, 0 }, { 0, 27, 0 }, { 32, 1, 26 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NE_NW_PART_1, { 0, 0, 0 }, { 0, 0, 27 }, { 32, 16, 1 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NE_NW_PART_2, { 0, 0, 0 }, { 16, 16, 27 }, { 16, 16, 1 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NE_NW_PART_3, { 0, 0, 0 }, { 0, 0, 27 }, { 16, 32, 1 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_NE_NW_PART_4, { 0, 0, 0 }, { 27, 0, 0 }, { 1, 32, 26 } },
        },
        {
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SE_NE_PART_0, { 0, 0, 0 }, { 6, 0, 0 }, { 20, 32, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SE_NE_PART_1, { 0, 0, 0 }, { 0, 0, 0 }, { 16, 32, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SE_NE_PART_2, { 0, 0, 0 }, { 16, 0, 0 }, { 16, 16, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SE_NE_PART_3, { 0, 0, 0 }, { 0, 16, 0 }, { 32, 16, 3 } },
            { SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_SE_NE_PART_4, { 0, 0, 0 }, { 0, 6, 0 }, { 32, 20, 3 } },
        },
    };

    TrackPaintUtilRightQuarterTurn5TilesPaint2(session, height, direction, trackSequence, session.TrackColours, imageIds);

    if (direction == 1 && trackSequence == 6)
    {
        auto imageId = session.TrackColours.WithIndex(SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_FRONT_NW_SW_PART_4);
        PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 0, 27, height }, { 32, 1, 26 } });
    }
    else if (direction == 3 && trackSequence == 0)
    {
        auto imageId = session.TrackColours.WithIndex(SPR_AIR_POWERED_VERTICAL_RC_BANKED_QUARTER_TURN_5_FRONT_SE_NE_PART_0);
        PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 27, 0, height }, { 1, 32, 26 } });
    }

    TrackPaintUtilRightQuarterTurn5TilesWoodenSupports(session, height, direction, trackSequence);
    TrackPaintUtilRightQuarterTurn5TilesTunnel(session, height, direction, trackSequence, TUNNEL_SQUARE_FLAT);

    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            break;
        case 1:
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
            break;
        case 2:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(SEGMENT_D0 | SEGMENT_C4 | SEGMENT_D4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_CC, direction),
                0xFFFF, 0);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_C4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_D0 | SEGMENT_D4,
                    direction),
                0xFFFF, 0);
            break;
        case 4:
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
            break;
        case 5:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(SEGMENT_D4 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C8, direction),
                0xFFFF, 0);
            break;
        case 6:
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            break;
    }

    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

static void AirPoweredVerticalRCTrackBankedLeftQuarterTurn5(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    AirPoweredVerticalRCTrackBankedRightQuarterTurn5(session, ride, trackSequence, (direction + 1) % 4, height, trackElement);
}

/** rct2: 0x008AFBD4 */
static void AirPoweredVerticalRCTrackLeftBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr uint32_t imageIds[4] = {
        SPR_AIR_POWERED_VERTICAL_RC_LEFT_BANK_SW_NE,
        SPR_AIR_POWERED_VERTICAL_RC_LEFT_BANK_NW_SE,
        SPR_AIR_POWERED_VERTICAL_RC_LEFT_BANK_NE_SW,
        SPR_AIR_POWERED_VERTICAL_RC_LEFT_BANK_SE_NW,
    };

    auto imageId = session.TrackColours.WithIndex(imageIds[direction]);
    if (direction == 0 || direction == 1)
    {
        PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 27, height }, { 32, 1, 26 } });
    }
    else
    {
        PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
    }

    WoodenASupportsPaintSetupRotated(
        session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);

    PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_SQUARE_FLAT);

    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

static void AirPoweredVerticalRCTrackRightBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    AirPoweredVerticalRCTrackLeftBank(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

static void AirPoweredVerticalRCTrackBrakes(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr uint32_t imageIds[4] = {
        SPR_AIR_POWERED_VERTICAL_RC_BRAKES_NW_SE,
        SPR_AIR_POWERED_VERTICAL_RC_BRAKES_SW_NE,
        SPR_AIR_POWERED_VERTICAL_RC_BRAKES_NW_SE,
        SPR_AIR_POWERED_VERTICAL_RC_BRAKES_SW_NE,
    };

    auto imageId = session.TrackColours.WithIndex(imageIds[direction]);
    PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });

    WoodenASupportsPaintSetupRotated(
        session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);

    PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_SQUARE_FLAT);

    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

static void AirPoweredVerticalRCTrackVerticalSlopeUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr uint32_t trackImageIds[7][4] = {
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_0,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_0,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_0,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_0,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_1,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_1,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_1,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_1,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_2,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_2,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_2,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_2,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_3,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_3,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_3,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_3,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_4,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_4,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_4,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_4,
        },
        { 0, 0, 0, 0 },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SW_NE_6,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NW_SE_6,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_NE_SW_6,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SE_NW_6,
        },
    };

    static constexpr uint32_t supportImageIds[7][4] = {
        {
            22264,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_0,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_0,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_0,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_1,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_1,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_1,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_1,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_2,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_2,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_2,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_2,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_3,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_3,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_3,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_3,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_4,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_4,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_4,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_4,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_5,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_5,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_5,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_5,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SW_NE_6,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NW_SE_6,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_NE_SW_6,
            SPR_AIR_POWERED_VERTICAL_RC_SLOPE_SUPPORTS_SE_NW_6,
        },
    };

    static constexpr int8_t bbHeights03[] = {
        1, 6, 14, 37, 76,
    };
    static constexpr int8_t bbHeights12[] = {
        1, 6, 14, 27, 59,
    };
    static constexpr int32_t supportHeights[] = {
        48, 64, 128, 176, 208, 240, 240,
    };

    auto supportsImageId = session.SupportColours.WithIndex(supportImageIds[trackSequence][direction]);
    auto trackImageId = session.TrackColours.WithIndex(trackImageIds[trackSequence][direction]);
    int8_t bbHeight;
    bool isDirection03 = (direction == 0 || direction == 3);
    switch (trackSequence)
    {
        case 0:
            bbHeight = bbHeights12[trackSequence];
            PaintAddImageAsParentRotated(
                session, direction, supportsImageId, { 0, 0, height }, { { 0, 6, height }, { 20, 32, bbHeight } });
            PaintAddImageAsChildRotated(
                session, direction, trackImageId, { 0, 0, height }, { { 0, 6, height }, { 20, 32, bbHeight } });

            WoodenASupportsPaintSetup(
                session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, height, session.SupportColours);

            PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_SQUARE_FLAT);

            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + supportHeights[trackSequence], 0x20);
            break;
        case 1:
        case 2:
        case 3:
            if (isDirection03)
            {
                bbHeight = bbHeights03[trackSequence];

                PaintAddImageAsParentRotated(
                    session, direction, supportsImageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, bbHeight } });
                PaintAddImageAsChildRotated(
                    session, direction, trackImageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, bbHeight } });
            }
            else
            {
                bbHeight = bbHeights12[trackSequence];
                PaintAddImageAsParentRotated(
                    session, direction, supportsImageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, bbHeight } });
                PaintAddImageAsChildRotated(
                    session, direction, trackImageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, bbHeight } });
            }

            WoodenASupportsPaintSetupRotated(
                session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);

            if (trackSequence == 0)
            {
                PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }

            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + supportHeights[trackSequence], 0x20);
            break;
        case 4:
            if (isDirection03)
            {
                bbHeight = bbHeights03[trackSequence];
                PaintAddImageAsParentRotated(
                    session, direction, supportsImageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, bbHeight } });
                PaintAddImageAsChildRotated(
                    session, direction, trackImageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, bbHeight } });
            }
            else
            {
                bbHeight = bbHeights12[trackSequence];
                PaintAddImageAsParentRotated(
                    session, direction, trackImageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, bbHeight } });
                PaintAddImageAsChildRotated(
                    session, direction, supportsImageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, bbHeight } });
            }

            WoodenASupportsPaintSetupRotated(
                session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + supportHeights[trackSequence], 0x20);
            break;
        case 5:
            if (WoodenASupportsPaintSetupRotated(
                    session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours))
            {
                ImageId floorImageId;
                if (direction & 1)
                {
                    floorImageId = session.SupportColours.WithIndex(SPR_FLOOR_PLANKS_90_DEG);
                }
                else
                {
                    floorImageId = session.SupportColours.WithIndex(SPR_FLOOR_PLANKS);
                }
                PaintAddImageAsParent(session, floorImageId, { 0, 0, height }, { { 3, 3, height }, { 26, 26, 126 } });
                PaintAddImageAsChildRotated(
                    session, direction, supportsImageId, { 0, 0, height }, { { 3, 3, height }, { 26, 26, 126 } });
            }
            else
            {
                PaintAddImageAsParentRotated(
                    session, direction, supportsImageId, { 0, 0, height }, { { 3, 3, height }, { 26, 26, 126 } });
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + supportHeights[trackSequence], 0x20);
            break;
        case 6:
            if (isDirection03)
            {
                PaintAddImageAsParentRotated(
                    session, direction, supportsImageId, { 0, 0, height }, { { 0, 6, height + 128 }, { 5, 20, 79 } });
                PaintAddImageAsChildRotated(
                    session, direction, trackImageId, { 0, 0, height }, { { 0, 6, height + 128 }, { 5, 20, 79 } });
            }
            else
            {
                PaintAddImageAsParentRotated(
                    session, direction, trackImageId, { 0, 0, height }, { { 27, 6, height }, { 1, 20, 126 } });
                PaintAddImageAsChildRotated(
                    session, direction, supportsImageId, { 0, 0, height }, { { 27, 6, height }, { 1, 20, 126 } });
            }
            WoodenASupportsPaintSetupRotated(
                session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);

            PaintUtilSetVerticalTunnel(session, height + 240);

            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + supportHeights[trackSequence], 0x20);
            break;
    }
}

static void AirPoweredVerticalRCTrackVerticalUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr uint32_t imageIds[4][2] = {
        { SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_SW_NE_SEQ_0, SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_SW_NE_SEQ_1 },
        { SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_NW_SE_SEQ_0, SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_NW_SE_SEQ_1 },
        { SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_NE_SW_SEQ_0, SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_NE_SW_SEQ_1 },
        { SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_SE_NW_SEQ_0, SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_UP_SE_NW_SEQ_1 },
    };

    ImageId imageId;
    switch (trackSequence)
    {
        case 0:
            imageId = session.SupportColours.WithIndex(imageIds[direction][0]);
            PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 3, 3, height }, { 26, 26, 79 } });
            break;
        case 1:
            imageId = session.TrackColours.WithIndex(imageIds[direction][1]);
            if (direction == 0 || direction == 3)
            {
                PaintAddImageAsParentRotated(
                    session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 2, 20, 79 } });
            }
            else
            {
                PaintAddImageAsParentRotated(
                    session, direction, imageId, { 0, 0, height }, { { 30, 6, height }, { 2, 20, 79 } });
            }

            PaintUtilSetVerticalTunnel(session, height + 80);
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 80, 0x20);
}

static void AirPoweredVerticalRCTrackVerticalTop(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (direction == 2 || direction == 3)
    {
        AirPoweredVerticalRCTrackVerticalTop(session, ride, 3 - trackSequence, (direction + 2) & 3, height, trackElement);
        return;
    }

    static constexpr uint32_t imageIds[4][6] = {
        {
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_SUPPORT_SW_NE,
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_SW_NE_SEQ_0,
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_SW_NE_SEQ_1,
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_SW_NE_SEQ_2,
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_SUPPORT_NE_SW,
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_SW_NE_SEQ_3,
        },
        {
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_SUPPORT_NW_SE,
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_NW_SE_SEQ_0,
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_NW_SE_SEQ_1,
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_NW_SE_SEQ_2,
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_SUPPORT_SE_NW,
            SPR_AIR_POWERED_VERTICAL_RC_VERTICAL_TOP_TRACK_NW_SE_SEQ_3,
        },
    };

    ImageId imageIdS, imageIdT;
    switch (trackSequence)
    {
        case 0:
            imageIdS = session.SupportColours.WithIndex(imageIds[direction][0]);
            imageIdT = session.TrackColours.WithIndex(imageIds[direction][1]);
            if (direction == 0)
            {
                PaintAddImageAsParentRotated(
                    session, direction, imageIdS, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 15 } });
                PaintAddImageAsChildRotated(
                    session, direction, imageIdT, { 0, 0, height }, { { 1, 6, height }, { 31, 20, 15 } });
            }
            else
            {
                PaintAddImageAsParentRotated(
                    session, direction, imageIdS, { 0, 0, height }, { { 24, 6, height }, { 5, 20, 1 } });
                PaintAddImageAsChildRotated(
                    session, direction, imageIdT, { 0, 0, height }, { { 24, 6, height }, { 5, 20, 1 } });
            }
            break;
        case 1:
            imageIdT = session.TrackColours.WithIndex(imageIds[direction][2]);
            if (direction == 0)
            {
                PaintAddImageAsParentRotated(
                    session, direction, imageIdT, { 0, 0, height }, { { 0, 6, height }, { 2, 20, 15 } });
            }
            else
            {
                PaintAddImageAsParentRotated(
                    session, direction, imageIdT, { 0, 0, height }, { { 33, 6, height }, { 2, 20, 1 } });
            }
            PaintUtilSetVerticalTunnel(session, height + 80);
            break;
        case 2:
            imageIdT = session.TrackColours.WithIndex(imageIds[direction][3]);
            if (direction == 0)
            {
                PaintAddImageAsParentRotated(
                    session, direction, imageIdT, { 0, 0, height }, { { 33, 6, height }, { 2, 20, 1 } });
            }
            else
            {
                PaintAddImageAsParentRotated(
                    session, direction, imageIdT, { 0, 0, height }, { { 0, 6, height }, { 2, 20, 15 } });
            }
            PaintUtilSetVerticalTunnel(session, height + 80);
            break;
        case 3:
            imageIdS = session.SupportColours.WithIndex(imageIds[direction][4]);
            imageIdT = session.TrackColours.WithIndex(imageIds[direction][5]);
            if (direction == 0)
            {
                PaintAddImageAsParentRotated(
                    session, direction, imageIdS, { 0, 0, height }, { { 24, 6, height }, { 5, 20, 1 } });
                PaintAddImageAsChildRotated(
                    session, direction, imageIdT, { 0, 0, height }, { { 24, 6, height }, { 5, 20, 1 } });
            }
            else
            {
                PaintAddImageAsParentRotated(
                    session, direction, imageIdS, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 15 } });
                PaintAddImageAsChildRotated(
                    session, direction, imageIdT, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 15 } });
            }
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 80, 0x20);
}

static void AirPoweredVerticalRCTrackVerticalDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    AirPoweredVerticalRCTrackVerticalUp(session, ride, trackSequence ^ 1, (direction + 2) & 3, height, trackElement);
}

static void AirPoweredVerticalRCTrackVerticalSlopeDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    AirPoweredVerticalRCTrackVerticalSlopeUp(session, ride, 6 - trackSequence, (direction + 2) & 3, height, trackElement);
}

static void AirPoweredVerticalRCTrackBooster(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    // The booster piece is borrowed from the Reverse Freefall Colour.
    // It has two track colours, instead of the one that the APVC has.
    auto colour = session.TrackColours;
    if (!trackElement.IsGhost() && !trackElement.IsHighlighted())
    {
        colour = colour.WithSecondary(colour.GetPrimary());
    }

    if (direction & 1)
    {
        auto imageId = colour.WithIndex(SPR_REVERSE_FREEFALL_RC_FLAT_NW_SE);
        PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 6, 0, height }, { 20, 32, 1 } });
        PaintUtilPushTunnelRight(session, height, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        auto imageId = colour.WithIndex(SPR_REVERSE_FREEFALL_RC_FLAT_SW_NE);
        PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });
        PaintUtilPushTunnelLeft(session, height, TUNNEL_SQUARE_FLAT);
    }

    WoodenASupportsPaintSetupRotated(
        session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);
    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

static void AirPoweredVerticalRCTrackOnridePhoto(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr uint32_t imageIds[4] = {
        SPR_AIR_POWERED_VERTICAL_RC_FLAT_SW_NE,
        SPR_AIR_POWERED_VERTICAL_RC_FLAT_NW_SE,
        SPR_AIR_POWERED_VERTICAL_RC_FLAT_SW_NE,
        SPR_AIR_POWERED_VERTICAL_RC_FLAT_NW_SE,
    };

    auto imageId = session.TrackColours.WithIndex(imageIds[direction]);
    PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });

    WoodenASupportsPaintSetupRotated(
        session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height, session.SupportColours);

    TrackPaintUtilOnridePhotoPaint(session, direction, height + 3, trackElement);
    PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_SQUARE_FLAT);

    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

TRACK_PAINT_FUNCTION GetTrackPaintFunctionAirPoweredVerticalRC(int32_t trackType)
{
    switch (trackType)
    {
        case TrackElemType::Flat:
            return AirPoweredVerticalRCTrackFlat;
        case TrackElemType::EndStation:
        case TrackElemType::BeginStation:
        case TrackElemType::MiddleStation:
            return AirPoweredVerticalRCTrackStation;
        case TrackElemType::LeftQuarterTurn5Tiles:
            return AirPoweredVerticalRCTrackLeftQuarterTurn5;
        case TrackElemType::RightQuarterTurn5Tiles:
            return AirPoweredVerticalRCTrackRightQuarterTurn5;
        case TrackElemType::FlatToLeftBank:
            return AirPoweredVerticalRCTrackFlatToLeftBank;
        case TrackElemType::FlatToRightBank:
            return AirPoweredVerticalRCTrackFlatToRightBank;
        case TrackElemType::LeftBankToFlat:
            return AirPoweredVerticalRCTrackLeftBankToFlat;
        case TrackElemType::RightBankToFlat:
            return AirPoweredVerticalRCTrackRightBankToFlat;
        case TrackElemType::BankedLeftQuarterTurn5Tiles:
            return AirPoweredVerticalRCTrackBankedLeftQuarterTurn5;
        case TrackElemType::BankedRightQuarterTurn5Tiles:
            return AirPoweredVerticalRCTrackBankedRightQuarterTurn5;
        case TrackElemType::LeftBank:
            return AirPoweredVerticalRCTrackLeftBank;
        case TrackElemType::RightBank:
            return AirPoweredVerticalRCTrackRightBank;
        case TrackElemType::Brakes:
            return AirPoweredVerticalRCTrackBrakes;
        case TrackElemType::ReverseFreefallSlope:
            return AirPoweredVerticalRCTrackVerticalSlopeUp;
        case TrackElemType::ReverseFreefallVertical:
            return AirPoweredVerticalRCTrackVerticalUp;
        case TrackElemType::AirThrustTopCap:
            return AirPoweredVerticalRCTrackVerticalTop;
        case TrackElemType::AirThrustVerticalDown:
            return AirPoweredVerticalRCTrackVerticalDown;
        case TrackElemType::AirThrustVerticalDownToLevel:
            return AirPoweredVerticalRCTrackVerticalSlopeDown;
        case TrackElemType::Booster:
            return AirPoweredVerticalRCTrackBooster;
        case TrackElemType::OnRidePhoto:
            return AirPoweredVerticalRCTrackOnridePhoto;
    }
    return nullptr;
}
