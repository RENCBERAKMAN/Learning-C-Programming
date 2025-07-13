#include <stdio.h>      // Standart giriş/çıkış işlemleri için kütüphane
#include <stdlib.h>     // Bellek ayırma ve çıkış işlemleri için kullanılır
#include <string.h>     // Karakter dizisi işlemleri için (örn. fgets, strcspn)
#include <math.h>       // Matematiksel işlemler için (örn. pow, M_PI)

// Kullanıcının temel bilgilerini tutmak için struct kullanılır
// Struct, birden fazla veriyi bir isim altında gruplandırmak için C'de kullanılan yapıdır.
typedef struct {
    char name[50];      // Kullanıcının adı
    int age;            // Kullanıcının yaşı
} User;

//  Menü seçeneklerini ekrana yazdıran fonksiyon
// Bu fonksiyon, kullanıcıya sunulan işlemlerin listesini gösterir
void printMenu() {
    printf("\n📍 Ana Menü\n");
    printf("1. Öğrenci Not Ortalaması Hesabı\n");
    printf("2. Geometrik Hesaplama (Dikdörtgen ve Daire)\n");
    printf("3. Sıcaklık Dönüşümü (Celsius - Fahrenheit)\n");
    printf("4. Üs Alma\n");
    printf("5. Faktöriyel Hesabı\n");
    printf("6. Dosyaya Kullanıcı Bilgisi Kaydet\n");
    printf("0. Çıkış\n");
}

//  Kullanıcının girdiği notlara göre ortalama hesaplar
void calculateAverage() {
    int num, sum = 0;
    printf("Kaç not girilecek? ");
    scanf("%d", &num);

    int grades[num]; // C99 ile gelen esnek dizi tanımı
    for(int i = 0; i < num; i++) {
        printf("Not %d: ", i+1);
        scanf("%d", &grades[i]); // Her notu diziye alır
        sum += grades[i];        // Toplam değere eklenir
    }

    // Ortalama, toplamı öğrenci sayısına bölerek bulunur
    float avg = (float)sum / num;
    printf("📊 Not Ortalaması: %.2f\n", avg);
}

// Basit geometrik hesaplamalar yapar: dikdörtgen ve daire
void geometricCalc() {
    int choice;
    printf("1. Dikdörtgen\n2. Daire\nSeçim: ");
    scanf("%d", &choice);

    if(choice == 1) {
        float w, h;
        printf("Genişlik: "); scanf("%f", &w);
        printf("Yükseklik: "); scanf("%f", &h);
        // Alan = genişlik × yükseklik, Çevre = 2 × (genişlik + yükseklik)
        printf("Alan: %.2f | Çevre: %.2f\n", w*h, 2*(w+h));
    } else if(choice == 2) {
        float r;
        printf("Yarıçap: "); scanf("%f", &r);
        // Alan = π × r², Çevre = 2 × π × r
        printf("Alan: %.2f | Çevre: %.2f\n", M_PI*r*r, 2*M_PI*r);
    } else {
        printf(" Geçersiz seçim.\n");
    }
}

// Celsius sıcaklığı Fahrenheit'a dönüştürür
void temperatureConversion() {
    float c;
    printf("Celsius giriniz: ");
    scanf("%f", &c);
    // Fahrenheit = (Celsius × 9 / 5) + 32
    printf(" Fahrenheit: %.2f\n", (c * 9 / 5) + 32);
}

// Üs alma işlemi: taban ve üs değerlerini kullanıcıdan alır
void calculatePower() {
    double base, exponent;
    printf("Taban: "); scanf("%lf", &base);
    printf("Üs: "); scanf("%lf", &exponent);
    // pow(x, y) → x üzeri y
    printf("Sonuç: %.2lf\n", pow(base, exponent));
}

// Faktöriyel hesaplama: n! = 1 × 2 × 3 × ... × n
void factorial() {
    int n;
    printf("Faktöriyel hesaplamak için sayı girin: ");
    scanf("%d", &n);
    
    unsigned long long result = 1; // Büyük sayılar için veri tipi
    for(int i = 1; i <= n; i++)
        result *= i;

    printf("%d! = %llu\n", n, result);
}

// Kullanıcıdan isim ve yaş bilgisi alır, bir dosyaya kaydeder
void saveUserToFile() {
    User u; // struct değişkeni tanımlanır
    getchar(); // scanf sonrası \n karakterini temizler

    // Ad bilgisi alınır, fgets ile boşluklu adlar da kabul edilir
    printf("Adınız: ");
    fgets(u.name, sizeof(u.name), stdin);
    u.name[strcspn(u.name, "\n")] = 0; // newline karakterini kaldırır

    printf("Yaşınız: ");
    scanf("%d", &u.age);

    // Dosya açılır ve bilgilerin yazılması sağlanır
    FILE *f = fopen("user_data.txt", "w");
    if(f == NULL) {
        printf("Dosya açılamadı \n");
        return;
    }

    // Bilgiler dosyaya yazdırılır
    fprintf(f, "Ad: %s | Yaş: %d\n", u.name, u.age);
    fclose(f);

    printf("Bilgiler 'user_data.txt' dosyasına kaydedildi.\n");
}

// Programın giriş noktası
int main() {
    int selection; // Menü seçimi

    // Kullanıcı "0" girene kadar döngü devam eder
    do {
        printMenu(); // Menü yazdırılır
        printf("Seçiminizi girin: ");
        scanf("%d", &selection); // Seçim alınır

        // Kullanıcının seçimine göre ilgili fonksiyon çalıştırılır
        switch(selection) {
            case 1: calculateAverage(); break;
            case 2: geometricCalc(); break;
            case 3: temperatureConversion(); break;
            case 4: calculatePower(); break;
            case 5: factorial(); break;
            case 6: saveUserToFile(); break;
            case 0: printf("Program sonlandırılıyor...\n"); break;
            default: printf(" Geçersiz seçim!\n");
        }

    } while(selection != 0); // 0 girilene kadar devam

    return 0; // Program başarıyla bitti
}