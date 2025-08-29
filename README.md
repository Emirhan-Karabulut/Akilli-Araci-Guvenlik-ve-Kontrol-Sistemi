# Akıllı Araç İçi Güvenlik ve Kontrol Sistemi

## Screenshots
<table>
  <tr>
    <td>Proteus Devre Tasarımı</td>
    <td>Arduino Kod Yapısı</td>
    <td>Sistem Simülasyon Sonuçları</td>
  </tr>
  <tr>
    <td><img src="screenshots/ss1.jpeg" alt="Proteus Devre Tasarımı" width="300px"></td>
    <td><img src="screenshots/ss2.jpeg" alt="Arduino Kod Yapısı" width="300px"></td>
    <td><img src="screenshots/ss3.jpeg" alt="Sistem Simülasyon Sonuçları" width="300px"></td>
  </tr>
</table>

Bu proje, modern araçlarda bulunan güvenlik ve konfor özelliklerinin mikroişlemci tabanlı bir sistem üzerinde simüle edilmesini amaçlamaktadır. Arduino Mega mikrodenetleyicisi kullanılarak, araç içi güvenlik sistemi, otomatik klima kontrolü, akıllı far sistemi ve yakıt yönetimi gibi kritik araç fonksiyonlarının entegre bir şekilde çalışması sağlanmıştır.

## Proje Özeti

- **Tema:** Arduino tabanlı araç içi güvenlik ve konfor sistemlerinin simülasyonu
- **Temel İşlevler:**
  - **Motor Güvenlik Sistemi:** Emniyet kemeri ve kapı durumu kontrolü ile motor çalıştırma engelleme
  - **Akıllı Klima Kontrolü:** LM35 sıcaklık sensörü ile otomatik fan kontrolü (25°C eşik değeri)
  - **Otomatik Far Sistemi:** LDR sensörü ile ortam ışığına göre far kontrolü (250 eşik değeri)
  - **Yakıt Yönetim Sistemi:** Potansiyometre ile yakıt seviyesi simülasyonu ve kademeli uyarı sistemi
  - **Kapı Güvenlik Kontrolü:** Switch ile kapı durumu takibi ve motor kilitleme
  - **Çok Katmanlı Uyarı Sistemi:** LCD, LED ve buzzer ile sesli/görsel bildirimler
  - **Real-Time Monitoring:** Sensör verilerinin sürekli izlenmesi ve anlık güncelleme

Sistem, kritik güvenlik koşullarında fail-safe moduna geçerek (yakıt bitimi, kapı açık, kemer takılmamış) motor çalışmasını engeller ve kullanıcıyı çoklu kanallardan uyarır.

## Kullanılan Teknolojiler ve Yöntemler

- **Arduino Mega 2560:** Ana mikroişlemci platformu ve GPIO pin yönetimi
- **Proteus Design Suite:** Devre simülasyonu ve sistem validasyonu
- **C/C++ Programlama:** Arduino IDE'de embedded system development
- **Sensör Teknolojileri:**
  - Analog sensör okumaları (LM35 sıcaklık sensörü, LDR ışık sensörü)
  - Dijital GPIO kontrolü (butonlar, switchler)
  - PWM sinyalleri ile motor kontrol
- **Çoklu I/O Yönetimi:**
  - LCD Display (16x2) ile bilgi gösterimi
  - LED kontrolleri (standart ve RGB LED'ler)
  - Buzzer ile ses sinyalizasyonu
  - DC Motor sürücü devreleri
- **Real-Time Programming:**
  - Interrupt tabanlı olay işleme
  - Non-blocking delay fonksiyonları
  - Multi-tasking simulation with millis() timer
- **Güvenlik Algoritmalar:**
  - Fail-safe state machine implementation
  - Priority-based alert system
  - Cascading failure prevention logic

## Teknik Kazanımlar

- **Gömülü Sistem Mimarisi:** Arduino platformunda modüler kod yapısı tasarlayarak, sensör veri akışı ve çıkış kontrollerinin koordine edilmesi konusunda deneyim kazandım.
- **Real-Time System Programming:** Çoklu sensörden gelen verilerin eş zamanlı işlenmesi ve millis() tabanlı non-blocking timer kullanımıyla sistem yanıt sürelerini optimize ettim.
- **Hardware Abstraction:** GPIO pin konfigürasyonu, analog-dijital dönüşümler ve PWM kontrolleri ile donanım seviyesinde programlama becerim gelişti.
- **State Machine Design:** Araç durumlarının (motor çalışır/durur, klima açık/kapalı) mantıksal kontrolü için durum makinesi algoritmaları geliştirdim.
- **Safety-Critical Programming:** Fail-safe mekanizmalar ve öncelik tabanlı uyarı sistemleri tasarlayarak güvenlik odaklı yazılım geliştirme deneyimi edindim.
- **Sensor Calibration & Processing:** LM35, LDR ve potansiyometre sensörlerinin kalibrasyon süreçleri ve sinyal filtreleme teknikleriyle çalıştım.
- **Debugging & Simulation:** Proteus ortamında devre analizi ve Arduino Serial Monitor kullanarak sistem davranışlarını gözlemleme yeteneğim gelişti.

## Sistem Özellikleri

- **Çok Katmanlı Güvenlik Sistemi:** Emniyet kemeri, kapı durumu kontrolü ile motor çalıştırma engelleme
- **Akıllı Çevre Adaptasyonu:** LDR ve LM35 sensörleriyle otomatik far ve klima aktivasyonu
- **Kademeli Uyarı Sistemi:** Yakıt seviyesine göre normal (%10-5), kritik (%5-0) ve acil durum (0%) uyarıları
- **Real-Time Dashboard:** 16x2 LCD ile anlık sistem durumu görüntüleme
- **Multi-Modal Alert System:** LED (4 farklı renk), buzzer ve LCD ile eş zamanlı bildirim
- **Automatic Fail-Safe:** Kritik durumlarda motor otomatik durdurma ve güvenli mod geçişi
- **Sensor Fusion:** Çoklu sensör verilerinin koordine işlenmesi ve karar verme algoritması

## Çalışma Senaryoları

**1. Motor Güvenlik Kontrolü**
- Emniyet kemeri kontrolü: Motor çalıştırma öncesi zorunlu kemer takma kontrolü
- Kapı güvenlik sistemi: Açık kapı durumunda motor kilitleme mekanizması
- Sesli ve görsel uyarılar: Buzzer + Kırmızı LED + LCD mesaj kombinasyonu

**2. Otomatik İklim Kontrol**
- 25°C eşik kontrolü ile klima fan otomasyonu
- DC motor hız kontrol ve LCD'de sıcaklık gösterimi
- Sıcaklık düştüğünde otomatik sistem kapatma

**3. Akıllı Aydınlatma Sistemi**
- LDR sensörü ile 250 değer eşiği kontrol
- Karanlık ortamda otomatik far açma (Mavi LED)
- LCD'de far durumu bilgisi gösterimi

**4. Yakıt Yönetim Algoritması**
- %10 altında sarı LED uyarısı
- %5 altında yanıp sönen LED + kritik mesaj
- %0'da complete system shutdown

## Sonuç

Bu projede, modern araç güvenlik sistemlerinin mikroişlemci seviyesinde modellenmesi ile gömülü sistem programlama ve donanım entegrasyonu konularında derinlemesine deneyim kazandım. Arduino Mega platformunda çoklu sensör yönetimi, real-time veri işleme ve güvenlik odaklı algoritma geliştirme yeteneklerimi geliştirdim. 

Sistem mimarisi, kritik güvenlik koşullarında fail-safe davranış sergileyecek şekilde tasarlandı ve Proteus simülasyon ortamında kapsamlı test süreçlerinden geçirildi. Bu proje, otomotiv endüstrisindeki embedded system geliştirme süreçlerine yönelik pratik deneyim sağlamış ve hardware-software interface programlama becerilerimi güçlendirmiştir.

---

*Not: Bu proje, iş başvuruları kapsamında portföy olarak sunulmuştur. Dolayısıyla, kullanıcı kurulumu veya kullanım talimatları yerine, yapılan işin genel hatlarını ve teknolojik altyapısını vurgulamak amaçlanmıştır.*
