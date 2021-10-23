# turing-board-turning
This Repo contains code to drive a motor driver and/or a motor controller to drive and control the stepper motor used to turn the front wheels of the turing board

There are two files with a main: main.c and stepper_motor.c.
main.c runs the stepper motor in half steps (not smooth, but high torque)
stepper_motor runs the stepper motor in whatever step configuration the set angle corresponds to. (smooth, but weak torque)

to try out main.c, comment out the whole of stepper_motor.c
to try out stepper_motor.c, comment out the whole main.c
