#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>
#include <vector>

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_handler.hpp"
#include "oxts/gal-cpp/gad_output/gad_output_file.hpp"
#include "oxts/gal-cpp/gad_output/gad_output_udp.hpp"
#include "oxts/gal-cpp/gad_encoders/gad_encoder_csv.hpp"
#include "oxts/gal-cpp/gad_encoders/gad_encoder_bin.hpp"

namespace py = pybind11;

#define UNPACK2(cls, func) [](OxTS::Gal_Cpp::cls &c, std::vector<double> vec) {if(vec.size() == 2){c.func(vec[0], vec[1]);} else{std::cout<< "invalid variance length (must be 2)"<<std::endl;}}
#define UNPACK3(cls, func) [](OxTS::Gal_Cpp::cls &c, std::vector<double> vec) {if(vec.size() == 3){c.func(vec[0], vec[1], vec[2]);} else{std::cout<< "invalid variance length (must be 3)"<<std::endl;}}
#define UNPACK(cls, func)  [](OxTS::Gal_Cpp::cls &c, std::vector<double> vec) {if(vec.size() == 6){c.func(vec[0], vec[1], vec[2], vec[3], vec[4], vec[5]);} else if(vec.size() == 3){c.func(vec[0], vec[1], vec[2]);} else{std::cout<< "invalid variance length (must be 3 or 6)"<<std::endl;}}


PYBIND11_MODULE(oxts_sdk, m) {
    m.doc() = "OxTS SDK"; // optional module docstring

    py::class_<OxTS::Gal_Cpp::Gad>(m, "Gad")
        // Constructors
        .def(py::init<>())
        .def(py::init<uint8_t, int8_t>(), py::arg("stream_id"), py::arg("aiding_type"))
        // General Accessors
        .def_property("stream_id", &OxTS::Gal_Cpp::Gad::GetStreamId, &OxTS::Gal_Cpp::Gad::SetStreamId)
        // Time accessors
        .def_property("time_valid", &OxTS::Gal_Cpp::Gad::GetTimeValid, &OxTS::Gal_Cpp::Gad::SetTimeValid)
        .def_property("time_external", &OxTS::Gal_Cpp::Gad::GetTimeExternal, UNPACK2(Gad, SetTimeExternal))
        .def_property("time_gps", &OxTS::Gal_Cpp::Gad::GetTimeGps, UNPACK2(Gad, SetTimeGps))
        .def_property("time_tai", &OxTS::Gal_Cpp::Gad::GetTimeTAI, &OxTS::Gal_Cpp::Gad::SetTimeTAI)
        .def_property("time_pps_relative", &OxTS::Gal_Cpp::Gad::GetTimePpsRelative, &OxTS::Gal_Cpp::Gad::SetTimePpsRelative)
        .def_property("time_latency", &OxTS::Gal_Cpp::Gad::GetTimeLatency, &OxTS::Gal_Cpp::Gad::SetTimeLatency)
        .def_property("time_utc_unix", &OxTS::Gal_Cpp::Gad::GetTimeUTCUnix, &OxTS::Gal_Cpp::Gad::SetTimeUTCUnix)
        .def("set_time_void", &OxTS::Gal_Cpp::Gad::SetTimeVoid)
        // Acquisiton time accessors.
        .def_property("acq_valid", &OxTS::Gal_Cpp::Gad::GetAcqValid, &OxTS::Gal_Cpp::Gad::SetAcqValid)
        .def_property("acq_timestamp", &OxTS::Gal_Cpp::Gad::GetAcqTimestamp, &OxTS::Gal_Cpp::Gad::SetAcqTimestamp);

    py::class_<OxTS::Gal_Cpp::GadPosition, OxTS::Gal_Cpp::Gad>(m, "GadPosition")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("pos_geodetic", &OxTS::Gal_Cpp::GadPosition::GetPos, UNPACK3(GadPosition, SetPosGeodetic))
        .def_property("pos_local", &OxTS::Gal_Cpp::GadPosition::GetPos, UNPACK3(GadPosition, SetPosLocal))
        .def_property("pos_geodetic_var", &OxTS::Gal_Cpp::GadPosition::GetPosVar, UNPACK(GadPosition, SetPosGeodeticVar))
        .def_property("pos_local_var", &OxTS::Gal_Cpp::GadPosition::GetPosVar, UNPACK(GadPosition, SetPosLocalVar))
        .def_property("aiding_lever_arm_fixed", &OxTS::Gal_Cpp::GadPosition::GetAidingLeverArm, UNPACK3(GadPosition, SetAidingLeverArmFixed))
        .def_property("aiding_lever_arm_var", &OxTS::Gal_Cpp::GadPosition::GetAidingLeverArmVar, UNPACK3(GadPosition, SetAidingLeverArmVar))
        .def("set_aiding_lever_arm_optimising", &OxTS::Gal_Cpp::GadPosition::SetAidingLeverArmOptimising)
        .def("set_aiding_lever_arm_config", &OxTS::Gal_Cpp::GadPosition::SetAidingLeverArmConfig);

    py::class_<OxTS::Gal_Cpp::GadVelocity, OxTS::Gal_Cpp::Gad>(m, "GadVelocity")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("vel_ned", &OxTS::Gal_Cpp::GadVelocity::GetVel, UNPACK3(GadVelocity, SetVelNed))
        .def_property("vel_odom", &OxTS::Gal_Cpp::GadVelocity::GetVel, UNPACK3(GadVelocity, SetVelOdom))
        .def_property("vel_local", &OxTS::Gal_Cpp::GadVelocity::GetVel, UNPACK3(GadVelocity, SetVelLocal))
        .def_property("vel_ned_var", &OxTS::Gal_Cpp::GadVelocity::GetVelVar, UNPACK(GadVelocity, SetVelNedVar))
        .def_property("vel_odom_var", &OxTS::Gal_Cpp::GadVelocity::GetVelVar, UNPACK(GadVelocity, SetVelOdomVar))
        .def_property("vel_local_var", &OxTS::Gal_Cpp::GadVelocity::GetVelVar, UNPACK(GadVelocity, SetVelLocalVar))
        .def_property("aiding_lever_arm_fixed", &OxTS::Gal_Cpp::GadVelocity::GetAidingLeverArm, UNPACK3(GadVelocity, SetAidingLeverArmFixed))
        .def_property("aiding_lever_arm_var", &OxTS::Gal_Cpp::GadVelocity::GetAidingLeverArmVar, UNPACK3(GadVelocity, SetAidingLeverArmVar))
        .def("set_aiding_lever_arm_optimising", &OxTS::Gal_Cpp::GadVelocity::SetAidingLeverArmOptimising)
        .def("set_aiding_lever_arm_config", &OxTS::Gal_Cpp::GadVelocity::SetAidingLeverArmConfig);

    py::class_<OxTS::Gal_Cpp::GadWheelSpeed, OxTS::Gal_Cpp::Gad>(m, "GadWheelSpeed")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("speed_fw", &OxTS::Gal_Cpp::GadWheelSpeed::GetWheelSpeedFw, &OxTS::Gal_Cpp::GadWheelSpeed::SetWheelSpeedFw)
        .def_property("speed_fw_var", &OxTS::Gal_Cpp::GadWheelSpeed::GetWheelSpeedFwVar, &OxTS::Gal_Cpp::GadWheelSpeed::SetWheelSpeedFwVar)
        .def_property("wheelspeed_count", &OxTS::Gal_Cpp::GadWheelSpeed::GetWheelSpeedCount, UNPACK2(GadWheelSpeed, SetWheelSpeedCount))
        .def_property("wheelspeed_var", &OxTS::Gal_Cpp::GadWheelSpeed::GetWheelSpeedVar, &OxTS::Gal_Cpp::GadWheelSpeed::SetWheelSpeedVar)
        .def_property("aiding_lever_arm_fixed", &OxTS::Gal_Cpp::GadWheelSpeed::GetAidingLeverArm, UNPACK3(GadWheelSpeed, SetAidingLeverArmFixed))
        .def_property("aiding_lever_arm_var", &OxTS::Gal_Cpp::GadWheelSpeed::GetAidingLeverArmVar, UNPACK3(GadWheelSpeed, SetAidingLeverArmVar))
        .def("set_aiding_lever_arm_optimising", &OxTS::Gal_Cpp::GadWheelSpeed::SetAidingLeverArmOptimising)
        .def("set_aiding_lever_arm_config", &OxTS::Gal_Cpp::GadWheelSpeed::SetAidingLeverArmConfig);

    py::class_<OxTS::Gal_Cpp::GadSpeed, OxTS::Gal_Cpp::Gad>(m, "GadSpeed")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("speed_fw_ms", &OxTS::Gal_Cpp::GadSpeed::GetSpeed, &OxTS::Gal_Cpp::GadSpeed::SetSpeedFwMs)
        .def_property("speed_bw_ms", &OxTS::Gal_Cpp::GadSpeed::GetSpeed, &OxTS::Gal_Cpp::GadSpeed::SetSpeedBwMs)
        .def_property("speed_un_ms", &OxTS::Gal_Cpp::GadSpeed::GetSpeed, &OxTS::Gal_Cpp::GadSpeed::SetSpeedUnMs)
        .def_property("speed_fw_pulsed", &OxTS::Gal_Cpp::GadSpeed::GetSpeed, UNPACK3(GadSpeed, SetSpeedFwPulsed))
        .def_property("speed_bw_pulsed", &OxTS::Gal_Cpp::GadSpeed::GetSpeed, UNPACK3(GadSpeed, SetSpeedBwPulsed))
        .def_property("speed_un_pulsed", &OxTS::Gal_Cpp::GadSpeed::GetSpeed, UNPACK3(GadSpeed, SetSpeedUnPulsed))
        .def_property("speed_ms_var", &OxTS::Gal_Cpp::GadSpeed::GetSpeedVar, &OxTS::Gal_Cpp::GadSpeed::SetSpeedMsVar)
        .def_property("speed_pulsed_var", &OxTS::Gal_Cpp::GadSpeed::GetSpeedVar, UNPACK2(GadSpeed, SetSpeedPulsedVar))
        .def_property("speed_pulsed_var_period", &OxTS::Gal_Cpp::GadSpeed::GetSpeedVar, UNPACK3(GadSpeed, SetSpeedPulsedVarPeriod))
        .def_property("aiding_lever_arm_fixed", &OxTS::Gal_Cpp::GadSpeed::GetAidingLeverArm, UNPACK3(GadSpeed, SetAidingLeverArmFixed))
        .def_property("aiding_lever_arm_var", &OxTS::Gal_Cpp::GadSpeed::GetAidingLeverArmVar, UNPACK3(GadSpeed, SetAidingLeverArmVar))
        .def("set_aiding_lever_arm_config", &OxTS::Gal_Cpp::GadSpeed::SetAidingLeverArmConfig);

    py::class_<OxTS::Gal_Cpp::GadAttitude, OxTS::Gal_Cpp::Gad>(m, "GadAttitude")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("att", &OxTS::Gal_Cpp::GadAttitude::GetAtt, UNPACK3(GadAttitude, SetAtt))
        .def_property("att_local", &OxTS::Gal_Cpp::GadAttitude::GetAtt, UNPACK3(GadAttitude, SetAttLocal))
        .def_property("att_var", &OxTS::Gal_Cpp::GadAttitude::GetAttVar, UNPACK3(GadAttitude, SetAttVar))
        .def_property("aiding_alignment_var", &OxTS::Gal_Cpp::GadAttitude::GetAidingAlignmentVar, UNPACK3(GadAttitude, SetAidingAlignmentVar))
        .def_property("aiding_alignment_fixed", &OxTS::Gal_Cpp::GadAttitude::GetAidingAlignment, UNPACK3(GadAttitude, SetAidingAlignmentFixed))
        .def("set_aiding_alignment_optimising", &OxTS::Gal_Cpp::GadAttitude::SetAidingAlignmentOptimising)
        .def("set_aiding_alignment_config", &OxTS::Gal_Cpp::GadAttitude::SetAidingAlignmentConfig);
    
    py::class_<OxTS::Gal_Cpp::GadHeading, OxTS::Gal_Cpp::Gad>(m, "GadHeading")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("heading", &OxTS::Gal_Cpp::GadHeading::GetHeading, &OxTS::Gal_Cpp::GadHeading::SetHeading)
        .def_property("heading_local", &OxTS::Gal_Cpp::GadHeading::GetHeading, &OxTS::Gal_Cpp::GadHeading::SetHeadingLocal)
        .def_property("heading_var", &OxTS::Gal_Cpp::GadHeading::GetHeadingVar, &OxTS::Gal_Cpp::GadHeading::SetHeadingVar)
        .def_property("aiding_alignment_var", &OxTS::Gal_Cpp::GadHeading::GetAidingAlignmentVar, UNPACK3(GadHeading, SetAidingAlignmentVar))
        .def_property("aiding_alignment_fixed", &OxTS::Gal_Cpp::GadHeading::GetAidingAlignment, UNPACK3(GadHeading, SetAidingAlignmentFixed))
        .def("set_aiding_alignment_config", &OxTS::Gal_Cpp::GadHeading::SetAidingAlignmentConfig);

    py::class_<OxTS::Gal_Cpp::GadAngularRate, OxTS::Gal_Cpp::Gad>(m, "GadAngularRate")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("angular_rate", &OxTS::Gal_Cpp::GadAngularRate::GetAngularRate, &OxTS::Gal_Cpp::GadAngularRate::SetAngularRate)
        .def_property("angular_rate_var", &OxTS::Gal_Cpp::GadAngularRate::GetAngularRateVar, &OxTS::Gal_Cpp::GadAngularRate::SetAngularRateVar)
        .def_property("aiding_alignment_var", &OxTS::Gal_Cpp::GadAngularRate::GetAidingAlignmentVar, UNPACK3(GadAngularRate, SetAidingAlignmentVar))
        .def_property("aiding_alignment_fixed", &OxTS::Gal_Cpp::GadAngularRate::GetAidingAlignment, UNPACK3(GadAngularRate, SetAidingAlignmentFixed))
        .def("set_aiding_alignment_config", &OxTS::Gal_Cpp::GadAngularRate::SetAidingAlignmentConfig);

    py::class_<OxTS::Gal_Cpp::GadHandler>(m, "GadHandler")
        .def(py::init<>())
        .def("set_encoder_to_bin", &OxTS::Gal_Cpp::GadHandler::SetEncoderToBin)
        .def("set_encoder_to_csv", &OxTS::Gal_Cpp::GadHandler::SetEncoderToCsv)
        .def("set_output_mode_to_file", &OxTS::Gal_Cpp::GadHandler::SetOutputModeToFile, py::arg("file_path"))
        .def("set_output_mode_to_udp", &OxTS::Gal_Cpp::GadHandler::SetOutputModeToUdp, py::arg("ip"))
        .def("send_packet", &OxTS::Gal_Cpp::GadHandler::SendPacket, py::arg("gad"));

}

