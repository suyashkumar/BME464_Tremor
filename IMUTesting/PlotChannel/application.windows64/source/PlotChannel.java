import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.io.*; 
import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class PlotChannel extends PApplet {

/*
PlotChannel
Plot serial data in realtime, currently plotting pitch
@author Suyash Kumar
*/


Serial myPort;
int value;
int xPos = 1;
String readIn;
public void setup(){
  size(800, 600);
  String portName = Serial.list()[4]; 
  myPort = new Serial(this, portName, 9600); 
  background(0,0,0);
  myPort.bufferUntil('\n'); 
  
}
public void draw(){

}
public void serialEvent (Serial myPort) {
	 // Clear background
	 //background(0); 
	 // get the ASCII string:
	 String inString = myPort.readStringUntil('\n');
	 System.out.println(inString);
	 if (inString != null) {
		 // trim off any whitespace:
		 inString = trim(inString);
		 // convert to an int and map to the screen height:
                 //inString=inString.substring(1,5);
                 System.out.println(inString);
		 float inByte = PApplet.parseFloat(inString); 
		 inByte = map(inByte, -20, 90, 0, height);
		 
		 // draw the line:
		 stroke(127,34,255);
		 line(xPos, height, xPos, height - inByte); 
		 
		 // at the edge of the screen, go back to the beginning:
		 if (xPos >= width) {
			 xPos = 0;
			 background(0); 
		 } 
		 else {
			 // increment the horizontal position:
			 xPos++;
		 }
	 }
 }
 
public void changeColor(){
  background(0,100,0);
  
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "PlotChannel" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
