#  HiRes Interface Test

This program will run on a CoCo 3 and let the user test a Tandy Hi-Res Joystick Interface or CoCo Max III hi res interface.

Plug the unit into the casette and right joystick ports and then plug a joystick or mouse into the interface.

Start the program by typing:

 LOADM "JOY":EXEC

and slowly move the joystick or mouse to hit every point that the input device is capable of achieving.

You will see the program keep track of the minimum and maximum sampled values for both slow and fast processor speeds. It will also show the current value.

Press the 'S' key on the keyboard, and the program will calculate the mean between the min and max values. It will also display the number values returned between the minimum and maximum. This is called the "percent".

Press "G" to see a graphical representation of the values returned.

Press "T" to return to the information page.

Press "C" to clear all statistics.

Press "M" to switch to CoCo Max III mode.

Press "T" to switch back to Tandy mode.

The program throws away values below 20, and above 1000.

The disk also contains `JOY.BAS` which let you examine the joystick values with out a hi-res interface.

---

Here is how Martin H. Goodman described the device worked in the July 1987 issue of The Rainbow, p.78:

> The Interface consists of a quad op amp and an RC ramp generator circuit. Using a trigger signal from the cassette output line, it starts the ramp generator, and then timing loops in assembly language software are used to measure the exact amount of time it takes for the voltage in the RC circuit to rise to the level of the wiper of the pots in the joystick. By measuring this time very precisely, the joystick position can be read to 10 times the precision measured with the ordinary (6-bit DAC) joystick
port.

---

The program can be built using CMOC <http://perso.b2b2c.ca/~sarrazip/dev/cmoc.html>, LWTools <http://www.lwtools.ca>, and Toolshed <https://sourceforge.net/projects/toolshed/>.

---

tim lindner
<tlindner@macmess.org>
March 26, 2022
