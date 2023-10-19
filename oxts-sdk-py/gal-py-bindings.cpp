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

#define UNPACK2(cls, func) [](OxTS::cls &c, std::vector<double> vec) {c.func(vec[0], vec[1]);}
#define UNPACK3(cls, func) [](OxTS::cls &c, std::vector<double> vec) {c.func(vec[0], vec[1], vec[2]);}
#define UNPACK(cls, func)  [](OxTS::cls &c, std::vector<double> vec) {if(vec.size() == 6){c.func(vec[0], vec[1], vec[2], vec[3], vec[4], vec[5]);} else if(vec.size() == 3){c.func(vec[0], vec[1], vec[2]);} else{std::cout<< "invalid variance length (must be 3 or 6)"<<std::endl;}}


PYBIND11_MODULE(oxts_sdk, m) {
    m.doc() = "OxTS SDK"; // optional module docstring

    py::class_<OxTS::Gad>(m, "Gad")
        // Constructors
        .def(py::init<>())
        .def(py::init<uint8_t, int8_t>(), py::arg("stream_id"), py::arg("aiding_type"))
        // General Accessors
        .def_property("stream_id", &OxTS::Gad::GetStreamId, &OxTS::Gad::SetStreamId)
        // Time accessors
        .def_property("time_valid", &OxTS::Gad::GetTimeValid, &OxTS::Gad::SetTimeValid)
        .def_property("time_external", &OxTS::Gad::GetTimeExternal, UNPACK2(Gad, SetTimeExternal))
        .def_property("time_gps", &OxTS::Gad::GetTimeGps, UNPACK2(Gad, SetTimeGps))
        .def_property("time_tai", &OxTS::Gad::GetTimeTAI, &OxTS::Gad::SetTimeTAI)
        .def_property("time_pps_relative", &OxTS::Gad::GetTimePpsRelative, &OxTS::Gad::SetTimePpsRelative)
        .def_property("time_latency", &OxTS::Gad::GetTimeLatency, &OxTS::Gad::SetTimeLatency)
        .def_property("time_utc_unix", &OxTS::Gad::GetTimeUTCUnix, &OxTS::Gad::SetTimeUTCUnix)
        .def("set_time_void", &OxTS::Gad::SetTimeVoid)
        // Acquisiton time accessors.
        .def_property("acq_valid", &OxTS::Gad::GetAcqValid, &OxTS::Gad::SetAcqValid)
        .def_property("acq_timestamp", &OxTS::Gad::GetAcqTimestamp, &OxTS::Gad::SetAcqTimestamp);

    py::class_<OxTS::GadPosition, OxTS::Gad>(m, "GadPosition")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("pos_geodetic", &OxTS::GadPosition::GetPos, UNPACK3(GadPosition, SetPosGeodetic))
        .def_property("pos_local", &OxTS::GadPosition::GetPos, UNPACK3(GadPosition, SetPosLocal))
        .def_property("pos_geodetic_var", &OxTS::GadPosition::GetPosVar, UNPACK(GadPosition, SetPosGeodeticVar))
        .def_property("pos_local_var", &OxTS::GadPosition::GetPosVar, UNPACK(GadPosition, SetPosLocalVar))
        .def_property("aiding_lever_arm_fixed", &OxTS::GadPosition::GetAidingLeverArm, UNPACK3(GadPosition, SetAidingLeverArmFixed))
        .def_property("aiding_lever_arm_var", &OxTS::GadPosition::GetAidingLeverArmVar, UNPACK3(GadPosition, SetAidingLeverArmVar))
        .def("set_aiding_lever_arm_optimising", &OxTS::GadPosition::SetAidingLeverArmOptimising)
        .def("set_aiding_lever_arm_config", &OxTS::GadPosition::SetAidingLeverArmConfig);

    py::class_<OxTS::GadVelocity, OxTS::Gad>(m, "GadVelocity")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("vel_ned", &OxTS::GadVelocity::GetVel, UNPACK3(GadVelocity, SetVelNed))
        .def_property("vel_odom", &OxTS::GadVelocity::GetVel, UNPACK3(GadVelocity, SetVelOdom))
        .def_property("vel_local", &OxTS::GadVelocity::GetVel, UNPACK3(GadVelocity, SetVelLocal))
        .def_property("vel_ned_var", &OxTS::GadVelocity::GetVelVar, UNPACK(GadVelocity, SetVelNedVar))
        .def_property("vel_odom_var", &OxTS::GadVelocity::GetVelVar, UNPACK(GadVelocity, SetVelOdomVar))
        .def_property("vel_local_var", &OxTS::GadVelocity::GetVelVar, UNPACK(GadVelocity, SetVelLocalVar))
        .def_property("aiding_lever_arm_fixed", &OxTS::GadVelocity::GetAidingLeverArm, UNPACK3(GadVelocity, SetAidingLeverArmFixed))
        .def_property("aiding_lever_arm_var", &OxTS::GadVelocity::GetAidingLeverArmVar, UNPACK3(GadVelocity, SetAidingLeverArmVar))
        .def("set_aiding_lever_arm_optimising", &OxTS::GadVelocity::SetAidingLeverArmOptimising)
        .def("set_aiding_lever_arm_config", &OxTS::GadVelocity::SetAidingLeverArmConfig);

    py::class_<OxTS::GadSpeed, OxTS::Gad>(m, "GadSpeed")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("speed_fw", &OxTS::GadSpeed::GetSpeedFw, &OxTS::GadSpeed::SetSpeedFw)
        .def_property("speed_fw_var", &OxTS::GadSpeed::GetSpeedFwVar, &OxTS::GadSpeed::SetSpeedFwVar)
        .def_property("wheelspeed_count", &OxTS::GadSpeed::GetWheelspeedCount, UNPACK2(GadSpeed, SetWheelspeedCount))
        .def_property("wheelspeed_var", &OxTS::GadSpeed::GetWheelspeedVar, &OxTS::GadSpeed::SetWheelspeedVar)
        .def_property("aiding_lever_arm_fixed", &OxTS::GadSpeed::GetAidingLeverArm, UNPACK3(GadSpeed, SetAidingLeverArmFixed))
        .def_property("aiding_lever_arm_var", &OxTS::GadSpeed::GetAidingLeverArmVar, UNPACK3(GadSpeed, SetAidingLeverArmVar))
        .def("set_aiding_lever_arm_optimising", &OxTS::GadSpeed::SetAidingLeverArmOptimising)
        .def("set_aiding_lever_arm_config", &OxTS::GadSpeed::SetAidingLeverArmConfig);

    py::class_<OxTS::GadAttitude, OxTS::Gad>(m, "GadAttitude")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("att", &OxTS::GadAttitude::GetAtt, UNPACK3(GadAttitude, SetAtt))
        .def_property("att_local", &OxTS::GadAttitude::GetAtt, UNPACK3(GadAttitude, SetAttLocal))
        .def_property("att_var", &OxTS::GadAttitude::GetAttVar, UNPACK3(GadAttitude, SetAttVar))
        .def_property("aiding_alignment_var", &OxTS::GadAttitude::GetAidingAlignmentVar, UNPACK3(GadAttitude, SetAidingAlignmentVar))
        .def_property("aiding_alignment_fixed", &OxTS::GadAttitude::GetAidingAlignment, UNPACK3(GadAttitude, SetAidingAlignmentFixed))
        .def("set_aiding_alignment_optimising", &OxTS::GadAttitude::SetAidingAlignmentOptimising);
    
    py::class_<OxTS::GadHeading, OxTS::Gad>(m, "GadHeading")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("heading", &OxTS::GadHeading::GetHeading, &OxTS::GadHeading::SetHeading)
        .def_property("heading_local", &OxTS::GadHeading::GetHeading, &OxTS::GadHeading::SetHeadingLocal)
        .def_property("heading_var", &OxTS::GadHeading::GetHeadingVar, &OxTS::GadHeading::SetHeadingVar)
        .def_property("aiding_alignment_var", &OxTS::GadHeading::GetAidingAlignmentVar, UNPACK3(GadHeading, SetAidingAlignmentVar))
        .def_property("aiding_alignment_fixed", &OxTS::GadHeading::GetAidingAlignment, UNPACK3(GadHeading, SetAidingAlignmentFixed));

    py::class_<OxTS::GadAngularRate, OxTS::Gad>(m, "GadAngularRate")
        .def(py::init<uint8_t>(), py::arg("stream_id"))
        .def_property("angular_rate", &OxTS::GadAngularRate::GetAngularRate, &OxTS::GadAngularRate::SetAngularRate)
        .def_property("angular_rate_var", &OxTS::GadAngularRate::GetAngularRateVar, &OxTS::GadAngularRate::SetAngularRateVar)
        .def_property("aiding_alignment_var", &OxTS::GadAngularRate::GetAidingAlignmentVar, UNPACK3(GadAngularRate, SetAidingAlignmentVar))
        .def_property("aiding_alignment_fixed", &OxTS::GadAngularRate::GetAidingAlignment, UNPACK3(GadAngularRate, SetAidingAlignmentFixed));

    py::class_<OxTS::GadHandler>(m, "GadHandler")
        .def(py::init<>())
        // .def(py::init<OxTS::GadEncoder*>(), py::arg("encoder_strategy"))
        .def("set_encoder_to_bin", &OxTS::GadHandler::SetEncoderToBin)
        .def("set_encoder_to_csv", &OxTS::GadHandler::SetEncoderToCsv)
        .def("set_output_mode_to_file", &OxTS::GadHandler::SetOutputModeToFile, py::arg("file_path"))
        .def("set_output_mode_to_udp", &OxTS::GadHandler::SetOutputModeToUdp, py::arg("ip"))
        .def("send_packet", &OxTS::GadHandler::SendPacket, py::arg("gad"));

    py::class_<OxTS::GadEncoderCsv>(m,"GadEncoderCsv")
        .def(py::init<>())
        .def("encode_packet", &OxTS::GadEncoderCsv::EncodePacket, py::arg("gad"))
        .def("get_packet", &OxTS::GadEncoderCsv::GetPacket)
        .def("get_packet_size", &OxTS::GadEncoderCsv::GetPacketSize);

    py::class_<OxTS::GadEncoderBin>(m,"GadEncoderBin")
        .def(py::init<>())
        .def("encode_packet", &OxTS::GadEncoderBin::EncodePacket, py::arg("gad"))
        .def("get_packet", &OxTS::GadEncoderBin::GetPacket)
        .def("get_packet_size", &OxTS::GadEncoderBin::GetPacketSize);

    py::class_<OxTS::GadOutputUdp>(m,"GadOutputUdp")
        .def(py::init<std::string>(), py::arg("ip"))
        .def("output_packet", &OxTS::GadOutputUdp::OutputPacket, py::arg("gad_packet"), py::arg("packet_size"));

    py::class_<OxTS::GadOutputFile>(m,"GadOutputFile")
        .def(py::init<std::string>(), py::arg("file_path"))
        .def("output_packet", &OxTS::GadOutputFile::OutputPacket, py::arg("gad_packet"), py::arg("packet_size"))
        .def_property("output_file", &OxTS::GadOutputFile::GetOutputFile, &OxTS::GadOutputFile::SetOutputFile)
        .def_property("output_file_path", &OxTS::GadOutputFile::GetOutputFilePath, &OxTS::GadOutputFile::SetOutputFilePath);
}

