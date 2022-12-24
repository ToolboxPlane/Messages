/**
 * @file MessageConversion.hpp
 * @author paul
 * @date 20.10.22
 * @brief Conversion functions from protobuf types to SI-enabled structs.
 * @ingroup Messages
 */
#ifndef MESSAGES_MESSAGE_CONVERSION_HPP
#define MESSAGES_MESSAGE_CONVERSION_HPP

#include <FlightComputer.pb.h>

#include "MessageIds.h"
#include "Types/Types.hpp"

namespace messages {
    template<typename T>
    struct Conversion {};

    template<>
    struct Conversion<types::FlightControllerData> {
        using ThisType = types::FlightControllerData;
        using ProtobufType = ToolboxPlaneMessages_FlightController;
        static constexpr const pb_msgdesc_s *description = ToolboxPlaneMessages_FlightController_fields;
        static constexpr uint8_t ID = FC_ID;

        static auto fromProtobuf(const ProtobufType &obj) -> ThisType {
            types::ImuData imuData{
                    .imuOk = obj.imu.imu_ok,
                    .roll = obj.imu.roll_mul_16 / 16.0F,
                    .pitch = obj.imu.pitch_mul_16 / 16.0F,
                    .yaw = obj.imu.yaw_mul_16 / 16.0F,
                    .dRoll = obj.imu.dRoll_mul_16 / 16.0 * si::hertz,
                    .dPitch = obj.imu.dPitch_mul_16 / 16.0 * si::hertz,
                    .dYaw = obj.imu.dYaw_mul_16 / 16.0 * si::hertz,
                    .accX = obj.imu.accX_mul_100 / 100.0 * si::acceleration,
                    .accY = obj.imu.accY_mul_100 / 100.0 * si::acceleration,
                    .accZ = obj.imu.accZ_mul_100 / 100.0 * si::acceleration,
            };
            types::RemoteData remoteData{.throttleRaw = obj.remote.throttleRaw,
                                         .pitchRaw = obj.remote.pitchRaw,
                                         .rollRaw = obj.remote.rollRaw,
                                         .throttleMixed = obj.remote.throttleMixed,
                                         .elevonLeftMixed = obj.remote.elevonLeftMixed,
                                         .elevonRightMixed = obj.remote.elevonRightMixed,
                                         .isArmed = obj.remote.isArmed,
                                         .manualOverrideActive = obj.remote.overrideActive};

            return ThisType{
                    .imu = imuData,
                    .remote = remoteData,
                    .elevonLeft = (obj.servoLeft - 500) / 500.0f,
                    .elevonRight = (obj.servoRight - 500) / 500.0F,
                    .motor = obj.motor / 1000.0F,
            };
        }
    };

    template<>
    struct Conversion<types::PdbPackage> {
        using ThisType = types::PdbPackage;
        using ProtobufType = ToolboxPlaneMessages_PDB;
        static constexpr const pb_msgdesc_s *description = ToolboxPlaneMessages_PDB_fields;
        static constexpr uint8_t ID = PDB_ID;

        static auto fromProtobuf(const ProtobufType &obj) -> ThisType {
            return ThisType{
                    .voltageVcc = static_cast<si::default_type>(obj.v_vcc) * 128 / 1000.0f * si::volt,
                    .currentVcc = static_cast<si::default_type>(obj.i_vcc) * 256 / 1000.0f * si::ampere,
                    .voltage5V = static_cast<si::default_type>(obj.v_5v) * 32 / 1000.0f * si::volt,
                    .current5V = static_cast<si::default_type>(obj.i_5v) * 64 / 1000.0f * si::ampere,
            };
        }
    };

    template<>
    struct Conversion<types::FlightControllerSetpoint> {
        using ThisType = types::FlightControllerSetpoint;
        using ProtobufType = ToolboxPlaneMessages_FlightControllerSetpoint;
        static constexpr const pb_msgdesc_s *description = ToolboxPlaneMessages_FlightController_fields;
        static constexpr uint8_t ID = FC_SP_ID;

        static auto toProtobuf(const ThisType &obj) -> ProtobufType {
            return ProtobufType{
                    .motor = static_cast<int32_t>(static_cast<float>(obj.power) * 1023),
                    .pitch = static_cast<int32_t>(static_cast<float>(obj.pitch) + 180.0F),
                    .roll = static_cast<int32_t>(static_cast<float>(obj.roll) + 180),
            };
        }
    };

} // namespace messages

#endif // MESSAGES_MESSAGE_CONVERSION_HPP
