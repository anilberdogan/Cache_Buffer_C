#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX 30

	
	struct n {
	char adres[MAX];
	int sayac;               // DOUBLY LÝNKED LÝST OLDUGUNDAN NEXT PREV TANIMLADIM
	struct n * next;
	struct n * prev;
	};
	typedef struct n node;
	
		
	//bastir
		void bastir(node * r){
		while(r!=NULL){
			printf(" %s, ",r->adres);   	//BASTIR FONKSÝYONU ÝLK NODEDAN BASLAYIP SONA KADAR TEK TEK BASTIRIYOR
			printf("%d",r->sayac);
			r=r->next;
			printf("  ->  ");
		}		
	}
	
			//FONKSÝYON		VOÝD DISINDAKÝ TEK FONKSÝYONUM TÜM ÝSLEMLER BURADA GERCEKLESÝYOR
		node * search (node * r,int Length,int sayacsiniri,int * bitti,FILE *f,int * secimim){
		/*ALDIÐIM PARAMETRELER ROOT,UZUNLUK,ASAYCSINIRI,BÝTTÝ ADLI POÝNTER(BÝTÝRMEK ÝSTENDÝÐÝNDE GEREKÝYOR,
		FILE POÝNTER,SECÝMÝM ADLI ÝNT POÝNTER, ÝNPUTU NASIL ALMAK ÝSTEDÝÐÝMÝ BELÝRLÝYOR*/
		
		char yeniadr[30];
		node*silici=r;
		
		if(secimim==1){
				printf("\neleman giriniz: ");            //ELLE ELEMAN GÝRÝLEN KISIM
				scanf("%s",yeniadr);
		}
		else{
				fscanf(f,"%s",yeniadr);					 // DOSYADAN ELEMAN ALINAN KISIM
			
		}
				
		if(strcmp(yeniadr,"-1")==0){
			bitti=1;									// PROGRAMI BÝTÝRME KISMI
			printf("program kapaniyor");
			return bitti;
		}
				
		
		if(strcmp(yeniadr,"sil")==0){
			
			while(r->next!=NULL){
				silici=r;
				silici->prev=NULL;						// "sil" GÝRÝLDÝÐÝNDE ÇALIÞACAK OLAN
				r=r->next;								// TÜM NODELARI SÝLME KISMI
				silici->next=NULL;
				r->prev=NULL;
				free(silici);						
			}
			free(r);
						
			node * yeni=(node*)malloc(sizeof(node));
			printf("\neleman giriniz: ");
			scanf("%s",&yeni->adres);			// SIKINTI ÇIKMAMASI ÝÇÝN ÝLK ELEMANI OLUÞTURUYORUM 
			yeni->sayac=1;						// KÝ ROOT HÝÇ BÝ ZAMAN NULL KALMASIN
			return yeni;				
		}
						
		node * enbas=r;
		node * yardimci;				// AÞAÐIDA KULLANMKA ÝÇÝN YARDIMCI NODE POÝNTERLARIM
		node * p=r;
		node * iter=r;
				
			
	while (r) {
        if (strcmp(r, yeniadr) == 0) {		//GÝRÝLEN STRÝNG LÝSTEDE VAR MI KONTROLÜ
            r->sayac++;
            
            if(r->sayac > sayacsiniri){
				
				// zaten basta olma ihtimali		
				if(r->prev!=NULL){ // ilk eleman deðilse kontrolu, ilk eleman olsaydý bisey yapmayacaktým
																			
					if(r->next==NULL){ // SON ELEMANSA  
						iter=r->prev;
						iter->next=NULL;
						r->next=p;
						r->prev=NULL;
						p->prev=r;
						return r;			//ROOTUM DEÐÝÞTÝÐÝ ÝÇÝN ROOTU DÖNDÜRÜYORUM
					}					
					//arada bir elemansa
					else{
						iter=r->prev;
						yardimci=r->next;
						iter->next=yardimci;
						yardimci->prev=iter;
						r->next=p;
						r->prev=NULL;
						p->prev=r;
						return r;
					}					
				}
				else{
					return enbas;  // ÝLK ELEMANSA ÝÞLEME GEREK YOK
				}												
			}
			else{
				return enbas ; // SAYAC SINIRI GEÇMEDÝYSE ÝÞLEME GEREK YOK
			}           
        }
        else{
        	r = r->next;
		}      	 	      
    }
    
		// EGER ELEMAN LÝSTEDE YOKSA
		
		if(r==NULL){
		
			//BASA EKLEME
			node * temp=(node *)malloc(sizeof(node));
			temp->next=enbas;   
			enbas->prev=temp;
			temp->prev=NULL;
			temp->sayac=1;
		
			strcpy(temp->adres,yeniadr); 			//ALDIÐIM STRÝNGÝ NODE DA YERÝNE YERLEÞTÝRÝYORUM
			node * current =temp->next;
			node * onceki=temp;
		
			int kontrol=1;
			while(current!=NULL){
				kontrol++;
				onceki=current;	
				current=current->next;			
			}
			if(kontrol>Length){
				onceki->prev->next=NULL;		   // UZUNLUK (LENGTH KONTROLU)
				onceki->prev=NULL;
				free(onceki);				
			}
			return temp;
				
		}	
	}	
		///////////////////////// MAIN ////////////////////////////////////	
		
		int main(){
		int i,secim;
		int *bitti;
		bitti=0;
		int *secimim;
		char yeniadr[MAX],dosya[MAX];
		int Length,sayacsiniri;
				
		
		printf("Linked listi silmek icin sil yaziniz: \n");
		printf("Bitirmek icin -1 giriniz\n");
		printf("Kac elemali bir liste olacak giriniz (L) : ");			//T VE L'YÝ ALIYORUM
		scanf("%d",&Length);
		printf("Adreslerin sayac siniri kac (T) : ");
		scanf("%d",&sayacsiniri);
		
		
		node * root=(node*)malloc(sizeof(node));
		
		printf("elemanlari kendiniz girmek icin 1 dosyadan almak icin 2 ye basiniz. ");
		scanf("%d",&secim);			
		
		FILE *f;			// FILE POÝNTER TANIMLIYORUM ÜSTTE TANIMLIYORUM CUNKÜ PARAMETRE
		
		secimim=secim;
		
		if(secim==1){
		printf("ilk stringi giriniz: ");
		scanf("%s",&root->adres); 				// ÝLK NODE U OLUÞTURUYORUM
		root->sayac=1;
		root->next=NULL;
		root->prev=NULL;
		bastir(root);
		
		while(bitti==0){
			root=search (root,Length,sayacsiniri,bitti,f,secimim);
			bastir(root);				//ÝÞLEM GERÇEKLEÞÝYOR
		}		
		}
		
		else{
			printf("dosya adinizi yaziniz : orn (dosya.txt):  ");
			scanf("%s",dosya);
			f=fopen(dosya,"r");
			
			fscanf(f,"%s",root->adres);				
			root->sayac=1;
			root->next=NULL;
			root->prev=NULL;
			
			
			while(!feof(f)){
				
				root=search (root,Length,sayacsiniri,bitti,f,secimim);
				bastir(root);
				printf("\n");		
			}
			fclose(f)	;	
		}	
	}
			
