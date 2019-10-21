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

#include <EIRremote.h>

/*============================================================*
 *                     VAR DECLARATIONS                       *
 *============================================================*/
//Some defines for the Remote Buttons (used for easier reading)
#define BTN_POWER 0xFFA25D
#define BTN_FUNC 0xFFE21D
#define BTN_VOLUP 0xFF629D
#define BTN_REWIND 0xFF22DD
#define BTN_PAUSE 0XFF02FD
#define BTN_FSTFWD 0xFFC23D
#define BTN_DOWN 0xFFE01F
#define BTN_VOLDWN 0xFFA857
#define BTN_UP 0xFF906F
#define BTN_EQ 0xFF9867
#define BTN_STREPT 0xFFB04F
#define BTN_0 0xFF6897
#define BTN_1 0xFF30CF
#define BTN_2 0xFF18E7
#define BTN_3 0xFF7A85
#define BTN_4 0xFF10EF
#define BTN_5 0xFF38C7
#define BTN_6 0xFF5AA5
#define BTN_7 0xFF42BD
#define BTN_8 0xFF4AB5
#define BTN_9 0xFF52AD

#define REPEAT 0xFFFFFFFF

class IR_Control{
private:
    IRrecv remote;
    decode_results prev_cmd;
    decode_results current_cmd;
public:
    IR_Control();
    ~IR_Control();
    void translateIR();
    
};

IR_Control::IR_Control(){
    remote.enableIRIn();
}

IR_Control::~IR_Control(){
}
