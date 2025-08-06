# DomainScanner

Basit bir C++ port tarayıcı.

Belirttiğiniz domain üzerindeki TCP portları kontrol eder, hangileri açık diye bakar.  

## Özellikleri

- Domain üzerinden açık portları kontrol eder  
- Belirli bir port aralığında tarama yapar  
- Her port için ayrı thread kullanır 
- Timeout ayarı sayesinde takılmaz
- hızlı

## Kullanım
g++ DomainScanner.cpp -o DomainScan -pthread
### 1. Derleme

Terminalde aşağıdaki komutla derleyebilirsiniz:
### çalıştırma
./DomainScan

Sonra şu bilgileri ister;
Domain: example.com
Start port: 20
End port: 100

örnek çıktısı:
[+] Port 22 is OPEN on example.com
[+] Port 80 is OPEN on example.com


