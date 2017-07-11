Phidgets - LabVIEW Library

March 07, 2011

Extract the folder called "Phidgets" from the zip file to any location you want.

\Phidgets\Library directory contains Phidgets Labview library functions.

\Phidgets\Examples directory has various examples. We DO NOT recommend dropping examples into user's programs as sub-VIs. These examples are designed to demonstrate how to write user's own VIs only. Please also keep in mind that these examples might be designed by using different Phidgets hardware from the users. There will be a great chance that these examples are not executable or partial executable. Please refer to the product manual for specific functions supported on the user's own Phidgets hardware.

We also DO NOT recommend modifying any VIs from the folder. User can always make a copy in a different directory for different Labview versions.



There are 2 ways to call the Phidget Labview Library:



   1)  Store the folder anywhere and copy and paste library functions from the folder;


   2)  Call from the Labview function palette (Recommended). User needs to do the following:

	i) Open Labview and select "Tools" -> "Advanced" -> "Edit Palette Set...";
	ii) The "Edit Controls and Function Palette Set" will appear. Right click on the free space of the "Functions" palette, and select "Insert" -> "Subpalette...";
	iii) Select "Link to a directory". Choose the "Phidgets" folder and select "Current Folder". (If it's a 64-bit, choose the "PhidgetX64" folder instead.); 
	iv) Select "Save Changes" on the "Edit Controls and Functions Palette Set" palette and all Phidgets Labview functions will appear on the Labview function palette; 
	v) For a more detailed illustration, please refer to the Phidgets Labview Manual "2.3 Installation".


For more details, please refer to the Phidgets Labview Manual or Labview Manual.


