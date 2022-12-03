/**
 * @file Types.hpp
 * @author paul
 * @date 03.12.22
 * Description here TODO
 */
#ifndef MESSAGES_TYPES_TYPES_HPP
#define MESSAGES_TYPES_TYPES_HPP

#include <SI/Si.hpp>

#include "Gps_t.hpp"

namespace messages::types {
    struct FlightControllerSetpoint {
        si::Scalar<> power, pitch, roll;
    };

    enum class FlightMode { RTH = 0, LAUNCH = 1, LAND = 2, LOITER = 3, WAYPOINT = 4 };

    enum class SwitchPos { UP, CENTRE, DOWN };

    enum class CalibStatus : uint8_t { NOT_CALIBRATED = 0, CALIB_STAT_1 = 1, CALIB_STAT_2 = 2, FULLY_CALIBRATED = 3 };

    struct FlightControllerPackage {
        bool imuOk;
        si::Scalar<> roll, pitch, yaw;
        si::Hertz<> rollDeriv, pitchDeriv, yawDeriv;
        si::Acceleration<> accX, accY, accZ;
        si::Scalar<> elevonLeft, elevonRight;
        si::Scalar<> motor;
    };

    struct PdbPackage {
        si::Volt<> voltageVcc;
        si::Ampere<> currentVcc;
        si::Volt<> voltage5V;
        si::Ampere<> current5V;
    };

    struct TaranisPackage {
        si::Scalar<> throttle, pitch, roll;
        bool isArmed, manualOverrideActive;
        int rssi;
    };

    struct LoraPackage {
        si::Scalar<> joyLeftX, joyRightX, joyLeftY, joyRightY;
        FlightMode flightMode;
        bool isArmed;
        int rssi;
    };

    struct NavPackage {
        int rssi;
        si::Meter<> baroAltitude;
        si::Volt<> pitotVoltage;
        si::Meter<> usDistance;
    };

    struct State {
        si::Scalar<> roll{};
        si::Hertz<> rollDeriv{};
        si::Scalar<> pitch{};
        si::Hertz<> pitchDeriv{};
        si::Scalar<> yaw{};
        si::Hertz<> yawDeriv{};
        si::Speed<> speed{};
        si::Meter<> altitudeAboveGround{};
        si::Meter<> altitudeGround{};
        Gps_t position{0, 0};
        si::Acceleration<> accX{}, accY{}, accZ{};
        Gps_t startLocation{0, 0, 0.0F * si::meter};
        si::Second<long double> startTime{};
    };

    struct FusionResult {
        State state;
        FlightControllerPackage flightControllerPackage{};
        PdbPackage pdbPackage{};
        TaranisPackage taranisPackage{};
        LoraPackage loraRemote{};
        NavPackage navPackage{};
    };
} // namespace messages::types

#endif // MESSAGES_TYPES_TYPES_HPP
