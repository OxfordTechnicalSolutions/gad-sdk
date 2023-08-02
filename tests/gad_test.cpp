#define BOOST_TEST_MODULE GAD_Test
#include <boost/test/included/unit_test.hpp>

#include "oxts/gal-cpp/gad.hpp"
#include "oxts/gal-cpp/gad_encoders/gad_encoder_bin.hpp"
#include "oxts/gal-c/gad_decode.h"

namespace OxTS
{
	namespace Tests
	{
		namespace Gen3d
		{
			BOOST_AUTO_TEST_CASE(Gen3d_Mode)
			{
				OxTS::Gen3d g;

				g.SetMode(1);

				BOOST_CHECK(g.GetMode() == 1);
			}

			BOOST_AUTO_TEST_CASE(Gen3d_ValType)
			{
				OxTS::Gen3d g;

				g.SetValType(1);

				BOOST_CHECK(g.GetValType() == 1);
			}

			BOOST_AUTO_TEST_CASE(Gen3d_ValX)
			{
				OxTS::Gen3d g;

				g.SetValX(1.99);

				BOOST_CHECK(g.GetValX() == 1.99);
			}

			BOOST_AUTO_TEST_CASE(Gen3d_ValY)
			{
				OxTS::Gen3d g;

				g.SetValY(1.99);

				BOOST_CHECK(g.GetValY() == 1.99);
			}

			BOOST_AUTO_TEST_CASE(Gen3d_ValZ)
			{
				OxTS::Gen3d g;

				g.SetValZ(1.99);

				BOOST_CHECK(g.GetValZ() == 1.99);
			}

			BOOST_AUTO_TEST_CASE(Gen3d_Val)
			{
				OxTS::Gen3d g;

				g.SetVal(0.99, 1.99, 2.99);

				std::vector<double> ret = g.GetVal();
				BOOST_CHECK(ret[0] == 0.99);
				BOOST_CHECK(ret[1] == 1.99);
				BOOST_CHECK(ret[2] == 2.99);
			}

			BOOST_AUTO_TEST_CASE(Gen3d_SetVarUpperDiag)
			{
				OxTS::Gen3d g;

				g.SetVarUpperDiag(0.99, 1.99, 2.99, 3.99, 4.99, 5.99);

				BOOST_CHECK(g.GetVarType() == GEN_VAR_TYPE::GEN_VAR_HMAT);
				std::vector<double> ret = g.GetVar();
				BOOST_CHECK(ret[0] == 0.99);
				BOOST_CHECK(ret[1] == 1.99);
				BOOST_CHECK(ret[2] == 2.99);
				BOOST_CHECK(ret[3] == 3.99);
				BOOST_CHECK(ret[4] == 4.99);
				BOOST_CHECK(ret[5] == 5.99);
			}

			BOOST_AUTO_TEST_CASE(Gen3d_SetVarDiag)
			{
				OxTS::Gen3d g;

				g.SetVarDiag(0.99, 1.99, 2.99);

				BOOST_CHECK(g.GetVarType() == GEN_VAR_TYPE::GEN_VAR_DIAG);
				std::vector<double> ret = g.GetVar();
				BOOST_CHECK(ret[0] == 0.99);
				BOOST_CHECK(ret[1] == 1.99);
				BOOST_CHECK(ret[2] == 2.99);
			}

			BOOST_AUTO_TEST_CASE(Gen3d_SetVarSingle)
			{
				OxTS::Gen3d g;

				g.SetVarSingle(0.99);

				BOOST_CHECK(g.GetVarType() == GEN_VAR_TYPE::GEN_VAR_SINGLE);
				std::vector<double> ret = g.GetVar();
				BOOST_CHECK(ret[0] == 0.99);
			}
		}

		namespace Gad
		{
			BOOST_AUTO_TEST_CASE(Gad_StreamId)
			{
				OxTS::Gad g;

				g.SetStreamId(1);

				BOOST_CHECK(g.GetStreamId() == 1);
			}

			BOOST_AUTO_TEST_CASE(Gad_TimeValid)
			{
				OxTS::Gad g;

				g.SetTimeValid(true);

				BOOST_CHECK(g.GetTimeValid());

				g.SetTimeValid(false);

				BOOST_CHECK(!g.GetTimeValid());
			}

			BOOST_AUTO_TEST_CASE(Gad_TimeExternal)
			{
				OxTS::Gad g;

				g.SetTimeExternal(1, 2.5);

				BOOST_CHECK(g.GetTimeExternalWeek() == 1);
				BOOST_CHECK(g.GetTimeExternalSecondsFromSunday() == 2.5);
				BOOST_CHECK(g.GetTimeValid() == true);

				auto ret = g.GetTimeExternal();

				BOOST_CHECK(ret[0] == 1);
				BOOST_CHECK(ret[1] == 2.5);
			}

			BOOST_AUTO_TEST_CASE(Gad_TimeGPS)
			{
				OxTS::Gad g;

				g.SetTimeGps(1, 2.5);

				BOOST_CHECK(g.GetTimeGpsWeek() == 1);
				BOOST_CHECK(g.GetTimeGpsSecondsFromSunday() == 2.5);
				BOOST_CHECK(g.GetTimeValid() == true);

				auto ret = g.GetTimeGps();

				BOOST_CHECK(ret[0] == 1);
				BOOST_CHECK(ret[1] == 2.5);
			}

			BOOST_AUTO_TEST_CASE(Gad_TimePpsRelative)
			{
				OxTS::Gad g;

				g.SetTimePpsRelative(1.99);

				BOOST_CHECK(g.GetTimePpsRelative() == 1.99);
				BOOST_CHECK(g.GetTimeValid() == true);
			}

			BOOST_AUTO_TEST_CASE(Gad_TimeLatency)
			{
				OxTS::Gad g;

				g.SetTimeLatency(1.99);

				BOOST_CHECK(g.GetTimeLatency() == 1.99);
				BOOST_CHECK(g.GetTimeValid() == true);
			}

			BOOST_AUTO_TEST_CASE(Gad_TimeVoid)
			{
				OxTS::Gad g;

				g.SetTimeVoid();

				BOOST_CHECK(g.GetTimeValid() == true);
			}

			BOOST_AUTO_TEST_CASE(Gad_Res1Valid)
			{
				OxTS::Gad g;

				g.SetRes1Valid(true);

				BOOST_CHECK(g.GetRes1Valid());

				g.SetRes1Valid(false);

				BOOST_CHECK(!g.GetRes1Valid());
			}

			BOOST_AUTO_TEST_CASE(Gad_Res2Valid)
			{
				OxTS::Gad g;

				g.SetRes2Valid(true);

				BOOST_CHECK(g.GetRes2Valid());

				g.SetRes2Valid(false);

				BOOST_CHECK(!g.GetRes2Valid());
			}

			BOOST_AUTO_TEST_CASE(Gad_AcqValid)
			{
				OxTS::Gad g;

				g.SetAcqValid(true);

				BOOST_CHECK(g.GetAcqValid());

				g.SetAcqValid(false);

				BOOST_CHECK(!g.GetAcqValid());
			}

			BOOST_AUTO_TEST_CASE(Gad_AcqTimestamp)
			{
				OxTS::Gad g;

				g.SetAcqTimestamp(1);

				BOOST_CHECK(g.GetAcqValid());
				BOOST_CHECK(g.GetAcqTimestamp() == 1);

			}

			BOOST_AUTO_TEST_CASE(Gad_CStructConstructor)
			{
				OxTS::Gad g;

				g.SetTimeGps(1, 2.5);

				auto g_struct = g.getCStruct();

				OxTS::Gad g2(g_struct);


				BOOST_CHECK(g.GetTimeGps()[0] == g2.GetTimeGps()[0]);
				BOOST_CHECK(g.GetTimeGps()[1] == g2.GetTimeGps()[1]);
			}
		}

		namespace GadPosition
		{
			BOOST_AUTO_TEST_CASE(GadPosition_PosGeodetic)
			{
				OxTS::GadPosition g(0);

				g.SetPosGeodetic(1.99, 2.99, 3.99);

				auto ret = g.GetPos();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadPosition_PosLocal)
			{
				OxTS::GadPosition g(0);

				g.SetPosLocal(1.99, 2.99, 3.99);

				auto ret = g.GetPos();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadPosition_PosGeodeticVar3)
			{
				OxTS::GadPosition g(0);

				g.SetPosGeodeticVar(1.99, 2.99, 3.99);

				auto ret = g.GetPosVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadPosition_PosGeodeticVar6)
			{
				OxTS::GadPosition g(0);

				g.SetPosGeodeticVar(1.99, 2.99, 3.99, 4.99, 5.99, 6.99);

				auto ret = g.GetPosVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
				BOOST_CHECK(ret[3] == 4.99);
				BOOST_CHECK(ret[4] == 5.99);
				BOOST_CHECK(ret[5] == 6.99);
			}

			BOOST_AUTO_TEST_CASE(GadPosition_PosLocalVar3)
			{
				OxTS::GadPosition g(0);

				g.SetPosLocalVar(1.99, 2.99, 3.99);

				auto ret = g.GetPosVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadPosition_PosLocalVar6)
			{
				OxTS::GadPosition g(0);

				g.SetPosLocalVar(1.99, 2.99, 3.99, 4.99, 5.99, 6.99);

				auto ret = g.GetPosVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
				BOOST_CHECK(ret[3] == 4.99);
				BOOST_CHECK(ret[4] == 5.99);
				BOOST_CHECK(ret[5] == 6.99);
			}

			BOOST_AUTO_TEST_CASE(GadPosition_AidingLeverArmFixed)
			{
				OxTS::GadPosition g(0);

				g.SetAidingLeverArmFixed(1.99, 2.99, 3.99);

				auto ret = g.GetAidingLeverArm();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}
			BOOST_AUTO_TEST_CASE(GadPosition_AidingLeverArmVar)
			{
				OxTS::GadPosition g(0);

				g.SetAidingLeverArmVar(1.99, 2.99, 3.99);

				auto ret = g.GetAidingLeverArmVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}
			BOOST_AUTO_TEST_CASE(GadPosition_AidingLeverArmVarUpperDiag)
			{
				OxTS::GadPosition g(0);

				g.SetAidingLeverArmVarUpperDiag(1.99, 2.99, 3.99, 4.99, 5.99, 6.99);

				auto ret = g.GetAidingLeverArmVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
				BOOST_CHECK(ret[3] == 4.99);
				BOOST_CHECK(ret[4] == 5.99);
				BOOST_CHECK(ret[5] == 6.99);
			}

		}

		namespace GadVelocity
		{
			BOOST_AUTO_TEST_CASE(GadVelocity_VelNed)
			{
				OxTS::GadVelocity g(0);

				g.SetVelNed(1.99, 2.99, 3.99);

				auto ret = g.GetVel();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadVelocity_VelOdom)
			{
				OxTS::GadVelocity g(0);

				g.SetVelOdom(1.99, 2.99, 3.99);

				auto ret = g.GetVel();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadVelocity_VelLocal)
			{
				OxTS::GadVelocity g(0);

				g.SetVelLocal(1.99, 2.99, 3.99);

				auto ret = g.GetVel();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadVelocity_VelNedVar3)
			{
				OxTS::GadVelocity g(0);

				g.SetVelNedVar(1.99, 2.99, 3.99);

				auto ret = g.GetVelVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadVelocity_VelNedVar6)
			{
				OxTS::GadVelocity g(0);

				g.SetVelNedVar(1.99, 2.99, 3.99, 4.99, 5.99, 6.99);

				auto ret = g.GetVelVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
				BOOST_CHECK(ret[3] == 4.99);
				BOOST_CHECK(ret[4] == 5.99);
				BOOST_CHECK(ret[5] == 6.99);
			}

			BOOST_AUTO_TEST_CASE(GadVelocity_VelOdomVar3)
			{
				OxTS::GadVelocity g(0);

				g.SetVelOdomVar(1.99, 2.99, 3.99);

				auto ret = g.GetVelVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadVelocity_VelOdomVar6)
			{
				OxTS::GadVelocity g(0);

				g.SetVelOdomVar(1.99, 2.99, 3.99, 4.99, 5.99, 6.99);

				auto ret = g.GetVelVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
				BOOST_CHECK(ret[3] == 4.99);
				BOOST_CHECK(ret[4] == 5.99);
				BOOST_CHECK(ret[5] == 6.99);
			}

			BOOST_AUTO_TEST_CASE(GadVelocity_VelLocalVar3)
			{
				OxTS::GadVelocity g(0);

				g.SetVelLocalVar(1.99, 2.99, 3.99);

				auto ret = g.GetVelVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadVelocity_VelLocalVar6)
			{
				OxTS::GadVelocity g(0);

				g.SetVelLocalVar(1.99, 2.99, 3.99, 4.99, 5.99, 6.99);

				auto ret = g.GetVelVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
				BOOST_CHECK(ret[3] == 4.99);
				BOOST_CHECK(ret[4] == 5.99);
				BOOST_CHECK(ret[5] == 6.99);
			}

			BOOST_AUTO_TEST_CASE(GadVelocity_AidingLeverArmFixed)
			{
				OxTS::GadVelocity g(0);

				g.SetAidingLeverArmFixed(1.99, 2.99, 3.99);

				auto ret = g.GetAidingLeverArm();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadVelocity_AidingLeverArmVar)
			{
				OxTS::GadVelocity g(0);

				g.SetAidingLeverArmVar(1.99, 2.99, 3.99);

				auto ret = g.GetAidingLeverArmVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}
		}

		namespace GadSpeed
		{
			BOOST_AUTO_TEST_CASE(GadSpeed_SpeedFw)
			{
				OxTS::GadSpeed g(0);

				g.SetSpeedFw(1.99);

				BOOST_CHECK(g.GetSpeedFw() == 1.99);
			}

			BOOST_AUTO_TEST_CASE(GadSpeed_SpeedFwVar)
			{
				OxTS::GadSpeed g(0);

				g.SetSpeedFwVar(1.99);

				BOOST_CHECK(g.GetSpeedFwVar() == 1.99);
			}

			BOOST_AUTO_TEST_CASE(GadSpeed_WheelSpeedCount)
			{
				OxTS::GadSpeed g(0);

				g.SetWheelspeedCount(1.99, 2.99);

				auto ret = g.GetWheelspeedCount();
				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
			}

			BOOST_AUTO_TEST_CASE(GadSpeed_AidingLeverArmFixed)
			{
				OxTS::GadSpeed g(0);

				g.SetAidingLeverArmFixed(1.99, 2.99, 3.99);

				auto ret = g.GetAidingLeverArm();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadSpeed_AidingLeverArmVar)
			{
				OxTS::GadSpeed g(0);

				g.SetAidingLeverArmVar(1.99, 2.99, 3.99);

				auto ret = g.GetAidingLeverArmVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}
		}

		namespace GadAttititude
		{
			BOOST_AUTO_TEST_CASE(GadAttitude_Att)
			{
				OxTS::GadAttitude g(0);

				g.SetAtt(1.99, 2.99, 3.99);

				auto ret = g.GetAtt();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}

			BOOST_AUTO_TEST_CASE(GadAttitude_AttVar)
			{
				OxTS::GadAttitude g(0);

				g.SetAttVar(1.99, 2.99, 3.99);

				auto ret = g.GetAttVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
			}
		}

		namespace GadEncoderBin
		{
			//Testing encode + decode
			BOOST_AUTO_TEST_CASE(GadEncoderBin_Position)
			{
				OxTS::Gad g;

				g.SetTimeGps(1, 2.5);

				OxTS::GadEncoderBin enc;

				enc.EncodePacket(g);

				GEN_AIDING_DATA g_struct;

				//encoded packet without CCOM header
				int decoded = update_genaid_from_bin(&g_struct, enc.GetPacket() + 8, enc.GetPacketSize() - 8);

				BOOST_CHECK(decoded == 0);

				OxTS::Gad ret_g(g_struct);

				auto ret = ret_g.GetTimeGps();

				BOOST_CHECK(ret[0] == 1);
				BOOST_CHECK(ret[1] == 2.5);
			}
		}
		namespace GadEncoderCSV
		{
		}

		namespace GadOutputFile
		{
		}

		//C functions
		namespace gad_decode
		{
			/*
			**Tested as part of gad_encode_bin functions** Requires offsets **
			int decode_gen3d_bin(GEN_3D* field, unsigned char* b, size_t* b_offset);
			int decode_gen3d_var_bin(GEN_3D* field, unsigned char* b, size_t* b_offset);
			**NOT TESTED**
			int decode_acq_timestamp_bin(uint32_t* acq_time, unsigned char* b, size_t *b_offset);
			*/

			BOOST_AUTO_TEST_CASE(GadDecode_update_genaid_from_bin)
			{
				GEN_AIDING_DATA g_struct;

				//this should probably fail for any garbage data but give it specific data for now
				unsigned char garbage[100] = { 9 };

				int decoded = update_genaid_from_bin(&g_struct, garbage, 100);

				BOOST_CHECK(decoded != 0);
			}

			BOOST_AUTO_TEST_CASE(GadDecode_genaid_basic_checks_bin)
			{
				OxTS::Gad g;

				g.SetTimeGps(1, 2.5);

				OxTS::GadEncoderBin enc;

				enc.EncodePacket(g);

				//encoded packet without CCOM header
				int check = genaid_basic_checks_bin(enc.GetPacket() + 8, enc.GetPacketSize() - 8);

				BOOST_CHECK(check == 0);

				//this should probably fail for any garbage data but give it specific data for now
				unsigned char garbage[100] = {255};

				//garbage data
				check = genaid_basic_checks_bin(garbage, 100);

				BOOST_CHECK(check != 0);
			}
		}

		namespace gad_encode_bin
		{
			BOOST_AUTO_TEST_CASE(GadEncodeBin_encode_gen_aid)
			{
				OxTS::Gad g;

				g.SetTimeGps(1, 2.5);

				GEN_AIDING_DATA g_c_struct = g.getCStruct();

				OxTS::GadEncoderBin enc;

				enc.EncodePacket(g);

				unsigned char buffer[256] = { 0 };

				size_t buffer_usage;

				int encoded = encode_gen_aid(&g_c_struct, buffer, 256, &buffer_usage);

				BOOST_CHECK(encoded == 0);

				unsigned char* cpp_buffer = enc.GetPacket();

				//check C and C++ decoders match
				//-8 for CCOM header
				BOOST_CHECK(buffer_usage == enc.GetPacketSize() - 8);

				for (int i = 0; i < buffer_usage; ++i)
				{

					//cpp adds CCOM header
					BOOST_CHECK(buffer[i] == cpp_buffer[i + 8]);
				}

				GEN_AIDING_DATA g_c_struct_out = g.getCStruct();

				//check decoded data matches encoded
				int decoded = update_genaid_from_bin(&g_c_struct_out, buffer, buffer_usage);

				BOOST_CHECK(decoded == 0);

				OxTS::Gad ret_g(g_c_struct_out);

				auto ret = ret_g.GetTimeGps();

				BOOST_CHECK(ret[0] == 1);
				BOOST_CHECK(ret[1] == 2.5);
			}

			BOOST_AUTO_TEST_CASE(GadEncodeBin_encode_gen_3d)
			{
				OxTS::Gad g;

				g.SetTimeGps(1, 2.5);

				GEN_AIDING_DATA g_c_struct = g.getCStruct();

				OxTS::GadEncoderBin enc;

				enc.EncodePacket(g);

				unsigned char buffer[256];

				size_t buffer_size = 256;

				size_t offset = 0;

				int encoded = encode_gen_3d(g_c_struct.time, buffer, &offset, buffer_size);

				BOOST_CHECK(encoded == 0);

				OxTS::Gad g2;
				GEN_AIDING_DATA g_c_struct_out = g2.getCStruct();

				offset = 0;

				int decoded = decode_gen3d_bin(&g_c_struct_out.time, buffer, &offset);

				BOOST_CHECK(decoded == 0);

				OxTS::Gad ret_g(g_c_struct_out);

				auto ret = ret_g.GetTimeGps();

				BOOST_CHECK(ret[0] == 1);
				BOOST_CHECK(ret[1] == 2.5);
			}

			BOOST_AUTO_TEST_CASE(GadEncodeBin_encode_gen_3d_var)
			{
				OxTS::GadVelocity g(0);

				g.SetVelLocalVar(1.99, 2.99, 3.99, 4.99, 5.99, 6.99);

				GEN_AIDING_DATA g_c_struct = g.getCStruct();

				OxTS::GadEncoderBin enc;

				enc.EncodePacket(g);

				unsigned char buffer[256];

				size_t buffer_size = 256;

				size_t offset = 0;

				int encoded = encode_gen_3d_var(g_c_struct.val, buffer, &offset, buffer_size);

				BOOST_CHECK(encoded == 0);

				OxTS::Gad g2;
				GEN_AIDING_DATA g_c_struct_out = g2.getCStruct();

				offset = 0;

				int decoded = decode_gen3d_var_bin(&g_c_struct_out.val, buffer, &offset);

				BOOST_CHECK(decoded == 0);

				OxTS::Gad gad_temp = OxTS::Gad(g_c_struct_out);

				OxTS::GadVelocity* ret_g = static_cast<OxTS::GadVelocity*>(&gad_temp);

				auto ret = ret_g->GetVelVar();

				BOOST_CHECK(ret[0] == 1.99);
				BOOST_CHECK(ret[1] == 2.99);
				BOOST_CHECK(ret[2] == 3.99);
				BOOST_CHECK(ret[3] == 4.99);
				BOOST_CHECK(ret[4] == 5.99);
				BOOST_CHECK(ret[5] == 6.99);
			}

			BOOST_AUTO_TEST_CASE(GadEncodeBin_buffer_overrun_chk)
			{
				BOOST_CHECK(buffer_overrun_chk(1, 2) != 0);
				BOOST_CHECK(buffer_overrun_chk(2, 1) == 0);
			}
		}

		namespace gad_encode_csv
		{
			//**NOT TESTED*** No Decoder
		}
	}
}
