.. _ori_aidingtype:

Orientation
********

The orientation update works very similar to an attitude update, but gets registered differently with our system. While the attitude update only handles heading and pitch (ignoring roll), the orientation update handles all 3-axes inside the system. 

Each of the fields for this data type can be set using functions from the GadOrientation class.

Aiding Frames
-------------

Similar to the attitude update, orientation aiding can be provided in two frames:

•	**Vehicle frame** This frame is attached to the vehicle and rotates with it in all three axes with the heading, pitch and roll of the vehicle.
•	**User-defined local frame** Orientation of the sensor relative to a user-defined local reference frame. More information on how to define the frame itself can be found in the user-defined local frame section. 

For both frames, measurements are expected in degrees.

Covariance
----------

Covariance is used as an estimate of the accuracy of a measurement. Measurements with a smaller covariance will be given greater weight in the navigation solution, and any obvious outliers will be rejected by the navigation engine. The attitude covariance is expected in **degrees squared**. 
To learn more about covariance and how to derive the values you need, see :ref:`here <cov>`. In your code, you can either add a diagonal covariance matrix, or a full covariance matrix. Note that you will need to add covariance for both your data, and for your alignment.

Alignment
---------

Orientation measurements require an alignment instead of a lever arm. 
This is because the linear offset between the attitude sensor and the IMU does not affect the orientation  – you only need to account for the angular offset between the two.

**Fixed**

A fixed alignment is the simplest to set up, as it requires no external configuration. Set it within the generic aiding packet itself.

**Config**

A Config alignment is functionally equivalent to a fixed alignment. The difference is that the lever arm is set in the config file of the INS, instead of within the data packet.

Code examples
-------------

Here are two examples of how to configure the GadHandler to transmit orientation data.

**Example 1: Global frame, with a diagonal covariance matrix and fixed alignment.**

.. tabs::

   .. code-tab:: c++
   
		OxTS::Gal_Cpp::GadOrientation go(134); // Sets orientation aiding data to GAD stream ID 134
		go.SetOri(var_hea, var_pit, var_rol); // Set an orientation measurement in heading, pitch and roll
		go.SetOriVar(var_hea, var_pit, var_rol); // Diagonal covariance matrix
		go.SetAidingAlignmentFixed(3.0, 15.0, 0.0); // Set an alignment in the packet of 3 and 15 degrees respectively from the INS axes
		go.SetAidingAlignmentVar(1.0, 1.0, 4.0); // Set alignment covariance matrix to a diagonal matrix


	
   .. code-tab:: py
   
		go = oxts_sdk.GadOrientation(134) # Sets orientation aiding data to GAD stream ID 134
		go.ori = [heading, pitch, roll] # Set an orientation measurement in heading, pitch and roll
		go.ori_var = [var_hea, var_pit, var_rol] # Diagonal covariance matrix
		go.aiding_alignment_fixed = [3.0, 15.0, 0.0] # Set an alignment in the packet of 3 and 15 degrees respectively from the INS axes
		go.aiding_alignment_var = [1.0, 1.0, 4.0] # Set alignment covariance matrix to a diagonal matrix

**Example 2: User-defined Local Frame, with a diagonal covariance matrix and an alignment from the config file.**

.. tabs::

   .. code-tab:: c++
   
		OxTS::Gal_Cpp::GadOrientation go(134);  // Sets orientation aiding data to GAD stream ID 137
		go.SetOriLocal(hea, pit, rol); // Set an orientation measurement in heading, pitch and roll in local reference frame
		go.SetOriVar(var_hea, var_pit, var_rol); // Diagonal covariance matrix. Note there is no local orientation variance command
		go.SetAidingAlignmentConfig(); // Set alignment to 'config', i.e. set in the configuration file


	
   .. code-tab:: py
   
		go = oxts_sdk.GadOrientation(134) # Sets orientation aiding data to GAD stream ID 137
		go.ori_local = [heading, pitch, roll] # Set an orientation measurement in heading, pitch and roll in local reference frame
		go.ori_var = [var_hea, var_pit, var_rol] # Diagonal covariance matrix. Note there is no local orientation variance command. 
		go.set_aiding_alignment_config() # Set alignment to 'config', i.e. set in the configuration file

Note that, to make use of the local frame, you must define the local coordinate frame in the configuration of the INS. To do this, add the similar commands to the config file of your INS:

.. code-block:: c

		-gad_on134 //informs the system it should get gad aiding on stream 134
		-gad_lrf3_51.915_-1.244_94.597_-90.0_180.0_0.0 // This sets the lrf ID '3' with an example lat, long, alt, yaw, pitch, roll.
		-gad_lrf_id134_3 // Match the aiding stream with ID '134' with lrf ID '3'
		-rotation3_1.0_10.0_0.0_1.0_1.0_5.0 // # Set an alignment in the packet of 1, 10 and 0 degrees respectively from the INS axes. Also Set alignment covariance matrix to a diagonal matrix

**Note** it's good practice to use a number ID different than 1 for the lrf and orientation offset, since ID 1 might sometime be used for internal updates.