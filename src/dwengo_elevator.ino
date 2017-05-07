#include <math.h>
#include <Arduino.h>

#include <LiquidCrystal.h>
#include <Wire.h>
#include <Dwenguino.h>
#include <DwenguinoMotor.h> // the motor library

// We hebben 1 motor nodig om de lift te bedienen.
// We sluiten deze aan op de tweede poort.
DCMotor dcMotor1(MOTOR_1_0, MOTOR_1_1);

// We moeten bijhouden welke knop werd ingedrukt om te beslissen of we de lift omhoog dan wel omlaang moeten doen.
bool is_button_pressed, button_pressed;

// We stellen de bewegingssnelheid in als constante
int LIFT_SPEED = 255;
int LIFT_TIME = 200;

// We houden de laatste verdieping bij waar de lift gestopt is.
int current_lift_floor = 0;

// Bepaal de tijd die nodig is om de lift 1 cm omhoog te verplaatsen met de aangegeven snelheid
int time_required_to_move_up_one_cm(int speed) {
    // na metingen, bekwamen de volgende formule: y = 14843 x^(-1.1225)
    return int(14843 * pow(speed, -1.1225));
}

// Bepaal de tijd die nodig is om de lift 1 cm omlaag te verplaatsen met de aangegeven snelheid
int time_required_to_move_down_one_cm(int speed) {
    // na metingen, bekwamen de volgende formule: y = 5138.5 x^(0.9447)
    return int(5138.5 * pow(speed, -0.9447));
}


void setup() {
  initDwenguino();

  is_button_pressed = false;
  button_pressed = false;
}

void move_lift_up() {
  dcMotor1.setSpeed(LIFT_SPEED);
  delay(time_required_to_move_up_one_cm(LIFT_SPEED));
  dcMotor1.setSpeed(0);
}

void move_lift_down() {
  dcMotor1.setSpeed(-LIFT_SPEED);
  delay(time_required_to_move_down_one_cm(LIFT_SPEED));
  dcMotor1.setSpeed(0);
}

void loop() {

    is_button_pressed = false;
    while(!is_button_pressed) {
        is_button_pressed = true;
        if(digitalRead(SW_S) == PRESSED) {
            move_lift_down();
            
        }
        else if(digitalRead(SW_N) == PRESSED) {
            move_lift_up();
        }
        else {
            is_button_pressed = false;
        }
    }
    delay(250); // wachten op de volgende druk
}
