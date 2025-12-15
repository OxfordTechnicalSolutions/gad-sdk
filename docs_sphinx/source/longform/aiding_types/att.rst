.. _att_aidingtype:

Attitude
********

Attitude is the term used for orientation.

Each of the fields for this data type can be set using functions from the GadAttitude class.

Aiding Frames
-------------

Attitude aiding can be provided with respect to two frames:

•	**Global NED frame** In this case, the measurement should be described in the North, East, Down (NED) frame (see :ref:`Frames <Frames>` section).
•	**User-defined local frame** Orientation of the sensor relative to a user-defined local reference frame. More information on how to define the frame itself can be found in the user-defined local frame section. 

For both frames, measurements are expected in degrees.

Covariance
----------

Covariance is used as an estimate of the accuracy of a measurement. Measurements with a smaller covariance will be given greater weight in the navigation solution, and any obvious outliers will be rejected by the navigation engine. The attitude covariance is expected in degrees squared. 
To learn more about covariance and how to derive the values you need, see :ref:`here <cov>`. In your code, you can either add a diagonal covariance matrix, or a full covariance matrix. Note that you will need to add covariance for both your data, and for your alignment.

Alignment
---------

Attitude measurements require an alignment instead of a lever arm. 
This is because the linear offset between the attitude sensor and the IMU does not affect the orientation  – you only need to account for the angular offset between the two.

**Fixed**

A fixed alignment is the simplest to set up, as it requires no external configuration. Set it within the generic aiding packet itself.

**Config**

A Config alignment is functionally equivalent to a fixed alignment. The difference is that the lever arm is set in the config file of the INS, instead of within the data packet.

Code examples
-------------

Here are two examples of how to configure the GadHandler to transmit attitude data.

**Example 1: Global frame, with a diagonal covariance matrix and fixed alignment.**

.. tabs::

   .. code-tab:: c++
   
		OxTS::Gal_Cpp::GadAttitude ga(134); // Sets attitude aiding data to GAD stream ID 134
		ga.SetAtt(hea, pit, rol); // Set an attitude measurement in heading, pitch and roll
		ga.SetAttVar(var_hea, var_pit, var_rol); // Diagonal covariance matrix
		ga.SetAidingAlignmentFixed(3.0, 15.0, 0.0); // Set an alignment in the packet of 3 and 15 degrees respectively from the INS axes
		ga.SetAidingAlignmentVar(1.0, 1.0, 4.0); // Set alignment covariance matrix to a diagonal matrix


	
   .. code-tab:: py
   
		ga = oxts_sdk.GadAttitude(134) # Sets attitude aiding data to GAD stream ID 134
		ga.att = [heading, pitch, roll] # Set an attitude measurement in heading, pitch and roll
		ga.att_var = [var_hea, var_pit, var_rol] # Diagonal covariance matrix
		ga.aiding_alignment_fixed = [3.0, 15.0, 0.0] # Set an alignment in the packet of 3 and 15 degrees respectively from the INS axes
		ga.aiding_alignment_var = [1.0, 1.0, 4.0] # Set alignment covariance matrix to a diagonal matrix

**Example 2: User-defined Local Frame, with a diagonal covariance matrix and an alignment from the config file.**

.. tabs::

   .. code-tab:: c++
   
		OxTS::Gal_Cpp::GadAttitude ga(134);  // Sets attitude aiding data to GAD stream ID 137
		ga.SetAttLocal(hea, pit, rol); // Set an attitude measurement in heading, pitch and roll in local reference frame
		ga.SetAttVar(var_hea, var_pit, var_rol); // Diagonal covariance matrix. Note there is no local attitude variance command
		ga.SetAidingAlignmentConfig(); // Set alignment to 'config', i.e. set in the configuration file


	
   .. code-tab:: py
   
		ga = oxts_sdk.GadAttitude(134) # Sets attitude aiding data to GAD stream ID 137
		ga.att_local = [heading, pitch, roll] # Set an attitude measurement in heading, pitch and roll in local reference frame
		ga.att_var = [var_hea, var_pit, var_rol] # Diagonal covariance matrix. Note there is no local attitude variance command. 
		ga.set_aiding_alignment_config() # Set alignment to 'config', i.e. set in the configuration file

Note that, to make use of the local frame, you must define the local coordinate frame in the configuration of the INS. To do this, add the similar commands to the config file of your INS:

.. code-block:: c

		-gad_lrf2_51.915_-1.244_94.597_-90.0_180.0_0.0 // This sets the lrf ID '1' with an example lat, long, alt, yaw, pitch, roll.
		-gad_lrf_id134_1 // Match the aiding stream with ID '134' with lrf ID '1'
		-rotation1_1.0_10.0_0.0_1.0_1.0_5.0 // # Set an alignment in the packet of 1, 10 and 0 degrees respectively from the INS axes. Also Set alignment covariance matrix to a diagonal matrix

