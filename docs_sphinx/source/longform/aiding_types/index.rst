.. _aidingtypes:


Aiding types
############

An OxTS INS can currently accept five fundamental aiding types through the 
Generic Aiding interface:

-	:ref:`Position <pos_aidingtype>`
-	:ref:`Velocity <vel_aidingtype>`
-	:ref:`Speed <spe_aidingtype>`
-	:ref:`Attitude <att_aidingtype>`
-	:ref:`Heading <hea_aidingtype>`


Each of these aiding types will require a slightly different setup, but they 
follow a common pattern:

-	Measurement
-	Measurement accuracy (covariance)
-	Timestamp
-	IMU-sensor transform (lever arm, rotation alignment, or both)
-	IMU-sensor transform accuracy (covariance)

For each aiding type we will explain how to send data of that type and give 
a code example. Before diving into the page for a specific aiding type, 
it's worth considering what type of aiding you are considering sending to the 
INS. This will be dictated by the sensors you have available and the 
measurements those sensors can output. 


