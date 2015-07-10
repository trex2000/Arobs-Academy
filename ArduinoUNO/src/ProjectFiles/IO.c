enum{
EN_SIA_LIGHTSENSOR ,
SID_WIFICONTROLUP ,
SID_WIFIControlDown ,
SID_WIFIControlRight ,
SID_WIFIControlLeft ,
EN_NUMBER_OF_ELEMENTS_INPUT ,
}EN_INPUT_PINS


enum{
SOD_Motor12_0,
SOD_Motor12_1,
SOD_Motor12_2,
SOD_Motor12_3,
SODPWM_EnableMotor1 ,
SODPWM_EnableMotor2,
SOD_LeftFlasher,
SOD_RightFlasher,
SOD_LowBeam,
EN_NUMBER_OF_ELEMENTS_OUTPUTS
}EN_OUTPUT_PINS


enum
{
   EN_PORT_B,
   EN_PORT_C,
   EN_PORT_D,
   //EN_PORT_E
}EN_PORT_ENUMS

typedef struct
{
  uint8_t portVal_u8;
  EN_PORT_ENUMS  portType;
 }PORT_TYPES;
 
 
PORT_TYPES matchingTableOutputPins[EN_NUMBER_OF_ELEMENTS_OUTPUTS]={
    {PORTD2, EN_PORT_D},//SOD_Motor12_0
	{PORTD3, EN_PORT_D},//SOD_Motor12_1
	{PORTB6, EN_PORT_B},//SOD_Motor12_2
	{PORTB7, EN_PORT_B},//SOD_Motor12_3,
	{PORTD1, EN_PORT_D},//SODPWM_EnableMotor1 
	{PORTD5, EN_PORT_D},//SODPWM_EnableMotor2
	{PORTC2, EN_PORT_C},//SOD_LeftFlasher
	{PORTC1, EN_PORT_C},//SOD_RightFlasher
	{PORTD4, EN_PORT_D},//SOD_LowBeam
}



enum
{
  EN_PORT_DI,
  EN_PORT_DO,
  EN_PORT_AI,
  EN_PORT_DOPWM,
  EN_PORT_LAST_ELEMENT
}EN_PORT_TYPES

#define MAX_PWM_VALUE  100u
#define MAX_DIGITAL_VALUE 1u



EN_PORT_TYPES  cas_inputTypes[EN_NUMBER_OF_ELEMENTS_INPUT]
{
  	
	EN_PORT_AI,//EN_SIA_LIGHTSENSOR
	EN_PORT_DI  ,//SID_WIFICONTROLUP
	EN_PORT_DI  ,//SID_WIFIControlDown
	EN_PORT_DI  ,//SID_WIFIControlRight
	EN_PORT_DI  ,//SID_WIFIControlLeft

}	

void setOutputPort()
{
   uint8_t sw_pin_enum;
   for(sw_pin_enum=SOD_Motor12_0;sw_pin_enum<EN_OUTPUT_PINS; sw_pin_enum++)
   local_port_type_st = matchingTableOutputPins[sw_pin_enum].portType;
   local_port_number_lu8 = matchingTableOutputPins[sw_pin_enum].portVal_u8;
   switch(local_port_type_st)
   {
	 case EN_PORT_B:
	  DDRB | = (1 << local_port_number_lu8);
	  break;
	  case EN_PORT_C:
	  DDRC | = (1 << local_port_number_lu8);
	  break;
	  case EN_PORT_D:
	  DDRD | = (1 << local_port_number_lu8);
	  break;
	  //case EN_PORT_E:
	  //DDRE | = (1 << local_port_number_lu8); /* nu exista portul E*/
	  // break;
   }
   
}



uint8_t GetInputPin (EN_INPUT_PINS pinId_en);
{
	getValue(EN_INPUT_PINS); //functia care citeste starea pinilor digitali
   if (pinId_en>=EN_NUMBER_OF_ELEMENTS_INPUT)
   {
	  return 0;
   }
   else
   {
		return inputBuffer_st[pinId_en];
   }   
}


void setOutputPin (EN_INPUT_PINS pinId_en, uint8_t value_u8)
{
   if (pinId_en>=EN_NUMBER_OF_ELEMENTS_INPUT)
   {
	  return 0;
   }
   else
   {
		if ( getPortTypePWM(pinId_en))
		{
				//avem port cu pwm
				if (value_u8 <= MAX_PWM_VALUE)
				{
					outputBuffer_u8[pinId_en] = value_u8;
					DOPWM_setValue(EN_INPUT_PINS pinId_en, uint8_t value_u8); //setam ciclul PWM
				}
				else
				{
					//do nothing
				}			
		}
		else
		{ 
		 //nu este port cu pwm
		 if (value<=MAX_DIGITAL_VALUE)
		 {
			outputBuffer_u8[pinId_en] = value_u8;
			//functia de Set pini digitali
		 }
		 else
		 {
			//nu facem nimic
		 }
		}
		
  }
}

getPortTypePWM(EN_INPUT_PINS pinId_en)
{
	if (cas_inputTypes[pinId_en]==EN_PORT_DOPWM)
	{
		return TRUE;
	}
	else
	{
	    return FALSE;
	}
}

...
Task_20ms()
{
   getInputs();
   application1_Input_Aquisition()
   application1_StateMachine();
   application2_StateMAchine();
   ...
   application1_Output_Activation();
   aaplication2_Output_Activation();
   setOutputs();
}


Task_40ms()
{
  Application5_StateMachine();
  Application6_StateMachine();
}


//cyclic task 20ms
getinputs()
{
  //processing of digital inputs
  for (forIdx_en = EN_SIA_LIGHTSENSOR; forIdx_en<=EN_NUMBER_OF_ELEMENTS_INPUT; forIdx_en++)
  {
     input_type_len = cas_inputTypes[forIdx_en];
	 switch (input_type_len)
	 {
		case EN_PORT_DI:
		//citire valoare digitala
		//citim portul digital
		digitalRead(cas_PortMatchingInputs[forIdx_en]); //cas_PortMatching  este corespondenta intre EN_INPUT_PINS si EN_OUTPUT_PINS si id-ul porturilor fizice ce sunt folosite de digitalread
		inputBuffer_st[forIdx_en] = val_port;
		
		
		break;
		case EN_PORT_AI:
		//citire valoare analogica
		   if (conversionRunningFlag)
		   {
			//do not update buffers yet
		   }
		   else
		   {
			  val_conversie_analogica = REG_ANRESULT;
			  inputBuffer_st[forIdx_en] = val_conversie_analogica;
			  StartAnalogConversion();//
		   }
			  
		break;
		default:
		//nu facem nimic, e port de iesire
		break;
	 }
	 
  }
  
}

//functia data de arduino.h
setup()
{
   InitInputs();
}


InitInputs()
{
  //setaredirectie porturilor
  //setare rezulutie ADC
  //setare perioada PWM
  //setare Intreruperi
  StartAnalogConversion();
}