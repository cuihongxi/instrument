//--------------------------------------
//General Definition of the Sensors
//--------------------------------------



//-------POWER_UP_INTERRUPT-------------------------------------------------//
//This value is defined based on the number of stages you have configured.
//e.g. If you configured stages 0 - 5 inc then this value must be 0x003F
//For each Single-Ended or Activation stage we must set one bit on this value
//If we configure more than one input on one stage Differentially, 
//these inputs must also be configured on a different stage 
//in single ended mode for calibration purposes
//Any low limit interrupt on these bits will force calibration
//*****************************************************************************//
//********** Please Double Check this value based on your configuration********//
//*****************************************************************************//
//-----------------------------------------------------------------------------//


//---------------------
//Function declarations
//---------------------
void ConfigAD7147(void);


