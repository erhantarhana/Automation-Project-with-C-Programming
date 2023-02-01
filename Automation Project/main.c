#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include"fonksiyonlar.h"

int main() {
	char secim;
	secim=menuCiz();
	
	while(secim!='C'){
		switch(secim){
			case 'S':
				satisYap();
				break;
			case 'L':
				satisListele();
				break;
			case 'K':
				telefonKayitYap();
				break;	
			case 'T':
				telefonListele();
				break;
			case 'M':
				musteriKayitYap();
				break;
			case 'J':
				musteriListele();
				break;
			case 'G':
				telefonGuncelle();
				break;
			case 'D':
				telefonKayitSil();
				break;
			case 'E':
				musteriKayitSil();
				break;	
			case 'C':
				break;
			default :
				printf("Hatali Secim Yaptiniz...\n");
				break;							
		}
		secim=menuCiz();
	}
	return 0;
}
