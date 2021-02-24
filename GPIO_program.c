/*
 * GPIO_program.c
 *
 *  Created on: Feb 3, 2021
 *      Author: Boon
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

/*void	DIO_voidSetPinDirection(port,pin,mode);*/
void	DIO_voidSetPinDirection(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8Mode)
{
	/*		Range Check							*/
	if( (Copy_u8PortID<3) && (Copy_u8PinID<16) )
	{
		switch(Copy_u8PortID)
		{
		case DIO_U8_PORTA:
			/*		LOW PORT				*/
			if( Copy_u8PinID < 8 )
			{
				/*	To deal with Bit Masking 1- Clear a specific Bits 2- Assign a specific Bits	*/
				GPIOA_CRL &= ~((u32)(0b1111)<<(Copy_u8PinID * 4));
				GPIOA_CRL |=  ((u32)(Copy_u8Mode)<<(Copy_u8PinID * 4));
			}
			/*		HIGH PORT				*/
			else
			{
				Copy_u8PinID -= 8 ;
				/*	To deal with Bit Masking 1- Clear a specific Bits 2- Assign a specific Bits	*/
				GPIOA_CRH &= ~((u32)(0b1111)<<(Copy_u8PinID * 4));
				GPIOA_CRH |=  ((u32)(Copy_u8Mode)<<(Copy_u8PinID * 4));
			}
			break;
		case DIO_U8_PORTB:
			if( Copy_u8PinID < 8 )
			{
				/*	To deal with Bit Masking 1- Clear a specific Bits 2- Assign a specific Bits	*/
				GPIOB_CRL &= ~((u32)(0b1111)<<(Copy_u8PinID * 4));
				GPIOB_CRL |=  ((u32)(Copy_u8Mode)<<(Copy_u8PinID * 4));
			}
			/*		HIGH PORT				*/
			else
			{
				Copy_u8PinID -= 8 ;
				/*	To deal with Bit Masking 1- Clear a specific Bits 2- Assign a specific Bits	*/
				GPIOB_CRH &= ~((u32)(0b1111)<<(Copy_u8PinID * 4));
				GPIOB_CRH |=  ((u32)(Copy_u8Mode)<<(Copy_u8PinID * 4));
			}
			break;
		case DIO_U8_PORTC:
			if( Copy_u8PinID < 8 )
			{
				/*	To deal with Bit Masking 1- Clear a specific Bits 2- Assign a specific Bits	*/
				GPIOC_CRL &= ~((u32)(0b1111)<<(Copy_u8PinID * 4));
				GPIOC_CRL |=  ((u32)(Copy_u8Mode)<<(Copy_u8PinID * 4));
			}
			/*		HIGH PORT				*/
			else
			{
				Copy_u8PinID -= 8 ;
				/*	To deal with Bit Masking 1- Clear a specific Bits 2- Assign a specific Bits	*/
				GPIOC_CRH &= ~((u32)(0b1111)<<(Copy_u8PinID * 4));
				GPIOC_CRH |=  ((u32)(Copy_u8Mode)<<(Copy_u8PinID * 4));
			}
			break;
		}
	}else{/*	Return ERROR	*/}

}
/*		if Pin is Output (High or Low)	*/
void	DIO_voidSetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8Value)
{
	/*		Range Check							*/
	if( (Copy_u8PortID<3) && (Copy_u8PinID<16) )
	{
		switch(Copy_u8PortID)
		{
		case DIO_U8_PORTA:
			switch(Copy_u8Value)
			{
			case DIO_U8_HIGH:	SET_BIT(GPIOA_ODR , Copy_u8PinID);	break;
			case DIO_U8_LOW	:	CLR_BIT(GPIOA_ODR , Copy_u8PinID);	break;
			default:;	/*		Return ERROR		*/
			}
			break;
			case DIO_U8_PORTB:
				switch(Copy_u8Value)
				{
				case DIO_U8_HIGH:	SET_BIT(GPIOB_ODR , Copy_u8PinID);	break;
				case DIO_U8_LOW	:	CLR_BIT(GPIOB_ODR , Copy_u8PinID);	break;
				default:;	/*		Return ERROR		*/
				}
				break;
				case DIO_U8_PORTC:
					switch(Copy_u8Value)
					{
					case DIO_U8_HIGH:	SET_BIT(GPIOC_ODR , Copy_u8PinID);	break;
					case DIO_U8_LOW	:	CLR_BIT(GPIOC_ODR , Copy_u8PinID);	break;
					default:;	/*		Return ERROR		*/
					}
					break;
		}
	}else{/*	Return ERROR	*/}
}
/*		if Pin is Input (Return High or Low)	*/
u8		DIO_u8GetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinID)
{
	u8 Local_u8Value = 0XFF;
	/*		Range Check							*/
	if( (Copy_u8PortID<3) && (Copy_u8PinID<16) )
	{

		switch(Copy_u8PortID)
		{
		case DIO_U8_PORTA:	Local_u8Value = GET_BIT(GPIOA_IDR , Copy_u8PinID);	break;
		case DIO_U8_PORTB:	Local_u8Value = GET_BIT(GPIOB_IDR , Copy_u8PinID);	break;
		case DIO_U8_PORTC:	Local_u8Value = GET_BIT(GPIOC_IDR , Copy_u8PinID);	break;

		}
	}else{/*	Return ERROR	*/}

	return Local_u8Value;
}

void DIO_voidSetPortDirection(u8 Copy_u8PortID,u8 Copy_u8Mode)
{
	if(Copy_u8PortID<3)
	{
		switch(Copy_u8PortID)
		{
		case DIO_U8_PORTA:
		{
			/*	To deal with Bit Masking 1- Clear a specific Bits 2- Assign a specific Bits	*/
			GPIOA_CRL &= ~((u32)(0b1111));
			GPIOA_CRH &= ~((u32)(0b1111));
			for(u8 i=0;i<7;i++)
			{
				GPIOA_CRL |=  ((u32)(Copy_u8Mode)<<(i * 4));
				GPIOA_CRH |=  ((u32)(Copy_u8Mode)<<(i * 4));
			}
		}
		/*		HIGH PORT				*/

		break;
		case DIO_U8_PORTB:
		{
			/*	To deal with Bit Masking 1- Clear a specific Bits 2- Assign a specific Bits	*/
			GPIOA_CRL &= ~((u32)(0b1111));
			GPIOA_CRH &= ~((u32)(0b1111));
			for(u8 i=0;i<7;i++)
			{
				GPIOA_CRL |=  ((u32)(Copy_u8Mode)<<(i * 4));
				GPIOA_CRH |=  ((u32)(Copy_u8Mode)<<(i * 4));
			}
		}
		/*		HIGH PORT				*/

		break;
		case DIO_U8_PORTC:
		{
			/*	To deal with Bit Masking 1- Clear a specific Bits 2- Assign a specific Bits	*/
			GPIOA_CRL &= ~((u32)(0b1111));
			GPIOA_CRH &= ~((u32)(0b1111));
			for(u8 i=0;i<7;i++)
			{
				GPIOA_CRL |=  ((u32)(Copy_u8Mode)<<(i * 4));
				GPIOA_CRH |=  ((u32)(Copy_u8Mode)<<(i * 4));
			}
		}
		}
	}
}

u8 DIO_u8SetPortValue(u8 Copy_u8PortID, u8 Copy_u8Value)
{
	u8 Local_u8ERRORState=OK;
	if(Copy_u8PortID<3)
	{

		if( Copy_u8Value > DIO_U8_HIGH )
		{
			Local_u8ERRORState  = NOK;
		}
		else
		{
			switch(Copy_u8PortID)
			{
			case DIO_U8_PORTA:
				GPIOA_ODR=Copy_u8Value;	break;

			case DIO_U8_PORTB:

				GPIOA_ODR=Copy_u8Value;	break;

			case DIO_U8_PORTC:

				GPIOA_ODR=Copy_u8Value;	break;

			default: Local_u8ERRORState=NOK;break;	/*		Return ERROR		*/
			}
		}
	}

return Local_u8ERRORState;

}
