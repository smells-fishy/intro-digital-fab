---
layout: post
title:  "Week 2: My First Lab"
permalink: /02/Lab1
---

### Lab 1 (June 26)

During my first lab, I explored Arduino boards (as well as the Arduino programming language) and protoboard circuitry. At first, I started with a simple circuit to light a red LED using an Arduino board as a power source and a 100 ohm resistor. Initially, the circuit appeared to be dysfunctional, but upon re-examination it was discovered that the LED used was in fact an IR LED, resulting in an output in the non-visible infrared region. Once a red LED was connected, the LED visibly emitted light, indicating that the circuit was functional. I attempted to test the maximum voltage the LED could take by removing the resistor from the circuit, but upon reconnection, the LED burned out.

After exploring circuits, I attempted to manipulate the LED output using the Arduino programming language. Initially, I explored the "Blink" example packaged in the Arduino IDE, which causes an LED to alternate on/off cycles every second. I was able to manipulate the code to cause a single LED to blink ten times a second.

<img src="blink_arduino.png" alt="Blink program code">

Arduino's example blink code

<img src="ten_blink.png" alt="Blink program code">

My modified blink code

I continued to experiment with the code, moving on to making multiple lights blink simultaneously. I initially ran into issues involving the
<span markdown="1" style="background-color: lightgray; font-family:Courier New;">delay()</span>
function causing interrupts in the main loop in the Arduino code.

<img src="multiblink_one.png" alt="My initial attempt" style="height:492px; width:360px;">

My initial attempt at a program. The delays delay each other, and the two code blocks do not run simultaneously.

Attempts to run multiple
<span markdown="1" style="background-color: lightgray; font-family:Courier New;">void loop()</span>
simultaneously failed due to the Uno's single core being incapable of running multiple functions at once. However, after some experimentation and some inspiration from StackExchange and the Arduino Forums, I developed this program:

<img src="multiblink_one_s.png" alt="Code segment 1">
<img src="multiblink_two_s.png" alt="Code segment 1">

This program allows for multiple functions to run at the same time via calling in the
<span markdown="1" style="background-color: lightgray; font-family:Courier New;">void loop()</span>
. Each LED has its own timeOn variable to track how long it has been on in order to calculate when to switch next. (Note: The significance of the unsigned long variable is that Arduino's
<span markdown="1" style="background-color: lightgray; font-family:Courier New;">millis()</span>function resets after 50 days. An unsigned long integer in Arduino can store 32 bits, or values from 0 to 4,294,967,295. This amount of milliseconds corresponds to 49.7 days.)

<video width="955" height="541" controls>
	<source src="BLINK.MOV" type="video/mp4">
</video>

The takeaway from this lab is that Arduinos cannot run multiple functions at once, but there are ways around it. Possible improvements in my program would be to create a safeguard against integer overflow. which could potentially cause bugs/malfunctioning.