/*************************************************************************************************************************************************
 * File: PS2_Control.h
 * Author: Alex Westerman
 * Date Created: 10/20/2019
 * Description
 * ======================
 * This is a prototype file for the PS2_Control class, which defines Robot movement based on a PS2 Controller's input
 * 
 * Defined Values 
 * ======================
 * (Associated values are indicated in parenthesis beside the defined name)
 * DRIVE_FWD (1) - Value for the currentCMD associated with driving forward
 * DRIVE_BACKWARD (2) - Value for the currentCMD associated with driving backward
 * SPIN_LEFT (3) - Value for the currentCMD associated with spinning in place rotating counter-clockwise
 * SPIN_RIGHT (4) - Value for the currentCMD associated with spinning in place rotating clockwise
 * PIV_TRN_LEFT (5) - Value for the currentCMD associated with pivoting or turning toward the left
 * PIV_TRN_RIGHT (6) - Value for the currentCMD associated with pivoting or turning toward the right
 * GRAB (7) - Value for the currentCMD associated with activating the grabber
 *
 * V_I_B_E_S (0) - A required value for working with the PS2 Controller related to controller vibration strength
 * 
 * 
 * Class Variables
 * ======================
 * private PS2X* ps2_Gamepad - Pointer to a PS2 Controller object, used for reading input from a PS2 Controller
 * private Drive* robot - Pointer to a Drive object, used for controlling robot movement 
 * private int currentCMD - Integer used as a storage for the parsed input from the PS2 Controller
 * private boolean isTurnMode - Boolean serving as a toggle between pivoting and turning
 * 
 * Class Functions
 * ======================
 * public PS2_Control(PS2X*, Drive*) - Object Constructor
 * public ~PS2_Control() - Object Destructor (NOT USED)
 * public void init() - Initializaition function used to properly activate the PS2 Controller and Drive objects
 * public void read_controller() - Function that reads and converts input from the PS2 Controller to an int stored as currentCMD. Calls parseCMD() after execution
 * public void parseCMD() - Executes the proper movement based on the value of currentCMD 
 **************************************************************************************************************************************************/
#include <PS2X_lib.h>
#include <Drive.h>

#ifndef PS2_CONTROL_H_
#define PS2_CONTROL_H_

#define DRIVE_FWD 1
#define DRIVE_BACKWARD 2
#define SPIN_LEFT 3
#define SPIN_RIGHT 4
#define PIV_TRN_LEFT 5
#define PIV_TRN_RIGHT 6
#define GRAB 7

#define V_I_B_E_S 0

class PS2_Control {
 private:
    PS2X* ps2_Gamepad;
    Drive* robot;
    int currentCMD;
    boolean isTurnMode;
 public:
PS2_Control(PS2X* gamepad, Drive* robo) {
        ps2_Gamepad =gamepad;
        robot = robo;

}
~PS2_Control() {}
  void init();
  
  void read_controller();
  void parseCMD();
};

#endif
