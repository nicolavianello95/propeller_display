/* File: Display a Propulsione
autore: Vianello Nicola & Bellemo Enrico
data: Marzo-Maggio 2014  */

#include <htc.h>

// configurazione PIC
__CONFIG(HS & WDTDIS & PWRTEN & BORDIS & LVPDIS & WRTEN & DEBUGDIS & DUNPROT & UNPROTECT); 

// macro per ritardo
#define _XTAL_FREQ 20000000
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))

//definizione led/porta
#define cornice RA2
#define led1 RA3
#define led2 RC0
#define led3 RC1
#define led4 RC2
#define led5 RC3
#define led6 RB4
#define led7 RB3
#define led8 RB2
#define led9 RB1
#define led10 RC7
#define led11 RC6
#define led12 RC5
#define led13 RC4 

//definizione modalità
#define vianello_nicola 0
#define bellemo_enrico 1
#define itis_righi_2014 2
#define display_a_propulsione 3
#define smile 4
#define analogico 5
#define digitale 6

//dichiarazione variabili globali
unsigned int cambio=0;
unsigned int modalita=vianello_nicola;	//variabile usata per cambiare tipo di orologio o immagine visualizzata
unsigned int contatore=0;				//conta quante volte scatta l'interrupt su timer0
unsigned int settore=0;					//conta i centottantesimi di giro
//nella modalità analogica, uso terzi di secondo e di minuto, e quindicesimi di ora in modo che combacino con i settori
unsigned int secondi=0;					//variabile che contiene i terzi di secondo
unsigned int minuti=0;					//variabile che contiene i terzi di minuto
unsigned int ore=0;						//variabile che contiene i quindicesimi di ora
unsigned int j;
unsigned int i;							//variabili utilizzate per i cicli for
//nella modalità digitale, per usare la relativa funzione, uso decine e unità separate
unsigned int decine_ore=0;
unsigned int unita_ore=0;
unsigned int decine_minuti=0;
unsigned int unita_minuti=0;
unsigned int decine_secondi=0;
unsigned int unita_secondi=0;

//prototipazione funzioni
void visualizza_numero(unsigned int, unsigned int);
void visualizza(unsigned int);
void cambio_ora(void);

//interrupt
void interrupt routine(void){

//interrupt RB0
if(INTF==1){
	TMR0=50;		//riassegno il valore di partenza del timer0
	settore=0;		//azzero i settori	
	INTF=0;			//azzero il flag di interruzione su RB0
	T0IE=1;			//riattivo l'interrupt su TMR0
}	

//interrupt timer0
else{
	TMR0=50;			//riassegno subito il valore di partenza al timer0 in modo da non avere ulteriori ritardi

	switch(modalita){

		//visualizzo "Vianello Nicola"
		case vianello_nicola:
			switch(settore){
				case 8: case 9: case 10: case 11: case 14: case 15: case 16: case 17: case 106: case 159: case 178:
					visualizza(0b00001);
					break;
				case 74: case 75: case 76:
					visualizza(0b00101);
					break;
				case 158: case 160:
					visualizza(0b00110);
					break;
				case 105: case 177:
					visualizza(0b01110);
					break;
				case 79: case 80: case 81: case 82: case 104: case 176:
					visualizza(0b10000);
					break;
				case 5: case 20: case 21: case 22: case 86: case 87: case 88: case 91: case 92: case 93: case 94:
					visualizza(0b10001);
					break;
				case 170: case 171: case 172:
					visualizza(0b10100);
					break;
				case 2: case 3: case 4:
					visualizza(0b10101);
					break;
				case 157: case 161:
					visualizza(0b11000);
					break;
				case 1: case 7: case 13: case 19: case 23: case 73: case 77: case 83: case 85: case 89: case 95: case 99: case 103: case 107: case 165: case 169: case 173: case 175: case 179:
					visualizza(0b11111);
					break;
				default:
					visualizza(0b00000);
					break;
			}
		break;

		//visualizzo "Bellemo Enrico"
		case bellemo_enrico:
			switch(settore){
				case 0: case 1: case 2: case 100: case 173: case 174: case 175: case 176: case 179: case 180:
					visualizza(0b00001);
					break;
				case 94:
					visualizza(0b00101);
					break;
				case 164:
					visualizza(0b01010);
					break;
				case 12:
					visualizza(0b01100);
					break;
				case 93:
					visualizza(0b01101);
					break;
				case 99:
					visualizza(0b01110);
					break;
				case 11: case 13: case 98:
					visualizza(0b10000);
					break;
				case 8: case 17: case 18: case 19: case 74: case 75: case 76: case 79: case 80: case 81: case 82: case 103: case 170:
					visualizza(0b10001);
					break;
				case 5: case 6: case 7: case 92: case 104: case 105: case 106: case 161: case 162: case 163: case 167: case 168: case 169:
					visualizza(0b10101);
					break;
				case 91:
					visualizza(0b10111);
					break;
				case 4: case 10: case 14: case 16: case 20: case 73: case 77: case 83: case 87: case 95: case 97: case 101: case 107: case 160: case 166: case 172: case 178:
					visualizza(0b11111);
					break;
				default:
					visualizza(0b00000);
					break;
			}
		break;

		//visualizzo "ITIS Righi 2014"
		case itis_righi_2014:
			switch(settore){
				case 20: case 21: case 22: case 80: case 81: case 82:
					visualizza(0b00100);
					break;
				case 83:
					visualizza(0b00111);
					break;
				case 157: case 158: case 160: case 161:
					visualizza(0b10000);
					break;
				case 14: case 15: case 92: case 93: case 94:
					visualizza(0b10001);
					break;
				case 2:
					visualizza(0b10100);
					break;
				case 4: case 16: case 98: case 99: case 100: case 170: case 171: case 172:
					visualizza(0b10101);
					break;
				case 3:
					visualizza(0b10110);
					break;
				case 17: case 97: case 173:
					visualizza(0b10111);
					break;
				case 5: case 101: case 169:
					visualizza(0b11101);
					break;
				case 1: case 9: case 13: case 19: case 23: case 27: case 79: case 87: case 91: case 95: case 153: case 159: case 165:
					visualizza(0b11111);
					break;
				default:
					visualizza(0b00000);
					break;
			}
		break;

		//visualizzo "Display a Propulsione"
		case display_a_propulsione:
			switch(settore){
				case 0: case 1: case 2: case 67: case 179: case 180:
					visualizza(0b00001);
					break;
				case 12:
					visualizza(0b00011);
					break;
				case 11: case 13:
					visualizza(0b00100);
					break;
				case 101: case 102: case 103: case 115: case 119: case 120: case 121:
					visualizza(0b00101);
					break;
				case 100: case 118:
					visualizza(0b00111);
					break;
				case 114:
					visualizza(0b01101);
					break;
				case 66: case 158:
					visualizza(0b01110);
					break;
				case 65: case 88: case 89: case 90: case 91: case 95: case 96: case 97:
					visualizza(0b10000);
					break;
				case 58: case 71: case 72: case 73: case 107: case 108: case 109: case 155: case 156: case 157:
					visualizza(0b10001);
					break;
				case 5: case 6: case 7: case 23: case 24: case 25: case 173: case 174: case 175:
					visualizza(0b10100);
					break;
				case 59: case 60: case 61: case 83: case 84: case 85: case 113: case 167: case 168: case 169:
					visualizza(0b10101);
					break;
				case 86: case 112: case 170:
					visualizza(0b10111);
					break;
				case 10: case 14:
					visualizza(0b11000);
					break;
				case 176:
					visualizza(0b11100);
					break;
				case 82: case 166: 
					visualizza(0b11101);
					break;
				case 4: case 8: case 22: case 26: case 62: case 64: case 68: case 70: case 74: case 78: case 92: case 94: case 98: case 104: case 106: case 110: case 116: case 122: case 154: case 162: case 172: case 178:
					visualizza(0b11111);
					break;
				default:
					visualizza(0b00000);
					break;
			}
		break;

		//modalità smile
		case smile:	
			switch(settore){
				case 6:
					led6=1;
					led7=1;
					led8=0;
					led9=0;
					led10=0;
					led11=1;
					led12=1;
					break;
				case 7: 
					led6=1;
					led7=0;
					led8=0;
					led9=0;
					led10=0;
					led11=0;
					led12=1;
					break;
				case 8:
					led6=0;
					led7=0;
					led8=0;
					led9=0;
					led10=0;
					led11=0;
					led12=0;
					break;
				case 12:
					led6=1;
					led7=0;
					led8=0;
					led9=0;
					led10=0;
					led11=0;
					led12=0;
					break;
				case 13:
					led6=1;
					led7=1;
					led8=0;
					led9=0;
					led10=0;
					led11=0;
					led12=0;
					break;
				case 14:
					led6=1;
					led7=1;
					led8=1;
					led9=0;
					led10=0;
					led11=0;
					led12=0;
					break;
				case 15:
					led6=1;
					led7=1;
					led8=1;
					led9=1;
					led10=0;
					led11=0;
					led12=1;
					break;
				case 16:
					led10=1;
					led11=1;
					break;
				case 49:
					led5=0;
					led6=0;
					led7=0;
					break;
				case 132:
					led5=1;
					led6=1;
					led7=1;
					break;
				case 177:
					led6=1;
					led7=1;
					led8=1;
					led9=1;
					led10=1;
					led11=1;
					led12=1;
					break;
				case 176:
					if(i>18500){
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					else{
						led6=1;
						led7=1;
						led8=1;
						led9=1;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 175:
					if(i>18500){
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 174:
					if(i<18500){
						led6=1;
						led7=1;
						led8=1;
						led9=1;
						led10=1;
						led11=1;
						led12=1;
					}
					else if((i>18500)&&(i<19000)){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=1;
						led12=1;
					}
					else{
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 173:
					if(i<18000){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=1;
						led12=1;
					}
					else if((i>18000)&&(i<18500)){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=0;
						led12=1;
					}
					else if((i>18500)&&(i<19000)){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=1;
						led12=1;
					}
					else{
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 172:
					if(i<18000){
						led6=1;
						led7=0;
						led8=0;
						led9=0;
						led10=0;
						led11=0;
						led12=1;
					}
					else if((i>18000)&&(i<18500)){
						led6=1;
						led7=0;
						led8=0;
						led9=0;
						led10=0;
						led11=0;
						led12=1;
					}
					else if((i>18500)&&(i<19000)){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=1;
						led12=1;
					}
					else{
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 168:
					if(i<18000){
						led6=0;
						led7=0;
						led8=0;
						led9=0;
						led10=0;
						led11=0;
						led12=0;
					}
					else if((i>18000)&&(i<18500)){
						led6=1;
						led7=0;
						led8=0;
						led9=0;
						led10=0;
						led11=0;
						led12=1;
					}
					else if((i>18500)&&(i<19000)){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=1;
						led12=1;
					}
					else{
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 167:
					if(i<18000){
						led6=1;
						led7=0;
						led8=0;
						led9=0;
						led10=0;
						led11=0;
						led12=0;
					}
					else if((i>18000)&&(i<18500)){
						led6=1;
						led7=0;
						led8=0;
						led9=0;
						led10=0;
						led11=0;
						led12=1;
					}
					else if((i>18500)&&(i<19000)){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=1;
						led12=1;
					}
					else{
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 166:
					if(i<18000){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=0;
						led12=0;
					}
					else if((i>18000)&&(i<18500)){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=0;
						led12=1;
					}
					else if((i>18500)&&(i<19000)){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=1;
						led12=1;
					}
					else{
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 165:
					if(i<18000){
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=0;
						led11=0;
						led12=0;
					}
					else if((i>18000)&&(i<18500)){
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=0;
						led11=0;
						led12=1;
					}
					else if((i>18500)&&(i<19000)){
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					else{
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 164:
					if(i<18000){
						led6=1;
						led7=1;
						led8=1;
						led9=1;
						led10=0;
						led11=0;
						led12=1;
					}
					else if((i>18000)&&(i<18500)){
						led6=1;
						led7=1;
						led8=1;
						led9=1;
						led10=1;
						led11=1;
						led12=1;
					}
					else if((i>18500)&&(i<19000)){
						led6=1;
						led7=1;
						led8=0;
						led9=0;
						led10=0;
						led11=1;
						led12=1;
					}
					else{
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 163:
					if(i>18500){
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;
				case 162:
					if(i>19000){
						led6=1;
						led7=1;
						led8=1;
						led9=0;
						led10=1;
						led11=1;
						led12=1;
					}
					break;	
				default:
					break;
			}
			break;		//fine smile

	//modalità orologio analogico
	case analogico:						
		if(settore<=secondi) 	//visualizzo i secondi tramite la cornice
			cornice=1;
		else
			cornice=0;
		switch(settore){		//inizio scansione immagine fissa
			case 15: case 30: case 43: case 44: case 46: case 47: case 60: case 75: case 105: case 120: case 150: case 165:
				led1=1;
				led2=0;
				led3=0;
				led4=0;
				led5=0;
				break;
			case 42: case 48: case 132: case 135: case 138:
				led1=1;
				led2=1;
				led3=1;
				led4=0;
				led5=0;	
				break;
			case 1: case 90:
				led2=0;
				led3=1;
				led4=0;
				led5=1;
				break;
			case 2: case 89:
				led1=1;
				led2=1;
				led3=1;
				led4=0;
				led5=1;
				break;
			case 91: case 178:
				led1=1;
				led2=1;
				led3=1;
				led4=1;
				led5=1;
				break;
			case 133: case 134:
				led1=0;
				led2=0;
				led3=1;
				led4=0;
				led5=0;
				break;
			case 136: case 137:
				led2=0;
				led3=1;
				led4=0;
				led5=0;
				break;
			case 45:
				led2=1;
				led3=0;
				led4=0;
				led5=0;
				break;
			case 0:		
				led1=1;
				led2=0;
				led3=1;
				led4=1;
				led5=1;	
				break;
			default:
				led1=0;
				led2=0;
				led3=0;
				led4=0;
				led5=0;
				break;		//fine scansione immagine fissa
		}
		led6=0;				//azzero lancette precedenti
		led7=0;
		led8=0;
		led9=0;
		led10=0;
		led11=0;
		led12=0;
		led13=0;
		if(settore==minuti){		//visualizzo lancetta minuti
			led3=1;
			led4=1;
			led5=1;
			led6=1;
			led7=1;
			led8=1;
			led9=1;
			led10=1;
			led11=1;
			led12=1;
			led13=1;
		}
		else if((settore==minuti-2)||(settore==minuti+2)||(settore==minuti+178))	//visualizzo freccia lancetta minuti
			led5=1;
		else if((settore==minuti-1)||(settore==minuti+1)||(settore==minuti+179))
			led4=1;
		if(settore==ore){			//visualizzo lancetta ore
			led6=1;
			led7=1;
			led8=1;
			led9=1;
			led10=1;
			led11=1;
			led12=1;
			led13=1;
		}
		else if((settore==ore-2)||(settore==ore+2)||(settore==minuti+178))			//visualizzo freccia lancetta ore
			led8=1;
		else if((settore==ore-1)||(settore==ore+1)||(settore==minuti+179))
			led7=1;
	break;				//fine modalità orologio analogico

	//modalità orologio digitale
	case digitale:					
		switch(settore){
			case 8: case 172:					//visualizzo due punti
				led2=0;
				led3=1;
				led4=0;
				led5=1;
				led6=0;
				break;
			case 1:
				visualizza_numero(unita_minuti, 1);	//visualizzo unità dei minuti
				break;
			case 2:
				visualizza_numero(unita_minuti, 2);
				break;
			case 3:
				visualizza_numero(unita_minuti, 3);
				break;
			case 4:
				visualizza_numero(unita_minuti, 4);
				break;
			case 5:
				visualizza_numero(unita_minuti, 5);
				break;
			case 11:
				visualizza_numero(decine_secondi, 1);	//visualizzo decine dei secondi
				break;
			case 12:
				visualizza_numero(decine_secondi, 2);
				break;
			case 13:
				visualizza_numero(decine_secondi, 3);
				break;
			case 14:
				visualizza_numero(decine_secondi, 4);
				break;
			case 15:
				visualizza_numero(decine_secondi, 5);
				break;
			case 17:
				visualizza_numero(unita_secondi, 1);	//visualizzo unità dei secondi
				break;
			case 18:
				visualizza_numero(unita_secondi, 2);
				break;
			case 19:
				visualizza_numero(unita_secondi, 3);
				break;
			case 20:
				visualizza_numero(unita_secondi, 4);
				break;
			case 21:
				visualizza_numero(unita_secondi, 5);
				break;
			case 159:
				visualizza_numero(decine_ore, 1);		//visualizzo decine delle ore
				break;
			case 160:
				visualizza_numero(decine_ore, 2);
				break;
			case 161:
				visualizza_numero(decine_ore, 3);
				break;
			case 162:
				visualizza_numero(decine_ore, 4);
				break;
			case 163:
				visualizza_numero(decine_ore, 5);
				break;
			case 165:
				visualizza_numero(unita_ore, 1);		//visualizzo unità delle ore
				break;
			case 166:
				visualizza_numero(unita_ore, 2);
				break;
			case 167:
				visualizza_numero(unita_ore, 3);
				break;
			case 168:
				visualizza_numero(unita_ore, 4);
				break;
			case 169:
				visualizza_numero(unita_ore, 5);
				break;
			case 175:
				visualizza_numero(decine_minuti, 1);	//visualizzo decine dei minuti
				break;
			case 176:
				visualizza_numero(decine_minuti, 2);
				break;
			case 177:
				visualizza_numero(decine_minuti, 3);
				break;
			case 178:
				visualizza_numero(decine_minuti, 4);
				break;
			case 179:
				visualizza_numero(decine_minuti, 5);
				break;
			default:							//in tutti gli altri casi spengo i led
				led2=0;
				led3=0;
				led4=0;
				led5=0;
				led6=0;
				break;
		}
		break;					//fine modalità orologio digitale
	}		
	settore++;			//aumento il settore per il prossimo interrupt
	if(settore>179)		//se arrivo al 180esimo settore, disattivo l'interrupt su TMR0
		T0IE=0;
	contatore++;		//aumento il conteggio degli interrupt
	T0IF=0;				//riazzero il flag di interrupt sul timer0	
	}//fine interrupt timer0

}// fine interrupt

//funzione cambio ora
void cambio_ora(void){

	//avanzamento ora
	if(contatore>6067){			//quando scattano 6068 interrupt significa che è passato un secondo
		secondi=secondi+3;		//aumento di 3 i terzi di secondo ogni 6068 interrupt
		unita_secondi++;
		contatore=0;			//riazzero il contatore degli interrupt
		cambio++;
	}
	if(secondi>179){			//dopo 180 terzi di secondo = 60 secondi, aumentano i minuti, e i secondi ripartono da 0
		secondi=0;
		minuti=minuti+3;
	}	
	if(minuti>179){				//dopo 180 terzi di minut0 = 60 minuti, aumentano le ore, e i minuti ripartono da 0
		minuti=0;
		ore=ore+15;
	}
	if(ore>179)					//dopo 180 quindicesimi di ora, le ore ripartono da 0
		ore=0;
	if(unita_secondi>9){		//quando le unità dei secondi superano la cifra 9
		unita_secondi=0;		//azzero le unità dei secondi
		decine_secondi++;		//aumento le decine dei secondi
	}
	if(decine_secondi>5){		//quando le decine dei secondi superano la cifra 5
		decine_secondi=0;		//azzero le decine dei secondi
		unita_minuti++;			//aumento le unità dei minuti
	}
	if(unita_minuti>9){			//quando le unità dei minuti superano la cifra 9
		unita_minuti=0;			//azzero le unità dei minuti
		decine_minuti++;		//aumento le decine dei minuti
	}
	if(decine_minuti>5){		//quando le decine dei minuti superano la cifra 5
		decine_minuti=0;		//azzero le decine dei minuti
		unita_ore++;			//aumento le unità delle ore
	}
	if(unita_ore>9){			//quando le unità delle ore superano la cifra 9
		unita_ore=0;			//azzero le unità delle ore
		decine_ore++;			//aumento le decine delle ore
	}
	if((decine_ore==2)&&(unita_ore>3)){	//quando le ore superano le 23, azzero unità e decine delle ore
		unita_ore=0;
		decine_ore=0;
	}//fine avanzamento ora

	//scansione pulsanti
	if(RB6==0){						//se premo il primo pulsante
		PORTA=0xFF;
		PORTB=0xFF;
		PORTC=0xFF;
		for(i=0;i<30000;i++)		//antirimbalzo
			__delay_us(1);			
		minuti=minuti+3;			//aumento i minuti
		unita_minuti++;
		for(i=0;i<30000;i++)		//antirimbalzo
			__delay_us(1);

		PORTA=0x00;
		PORTB=0x00;
		PORTC=0x00;
		cornice=1;
	}
	else if(RB7==0){				//se premo il secondo pulsante
		PORTA=0xFF;
		PORTB=0xFF;
		PORTC=0xFF;
		for(i=0;i<30000;i++)		//antirimbalzo
			__delay_us(1);
		ore=ore+15;					//aumentano le ore
		unita_ore++;
		for(i=0;i<30000;i++)		//antirimbalzo
			__delay_us(1);

		PORTA=0x00;
		PORTB=0x00;
		PORTC=0x00;
		cornice=1;
	}//fine scansione pulsanti
		
}//fine funzione cambio_ora

//funzione per visualizzare i numeri nella modalità digitale
void visualizza_numero(unsigned int numero, unsigned int istante){
	int sequenza;
	switch(numero){
		case 1:
			switch(istante){
				case 1: case 2: case 3: case 4:
					sequenza=0b00000;
					break;
				case 5:
					sequenza=0b11111;
					break;
			}
			break;
		case 2:
			switch(istante){
				case 2: case 3: case 4:
					sequenza=0b10101;
					break;
				case 1:
					sequenza=0b10111;
					break;
				case 5:
					sequenza=0b11101;
					break;
			}
			break;
		case 3:
			switch(istante){
				case 1: case 2: case 3: case 4:
					sequenza=0b10101;
					break;
				case 5:
					sequenza=0b11111;
					break;
			}	
			break;
		case 4:
			switch(istante){
				case 2: case 3: case 4:
					sequenza=0b00100;
					break;
				case 1:
					sequenza=0b11100;
					break;
				case 5:
					sequenza=0b11111;
					break;
			}
			break;
		case 5:
			switch(istante){
				case 2: case 3: case 4:
					sequenza=0b10101;
					break;
				case 1:
					sequenza=0b11101;
					break;
				case 5:
					sequenza=0b10111;
					break;
			}
			break;
		case 6:
			switch(istante){
				case 2: case 3: case 4:
					sequenza=0b10101;
					break;
				case 1:
					sequenza=0b11111;
					break;
				case 5:
					sequenza=0b10111;
					break;
			}
			break;
		case 7:
			switch(istante){
				case 1: case 2: case 3: case 4:
					sequenza=0b10000;
					break;
				case 5:
					sequenza=0b11111;
					break;
			}
			break;
		case 8:
			switch(istante){
				case 2: case 3: case 4:
					sequenza=0b10101;
					break;
				case 1: case 5:
					sequenza=0b11111;
					break;
			}
			break;
		case 9:
			switch(istante){
				case 2: case 3: case 4:
					sequenza=0b10101;
					break;
				case 1:
					sequenza=0b11101;
					break;
				case 5:
					sequenza=0b11111;
					break;
			}
			break;
		case 0:
			switch(istante){
				case 2: case 3: case 4:
					sequenza=0b10001;
					break;
				case 1: case 5:
					sequenza=0b11111;
					break;
			}
		break;
	}
	visualizza(sequenza);
}//fine funzione visualizza_numero

//funzione per visualizzare lettere o simboli
void visualizza(unsigned int led){
	switch(led){
		case 0b00000:
			led2=0;
			led3=0;
			led4=0;
			led5=0;
			led6=0;
			break;
		case 0b00001:
			led2=0;
			led3=0;
			led4=0;
			led5=0;
			led6=1;
			break;
		case 0b00010:
			led2=0;
			led3=0;
			led4=0;
			led5=1;
			led6=0;
			break;
		case 0b00011:
			led2=0;
			led3=0;
			led4=0;
			led5=1;
			led6=1;
			break;
		case 0b00100:
			led2=0;
			led3=0;
			led4=1;
			led5=0;
			led6=0;
			break;
		case 0b00101:
			led2=0;
			led3=0;
			led4=1;
			led5=0;
			led6=1;
			break;
		case 0b00110:
			led2=0;
			led3=0;
			led4=1;
			led5=1;
			led6=0;
			break;
		case 0b00111:
			led2=0;
			led3=0;
			led4=1;
			led5=1;
			led6=1;
			break;
		case 0b01000:
			led2=0;
			led3=1;
			led4=0;
			led5=0;
			led6=0;
			break;
		case 0b01001:
			led2=0;
			led3=1;
			led4=0;
			led5=0;
			led6=1;
			break;
		case 0b01010:
			led2=0;
			led3=1;
			led4=0;
			led5=1;
			led6=0;
			break;
		case 0b01011:
			led2=0;
			led3=1;
			led4=0;
			led5=1;
			led6=1;
			break;
		case 0b01100:
			led2=0;
			led3=1;
			led4=1;
			led5=0;
			led6=0;
			break;
		case 0b01101:
			led2=0;
			led3=1;
			led4=1;
			led5=0;
			led6=1;
			break;
		case 0b01110:
			led2=0;
			led3=1;
			led4=1;
			led5=1;
			led6=0;
			break;
		case 0b01111:
			led2=0;
			led3=1;
			led4=1;
			led5=1;
			led6=1;
			break;
		case 0b10000:
			led2=1;
			led3=0;
			led4=0;
			led5=0;
			led6=0;
			break;
		case 0b10001:
			led2=1;
			led3=0;
			led4=0;
			led5=0;
			led6=1;
			break;
		case 0b10010:
			led2=1;
			led3=0;
			led4=0;
			led5=1;
			led6=0;
			break;
		case 0b10011:
			led2=1;
			led3=0;
			led4=0;
			led5=1;
			led6=1;
			break;
		case 0b10100:
			led2=1;
			led3=0;
			led4=1;
			led5=0;
			led6=0;
			break;
		case 0b10101:
			led2=1;
			led3=0;
			led4=1;
			led5=0;
			led6=1;
			break;
		case 0b10110:
			led2=1;
			led3=0;
			led4=1;
			led5=1;
			led6=0;
			break;
		case 0b10111:
			led2=1;
			led3=0;
			led4=1;
			led5=1;
			led6=1;
			break;
		case 0b11000:
			led2=1;
			led3=1;
			led4=0;
			led5=0;
			led6=0;
			break;
		case 0b11001:
			led2=1;
			led3=1;
			led4=0;
			led5=0;
			led6=1;
			break;
		case 0b11010:
			led2=1;
			led3=1;
			led4=0;
			led5=1;
			led6=0;
			break;
		case 0b11011:
			led2=1;
			led3=1;
			led4=0;
			led5=1;
			led6=1;
			break;
		case 0b11100:
			led2=1;
			led3=1;
			led4=1;
			led5=0;
			led6=0;
			break;
		case 0b11101:
			led2=1;
			led3=1;
			led4=1;
			led5=0;
			led6=1;
			break;
		case 0b11110:
			led2=1;
			led3=1;
			led4=1;
			led5=1;
			led6=0;
			break;
		case 0b11111:
			led2=1;
			led3=1;
			led4=1;
			led5=1;
			led6=1;
			break;
	}
}//fine funzione visualizza

//programma principale
void main(void){
	
	//configurazione porte
	ADCON1=0x07; 	 	//linee portA digitali
	TRISA=0x00;			//linee portA uscite
	TRISB=0b11000001;	//RB0, RB6, RB7 ingressi, tutto il resto uscite
	TRISC=0x00;			//linee portC uscite
	PORTA=0x00;			//inizializzo la portA
	PORTB=0x00;			//inizializzo la portB
	PORTC=0x00;			//inizializzo la portC
	cornice=1;
	RBPU=0;				//attivo pullup interno su ingressi porte B
	
	//configurazione timer0
	T0CS=0;		//Timer0 interno
	PSA=0;		//prescaler assegnato al timer0
	PS2=0;      //prescaler
	PS1=0;		//prescaler
	PS0=1;		//Prescaler 4 - overflow ogni 164,8us
	
	//configurazione interrupt
	INTEDG=1;	//interrupt sul fronte di salita di RB0
	T0IE=1;		//attivo interrupt su timer0
	INTE=1;		//attivo interrupt su RB0
	GIE=1;		//bit globale di abilitazione interrupt	

	for(i=0;i<10;i++){			//aspetto accensione motore
		while(RB0==0)
			cambio_ora();		//verifico regolazione dell'ora
		__delay_ms(100);
	}

	for(i=0;i<15000;i++)		//visualizzo "Vianello Nicola" per 5 secondi
		for(j=0;j<100;j++)
			__delay_us(1);	

	modalita=bellemo_enrico;
	for(i=0;i<15000;i++)		//visualizzo "Bellemo Enrico" per 5 secondi
		for(j=0;j<100;j++)
			__delay_us(1);

	modalita=itis_righi_2014;
	for(i=0;i<15000;i++)		//visualizzo "ITIS Righi A.S: 2013-2014" per 5 secondi
		for(j=0;j<100;j++)
			__delay_us(1);			
				
	modalita=display_a_propulsione;
	for(i=0;i<15000;i++)		//visualizzo "display a propulsione" per 5 secondi
		for(j=0;j<100;j++)
			__delay_us(1);	
						
	modalita=smile;
	PORTA=0xFF;
	PORTB=0xFF;
	PORTC=0xFF;
	for(i=5000;i<20000;i++){		//visualizzo lo smile per 5 secondi
		for(j=0;j<100;j++)
			__delay_us(1);
		}
	modalita=analogico;					//comincio a visualizzare l'orologio

	//ciclo infinito
	while(1){
	
		//verifico il cambio e la regolazione dell'ora 
		cambio_ora();

		//cambio modalità analogico/digitale ogni 2 minuti
		if(cambio>45){
			cambio=0;
			if(modalita==analogico){
				modalita=digitale;
				led1=0;
				cornice=1;
			}	
			else
				modalita=analogico;
		}

	}// fine ciclo infinito
}// fine main