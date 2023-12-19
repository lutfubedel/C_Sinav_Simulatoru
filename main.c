#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void cevap_anahtari_uret(char cevap_anahtari[],int S)
{
    srand(time(0));
    for(int i=0;i<S;i++)
    {
        //ASCII ile A-E arasinda rastgele harf üretip cevap anahtarinin i. degerine atamadım.
        cevap_anahtari[i]=(rand()%5)+65;
    }
}

void cevap_anahtari_yazdir(char cevap_anahtari[],int S)
{
    printf("Cevap anahtari : \n");
    // For dongusu ile cevap anahtarini dizisini ekrana yazdirdim.
    for(int i=0;i<S;i++)
    {
        printf("%.3d:%c | ",i+1,cevap_anahtari[i]);
    }
    printf("\n\n");
}

void sinavi_uygula(char ogrenci_cevaplari[][100],char cevap_anahtari[],int N,int S,double B,double D)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<S;j++)
        {
            // Bos birakma ya da dogru yapma olasiligini kontrol etmek icin olasilik adlı bir degisken tanimlandim.
            int olasilik=rand()%100; // olasilik degiskenine 0-100 arasinda rastgele bir sayi atadim.
            if(olasilik<B*100.0)//Bos birakma durumunda calisacak kod
                ogrenci_cevaplari[i][j]='X';
            else
            {
              if(olasilik<D*100.0)//Dogru cevap verme durumunda calisacak kod
                ogrenci_cevaplari[i][j]=cevap_anahtari[j];
              else//Cevabin yanlis olma durumunda dogru cevap disinda rastgele bir cevap uretecek kod
              {
                  //Ogrenci cevaplarina cevap anahtarindan farkli olana kadar rasstgele harfler atar.
                  do
                  {
                      ogrenci_cevaplari[i][j]=(rand()%5)+65;
                  }while(ogrenci_cevaplari[i][j]==cevap_anahtari[j]);
              }
            }
        }
    }
}

void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[][100], int ogrenci_ID,int S)
{
    //İc ice donguler ile ogrenci_cevaplari matrisini ekrana yazdirma kodu.
    for(int i=0;i<ogrenci_ID;i++)
    {
        printf("%.3d. ogrencinin cevaplari: \n",i+1);
        for(int j=0;j<S;j++)
        {
            printf("%.3d:%c | ",j+1,ogrenci_cevaplari[i][j]);
        }
        printf("\n");
    }
}

void ogrencileri_puanla(char ogrenci_cevaplari[][100],char cevap_anahtari[],double HBN[],int N, int S)
{

  for(int i=0;i<N;i++)
    {
      double puan; //Ogrencinin puanini tutmak icin tanimlanan degisken
      for(int j=0;j<S;j++)
        {
          if(ogrenci_cevaplari[i][j]==cevap_anahtari[j])//Cevabin dogru olma durumunda puan degiskenine soru basina düsen puan eklenecek.
            puan+=(100.0/S);
          else if(ogrenci_cevaplari[i][j]=='X')//Soru bos ise puana herhangi bir ekleme ya da cikarma islemi yapilmayacaktir.
            continue;
          else//Cevabin yanlis olma durumunda puan degiskeninin degeri 0.25 azalacak böylelikle 4 yanlis 1 dogruyu goturecek.
            puan -=0.25;
        }

      if(puan>=0)// Puan 0 dan buyukse HBN dizisinin i. degerine puani atar.
        HBN[i]=puan;
      else//Puanin eksi cikmasi durumunda puani 0 a esitler.
        HBN[i]==0;

      puan=0.0;//Bir sonraki ogrenciye gecmeden once puanı 0 a esitler.

    }
}

double sinif_ortalamasi_hesapla(double HBN[], int N)
{
    double ort=0;//Sinif ortalamasini tutacak degisken
    for(int i=0;i<N;i++)
    {
        ort+=HBN[i];//Her bir öðrencinin puani ort degiskenine eklenir.
    }
    ort=ort/N;//Toplam puan ogrenci sayisina bolunerek sinif ortalamasi bulunur.
    return ort;
}

double standart_sapma_hesapla(double ortalama, double HBN[],int N)
{
    double standart_sapma;//Standart sapma degerini tutacak degisken
    for(int i=0;i<N;i++)
    {
        standart_sapma+=pow((HBN[i]-ortalama),2);
    }
    standart_sapma=sqrt(standart_sapma/N);
    return standart_sapma;
}

void T_skoru_hesapla(double ortalama,double HBN[],int N,double std,double T_skoru[])
{
    for(int i=0;i<N;i++)
    {
        //T_skoru hesaplama formulu.
        T_skoru[i]=60+10*(HBN[i]-ortalama)/std;
    }
}

void Sinif_Duzeyi(double ortalama,int N,double T_skoru[],char Ogrenci_Harf_Notu[][100])
{
  int kontrol=0; //Sinif durumunu temsil eden degisken.
  int a=0; // Sinif durumuna göre harf notlarinin hangi aralikta olacagini belirleyen degisken.

  // Ortalamaya gore sinif durumunu belirleme kodlar.
  if(ortalama<=42.5)
  {
    printf("Sinif durumu: Kotu");
    kontrol=1;
  }
  else if(42.5<ortalama && ortalama<=47.5)
  {
    printf("Sinif durumu: Zayif");
    kontrol=2;
  }
  else if(47.5<ortalama && ortalama<=52.5)
  {
    printf("Sinif durumu: Orta");
    kontrol=3;
  }
  else if(52.5<ortalama && ortalama<=57.5)
  {
    printf("Sinif durumu: Ortanin Ustu");
    kontrol=4;
  }
  else if(57.5<ortalama && ortalama<=62.5)
  {
    printf("Sinif durumu: Iyi");
    kontrol=5;
  }
  else if(62.5<ortalama && ortalama<=70)
  {
    printf("Sinif durumu: Cok Iyi");
    kontrol=6;
  }
  else if(70<ortalama && ortalama<=80)
  {
    printf("Sinif durumu: Mukemmel");
    kontrol=7;
  }
  else
  {
    printf("Sinif durumu: Ustun Basari");
    kontrol=8;
  }

  //Sinif durumuna göre harf notlarinin hangi aralikta olacagini belirleyen kodlar.
  switch(kontrol)
  {
    case 1:
        a+=14;
        break;
    case 2:
        a+=12;
        break;
    case 3:
        a+=10;
        break;
    case 4:
        a+=8;
        break;
    case 5:
        a+=6;
        break;
    case 6:
        a+=4;
        break;
    case 7:
        a+=2;
        break;
    default:
        a=0;
  }

    //T_skoru dizisi ve a degiskenine göre harf notu veren kod.
    for(int i=0;i<N;i++)
    {
        if(T_skoru[i]<32+a)
            strcpy(Ogrenci_Harf_Notu[i],"FF");
        else if(32+a<=T_skoru[i] && T_skoru[i]<37+a)
            strcpy(Ogrenci_Harf_Notu[i],"FD");
        else if(37+a<=T_skoru[i] && T_skoru[i]<42+a)
            strcpy(Ogrenci_Harf_Notu[i],"DD");
        else if(42+a<=T_skoru[i] && T_skoru[i]<47+a)
            strcpy(Ogrenci_Harf_Notu[i],"DC");
        else if(74+a<=T_skoru[i] && T_skoru[i]<52+a)
            strcpy(Ogrenci_Harf_Notu[i],"CC");
        else if(52+a<=T_skoru[i] && T_skoru[i]<57+a)
            strcpy(Ogrenci_Harf_Notu[i],"CB");
        else if(57+a<=T_skoru[i] && T_skoru[i]<62+a)
            strcpy(Ogrenci_Harf_Notu[i],"BB");
        else if(62+a<=T_skoru[i] && T_skoru[i]<67+a)
            strcpy(Ogrenci_Harf_Notu[i],"BA");
        else
            strcpy(Ogrenci_Harf_Notu[i],"AA");
    }

}


int main()
{
    int N,S;
    double B,D;
    char cevap_anahtari[100];
    char ogrenci_cevaplari[100][100];
    double HBN[100];
    double T_skoru[100];
    double ortalama,std;
    char harfler[20];
    char Ogrenci_Harf_Notu[100][100];

    //Kullanicidan deger alma kodlari
    printf("Ogrenci sayisini giriniz (max 100): ");
    scanf("%d",&N);
    printf("Soru sayisini giriniz (max 100): ");
    scanf("%d",&S);
    printf("Bos Birakma ihtimalini giriniz (0.0 ~ 1.0): ");
    scanf("%lf",&B);
    printf("Dogru cevap verme ihtimalini giriniz (0.0 ~ 1.0): ");
    scanf("%lf",&D);

    //Fonksiyonlarin cagirildigi kisim
    cevap_anahtari_uret(cevap_anahtari,S);
    cevap_anahtari_yazdir(cevap_anahtari,S);

    sinavi_uygula(ogrenci_cevaplari,cevap_anahtari,N,S,B,D);
    ogrenci_cevabini_yazdir(ogrenci_cevaplari,N,S);

    ogrencileri_puanla(ogrenci_cevaplari,cevap_anahtari,HBN,N,S);
    standart_sapma_hesapla(ortalama,HBN,N);

    // ortalama ve standart sapma degerlerini tutan degiskenler.
    ortalama=sinif_ortalamasi_hesapla(HBN,N);
    std=standart_sapma_hesapla(ortalama,HBN,N);

    T_skoru_hesapla(ortalama,HBN,N,std,T_skoru);
    printf("\n");

    printf("Sinif ortalamasi: %.2lf , standart sapma: %.2lf \n",ortalama,std);
    Sinif_Duzeyi(ortalama,N,T_skoru,Ogrenci_Harf_Notu);
    printf("\n\n");

    printf("Ogrenci notlari: \n");
    for(int i=0;i<N;i++)
    {
        printf("%.2d. ogrencinin HBN: %.2lf, T-skoru: %.2lf, harf notu: %s  \n",i+1,HBN[i],T_skoru[i],Ogrenci_Harf_Notu[i]);
    }

    return 0;
}
