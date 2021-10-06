import oxts_sdk


gh = oxts_sdk.GadHandler()
gh.set_encoder_to_csv()
gh.set_output_mode_to_file("my_first.gad")

gp = oxts_sdk.GadPosition(122)
gp.pos_local = [0.5,0.6,0.7]
gp.pos_local_var = [0.1,0.1,0.1,0.01,0.02,0.04]
gp.time_gps = [10, 0]
gp.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gp.aiding_lever_arm_var = [0.01,0.01,0.01]

gv = oxts_sdk.GadVelocity(123)
gv.vel_neu = [0.0,0.0,0.0]
gv.vel_neu_var = [0.1,0.2,0.3]
gv.time_gps = [10, 0]
gv.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gv.aiding_lever_arm_var = [0.01,0.01,0.01]

gs = oxts_sdk.GadSpeed(124)
gs.wheelspeed_count = [3, 32]
gs.wheelspeed_var = 0.5
gv.time_gps = [10, 0]
gs.aiding_lever_arm_fixed = [0.0,0.0,1.0]
gs.aiding_lever_arm_var = [0.01,0.01,0.01]

num_packets = 100
# Send the packets
for i in range(0, num_packets):
    gh.send_packet(gp)
    gh.send_packet(gv)
    gh.send_packet(gs)
    gp.time_gps = [10, i]
    gv.time_gps = [10, i]
    gs.time_gps = [10, i]