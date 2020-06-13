#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX 30

	
	struct n {
	char adres[MAX];
	int sayac;               // DOUBLY L�NKED L�ST OLDUGUNDAN NEXT PREV TANIMLADIM
	struct n * next;
	struct n * prev;
	};
	typedef struct n node;
	
		
	//bastir
		void bastir(node * r){
		while(r!=NULL){
			printf(" %s, ",r->adres);   	//BASTIR FONKS�YONU �LK NODEDAN BASLAYIP SONA KADAR TEK TEK BASTIRIYOR
			printf("%d",r->sayac);
			r=r->next;
			printf("  ->  ");
		}		
	}
	
			//FONKS�YON		VO�D DISINDAK� TEK FONKS�YONUM T�M �SLEMLER BURADA GERCEKLES�YOR
		node * search (node * r,int Length,int sayacsiniri,int * bitti,FILE *f,int * secimim){
		/*ALDI�IM PARAMETRELER ROOT,UZUNLUK,ASAYCSINIRI,B�TT� ADLI PO�NTER(B�T�RMEK �STEND���NDE GEREK�YOR,
		FILE PO�NTER,SEC�M�M ADLI �NT PO�NTER, �NPUTU NASIL ALMAK �STED���M� BEL�RL�YOR*/
		
		char yeniadr[30];
		node*silici=r;
		
		if(secimim==1){
				printf("\neleman giriniz: ");            //ELLE ELEMAN G�R�LEN KISIM
				scanf("%s",yeniadr);
		}
		else{
				fscanf(f,"%s",yeniadr);					 // DOSYADAN ELEMAN ALINAN KISIM
			
		}
				
		if(strcmp(yeniadr,"-1")==0){
			bitti=1;									// PROGRAMI B�T�RME KISMI
			printf("program kapaniyor");
			return bitti;
		}
				
		
		if(strcmp(yeniadr,"sil")==0){
			
			while(r->next!=NULL){
				silici=r;
				silici->prev=NULL;						// "sil" G�R�LD���NDE �ALI�ACAK OLAN
				r=r->next;								// T�M NODELARI S�LME KISMI
				silici->next=NULL;
				r->prev=NULL;
				free(silici);						
			}
			free(r);
						
			node * yeni=(node*)malloc(sizeof(node));
			printf("\neleman giriniz: ");
			scanf("%s",&yeni->adres);			// SIKINTI �IKMAMASI ���N �LK ELEMANI OLU�TURUYORUM 
			yeni->sayac=1;						// K� ROOT H�� B� ZAMAN NULL KALMASIN
			return yeni;				
		}
						
		node * enbas=r;
		node * yardimci;				// A�A�IDA KULLANMKA ���N YARDIMCI NODE PO�NTERLARIM
		node * p=r;
		node * iter=r;
				
			
	while (r) {
        if (strcmp(r, yeniadr) == 0) {		//G�R�LEN STR�NG L�STEDE VAR MI KONTROL�
            r->sayac++;
            
            if(r->sayac > sayacsiniri){
				
				// zaten basta olma ihtimali		
				if(r->prev!=NULL){ // ilk eleman de�ilse kontrolu, ilk eleman olsayd� bisey yapmayacakt�m
																			
					if(r->next==NULL){ // SON ELEMANSA  
						iter=r->prev;
						iter->next=NULL;
						r->next=p;
						r->prev=NULL;
						p->prev=r;
						return r;			//ROOTUM DE���T��� ���N ROOTU D�ND�R�YORUM
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
					return enbas;  // �LK ELEMANSA ��LEME GEREK YOK
				}												
			}
			else{
				return enbas ; // SAYAC SINIRI GE�MED�YSE ��LEME GEREK YOK
			}           
        }
        else{
        	r = r->next;
		}      	 	      
    }
    
		// EGER ELEMAN L�STEDE YOKSA
		
		if(r==NULL){
		
			//BASA EKLEME
			node * temp=(node *)malloc(sizeof(node));
			temp->next=enbas;   
			enbas->prev=temp;
			temp->prev=NULL;
			temp->sayac=1;
		
			strcpy(temp->adres,yeniadr); 			//ALDI�IM STR�NG� NODE DA YER�NE YERLE�T�R�YORUM
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
		printf("Kac elemali bir liste olacak giriniz (L) : ");			//T VE L'Y� ALIYORUM
		scanf("%d",&Length);
		printf("Adreslerin sayac siniri kac (T) : ");
		scanf("%d",&sayacsiniri);
		
		
		node * root=(node*)malloc(sizeof(node));
		
		printf("elemanlari kendiniz girmek icin 1 dosyadan almak icin 2 ye basiniz. ");
		scanf("%d",&secim);			
		
		FILE *f;			// FILE PO�NTER TANIMLIYORUM �STTE TANIMLIYORUM CUNK� PARAMETRE
		
		secimim=secim;
		
		if(secim==1){
		printf("ilk stringi giriniz: ");
		scanf("%s",&root->adres); 				// �LK NODE U OLU�TURUYORUM
		root->sayac=1;
		root->next=NULL;
		root->prev=NULL;
		bastir(root);
		
		while(bitti==0){
			root=search (root,Length,sayacsiniri,bitti,f,secimim);
			bastir(root);				//��LEM GER�EKLE��YOR
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
			
