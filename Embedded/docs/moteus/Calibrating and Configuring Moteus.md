# Calibrating and Configuring Moteus

Created by: Sukhjeet Sekhon

# Instructions

1. Plug a USB-C cable into the fdcanusb x1 adapter
    1. Make sure the USB-C cable is data-capable and not a power-only cable
2. Unplug the Arduino CANFD Shield’s CAN wires from the CAN strip board
    1. The CANFD shield is the black board in the stack
3. Plug the fdcanusb x1 adapter’s CAN wire into the CAN strip board
4. Type into the Desktop search bar: “Terminal”
5. *Do once
    1. Type `pip3 install moteus-gui` into the terminal and press Enter to run the command
6. Paste into the terminal and press enter to run the telemetry viewer`python -m moteus_gui.tview`
7. Edit the parameters in the telemetry view on the left “config” panel
    1. Assign the correct `id` and set the servopos > max and min pos to `nan`
        1. Look at the motor assignment id
    2. Go to servo > max_current_A and set it to 8A for each motor
    3. Also go to servopos > max_position and min_position and set them to `NaN` if it’s `nan` please change it to `NaN` (not a huge deal, but I am not 100% sure if this affects anything)
    4. After setting all the motors, Type `conf write` in the telemetry viewer at the bottom of the window after making changes in the “config” panel to save
8. Run motor calibration with `python -m moteus.moteus_tool -t 1 --calibrate`
    1. Change `1` to the correct motor ID, which will be between 1 and 5
        1. default ID is `1` . Look at the motor assignment diagram below
            
            ![Diagram of Motor ID Configuration](..\Motor_ID_Configuration.png) <!--TODO: Fix the Image embed later-->
            
    2. Make sure to let the motor spin freely
    3. If nothing happens, then the ID is wrong or the USB-C cable is not transferring data, or the motor is not powered correctly, or the CAN wires are not wired correctly