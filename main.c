/**
@file

Bu uygulamada verilen renk degerleri icin bir matris olusturulmus ve her bir sutunda verilen sayi(yada renk) degerinin 1 kez
tekrar etmesi saglanacak sekilde rekursif bir backtracking algoritmasi tasarlanmistir.
Program menusu 3 kisimdir.
1-Kullanicidan matris boyutu alinir, matris olusturur, doldurtulur ve cozulur.
2-Boyut sabit kalir matris yeniden doldurulur ve cozulur.
3-Yeni bir Matris boyutu alinir, matris olusturur, doldurtulur ve cozulur.
0- Programdan cikmayi saglar.

@author

Name 			 :		Muhammed Yasin SAGLAM	
Student No		 :	 	15011804	
Date 			 :		18/11/2017
E-Mail			 :		myasinsaglam1907@gmail.com
Compiler Used	 :		GCC
IDE			 	 :		DEV-C++(Version 5.11)
Operating System :		Windows 10 Educational Edition
*/
#include <stdio.h>
#include <stdlib.h>

/*
verilen satiri 1 kez saga shift eden fonksiyon
*/
void shifteR(int *arr,int n){
    int temp,i;
    temp=arr[n-1]; //son elemani tempe atariz.
    for (i=1; i<n; i++) {
        arr[n-i]=arr[n-i-1]; //diger elemanlari 1 er saga kaydir...
    }
    arr[0]=temp; //son elemani en basa yaz
}

/*
verilen matrisi ekrana sayi degerleri olarak verilen satirina kadar yazdiran fonksiyon
*/
void printMatrix(int **arr,int row,int n){
    int i,j;
    printf("\nMATRIX :\n");
    for (i=0; i<row+1; i++) {  //verilen satira kadar
    	for(j=0;j<n;j++){ //matrisin tum sutunlarini
			printf(" %d ",arr[i][j]); //yazdir
		}
		printf("\n");
    }
}

/*
verilen matrisi ekrana karsiligi olan renk degerlerine gore verilen satirina kadar yazdiran fonksiyon
*/
void printColor(int **arr,int row,int n){
    int i,j;
    char colors[8][10]={"sari","mavi","yesil","mor","beyaz","siyah","kirmizi","gri"}; //soruda verilen renkler indislere uygun tanimlaniyor
    printf("\nCOLORS :\n");
    for (i=0; i<row+1; i++) { //verilen satira kadar 
    	for(j=0;j<n;j++){ //tum sutunlardaki renkleri
			printf(" %-7s ",colors[arr[i][j]-1]); //yazdir
		}
		printf("\n");
    }
}

/*
verilen satirin her bir elamaninin bulundugu sutundaki ust satirlara bakarak aynisinin olup olmadigini kontrol eden,
varsa 0 yoksa 1 donduren fonksiyon
*/
int control(int **arr,int row,int n){
    int i=0, j=row;
    int temp;
    
    if(row>0){ //satir 0 degilse
        for (i=0; i<n; i++) { //satirin elemanlarini sirayla al
        	temp=arr[row][i];
        	for (j=row-1; j>=0; j--) { //ayni sutununun ust degerleri icin 
            	if(temp==arr[j][i]){ //ayni sayidan bulunuyorsa 
            		//printf("\nnot fisible...\n");
            		return 0; //0 dondur
				}
        	}
    	}
		return 1;	//ilk satirsa 1 dondur
	}
	return 1; //0 ile cikilmamissa hersey fisible demektir 1 dondur
}

/*
verilen matrisin rekursif cozumu yapan fonksiyon
eger fisible olmussa 1 satir ilerler degilse eleman sayisi-1 kez shift islemi yapar
*/
int solve(int **arr,int row,int n){
	int i;
	if(row<n){ //eger bakilan satir eleman sayisindan kucukse
		for(i=0;i<n;i++){ //eleman sayisi kadar 
			if(control(arr,row,n)){ //varilen satiri kontrol et 
				solve(arr,row+1,n); //fisible ise bir sonraki satira gec
			}
			if(i<n-1){ //fisible degil ise ve n-1 defa ile sinirli olarak
				//printf("\n\nRow : %d Shift number : %d \n",row+1,i+1);  //kontrol amacli yazdirma 
				shifteR(arr[row],n); //ilgili satiri 1 saga kaydir.
				//printMatrix(arr,row,n);  //kontrol amacli yazdirma
			}
		}
	}
	else{ //degilse
		row--; //yazdirmada bir sorun cikmamasi icin row u 1 azalt
		printf("\n\nSOLVED !!!\nSolution is : "); 
		//printMatrix(arr,row,n);
		printColor(arr,row,n); //bulunan cozumu ekrana renk olarak yazdir
		return 1; // 1 dondur
	}
return 0; //cozum bulunamazsa 0 dondur
}

/*
Dinamik memory allocate eden ve diziyi disari donduren fonksiyon
*/
int **Allocator(int size){
	int **array;
	int i;
	array=(int**)malloc(sizeof(int*)*size);
	for(i=0;i<size;i++){
		array[i]=(int*)malloc(sizeof(int)*size);
	}	
	if(!array){
		system("COLOR c");
		printf("Array Not Allocated !!! Quitting...");
		exit(0);
	}
	return array;	
}

/*
Verilen integer dizinin boyutunu realloc islemiyle degistiren fonksiyon
*/
void ReAllocator(int ***matrix,int size){
	int i;
	(*matrix)=realloc((*matrix),sizeof(int*)*size);
	for(i=0;i<size;i++){
		(*matrix)[i]=malloc(sizeof(int)*size);
	}
	
}

int main(int argc, const char * argv[]) {
    int **matrix; //matris tanimlaniyor
    int i,j; //cevrim degiskenleri
    int n; //matris boyutu degiskeni
    int choice; //menu icin secenek degiskeni
    
    //menu bilgi mesaji
    printf("\n1.Create matrix and fill(REQUIRED) \n2.Change content of matrix that created in option 1 (SIZE is SAME)\n3.Change size and fill new matrix\n\nPlease enter the choice (0 for exit): ");
	scanf("%d",&choice);			//Kullanicidan tercih okunuyor
	system("CLS");	
    while(choice!=0){ //0-Cikis secilmedigi muddetce 
    	if(choice==1){ //matris olustur ve doldur
    		printf("\nPlease enter matrix size : ");
    		scanf("%d",&n); //eleman sayisini oku
    		matrix=Allocator(n); //matrisi allocate et
    		printf("\n Please fill the matrix that has size %dX%d :\n ",n,n);
			for(i=0;i<n;i++){ 
				for(j=0;j<n;j++){
					scanf("%d",&matrix[i][j]); //matrisi doldur
				}
			}
			solve(matrix,0,n); //matrisi coz
			system("PAUSE");
			system("CLS");
		}
		if(choice==2){ //1. tercihte olusturulan matrisin icerigini degistir.Boyut ayni...
    		printf("\n Please fill the matrix that has size %dX%d :\n ",n,n);
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					scanf("%d",&matrix[i][j]); //yeni icerik okunuyor
				}
			}
			solve(matrix,0,n); //matris cozunuyor
			system("PAUSE");
			system("CLS");
		}
		if(choice==3){ // yeni boyut al ve yeni bir matris olustur.
			printf("\nPlease enter new matrix size : ");
    		scanf("%d",&n); //yeni matris boyutu kullanicidan okunuyor 
    		ReAllocator(&matrix,n); //verilen boyut icin yer reallocate ediliyor
    		printf("\n Please fill the matrix that has size %dX%d :\n ",n,n); 
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					scanf("%d",&matrix[i][j]); //yeni boyutlu matrisin icerigi dolduruluyor
				}
			}
			solve(matrix,0,n); //matris cozuluyor
			system("PAUSE");
			system("CLS");
		}
	printf("\n1.Create matrix and fill(REQUIRED) \n2.Change content of matrix that created in option 1 (SIZE is SAME)\n3.Change size and fill new matrix\n\nPlease enter the choice (0 for exit): ");
	scanf("%d",&choice);			//Kullanicidan tercih okunuyor
	system("CLS");
	}
	
	//matris free ediliyor...
    for(i=0;i<n;i++){ 
    	free(matrix[i]);
	}
    free(matrix);
	return 0;
}
