/**
 * @file Gps_t.hpp
 * @author paul
 * @date 14.05.18.
 * @brief Declaration of the Gps-Type
 * @ingroup Messages
 */

#ifndef MESSAGES_TYPES_GPS_T_HPP
#define MESSAGES_TYPES_GPS_T_HPP

#include <SI/Si.hpp>
#include <cmath>

#define EARTH_CIRCUMFERENCE 40075017

class Gps_t {
  public:
    Gps_t(double lat, double lon, si::Meter<> altitude = 0.0 * si::meter) : lat(lat), lon(lon), altitude(altitude){};
    double lat, lon;
    si::Meter<> altitude;

    [[nodiscard]] auto distanceTo(const Gps_t &gps) const -> si::Meter<> {
        auto latDiff = gps.lat - this->lat;
        auto lonDiff = gps.lon - this->lon;
        auto latMean = (gps.lat + this->lat) / 2;
        auto altDiff = static_cast<double>(gps.altitude - this->altitude);

        auto latDist = latDiff / 360 * EARTH_CIRCUMFERENCE;
        auto lonDist = lonDiff / 360 * EARTH_CIRCUMFERENCE * std::cos(latMean / 180 * M_PI);

        return si::Meter<>{static_cast<float>(std::sqrt(latDist * latDist + lonDist * lonDist + altDiff * altDiff))};
    }

    [[nodiscard]] auto angleTo(const Gps_t &gps) const -> si::Scalar<> {
        auto latDiff = gps.lat - this->lat;
        auto lonDiff = gps.lon - this->lon;
        auto latMean = (gps.lat + this->lat) / 2;

        auto latDist = latDiff;
        auto lonDist = lonDiff * std::cos(latMean / 180 * M_PI);

        auto angle = -std::atan2(latDist, lonDist) * 180.0 / M_PI + 90;
        angle = std::fmod(angle, 360);
        if (angle > 180) {
            angle -= 360;
        } else if (angle < -180) {
            angle += 360;
        }
        return angle;
    }

    static constexpr si::Meter<> EARTH_RADIUS{EARTH_CIRCUMFERENCE / (2 * M_PI)};
};

#endif // MESSAGES_TYPES_GPS_T_HPP
