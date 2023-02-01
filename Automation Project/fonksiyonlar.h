
typedef struct musteriBilgi{
	char tcNo[12];
	char adSoyad[50];
	char cinsiyet;
	char il[20];
	char telefonNo[15];
}musteriBilgi;

typedef struct telefonBilgi{
	int barkod;
	char telefonMarka[20];
	char telefonModel[20];
	int stok;
	float fiyat;
}telefonBilgi;

typedef struct telefonSatis{
	char musteritcNo[12];
	char tarih[15];
	int barkodtelefonNo;
	int adet;
	float fiyat;
}telefonSatis;

void stokGuncelle(int barkod, int adet){
	int i=0;
	int durum=0;
	system("cls");
	telefonBilgi telefon;
	
	
	FILE *dosya;
	dosya=fopen("telefonbilgisi.txt","r+b");
	
	while(fread(&telefon,sizeof(telefonBilgi),1,dosya)!=NULL){
		if(barkod==telefon.barkod){
			durum=1;
			break;
		}
		i++;
	}
	if(durum==0){
		fclose(dosya);
	}
	else{
		rewind(dosya);
		telefon.stok=telefon.stok-adet;
		fseek(dosya,(i)*sizeof(telefonBilgi),0);
		fwrite(&telefon,sizeof(telefonBilgi),1,dosya);
		fclose(dosya);
	}
}

void satisYap(){
	system("cls");
	int musteriSonuc=0;
	int telefonSonuc=0;
	musteriBilgi musteri;
	telefonBilgi telefon;
	telefonSatis satis;
	
	printf("                 SATIS EKRANINA HOSGELDINIZ           \n\n");
	printf("Lutfen Musteri TC No Giriniz :");
	scanf(" %[^\n]s",satis.musteritcNo);
	printf("Lutfen Satilacak Telefonun Barkod Numarasini Giriniz :");
	scanf(" %d",&satis.barkodtelefonNo);
	printf("Lutfen Satis Adetini Giriniz :");
	scanf(" %d",&satis.adet);
	
	FILE *dosya2=fopen("musteribilgisi.txt","r");
	FILE *dosya3=fopen("telefonbilgisi.txt","r");
	
	while(fread(&musteri,sizeof(musteriBilgi),1,dosya2)!=NULL){
		if(strcmp(satis.musteritcNo,musteri.tcNo)==0){
			musteriSonuc=1;
			break;
		}
	}
	
	while(fread(&telefon,sizeof(telefonBilgi),1,dosya3)!=NULL){
		if(satis.barkodtelefonNo==telefon.barkod){
			telefonSonuc=1;
			break;
		}
	}
	fclose(dosya2);
	fclose(dosya3);
	
	if(musteriSonuc==0){
		printf("Girdiginiz TC Kimlik Numarasina Gore Kayitli Musteri Bulunamadi.\n");
		return;
	}
	if(telefonSonuc==0){
		printf("Girdiginiz Barkod Numarasina Gore Kayitli Urun Bulunamadi.\n");
		return;
	}
	if(satis.adet>telefon.stok){
		printf("Maalesef Stokta Istediginiz Kadar Urun Bulunmamaktadir.\n");
		return;
	}
	else{
		time_t tarih=time(NULL);
		float toplamFiyat;
		toplamFiyat=satis.adet*telefon.fiyat;
		
		FILE *dosya1;
		dosya1=fopen("satislar.txt","a");
		
		fprintf(dosya1,"------------------------------------------------\n");
		fprintf(dosya1,"Urunun Satis Tarihi : %s \n",ctime(&tarih));
		fprintf(dosya1,"Urunu Satin Alan Kisinin Bilgileri : %s\t%s\t%s\n",musteri.tcNo,musteri.adSoyad,musteri.telefonNo);
		fprintf(dosya1,"Satilan Urunun Bilgileri : %d\t%s\t%s\n",satis.barkodtelefonNo,telefon.telefonMarka,telefon.telefonModel);
		fprintf(dosya1,"Toplam Tutar (adet/birim/toplam fiyat) : %d\t%f\t%f\n",satis.adet,telefon.fiyat,toplamFiyat);
		fclose(dosya1);
		stokGuncelle(satis.barkodtelefonNo,satis.adet);
		printf("Satis Basariyla Tamamlandi.\nOdenmesi Gereken Toplam Ucret :%.2f TL\n",toplamFiyat);
		
	}
}

void telefonKayitYap(){
	system("cls");
	telefonBilgi telefon;
	
	printf("                 TELEFON KAYIT EKRANINA HOSGELDINIZ           \n\n");
	printf("Telefonun Barkod Numarasini Giriniz :");
	scanf(" %d",&telefon.barkod);
	printf("Telefonun Markasini Giriniz :");
	scanf(" %[^\n]s",telefon.telefonMarka);
	printf("Telefonun Modelini Giriniz :");
	scanf(" %[^\n]s",telefon.telefonModel);
	printf("Telefonun Stok Bilgisini Giriniz :");
	scanf(" %d",&telefon.stok);
	printf("Telefonun Fiyatini Giriniz :");
	scanf(" %f",&telefon.fiyat);
	
	FILE *dosya;
	dosya=fopen("telefonbilgisi.txt","a+b");
	fwrite(&telefon,sizeof(telefonBilgi),1,dosya);
	fclose(dosya);
	printf("Telefon Kaydi Basariyla Tamamlandi\n\n");
}

void musteriKayitYap(){
	system("cls");
	musteriBilgi musteri;
	
	printf("                 MUSTERI KAYIT EKRANINA HOSGELDINIZ           \n\n");
	printf("Musterinin TC No Giriniz :");
	scanf(" %[^\n]s",musteri.tcNo);
	printf("Musterinin Adi ve Soyadini Giriniz :");
	scanf(" %[^\n]s",musteri.adSoyad);
	printf("Musterinin Cinsiyetini Giriniz (E/K) :");
	scanf(" %c",&musteri.cinsiyet);
	printf("Musterinin Bulundugu Ili Giriniz :");
	scanf(" %[^\n]s",musteri.il);
	printf("Musterinin Telefon Numarasini Giriniz :");
	scanf(" %[^\n]s",musteri.telefonNo);
	
	FILE *dosya;
	dosya=fopen("musteribilgisi.txt","a+b");
	fwrite(&musteri,sizeof(musteriBilgi),1,dosya);
	fclose(dosya);
	printf("Musteri Kaydi Basariyla Tamamlandi\n\n");
}

void telefonListele(){
	system("cls");
	telefonBilgi telefon;
	
	printf("                 TELEFON LISTELEME EKRANINA HOSGELDINIZ           \n\n");
	printf("%-12s%-20s%-20s%-12s%-10s\n","BARKOD","MARKA ADI","MODEL ADI","STOK","FIYAT TL");
	
	FILE *dosya;
	dosya=fopen("telefonbilgisi.txt","r+b");
	
	while(fread(&telefon,sizeof(telefonBilgi),1,dosya)!=NULL){
		printf("\n%-12d%-20s%-20s%-12d%.2f TL\n",telefon.barkod,telefon.telefonMarka,telefon.telefonModel,telefon.stok,telefon.fiyat);
	}
	fclose(dosya);
}

void musteriListele(){
	system("cls");
	musteriBilgi musteri;
	
	printf("                 MUSTERI LISTELEME EKRANINA HOSGELDINIZ           \n\n");
	printf("%-12s%-20s%-10s%-20s%-11s","TC","AD SOYAD","CINSIYET","IL","TELEFON");
	
	FILE *dosya;
	dosya=fopen("musteribilgisi.txt","r+b");
	
	while(fread(&musteri,sizeof(musteriBilgi),1,dosya)!=NULL){
		printf("\n%-12s%-20s%-10c%-20s%-11s\n",musteri.tcNo,musteri.adSoyad,musteri.cinsiyet,musteri.il,musteri.telefonNo);
	}
	fclose(dosya);
}

void telefonGuncelle(){
	int i=0;
	int barkodNo;
	int durum=0;
	int yeniStok;
	float yeniFiyat;
	system("cls");
	telefonBilgi telefon;
	telefonListele();
	
	
	printf("\n                 TELEFON BILGI GUNCELLEME EKRANINA HOSGELDINIZ           \n\n");
	printf("Lutfen Guncellemek Istediginiz Urunun Barkod Numarasini Giriniz :");
	scanf("%d",&barkodNo);
	
	FILE *dosya;
	dosya=fopen("telefonbilgisi.txt","r+b");
	while(fread(&telefon,sizeof(telefonBilgi),1,dosya)!=NULL){
		if(barkodNo==telefon.barkod){
			durum=1;
			printf("\n%-12d%-20s%-20s%-12d%.2f TL\n\n",telefon.barkod,telefon.telefonMarka,telefon.telefonModel,telefon.stok,telefon.fiyat);
			break;
		}
		i++;
	}
	if(durum==0){
		printf("Girdiginiz %d Barkod Numarali Urunun Kaydi Bulunamadi.",barkodNo);
		fclose(dosya);
	}
	else{
		printf("Yeni Stok Adetini Giriniz :");
		scanf("%d",&yeniStok);
		printf("Yeni fiyati giriniz :");
		scanf("%f",&yeniFiyat);
		rewind(dosya);
		telefon.fiyat=yeniFiyat;
		telefon.stok=yeniStok;
		fseek(dosya,(i)*sizeof(telefonBilgi),0);
		fwrite(&telefon,sizeof(telefonBilgi),1,dosya);
		fclose(dosya);
		printf("Telefon Bilgi Guncellenme Tamamlandi.\n");
	}
}

void telefonKayitSil(){
	int silinenBarkod;
	int durum=0;
	telefonBilgi telefon;
	system("cls");
	telefonListele();
	
	
	printf("\n                TELEFON KAYIT SILME EKRANINA HOSGELDINIZ           \n\n");
	printf("Lutfen Silmek Istediginiz Telefonun Barkod Numarasini Giriniz :");
	scanf("%d",&silinenBarkod);
	
	FILE *dosya;
	dosya=fopen("telefonbilgisi.txt","r+b");
	
	FILE *dosya2;
	dosya2=fopen("yedektelefonbilgisi.txt","w+b");
	
	while(fread(&telefon,sizeof(telefonBilgi),1,dosya)!=NULL){
		if(silinenBarkod!=telefon.barkod){
		fwrite(&telefon,sizeof(telefonBilgi),1,dosya2);
		}
		else{
			durum=1;
		}
	}
	fclose(dosya);
	fclose(dosya2);
	
	if(durum==1){
	remove("telefonbilgisi.txt");
	rename("yedektelefonbilgisi.txt","telefonbilgisi.txt");
	printf("%d Barkod Numarali Telefon Kaydi Basariyla Silindi.\n",silinenBarkod);
	}
	else{
		printf("Girmis Oldugunuz %d Barkod Numarali Telefon Kaydi Bulunamadi.\n",silinenBarkod);
	}
}

void musteriKayitSil(){
	char silinentcNo[12];
	int durum=0;
	musteriBilgi musteri;
	system("cls");
	musteriListele();
	
	
	printf("\n                MUSTERI KAYIT SILME EKRANINA HOSGELDINIZ           \n\n");
	printf("Lutfen Silmek Istediginiz Musterinin TC Numarasini Giriniz :");
	scanf(" %[^\n]s",silinentcNo);
	
	FILE *dosya;
	dosya=fopen("musteribilgisi.txt","r+b");
	
	FILE *dosya2;
	dosya2=fopen("yedekmusteribilgisi.txt","w+b");
	
	while(fread(&musteri,sizeof(musteriBilgi),1,dosya)!=NULL){
		if(strcmp(silinentcNo,musteri.tcNo)==0){
		durum=1;
		}
		else{
			fwrite(&musteri,sizeof(musteriBilgi),1,dosya2);
		}
	}
	fclose(dosya);
	fclose(dosya2);
	
	if(durum==1){
	remove("musteribilgisi.txt");
	rename("yedekmusteribilgisi.txt","musteribilgisi.txt");
	printf("%s TC Numarali Musteri Kaydi Basariyla Silindi.\n",silinentcNo);
	}
	else{
		printf("Girmis Oldugunuz %s TC Numarali Musteri Kaydi Bulunamadi.\n",silinentcNo);
	}
}

void satisListele(){
	char secim;
	system("cls");
	
	printf("                 SATIS LISTELEME EKRANINA HOSGELDINIZ           \n\n");
	
	FILE *dosya;
	dosya=fopen("satislar.txt","r");
	
	if(dosya!=NULL){
	while(!feof(dosya)){
		secim=fgetc(dosya);
		printf("%c",secim);
		}
	}
	else{
		printf("Su An Herhangi Bir Satis Olmamistir.\n");
	}
	fclose(dosya);
}

char menuCiz(){
	char secim;
	
	printf("\n    TELEFON SATIS OTOMASYONUNA HOSGELDINIZ	  \n\n");
	printf("***************************************************\n");
	printf("*                                                 *\n");
	printf("*       1.Telefon Satisi Yap (S/s)                *\n");
	printf("*       2.Yapilan Satislari Listele (L/l)         *\n");
	printf("*       3.Telefon Kaydi Yap (K/k)                 *\n");
	printf("*       4.Telefonlari Listele (T/t)               *\n");
	printf("*       5.Musteri Kaydi Yap (M/m)                 *\n");
	printf("*       6.Musterileri Listele (J/j)               *\n");
	printf("*       7.Telefon Kayit Bilgi Guncelle (G/g)      *\n");
	printf("*       8.Telefon Kaydi Sil (D/d)                 *\n");
	printf("*       9.Musteri Kaydi Sil (E/e)                 *\n");
	printf("*       0.Otomasyondan Cikis Yap (C/c)            *\n");
	printf("*                                                 *\n");
	printf("***************************************************\n\n");
	printf("Lutfen Seciminizi Giriniz :");
	scanf(" %c",&secim);
	secim=toupper(secim);
	return secim;
}
