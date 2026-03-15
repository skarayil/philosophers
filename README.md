# 🍝 Philosophers - Dining Philosophers Problemi

<div align="center">

![42 School](https://img.shields.io/badge/School-42-black?style=for-the-badge&logo=42)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Philosophers](https://img.shields.io/badge/Project-philosophers-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**Edsger Dijkstra'nın klasik senkronizasyon problemini thread ve process kullanarak çözen simülasyon**

*Bu proje, eş zamanlı programlama, mutex kilitleri, semaforlar ve deadlock önleme konularında derinlemesine deneyim kazandırır.*

[Kurulum](#-kurulum) • [Kullanım](#-kullanım) • [Özellikler](#-özellikler) • [Bonus](#-bonus-kısmı)

</div>

---

## 🎯 Projenin Amacı

<img align="right" alt="Dining Philosophers" width="300" src="https://media2.giphy.com/media/v1.Y2lkPTc5MGI3NjExNjl1OGo5cDlicmY3em90YXg1bW1zMTdvcW5pZW0yMzNjM3N4YXQzMyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/VTtANKl0beDFQRLDTh/giphy.gif">

Bu proje, **Dining Philosophers** (Yemek Yiyen Filozoflar) problemini C dilinde çözmeyi amaçlar. Her filozof bir thread (mandatory) ya da process (bonus) olarak temsil edilir; paylaşımlı çatal kaynakları mutex veya semafor ile korunur. Projenin özü, açlıktan ölüm (starvation) ve kilitlenme (deadlock) olmadan tüm filozofların yemek yiyebilmesini sağlamaktır.

### 🎓 **Ana Öğrenme Hedefleri:**

#### 🧵 **Thread (Mandatory) — pthread Kütüphanesi**
- `pthread_create` ile her filozof için ayrı thread oluşturma
- `pthread_join` ile thread'lerin tamamlanmasını bekleme
- Thread yaşam döngüsü yönetimi ve paylaşılan bellek üzerinde güvenli okuma/yazma
- Aynı süreç içinde birden fazla çalışma akışını koordine etme

#### 👶 **Process (Bonus) — fork & waitpid**
- `fork()` ile her filozof için bağımsız child process oluşturma
- `waitpid(-1, ...)` ile parent'ın tüm child'ları takip etmesi
- Process'lerin birbirinden izole çalışması ve belleği paylaşmaması
- `SIGTERM` ile tüm child process'lerin düzgün biçimde sonlandırılması

#### 🔒 **Mutex (Mandatory) — pthread_mutex_t**
- Her çatal için ayrı `pthread_mutex_t` kilidi oluşturma
- `pthread_mutex_lock` / `pthread_mutex_unlock` ile paylaşılan veriye güvenli erişim
- Yalnızca bir thread'in aynı anda bir kaynağı kullanabilmesini sağlama
- Birden fazla mutex'i tutarlı sırada kilitleyerek **deadlock** önleme

#### 🚦 **Semaphore (Bonus) — sem_t / POSIX**
- `sem_open` ile isimli POSIX semaforları oluşturma (process'ler arası paylaşım)
- `sem_wait` / `sem_post` ile çatal havuzuna erişimi sayaç tabanlı yönetme
- Mutex'in aksine semafor, farklı process'ler arasında paylaşılabilir
- `sem_close` ve `sem_unlink` ile semafor temizliği ve isim çakışmasını önleme

#### 🔄 **Deadlock ve Race Condition**
- Döngüsel beklemeyi (circular wait) adres sıralamasıyla engelleme
- `volatile` ve mutex korumasıyla veri yarışını (data race) önleme
- Starvation (açlıktan ölüm) senaryolarını tespit etme ve yönetme
- Helgrind / Valgrind ile eş zamanlılık hatalarını analiz etme

#### ⏱️ **Zaman Yönetimi**
- `gettimeofday` ile milisaniye hassasiyetinde zaman ölçümü
- Busy-wait yerine `usleep` ile CPU dostu bekleme
- Simülasyonun başlangıç zamanına göre göreli zaman damgaları

#### 🛡️ **Bellek ve Kaynak Güvenliği**
- `malloc` / `free` ile dinamik bellek yönetimi
- Mutex ve semaforların doğru şekilde başlatılıp yok edilmesi
- Hata durumlarında tam kaynak temizleme

---

## ✨ Özellikler

<div align="center">

![Thread Safety](https://img.shields.io/badge/Thread-Safety-brightgreen?style=for-the-badge)
![Deadlock Free](https://img.shields.io/badge/Deadlock-Free-blue?style=for-the-badge)
![Color Output](https://img.shields.io/badge/Color-Output-orange?style=for-the-badge)

</div>

### 📋 **Kurallar**

| Kural | Açıklama |
|-------|----------|
| Her filozofun yemek yemesi için **iki çatala** ihtiyacı var | Sol ve sağındaki çatal |
| Bir çatal aynı anda yalnızca **bir filozof** tarafından kullanılabilir | Mutex ile korunur |
| Yemek yeme süresi `time_to_eat` ms | `ft_usleep` ile bekleme |
| Uyku süresi `time_to_sleep` ms | `ft_usleep` ile bekleme |
| `time_to_die` ms içinde yemek yemeyen filozof **ölür** | Monitor thread tarafından kontrol |
| Opsiyonel: Her filozofun en az `must_eat` kez yemek yemesi | Tüm filozoflar yediyse simülasyon biter |

### 🔧 **Mimari (Mandatory)**

```
main.c
  ├── ft_init()        → Argüman parse, malloc, mutex init, philo struct kurulumu
  ├── ft_simulation()  → Thread'leri başlatır, monitor thread'i oluşturur, join eder
  └── ft_cleanup()     → Mutex destroy, free

Her Philo Thread (ft_routine):
  └── while(alive): ft_eat() → ft_sleep() → ft_think()

Monitor Thread (ft_monitor):
  └── while(alive): ft_death() → ft_meals() → usleep(500)
```

### 🎨 **Renkli Çıktı**

| Durum | Renk | Mesaj |
|-------|------|-------|
| `has taken a fork` | 🟢 Yeşil | Çatal aldı |
| `is eating` | 🔵 Mavi | Yemek yiyor |
| `is sleeping` | 🟣 Mor | Uyuyor |
| `is thinking` | ⚫ Gri | Düşünüyor |
| `died` | 🔴 Kırmızı | Öldü |
| `All philosophers have eaten enough` | ⚪ Beyaz | Simülasyon tamamlandı |

---

## 📁 Dosya Yapısı

```
philo/
├── 📄 Makefile          # -Wall -Wextra -Werror -pthread
├── 📋 philo.h           # Tüm struct tanımları, enum ve fonksiyon prototipleri
├── 🎯 main.c            # Entry point, ft_simulation, ft_cleanup
├── ⚙️  init.c            # ft_init: parse, malloc, mutex init, philo kurulumu
├── 🔄 routine.c         # ft_routine: eat / sleep / think döngüsü, deadlock önleme
├── 👁️  monitor.c         # ft_monitor: ölüm kontrolü, yemek sayısı kontrolü
├── ✍️  write.c           # ft_write: renkli, mutex korumalı log çıktısı
├── 🛠️  utils.c           # ft_gettime, ft_usleep, ft_error
├── 🔢 atoi.c            # ft_atoi: overflow korumalı integer parse
└── 📚 libft.c           # ft_putstr_fd, ft_putnbr_fd, ft_memset
```

### 📊 **Dosya Açıklamaları**

| Dosya | İçerik | Sorumluluk |
|-------|--------|------------|
| `philo.h` | `t_data`, `t_philo`, `t_args`, `t_mtx`, `t_msg` | Tüm tip tanımları |
| `main.c` | `ft_simulation`, `ft_cleanup`, `main` | Thread yönetimi |
| `init.c` | `ft_parser`, `ft_malloc`, `ft_mutex`, `ft_philos`, `ft_init` | Başlatma |
| `routine.c` | `ft_eat`, `ft_sleep`, `ft_think`, `ft_run`, `ft_routine` | Filozof döngüsü |
| `monitor.c` | `ft_check`, `ft_death`, `ft_meals`, `ft_monitor` | Simülasyon takibi |
| `write.c` | `ft_write`, `ft_build`, `ft_buf` | Thread-safe çıktı |
| `utils.c` | `ft_gettime`, `ft_usleep`, `ft_error` | Yardımcılar |
| `atoi.c` | `ft_atoi` | Güvenli sayı parse |
| `libft.c` | `ft_putstr_fd`, `ft_putnbr_fd`, `ft_memset` | Temel yardımcılar |

---

## 🎁 Bonus Kısmı

<div align="center">

![Processes](https://img.shields.io/badge/Processes-fork()-gold?style=for-the-badge)
![Semaphores](https://img.shields.io/badge/Semaphores-POSIX-purple?style=for-the-badge)

</div>

Bonus versiyonu her filozofu ayrı bir **child process** olarak çalıştırır. Mutex yerine **POSIX semaforları** (`sem_open`, `sem_wait`, `sem_post`) kullanılır.

### 🔀 **Mandatory vs Bonus Farkları**

| Özellik | Mandatory (`philo/`) | Bonus (`philo_bonus/`) |
|---------|---------------------|----------------------|
| **Eş zamanlılık** | POSIX thread (`pthread`) | Process (`fork`) |
| **Senkronizasyon** | `pthread_mutex_t` | `sem_t` (POSIX semaphore) |
| **Çatal havuzu** | Her filozofun iki mutex pointer'ı | Tek global `/philo_forks` semafor |
| **Monitor** | Tek monitor thread | Her child içinde detached thread |
| **Ölüm bildirimi** | `data->alive` flag | `exit(1)` → parent `waitpid` |
| **Yemek takibi** | `time_eat` + `mtx.meal` | `t_local.time_eat` + per-process `lock` semafor |
| **Bölünmüş durum** | Paylaşılan `t_data` struct | `t_local` per-process yerel durum |

```
philo_bonus/
├── 📄 Makefile
├── 📋 philo_bonus.h      # t_data, t_philo, t_local, t_sem, t_args
├── 🎯 main_bonus.c       # main, ft_parser
├── ⚙️  init_bonus.c       # ft_semaphores, ft_philos, ft_processes, ft_init
├── 👶 child_bonus.c      # ft_child: process içi döngü ve monitor başlatma
├── 🔄 routine_bonus.c    # ft_eat, ft_sleep_think, ft_meal, ft_forks
├── 👁️  monitor_bonus.c    # ft_monitor (child thread), ft_parent (parent wait)
├── ✍️  write_bonus.c      # ft_write: semaphore korumalı çıktı
├── 🛠️  utils_bonus.c      # ft_gettime, ft_usleep, ft_cleanup, ft_error
├── 🔢 atoi_bonus.c       # ft_atoi
└── 📚 libft_bonus.c      # ft_putstr_fd, ft_memset, ft_itoa, ft_strcat
```

### 🧵 **Bonus'ta Monitor Mimarisi**

```
Parent Process
  └── waitpid(-1) → her child'ı bekler
        ├── exit(1)  → bir filozof öldü → diğerlerini SIGTERM ile öldür
        ├── exit(0)  → yemek limitine ulaştı
        └── Tüm child'lar exit(0) → simülasyon normal bitti

Her Child Process
  └── detached monitor thread → usleep(500) → last_eat kontrolü
        └── elapsed >= time_to_die → ft_write(DIED) → exit(1)
```

---

## 🚀 Kurulum

### 📋 **Ön Gereksinimler**

![GCC](https://img.shields.io/badge/GCC-Required-red?style=flat-square&logo=gnu&logoColor=white)
![Make](https://img.shields.io/badge/Make-Required-blue?style=flat-square&logo=gnu&logoColor=white)
![Unix](https://img.shields.io/badge/Unix-Compatible-green?style=flat-square&logo=linux&logoColor=white)

- **C Compiler**: `cc` (gcc veya clang)
- **Unix-like System**: Linux, macOS, WSL
- **POSIX Thread Support**: `-pthread` flag (mandatory)

### 📥 **Repository Klonlama**

```bash
git clone https://github.com/skarayil/philosophers.git
cd philosophers
```

### 🔨 **Derleme İşlemi**

```bash
# Mandatory versiyonu derle
cd philo && make

# Bonus versiyonu derle
cd philo_bonus && make

# Temizlik
make clean          # Object dosyalarını sil
make fclean         # Executable dahil tüm çıktıları sil
make re             # Yeniden derle
```

### 📦 **Çıktı Dosyaları**

```bash
philo/philo              # Mandatory executable
philo_bonus/philo_bonus  # Bonus executable
```

---

## 💻 Kullanım

### 🖥️ **Sözdizimi**

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat]
```

| Argüman | Tür | Açıklama |
|---------|-----|----------|
| `number_of_philosophers` | int > 0 | Filozofların ve çatalların sayısı |
| `time_to_die` | int > 0 | Yemekten bu kadar ms sonra ölüm (ms) |
| `time_to_eat` | int > 0 | Yeme süresi (ms) |
| `time_to_sleep` | int > 0 | Uyku süresi (ms) |
| `[must_eat]` | int > 0 *(opsiyonel)* | Herkes bu kadar yerse simülasyon biter |

### 📝 **Kullanım Örnekleri**

#### 🟢 **Temel Testler**

```bash
# 5 filozof, kimse ölmemeli
./philo 5 800 200 200

# Tek filozof → çatal eksik, ölmeli
./philo 1 800 200 200
# Beklenen çıktı: 0 800 1 died

# 4 filozof, kimse ölmemeli
./philo 4 410 200 200

# 4 filozof, 7 kez yedikten sonra durmalı
./philo 4 410 200 200 7

# Ölüm testi: çok kısa süre
./philo 4 310 200 100
# Beklenen: bir filozof ölür
```

#### 🟡 **Stres Testleri**

```bash
# Çok sayıda filozof
./philo 200 800 200 200

# Sınırda zamanlama
./philo 5 610 200 200

# Must-eat ile erken durdurma
./philo 5 800 200 200 5
```

#### 🟣 **Bonus Versiyonu**

```bash
cd philo_bonus

# Aynı argümanlarla çalışır
./philo_bonus 5 800 200 200
./philo_bonus 4 410 200 200 7
./philo_bonus 1 800 200 200
```

### 🎨 **Örnek Çıktı**

```
[0] 1 has taken a fork
[0] 2 has taken a fork
[1] 1 has taken a fork
[1] 2 has taken a fork
[1] 1 is eating
[1] 2 is eating
[201] 1 is sleeping
[201] 2 is sleeping
[401] 1 is thinking
[401] 2 is thinking
```

*(Renkli terminalde her satır farklı renkte görünür)*

---

## 🛠️ Teknik Detaylar

### 🏗️ **Veri Yapıları**

```c
typedef struct s_data {
    bool        alive;     // Simülasyon devam ediyor mu?
    long        start;     // Başlangıç zamanı (ms)
    t_args      args;      // Argümanlar
    t_mtx       mtx;       // Tüm mutex'ler
    t_philo     *philos;   // Filozof dizisi
} t_data;

typedef struct s_philo {
    int             id;
    int             time_eat;    // Kaç kez yedi
    long            last_eat;    // Son yemek zamanı (ms)
    pthread_t       thread;
    pthread_mutex_t *port;       // Sol çatal (küçük adres)
    pthread_mutex_t *star;       // Sağ çatal (büyük adres)
    t_data          *data;
} t_philo;

typedef struct s_mtx {
    pthread_mutex_t *forks;   // Çatal mutex dizisi
    pthread_mutex_t  write;   // Çıktı kilidi
    pthread_mutex_t  dead;    // alive flag kilidi
    pthread_mutex_t  meal;    // last_eat / time_eat kilidi
} t_mtx;
```

### 🔒 **Deadlock Önleme**

Filozofların aynı anda aynı çatala erişmesini engellemek için **adres sıralaması** kullanılır:

```c
// routine.c - ft_run()
if (philo->port < philo->star) {
    f1 = philo->port;   // Küçük adresli çatalı önce al
    f2 = philo->star;
} else {
    f1 = philo->star;   // Küçük adresli çatalı önce al
    f2 = philo->port;
}
```

Bu teknik, her filozofun çatalları **tutarlı bir sırada** kilitlemesini sağlayarak döngüsel beklemeyi (circular wait) önler.

### ⚡ **ft_usleep — Hassas Bekleme**

Standart `usleep` OS scheduling nedeniyle geç uyanabilir. Bu proje, `gettimeofday` ile sürekli kontrol eden ve aynı zamanda simülasyon durumunu izleyen özel bir bekleme fonksiyonu kullanır:

```c
bool ft_usleep(long ms, t_data *data) {
    long start = ft_gettime();
    while ((ft_gettime() - start) < ms) {
        pthread_mutex_lock(&data->mtx.dead);
        if (!data->alive) {
            pthread_mutex_unlock(&data->mtx.dead);
            return (false);   // Simülasyon bitti, erken çık
        }
        pthread_mutex_unlock(&data->mtx.dead);
        usleep(philos < 50 ? 100 : 500);
    }
    return (true);
}
```

### 🦠 **Tek Filozof Özel Durumu**

Tek filozof varken iki çatal hiçbir zaman mevcut olmayacak. Bu durum ayrı yönetilir:

```c
// routine.c - ft_routine()
if (philo->data->args.philos == 1) {
    pthread_mutex_lock(philo->port);
    ft_write(philo, MSG_TAKE_FORK);
    ft_usleep(philo->data->args.die, philo->data);
    pthread_mutex_unlock(philo->port);
    return (NULL);  // Ölüm monitor tarafından tespit edilecek
}
```

### 🧮 **Tek Sayılı Filozoflar için Thinking Gecikmesi**

Çift sayılı filozoflarda başlangıç gecikmesi (`eat / 2`) ve tek sayılı filozoflarda thinking sırasında ek bekleme ile kaynak çakışması minimize edilir:

```c
// routine.c - ft_think()
if (philo->data->args.philos % 2 != 0) {
    time = (philo->data->args.eat * 2) - philo->data->args.sleep;
    if (time > 0)
        return ft_usleep(time, philo->data);
}
```

### ✍️ **Thread-Safe Çıktı (write.c)**

Tüm log satırları `write` mutex ve `dead` mutex aynı anda kilitli şekilde yazılır; böylece simülasyon bittikten sonra mesaj çıkması engellenir:

```c
void ft_write(t_philo *philo, t_msg msg) {
    pthread_mutex_lock(&philo->data->mtx.write);
    pthread_mutex_lock(&philo->data->mtx.dead);
    if (philo->data->alive == false && msg != MSG_DIED) {
        // Simülasyon bittiyse yalnızca MSG_DIED geçebilir
        pthread_mutex_unlock(&philo->data->mtx.dead);
        pthread_mutex_unlock(&philo->data->mtx.write);
        return;
    }
    // ... çıktı yaz ...
    if (msg == MSG_DIED)
        philo->data->alive = false;
    pthread_mutex_unlock(&philo->data->mtx.dead);
    pthread_mutex_unlock(&philo->data->mtx.write);
}
```

---

## 🧪 Test Senaryoları

### ✅ **Standart Doğrulama Testleri**

```bash
# Kimse ölmemeli:
./philo 1 800 200 200    → Ölmeli
./philo 5 800 200 200    → Kimse ölmemeli
./philo 5 800 200 200 7  → 7 yemekten sonra durmalı
./philo 4 410 200 200    → Kimse ölmemeli
./philo 4 310 200 100    → Ölüm olmalı

# Sınır değerleri:
./philo 2 400 200 200    → Kimse ölmemeli
./philo 200 800 200 200  → Kimse ölmemeli
```

### ⚠️ **Hata Durumu Testleri**

```bash
# Eksik / fazla argüman
./philo                          # Error: kullanım mesajı
./philo 5 800 200                # Error
./philo 5 800 200 200 7 extra    # Error

# Geçersiz değerler
./philo 0 800 200 200            # Error: sıfır filozof
./philo 5 -100 200 200           # Error: negatif değer
./philo 5 800 0 200              # Error: sıfır yeme süresi
./philo abc 800 200 200          # Error: sayısal olmayan giriş
```

### 🔍 **Race Condition ve Deadlock Testi**

```bash
# Valgrind ile helgrind (thread hata tespiti)
valgrind --tool=helgrind ./philo 4 410 200 200

# Bellek sızıntısı kontrolü
valgrind --leak-check=full ./philo 4 410 200 200 5

# Uzun süreli stabilite
./philo 5 800 200 200 &
sleep 30 && kill %1
```

---

## 📚 Notlar

### ⚠️ **Dikkat Edilmesi Gerekenler**

#### 🔒 **Mutex Kilitleme Sırası**
- `write` → `dead` sırasıyla kilitlenmelidir; ters sıra deadlock'a yol açar
- `meal` mutex'i yalnızca `last_eat` ve `time_eat` alanları için kullanılır
- `dead` mutex'i `alive` flag okuma/yazma işlemlerini korur

#### ⏱️ **Zamanlama Hassasiyeti**
- `ft_gettime()` hata durumunda `1` döndürür; bu değer doğrudan fark hesabında kullanıldığından gerçek bir sorun oluşturmaz
- Büyük simülasyonlarda (`philos >= 50`) bekleme aralığı `500 µs`'ye çıkarılır, küçük simülasyonlarda `100 µs` kullanılır

#### 🧹 **Kaynak Temizleme**
- `ft_cleanup()` mutex'lerin yok edilmesinden önce tüm thread'lerin join edilmesini bekler
- Bonus'ta `ft_cleanup()` semafor close + unlink çiftini çalıştırır; SEM_FAILED kontrolü yapılır

#### 📦 **Bonus Semafor İsimlendirmesi**
- Per-process yemek kilidi: `/meal_lock_<pid>_<id>` formatında oluşturulur ve hemen `sem_unlink` ile kaldırılır; böylece isim çakışması önlenir

### 💡 **Best Practices**

1. Her sistem çağrısının dönüş değerini kontrol et (`pthread_create`, `pthread_mutex_init`, `sem_open`)
2. Hata yollarında da bellek ve mutex'leri temizle
3. Çıktı fonksiyonunu başka bir mutex içinde çağırma (iç içe kilit = deadlock riski)
4. `gettimeofday` tabanlı döngü beklemeyi simülasyon durumu kontrolüyle birleştir

---

## 🏆 Proje Başarıları

<div align="center">

![Score](https://img.shields.io/badge/Score-125%2F100-gold?style=for-the-badge)
![Tests](https://img.shields.io/badge/Tests-All%20Passed-success?style=for-the-badge)
![Norminette](https://img.shields.io/badge/Norminette-OK-brightgreen?style=for-the-badge)
![Bonus](https://img.shields.io/badge/Bonus-Completed-orange?style=for-the-badge)

### 📊 **Proje İstatistikleri**

| Metrik | Mandatory | Bonus |
|--------|-----------|-------|
| **Kaynak Dosya** | 9 | 9 |
| **Toplam Fonksiyon** | 25+ | 25+ |
| **Senkronizasyon Primitifi** | pthread mutex | POSIX semaphore |
| **Eş zamanlılık Birimi** | Thread | Process |
| **Bellek Sızıntısı** | ✅ Valgrind Temiz | ✅ Valgrind Temiz |
| **Deadlock** | ✅ Yok | ✅ Yok |

</div>

---

<div align="center">

### 🎯 **Kazanılan Temel Beceriler**

![Concurrency](https://img.shields.io/badge/Concurrency-blue?style=flat-square)
![Mutex](https://img.shields.io/badge/Mutex%20Locks-green?style=flat-square)
![Semaphores](https://img.shields.io/badge/Semaphores-orange?style=flat-square)
![Deadlock Prevention](https://img.shields.io/badge/Deadlock%20Prevention-red?style=flat-square)
![IPC](https://img.shields.io/badge/IPC-purple?style=flat-square)

---

**🍝 "Philosophers teaches you that sharing resources gracefully is harder than it looks — but elegant synchronization makes it possible."**

*Bu proje, eş zamanlı programlamanın temel zorluklarını ve bunlara zarif çözümler üretmeyi öğretir.*

---

### 👩‍💻 Created by Sude Naz Karayıldırım

[![42 Profile](https://img.shields.io/badge/42%20Profile-skarayil-black?style=flat-square&logo=42&logoColor=white)](https://profile.intra.42.fr/users/skarayil)
[![GitHub](https://img.shields.io/badge/GitHub-skarayil-181717?style=flat-square&logo=github&logoColor=white)](https://github.com/skarayil)

**⭐ Eğer bu proje işinize yaradıysa, repo'ya star vermeyi unutmayın!**

</div>
