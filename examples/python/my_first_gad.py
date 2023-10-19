import oxts_sdk

gad_handler = oxts_sdk.GadHandler()
gad_handler.set_encoder_to_csv()
gad_handler.set_output_mode_to_file("my_first.gad")

gp = oxts_sdk.GadPosition(129)
gp.pos_local = [0.5,0.6,0.7]
gp.pos_local_var = [0.11,0.12,0.13,0.01,0.02,0.04]
gp.time_gps = [10, 0]
gp.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gp.aiding_lever_arm_var = [0.01,0.01,0.01]

gv = oxts_sdk.GadVelocity(130)
gv.vel_ned = [0.0,0.0,0.0]
gv.vel_ned_var = [0.1,0.2,0.3]
gv.time_gps = [10, 0]
gv.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gv.aiding_lever_arm_var = [0.01,0.01,0.01]

gs = oxts_sdk.GadSpeed(131)
gs.wheelspeed_count = [3, 32]
gs.wheelspeed_var = 0.5
gs.time_gps = [10, 0]
gs.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gs.aiding_lever_arm_var = [0.01,0.01,0.01]

gh = oxts_sdk.GadHeading(132)
gh.heading = 180.0
gh.heading_var = 0.5
gh.time_gps = [10, 0]
gh.aiding_alignment_fixed = [180.0,0.0,0.0]
gh.aiding_alignment_var = [0.01,0.01,0.01]

ga = oxts_sdk.GadAngularRate(133)
ga.angular_rate = [0.0, 0.0, 0.0]
ga.angular_rate_var = [0.1, 0.1, 0.1]
ga.time_gps = [10, 0]
ga.aiding_alignment_fixed = [0.0,0.0,0.0]
ga.aiding_alignment_var = [0.01,0.01,0.01]

num_packets = 100
# Send the packets
for i in range(0, num_packets):
    gad_handler.send_packet(gp)
    gad_handler.send_packet(gv)
    gad_handler.send_packet(gs)
    gad_handler.send_packet(gh)
    gad_handler.send_packet(ga)
    gp.time_gps = [10, i]
    gv.time_gps = [10, i]
    gs.time_gps = [10, i]
    gh.time_gps = [10, i]
    ga.time_gps = [10, i]
