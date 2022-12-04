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

    struct ImuData {
        bool imuOk;
        si::Scalar<> roll, pitch, yaw;
        si::Hertz<> dRoll, dPitch, dYaw;
        si::Acceleration<> accX, accY, accZ;
    };

    struct RemoteData {
        si::Scalar<> throttleRaw, pitchRaw, rollRaw;
        si::Scalar<> throttleMixed, elevonLeftMixed, elevonRightMixed;
        bool isArmed, manualOverrideActive;
    };

    struct FlightControllerData {
        ImuData imu;
        RemoteData remote;
        si::Scalar<> elevonLeft, elevonRight;
        si::Scalar<> motor;
    };

    struct PdbPackage {
        si::Volt<> voltageVcc;
        si::Ampere<> currentVcc;
        si::Volt<> voltage5V;
        si::Ampere<> current5V;
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
        Gps_t startLocation{0, 0, 0.0 * si::meter};
        si::Second<long double> startTime{};
    };

    struct FusionResult {
        State state;
        ImuData flightControllerPackage{};
        PdbPackage pdbPackage{};
        RemoteData taranisPackage{};
        NavPackage navPackage{};
    };
} // namespace messages::types

#endif // MESSAGES_TYPES_TYPES_HPP
