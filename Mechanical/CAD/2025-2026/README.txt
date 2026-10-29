#2025 CAD storage 

##Folder Structure


|   2025_Triton_Bots_Assembly.SLDASM
|   README.txt
|
+---Chassis				
|       25_Baseplate.SLDPRT	#Primary support structure for robot parts.
|       25_Cover_Top.SLDPRT	#Top circular profile. Used to protect internal components and house colored circles for robot ID.
|       25_Shell.SLDPRT		#Cylindrical shell surrounding the robot. Used for internal component protection.		
|
+---Dribbler
|       2025_Dribbler_Assembly.SLDASM		#Full assembly of Dribbler subsystem
|       25_Damper_Bracket.SLDPRT		#Secures connection between damper shaft and damper coupler
|       25_Damper_Coupler.SLDPRT		#Couples the damper shaft to the Dribbler body
|       25_Damper_Holder.SLDPRT			#Houses the damper for the dribbler through thread. Holder is coupled to /Housing>25_Damper_Plate
|       25_Dribbler_Body_Encoder_Side.SLDPRT	#Dribbler Body (side that houses the motor encoder). Main structural component of the Dribbler sub-system
|       25_Dribbler_Body_Gears_Side.SLDPRT	#Dribbler Body (side closes to gear-transmission system) Main structural component of the Dribbler 
|						 subsystem
|       25_Dribbler_Holder.SLDPRT		#Secures Dribbler assembly to the robot with heat-inserts. coupled to the middle plate.  		 
|	
|       25_Dribbler_Roller.SLDPRT		#Cylindrical Polyurethane part that makes direct contact with the ball. Responsible for dribbling ball
|       25_Midde_Plate.SLDPRT			#Provides support for the Dribbler assembly and /Mist>25_Kicker_PCB 
|
+---Drivetrain
|       2025_Drive_Train.SLDASM			
|       25_Drive_Train_Motor.SLDPRT
|       25_Motor_Mount.SLDPRT
|       25_Omniwheel_Assembly.SLDASM
|       25_Omniwheel_Internal_Roller.SLDPRT
|       25_Omniwheel_Profile.SLDPRT
|       25_Omniwheel_Roller.SLDPRT
|       25_Omniwheel_Roller_Shaft.SLDPRT
|
+---Housing
|       25_Arduino_Plate.SLDPRT
|       25_Battery_Mount.SLDPRT
|       25_Capacitor_Holder.SLDPRT
|       25_Damper_Plate.SLDPRT
|       25_IR_Holder_Left_Side.SLDPRT
|       25_IR_Holder_Right_Side.SLDPRT
|
+---Kicker
|       2025_kicker_assembly.SLDASM
|       25_Adafruit_Solenoid.SLDPRT
|       25_Kicker_Mount_Female.SLDPRT
|       25_Kicker_Mount_Male.SLDPRT
|       25_Kicker_Shaft.SLDPRT
|       25_Plunger.SLDPRT
|       25_Plunger_Coupler.SLDPRT
|       25_Shaft_Coupler.SLDPRT
|
+---Misc
|       15mmgear.SLDPRT
|       20240305-moteus-c1-r1_2.step
|       25_Arduino_UNO_R3_Shield.sldprt
|       25_Battery.SLDPRT
|       25_Capacitor.SLDPRT
|       25_Kicker_PCB.SLDPRT
|       25_Moteus_Controller.SLDPRT
|       26mmgear.SLDPRT
|       38mmgear.SLDPRT
|       5010_motor.step
|       baterry.step
|       BSC_2810_FPV_Dribbler_Motor.SLDPRT
|       field.SLDPRT
|       flange.SLDPRT
|       m3_Countersunk_Screw.SLDPRT
|       m3_Hex_Nut.SLDPRT
|
\---Reference_Parts
        MK3_plunger_body_v1.SLDPRT
        MK3_Solenoid_Coupling_v2.SLDPRT
        Damper_Bracket_Spare.SLDPRT		#Same function as 25_Damper_Bracket, but used for different (spare) damper. 
        DribblerUpsideDownV2_Encoder.SLDPRT	#Old version of Dribbler body (encoder side). 

##Sub-Systems Documentation 