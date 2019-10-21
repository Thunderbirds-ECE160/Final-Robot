/*************************************************************************************************************************************************
 * Project:
 * Author: Alex Westerman
 * Date Created:
 * Description
 * ======================
 *
 *
 * Important Functions
 * ======================
 *
 *
 * Misc Functions
 * ======================
 *
 *
 **************************************************************************************************************************************************/
#include <PS2X_lib.h>
#include <Drive.h>
#include "cpu_map.h"

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
  PS2_Control(PS2X, Drive);
  ~PS2_Control();

  void init();
  
  void read_controller();
  void parseCMD();
};

PS2_Control::PS2_Control(PS2X gamepad, Drive robo) {
        ps2_Gamepad =&gamepad;
        robot = &robo;
\
}

PS2_Control::~PS2_Control() {}
