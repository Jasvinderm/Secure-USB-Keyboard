/*
 * binaryTree.h
 *
 *  Created on: 25 Jan 2013
 *      Author: Jasvinder
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_


char hex_to_char()
{
	char result;
	int i = 0,j = 7;

	for (i = 1; i < 9; i++) // Removes the data for processing
	{
		dataOut[j] = dataIn[i];
		j--;
	}

	// Ignore dataOut[0] as it is always 0 for any relevant value(except release and special keys)

	if(release) //If release has been pressed ignore the next byte
	{
		if(!dataOut[0] & !dataOut[1] & !dataOut[2] & dataOut[3] & !dataOut[4] & !dataOut[5] & dataOut[6] & !dataOut[7] )
		{
			shift = 0;
		}
		release = 0;
		return NULL;
	}
		if(dataOut[0] & dataOut[1] & dataOut[2] & dataOut[3])
		{
			release = 1;
			//TODO this means its an F0 or and E0
			return NULL;
		}
			if(dataOut[1]) //01------
			{
				if(dataOut[2]) //011-----
				{
					if(dataOut[3]) //0111----
					{
						if(dataOut[4]) //01111---
						{
							if(dataOut[5]) //011111--
							{
								if(dataOut[6]) //0111111-
								{
									if(dataOut[7]) //01111111
									{
										return NULL;
									}
									else //01111110
									{
										return NULL;
									}
								}
								else //0111110-
								{
									if(dataOut[7]) //01111101
									{
										return NULL;
									}
									else //01111100
									{
										return NULL;
									}
								}
							}
							else //011110--
							{
								if(dataOut[6]) //0111101-
								{
									if(dataOut[7]) //01111011
									{
										return NULL;
									}
									else //01111010
									{
										return NULL;
									}
								}
								else //0111100-
								{
									if(dataOut[7]) //01111001
									{
										return NULL;
									}
									else //01111000
									{
										return NULL;
									}
								}
							}
						}
						else //01110---
						{
							if(dataOut[5]) //011101--
							{
								if(dataOut[6]) //0111011-
								{
									if(dataOut[7]) //01110111
									{
										return NULL;
									}
									else //01110110
									{
										return NULL;
									}
								}
								else //0111010-
								{
									if(dataOut[7])  //01110101
									{
										return NULL;
									}
									else //01110100
									{
										return NULL;
									}
								}
							}
							else //011100--
							{
								if(dataOut[6]) //0111001-
								{
									if(dataOut[7]) //01110011
									{
										return NULL;
									}
									else //01110010
									{
										return NULL;
									}
								}
								else //0111000-
								{
									if(dataOut[7]) //01110001
									{
										return NULL;
									}
									else //01110000
									{
										return NULL;
									}
								}
							}
						}
					}
					else //0110----
					{
						if(dataOut[4]) //01101---
						{
							if(dataOut[5]) //011011--
							{
								if(dataOut[6]) //0110111-
								{
									if(dataOut[7]) //01101111
									{
										return NULL;
									}
									else //01101110
									{
										return NULL;
									}
								}
								else //0110110-
								{
									if(dataOut[7]) //01101101
									{
										return NULL;
									}
									else //01101100
									{
										return NULL;
									}
								}
							}
							else //011010--
							{
								if(dataOut[6]) //0110101-
								{
									if(dataOut[7]) //01101011
									{
										return NULL;
									}
									else //01101010
									{
										return NULL;
									}
								}
								else //0110100-
								{
									if(dataOut[7]) //01101001
									{
										return NULL;
									}
									else //01101000
									{
										return NULL;
									}
								}
							}
						}
						else //01100---
						{
							if(dataOut[5]) //011001--
							{
								if(dataOut[6]) //0110011-
								{
									if(dataOut[7]) //01100111
									{
										return NULL;
									}
									else //01100110
									{
										result = 8;
									}
								}
								else //0110010-
								{
									if(dataOut[7]) //01100101
									{
										return NULL;
									}
									else //01100100
									{
										return NULL;
									}
								}
							}
							else //011000--
							{
								if(dataOut[6]) //0110001-
								{
									if(dataOut[7]) //01100011
									{
										return NULL;
									}
									else //01100010
									{
										return NULL;
									}
								}
								else //0110000-
								{
									if(dataOut[7]) //01100001
									{
										return NULL;
									}
									else //01100000
									{

									}
								}
							}
						}
					}
				}
				else //010-----
				{
					if(dataOut[3]) //0101----
					{
						if(dataOut[4]) //01011---
						{
							if(dataOut[5]) //010111--
							{
								if(dataOut[6]) //0101111-
								{
									if(dataOut[7]) //01011111
									{
										return NULL;
									}
									else //01011110
									{
										return NULL;
									}
								}
								else //0101110-
								{
									if(dataOut[7]) //01011101
									{
										return NULL;
									}
									else //01011100
									{
										return NULL;
									}
								}
							}
							else //010110--
							{
								if(dataOut[6]) //0101101-
								{
									if(dataOut[7]) //01011011
									{
										return NULL;
									}
									else //01011010
									{
										//must be '\n'
										result = '\n';
										PINB |= _BV(7);
									}
								}
								else //0101100-
								{
									if(dataOut[7]) //01011001
									{
										return NULL;
									}
									else //01011000
									{
										return NULL;
									}
								}
							}
						}
						else //01010---
						{
							if(dataOut[5]) //010101--
							{
								if(dataOut[6]) //0101011-
								{
									if(dataOut[7]) //01010111
									{
										return NULL;
									}
									else //01010110
									{
										return NULL;
									}
								}
								else //0101010-
								{
									if(dataOut[7]) //01010101
									{
										return NULL;
									}
									else //01010100
									{
										return NULL;
									}
								}
							}
							else //010100--
							{
								if(dataOut[6]) //0101001-
								{
									if(dataOut[7]) //01010011
									{
										return NULL;
									}
									else //01010010
									{
										return NULL;
									}
								}
								else //0101000-
								{
									if(dataOut[7]) //01010001
									{
										return NULL;
									}
									else //01010000
									{
										return NULL;
									}
								}
							}
						}
					}
					else //0100----
					{
						if(dataOut[4]) //01001---
						{
							if(dataOut[5]) //010011--
							{
								if(dataOut[6]) //0100111-
								{
									if(dataOut[7]) //01001111
									{
										return NULL;
									}
									else //01001110
									{
										return NULL;
									}
								}
								else //0100110-
								{
									if(dataOut[7]) //01001101
									{
										//must be 'p'
										result = 'p';
									}
									else //01001100
									{
										return NULL;
									}
								}

							}
							else //010010--
							{
								if(dataOut[6]) //0100101-
								{
									if(dataOut[7]) //01001011
									{
										//must be 'l'
										result = 'l';
									}
									else //01001010
									{
										return NULL;
									}
								}
								else //0100100-
								{
									if(dataOut[7]) //01001001
									{
										return NULL;
									}
									else //01001000
									{
										return NULL;
									}
								}
							}
						}
						else //01000---
						{
							if(dataOut[5]) //010001--
							{
								if(dataOut[6]) //0100011-
								{
									if(dataOut[7]) //01000111
									{
										return NULL;
									}
									else //01000110
									{
										//must be '9'
										result = '9';
									}
								}
								else //0100010-
								{
									if(dataOut[7]) //01000101
									{
										//must be '0'
										result = '0';
									}
									else //01000100
									{
										//must be 'o'
										result = 'o';
									}
								}
							}
							else //010000--
							{
								if(dataOut[6]) //0100001-
								{
									if(dataOut[7]) //01000011
									{
										//must be 'i'
										result = 'i';
									}
									else //01000010
									{
										//must be 'k'
										result = 'k';
									}
								}
								else //0100000-
								{
									if(dataOut[7]) //01000001
									{
										return NULL;
									}
									else //01000000
									{
										return NULL;
									}
								}
							}
						}
					}
				}

			}
			else //00------
			{
				if(dataOut[2]) //001-----
				{
					if(dataOut[3]) //0011----
					{
						if(dataOut[4]) //00111---
						{
							if(dataOut[5]) //001111--
							{
								if(dataOut[6]) //0011111-
								{
									if (dataOut[7]) //00111111
									{
										return NULL;
									}
									else //00111110
									{
										//must be '8'
										result = '8';
									}
								}
								else //0011110-
								{
									if (dataOut[7]) //00111101
									{
										//must be '7'
										result = '7';
									}
									else //00111100
									{
										//must be 'u'
										result = 'u';
									}
								}
							}
							else //001110--
							{
								if(dataOut[6]) //0011101-
								{
									if (dataOut[7]) //00111011
									{
										//must be 'j'
										result = 'j';
									}
									else //00111010
									{
										//must be 'm'
										result = 'm';
									}
								}
								else //0011100-
								{
									if (dataOut[7]) //00111001
									{
										return NULL;
									}
									else //00111000
									{
										return NULL;
									}
								}
							}
						}
						else //00110---
						{
							if(dataOut[5]) //001101--
							{
								if(dataOut[6]) //0011011-
								{
									if (dataOut[7]) //00110111
									{
										return NULL;
									}
									else //00110110
									{
										//must be '6'
										result = '6';
									}
								}
								else //0011010-
								{
									if (dataOut[7]) //00110101
									{
										//must be 'y'
										result = 'y';
									}
									else //00110100
									{
										//must be 'g'
										result = 'g';
									}
								}
							}
							else //001100--
							{
								if(dataOut[6]) //0011001-
								{
									if (dataOut[7]) //00110011
									{
										//must be 'h'
										result = 'h';
									}
									else //00110010
									{
										//must be 'b'
										result = 'b';
									}
								}
								else //0011000-
								{
									if (dataOut[7]) //00110001
									{
										//must be 'n'
										result = 'n';
									}
									else //00110000
									{
										return NULL;
									}
								}
							}
						}
					}
					else //0010----
					{
						if(dataOut[4]) //00101---
						{
							if(dataOut[5]) //001011--
							{
								if(dataOut[6]) //0010111-
								{
									if (dataOut[7]) //00101111
									{
										return NULL;
									}
									else //00101110
									{
										//must be '5'
										result = '5';
									}
								}
								else //0010110-
								{
									if (dataOut[7]) //00101101
									{
										//must be 'r'
										result = 'r';
									}
									else //00101100
									{
										//must be 't'
										result = 't';
									}
								}
							}
							else //001010--
							{
								if(dataOut[6]) //0010101-
								{
									if (dataOut[7]) //00101011
									{
										//must be 'f'
										result = 'f';
									}
									else //00101010
									{
										//must be 'v'
										result = 'v';
									}
								}
								else //0010100-
								{
									if (dataOut[7]) //00101001
									{
										//must be ' '
										result = ' ';
									}
									else //00101000
									{
										return NULL;
									}
								}
							}
						}
						else //00100---
						{
							if(dataOut[5]) //001001--
							{
								if(dataOut[6]) //0010011-
								{
									if (dataOut[7]) //00100111
									{
										return NULL;
									}
									else //00100110
									{
										//must be '3'
										result = '3';
									}
								}
								else //0010010-
								{
									if (dataOut[7]) //00100101
									{
										//must be '4'
										result = '4';
									}
									else //00100100
									{
										//must be 'e'
										result = 'e';
									}
								}
							}
							else //001000--
							{
								if(dataOut[6]) //0010001-
								{
									if (dataOut[7]) //00100011
									{
										//must be 'd'
										result = 'd';
									}
									else //00100010
									{
										//must be 'x'
										result = 'x';
									}
								}
								else //0010000-
								{
									if (dataOut[7]) //00100001
									{
										//must be 'c'
										result = 'c';
									}
									else //00100000
									{
										return NULL;
									}
								}
							}
						}
					}
				}
				else //000-----
				{
					if(dataOut[3]) //0001----
					{
						if(dataOut[4]) //00011---
						{
							if(dataOut[5]) //000111--
							{
								if(dataOut[6]) //0001111-
								{
									if(dataOut[7]) //00011111
									{

									}
									else //00011110
									{
										//must be '2'
										result = '2';
									}
								}
								else //0001110-
								{
									if(dataOut[7]) //00011101
									{
										//must be 'w'
										result = 'w';
									}
									else //00011100
									{
										//must be 'a'
										result = 'a';
									}
								}
							}
							else //000110--
							{
								if(dataOut[6]) //0001101-
								{
									if(dataOut[7]) //00011011
									{
										//must be 's'
										result = 's';
									}
									else //00011010
									{
										//must be 'z'
										result = 'z';
									}
								}
								else //0001100-
								{
									if(dataOut[7]) //00011001
									{
										return NULL;
									}
									else //00011000
									{
										return NULL;
									}
								}
							}
						}
						else //00010---
						{
							if(dataOut[5]) //000101--
							{
								if(dataOut[6]) //0001011-
								{
									if(dataOut[7]) //00010111
									{
										return NULL;
									}
									else //00010110
									{
										//must be '1'
										result = '1';
									}
								}
								else //0001010-
								{
									if(dataOut[7]) //00010101
									{
										//must be 'q'
										result = 'q';
									}
									else //00010100
									{
										return NULL;
									}
								}
							}
							else //000100--
							{
								if(dataOut[6]) //0001001-
								{
									if(dataOut[7]) //00010011
									{
										return NULL;
									}
									else //00010010
									{
										shift = 1;
										return NULL;
									}
								}
								else //0001000-
								{
									if(dataOut[7]) //00010001
									{
										return NULL;
									}
									else  //00010000
									{
										return NULL;
									}
								}
							}
						}
					}
					else //0000----
					{
						if(dataOut[4]) //00001---
						{
							if(dataOut[5]) //000011--
							{
								if(dataOut[6]) //0000111-
								{
									if(dataOut[7]) //00001111
									{
										return NULL;
									}
									else //00001110
									{
										return NULL;
									}
								}
								else //0000110-
								{
									if(dataOut[7]) //00001101
									{
										//must be \t
										result = '\t';
									}
									else //00001100
									{
										return NULL;
									}
								}
							}
							else //000010--
							{
								if(dataOut[6]) //0000101-
								{
									if(dataOut[7]) //00001011
									{
										return NULL;
									}
									else //00001010
									{
										return NULL;
									}
								}
								else //0000100-
								{
									if(dataOut[7]) //00001001
									{
										return NULL;
									}
									else //00001000
									{

									}
								}
							}
						}
						else //00000---
						{
							if(dataOut[5]) //000001--
							{
								if(dataOut[6]) //0000011-
								{
									if(dataOut[7]) //00000111
									{
										return NULL;
									}
									else //00000110
									{
										return NULL;
									}
								}
								else //0000010-
								{
									if(dataOut[7]) //00000101
									{
										return NULL;
									}
									else //00000100
									{
										return NULL;
									}
								}
							}
							else //000000--
							{
								if(dataOut[6]) //0000001-
								{
									if(dataOut[7]) //00000011
									{
										return NULL;
									}
									else //00000010
									{
										return NULL;
									}
								}
								else //0000000-
								{
									if(dataOut[7]) //00000001
									{
										return NULL;
									}
									else //00000000
									{
										return NULL;
									}
								}
							}
						}
					}
				}
			}
	return result;
}

#endif /* BINARYTREE_H_ */
