#include "language.h"

/*
	The languages are in the followings order:
	0. English
	1. French
	2. Polish
	3. German
	4. Dutch
	5. Spanish
	6. Portuguese
	7. Brazilian Portuguese
	8. Norwegian
	9. Romanian 
	10. Italian
	11.Simplified Chinese
	12.Traditional Chinese
*/

const char lang_welcome[][4][100] = 
{	
	{"Welcome", "Use the analog stick to navigate the cursor and", "press A to open the application.", "GOT IT"},
	{"Bienvenue", "Utilisez le stick analogique pour déplacer le curseur et", "pressez le bouton X (croix) pour ouvrir l'application.", "OK"},
	{"Witamy", "Uzyj analoga by poruszać kursorem", "i przycisnij X by otworzyc aplikacje.", "Zrozumialem"},
	{"Willkommen", "Benutze den Analog-Stick um den Cursor zu navigieren \nund", "\n\ndrücke X (Kreuz) um die Anwendung zu öffnen.", "OK"},
	{"Welkom", "Gebruik de joystick om de aanwijzer te bewegen en", "druk X (kruisje) om de toepassing te openen.", "GOT IT"},
	{"Bienvenido", "Use el stick análogo para navegar con el cursor y", "presione X para abrir la aplicación", "ENTENDIDO"},
	{"Bem vindo", "Use o analogico para navegar o cursor e", "pressione X para abrir a aplicação", "ENTENDIDO"},
	{"Bem-vindo(a)", "Use a manete analógica para mover o cursor e", "aperte X para abrir a aplicação.", "ENTENDIDO"},
	{"Velkommen", "Bruk den analoge spaken for å flytte på pekeren og", "trykk X (kryss) for å åpne applikasjonen.", "SKJØNNER"},
	{"Bine ai venit", "Folosește joystickul pentru a naviga și", "apasă X pentru a deschide o aplicație", "AM ÎNȚELES"},
	{"Benvenuto", "Usa lo stick analogico per muovere il cursore e", "premi X (croce) per aprire l'applicazione.", "HO CAPITO"},
	{"欢迎", "使用摇杆以移动光标", "按X打开应用程序。", "知道了"},
	{"歡迎", "使用搖杆以移動光標", "按X打開應用程式。", "知道了"},
};


const char lang_appDrawer[][8][100] = 
{	
	{"Browser", "Clock", "Manager", "Gallery", "Game", "Messages", "Music", "Settings"},
	{"Navigateur", "Horloge", "Explorateur", "Galerie", "Jeux", "Messages", "Musique", "Configurations"},
	{"Internet", "Zegar", "Pliki", "Galeria", "Gry", "Wiadomosci", "Muzyka", "Ustawienia"},
	{"Browser", "Uhr", "Manager", "Galerie", "Spiel", "Nachrichten", "Musik", "Einstellungen"},
	{"Browser", "Klok", " Beheerder", "Gallerij", "Spel", "Berichten", "Muziek", "Instellingen"},
	{"Navegador", "Reloj", "Gestión", "Galería", "Juegos", "Mensajes", "Música", "Ajustes"},
	{"Navegador", "Relógio", "Gerenciador", "Galeria", "Jogo", "Mensagens", "Música", "Opções"},
	{"Navegador", "Relógio", "Gerenciador", "Galeria", "Jogo", "Mensagens", "Música", "Definições"},
	{"Nettleser", "Klokke", "Filbehandler", "Galleri", "Spill", "Meldinger", "Musikk", "Instillinger"},
	{"Internet", "Ceas", "Fișiere", "Galerie", "Joc", "Mesaje", "Muzică", "Setări"},
	{"Browser", "Orologio", "Manager", "Galleria", "Giochi", "Messaggi", "Musica", "Impostazioni"},
	{"浏览器", "时间", "文件", "图库", "游戏", "消息", "音乐", "设置"},
	{"瀏覽器", "時間", "文件", "圖庫", "遊戲", "消息", "音樂", "設置"}
};

const char lang_settingsMain[][6][100] = 
{	
	{"Wi-Fi", "Security", "Display", "Performance", "Developer Options", "About"},
	{"Wi-Fi", "Sécurité", "Affichage", "Performance", "Options de développeur", "À propos"},
	{"Wi-Fi", "Zabezpieczenia", "Wyswietlacz", "Wydajnosc", "Opcje developerskie", "O programie"},
	{"Wi-Fi", "Sicherheit", "Bildschirm", "Leistung", "Entwickler Optionen", "Über"},
	{"Wi-Fi", "Beveiliging", "Scherm", "Prestaties", "Opties voor ontwikkelaars", "Over"},
	{"Wi-Fi", "Seguridad", "Pantalla", "Rendimiento", "Opciones de Desarrollador", "Acerca de"},
	{"Wi-Fi", "Segurança", "Tela", "Desempenho", "Opções de desenvolvedor", "Sobre"},
	{"Wi-Fi", "Segurança", "Exibição", "Desempenho", "Opções de Desenvolvedor", "Sobre"},
	{"Wi-Fi", "Sikkerhet", "Skjerm", "Ytelse", "Utviklervalg", "Om"},
	{"Wi-Fi", "Securitate", "Ecran", "Performanță", "Opțiuni dezvoltator", "Despre consolă"},
	{"Wi-Fi", "Sicurezza", "Display", "Performance", "Opzione sviluppatore", "Informazioni"},
	{"Wi-Fi", "安全", "显示", "性能", "开发者选项", "关于"},
	{"Wi-Fi", "安全", "顯示", "性能", "開發者選項", "關於"}
};

const char lang_settingsDisplay[][4][100] = 
{	
	{"Themes", "Time", "Language", "Miscellaneous"},
	{"Thèmes", "Heure", "Langue", "Divers"},
	{"Motywy", "Czas", "Jezyk", "Rózne"},
	{"Themen", "Uhrzeit", "Sprache", "Allgemein"},
	{"Thema's", "Tijd", "Taal", "Diversen"},
	{"Temas", "Tiempo", "Idioma", "Miscelaneo"},
	{"Temas", "Tempo", "Idioma", "Variados"},
	{"Temas", "Horário", "Idioma", "Miscelâneas"},
	{"Temaer", "Tid", "språk", "Diverse"},
	{"Teme", "Ceas", "Limbă", "Diverse"},
	{"Temi", "Ora", "lingua", "Varie"},
	{"主题", "时间", "语言", "其他"},
	{"主題", "時間", "語言", "其他"}
};

const char lang_settingsThemes[][4][100] = 
{	
	{"Style", "Wallpaper", "Fonts", "Icon Packs"},
	{"Style", "Fond d'écran", "Polices", "Pack d'icones"},
	{"Wyglad", "Tapeta", "Czcionki", "Paczki ikon"},
	{"Designs", "Hintergründe", "Schriftarten", "Symbole"},
	{"Stijl", "Achtergrond", "Lettertypes", "Pictogrammen"},
	{"Estilo", "Fondo de Pantalla", "Fuentes", "Paquete de Iconos"},
	{"Estilo", "Papel de parede", "Fontes", "Pacotes de ícones"},
	{"Estilo", "Papel de Parede", "Fontes", "Pacotes de Ícones"},
	{"Stil", "Bakgrunnsbilde", "Skrifter", "Ikon-pakker"},
	{"Stil", "Fundal", "Fonturi", "Pachete de pictograme"},
	{"Stile", "Sfondo", "Fonts", "Pacchetti di icone"},
	{"风格", "壁纸", "字体", "图标"},
	{"風格", "壁紙", "字體", "圖標"}
};

const char lang_settingsTime[][1][100] = 
{	
	{"Use 24-hour format"},
	{"Utiliser le format 24 heures"},
	{"Uzyj czasu 24-godzinnego"},
	{"24-Stunden format nutzen"},
	{"24-uurs klok gebruiken "},
	{"Usar formato de 24 horas"},
	{"Usar formato de 24 horas"},
	{"Usar formato 24 horas"},
	{"Bruk 24-timers format"},
	{"Folosește formatul de 24 de ore"},
	{"Usa il formato 24 ore"},
	{"使用24小时制"},
	{"使用24小時制"}
};

const char lang_settingsMiscellaneous[][4][100] =
{	
	{"Toggle day/night widget", "Toggle expanded desktop", "Toggle boot animation", "Toggle game boot"},
	{"Basculer entre le widget jour/nuit", "Activer/Désactiver le bureau étendu", "Activer/Désactiver l'animation de démarrage", "Activer/Désactiver le l'animation de démarrage de jeu"},
	{"Uzyj widgetu dzien/noc", "Uzyj pulpitu rozszerzonego", "Uzyj animacji bootowania", "Animacja przy uruchamianiu gry"},
	{"Tag/Nacht-Widget ein-/ausschalten", "Erweiterten Desktop ein-/ausschalten", "Startanimation ein-/ausschalten", "Spielstart ein-/ausschalten"},
	{"Schakel tussen dag/nacht widget", "Uitgebreide desktop aan/uit", "Opstart animatie aan/uit", "Game boot aan/uit"},
	{"Usar widget de día/noche", "Usar escritorio expandido","Activar animación de inicio", "Activar inicio del juego"},
	{"Alternar widget dia/noite", "Alternar area de trabalho expandida", "Alternar animação de boot", "Alternar animação de boot de jogo"},
	{"Alternar widget de dia/noite", "Alternar área de trabalho expandida", "Alternar animação de boot", "Alternar boot de jogo"},
	{"Veksle dag/natt modul", "Veksle utvidet skrivebord", "Veklse oppstarts-animasjon", "Veksle spill-oppstart"},
	{"Activează widgetul de zi/noapte", "Activează desktop extins", "Activează animația de pornire", "Activează pornirea în joc"},
	{"Attiva il widget giorno/notte", "Attiva il desktop espanso", "Attiva animazione di avvio", "Attiva il boot del gioco"},
	{"亮度调整", "切换桌面扩展", "切换开机动画", "切换游戏引导"},
	{"亮度調整", "切換桌面擴展", "切換開機動畫", "切換遊戲引導"}
};

const char lang_settingsPerformance[][4][100] = 
{	
	{"Processor", "Memory", "Storage Management", "Battery Management"},
	{"Procceseur", "Memoire vive", "Gestion du stockage", "Gestion de la batterie"},
	{"Procesor", "Pamiec", "Zarzadzanie pamiecia", "Zarzadzanie bateria"},
	{"Prozessor", "Arbeitsspeicher", "Speicherverwaltung", "Akku"},
	{"Processor", "Geheugen", "Opslag Beheer", "Accu Beheer"},
	{"Procesador", "Memoria", "Gestión de Almacenamiento", "Gestión de la Batería"},
	{"Processador", "Memoria", "Armazenamento", "Bateria"},
	{"Processador", "Memória", "Gestão de Armazenamento", "Gestão de Bateria"},
	{"Prosessor", "Minne", "Administrer lagring", "Administrer batteri"},
	{"Procesor", "Memorie", "Gestionarea memoriei", "Gestionarea bateriei"},
	{"Processore", "Memoria", "Gestione dello spazio", "Gestione della batteria"},
	{"处理器", "储存", "存储管理", "电池管理"},
	{"處理器", "儲存", "存儲管理", "電池管理"}
};

const char lang_settingsProcessor[][5][100] = 
{	
	{"Current CPU frequency", "CPU over-clock", "Press R to increase frequency and L to decrease frequency.", "Current BUS frequency"},
	{"Fréquence processeur actuelle", "Surcadencement du processeur", "Pressez la touche R pour augmenter la fréquence, et L pour la diminuer.", "Fréquence BUS actuelle"},
	{"Czestotliwosc CPU", "Podkrecanie CPU", "Nacisnij R by zwiekszyc, a L by zmniejszyc czestotliwosc", "Czestotliwosc magistarli"},
	{"Derzeitige CPU frequenz", "CPU übertakten", "Drücke R um die Frequenz zu erhöhen und L um die Frequenz zu senken.", "Derzeitige BUS frequenz"},
	{"Huidige CPU kloksnelheid", "CPU overclock", "Druk R om de kloksnelheid te verhogen en L om het te verlagen.", "Huidige BUS snelheid"},
	{"Frecuencia actual de la CPU", "Over-clock de CPU", "Presione R para aumentar la frecuencia y L para disminuir la frecuencia", "Frecuencia actual de BUS"},
	{"Frenquencia atual da CPU", "Overclock da CPU", "Pressione R para aumentar a frequencia e L para diminui-la.", "Frequencia atual de BUS"},
	{"Atual frequência da CPU", "Overclock da CPU", "Aperte R para aumentar a frequência e L para diminuí-la.", "Atual frequência do BUS"},
	{"Nåværende CPU-frekvens", "CPU over-klokking", "Trykk R for å øke frekvensen og L for å senke frekvensen.", "Nåværende bussfrekvens"},
	{"Frecvența actuală a CPU", "Creșterea frecvenței CPU", "Apasă R pentru a crește frecvența și L pentru a descrește frecvența.", "Frecvența actuală a BUS"},
	{"Frequenza CPU attuale", "Over-clock CPU", "Premi R per incrementare la frequenza e L per diminuire la frequenza.", "Frequenza attuale BUS"},
	{"目前的CPU频率", "CPU超频", "按R键以提高频率，按L以降低频率", "CPU总线频率"},
	{"目前的CPU頻率", "CPU超頻", "按R鍵以提高頻率，按L以降低頻率", "CPU總線頻率"}
};

const char lang_settingsRAM[][3][100] = 
{	
	{"RAM available:", "available", "of RAM used"},
	{"RAM disponible :", "disponibles", "de la RAM utilisée"},
	{"Dotepny RAM:", "wolne", "RAM-u uzyte"},
	{"RAM verfügbar:", "verfügbar", "des RAMs genutzt"},
	{"RAM vrij:", "beschikbaar", "RAM in gebruik"},
	{"Memoria RAM disponible:", "disponible", "de la memoria RAM utilizada"},
	{"RAM disponível:", "disponível", "de RAM usada"},
	{"RAM disponível:", "disponíveis", "de RAM usada"},
	{"Tilgjengelig RAM:", "tilgjengelig", "av RAM brukt"},
	{"RAM disponibil:", "disponibil", "de RAM utilizat"},
	{"RAM disponibile:", "disponibile", "di RAM usata"},
	{"可用内存：", "可用的", "正使用"},
	{"可用記憶體：", "可用的", "正使用"}
};

const char lang_settingsStorage[][3][100] = 
{	
	{"Press select to toggle USB mass storage", "Total storage capacity:", "Available storage capacity:"},
	{"Appuyez sur Select pour activer/désactiver le mode clé USB", "Capacité de stockage totale :", "Capacité de stockage disponible :"},
	{"Nacisnij Select by podlaczyc pamiec USB", "Calkowita ilosc pamieci", "Wolna pamiec"},
	{"Drücke Select, um den USB-Speicher ein-/auszuschalten", "Gesamptspeicher kapazität:", "Verfügbar:"},
	{"Druk select om van massaopslag te wisselen", "Totale opslagruimte:", "Beschikbaare opslagruimte:"},
	{"Presione Select para activar el Almacenamiento Masivo USB", "Capacidad de almacenamiento total:", "Capacidad de almacenamiento disponible:"},
	{"Pressione Select para alternar o armazenamento em massa USB", "Capacidade de armazenamento total:", "Capacidade de armazenamento disponível:"},
	{"Aperte select para alternar o dispositivo de armazenmanento USB", "Capacidade total de armazenamento:", "Capacidade de armazenamento disponível:"},
	{"Trykk select for å veksle USB masselagring", "Total lagringskapasitet:", "Tilgjengelig lagringskapasitet:"},
	{"Apasă SELECT pentru a activa stocarea USB", "Capacitate de stocare totală:", "Capacitate de stocare disponibilă:"},
	{"Premi select per attivare memoria di massa USB", "Capacità totale della memoria:", "Capacità di archiviazione disponibile"},
	{"按Select切换USB大容量存储", "总容量：", "可用的存储容量："},
	{"按Select切換USB大容量存儲", "總容量：", "可用的存儲容量："}
};

const char lang_settingsBattery[][3][60] = 
{	
	{"Powersave", "Balanced", "Performance"},
	{"Economie d'énergie", "Equilibré", "Hautes performances"},
	{"Oszczedzanie baterii", "Zbalansowane", "Wydajnosc"},
	{"Energiesparmodus", "Balanced", "Leistung"},
	{"Accubesparing", "Gebalanceerd", "Prestatie"},
	{"Ahorro de Energía", "Balanceado", "Alto Rendimiento"},
	{"Powersave", "Balanciado", "Desempenho"},
	{"Econômico", "Equilibrado", "Desempenhado"},
	{"Strømsparing", "Balansert", "Ytelse"},
	{"Economisire", "Echilibrat", "Performanță"},
	{"Risparmio energetico", "Bilanciato", "Prestazioni"},
	{"节电", "平衡", "性能"},
	{"節電", "平衡", "性能"}
};

const char lang_settingsAbout[][6][100] = 
{	
	{"Cyanogen3DS updates", "Click for, view or install available updates", "Cyanogen3DS version:", "OFFICIAL", "Mac Address:", "Kernel version:"},
	{"Mises à jour de Cyanogen3DS", "Cliquez pour voir et installer les mises à jour disponibles", "Version Cyanogen3DS :", "OFFICIEL", "Adresse MAC :", "Version du noyau :"},
	{"Aktualizacje Cyanogen3DS", "Nacisnij aby sprawdzic/zainstalowac aktualizacje", "Wersja Cyanogen3DS:", "OFFICIAL", "Adres Mac:", "Wersja jadra:"},
	{"Cyanogen3DS updates", "Click for, view or install available updates", "Cyanogen3DS version:", "OFFIZIELL", "Mac Adresse:", "Kernel version:"},
	{"Cyanogen3DS updates", "Klik om updates weer te geven/installeren", "Cyanogen3DS versie:", "OFFICIEEL", "Mac Adres:", "Kernel versie:"},
	{"Actualizaciones de Cyanogen3DS", "Haga click para ver o instalar actualizaciones", "Versión de Cyanogen3DS:", "OFICIAL", "Dirección MAC:", "Versión del Kernel:"},
	{"Atualizações Cyanogen3DS", "Clique para, ver ou instalar atualizações disponiveis", "versão Cyanogen3DS:", "OFICIAL", "Endereço MAC:", "Versão do kernel:"},
	{"Atualizações do Cyanogen3DS", "Clique para, ver ou instalar atualizações disponíveis", "Versão do Cyanogen3DS:", "OFICIAL", "Endereço Mac:", "Versão do Kernel:"},
	{"Cyanogen3DS oppdateringer", "Trykk for, vis eller installer tilgjengelige oppdateringer", "Cyanogen3DS versjon:", "OFFISIELL", "Mac Adresse:", "Kernel versjon:"},
	{"Actualizări Cyanogen3DS", "Apasă pentru a vedea și instala actualizări disponibile", "Versiune Cyanogen3DS:", "OFICIAL", "Adresă Mac:", "Versiune de kernel:"},
	{"Aggiornamenti Cyanogen3DS", "Clicca per, vedere o installare gli aggiornamenti disponibili", "Versione Cyanogen3DS:", "UFFICIALE", "Indirizzo MAC:", "Versione kernel:"},
	{"Cyanogen3DS 更新", "点击以查看或安装可用更新", "Cyanogen3DS 版本:", "正式版", "MAC地址:", "内核版本:"},
	{"Cyanogen3DS 更新", "點擊以查看或安裝可用更新", "Cyanogen3DS 版本:", "正式版"," MAC地址:", "内核版本:"}
};

const char lang_settingsUpdates[][1][100] = 
{	
	{"Check for updates"},
	{"Vérifier la présence de mises à jour"},
	{"Sprawdz aktualizacje"},
	{"Auf Updates prüfen"},
	{"Updates zoeken"},
	{"Buscar actualizaciones"},
	{"Procurar por atualizações"},
	{"Checar por atualizações"},
	{"Se etter oppdateringer"},
	{"Caută actualizări"},
	{"Ricerca aggiornamenti"},
	{"Проверить обновления"},
	{"Перевірити оновлення"},
	{"检查更新"},
	{"檢查更新"}
};

const char lang_settingsSecuirty[][3][100] = 
{	
	{"Password lock", "Pin lock", "Swipe"},
	{"Verrouillage par mot de passe", "Verrouillage par code PIN", "Chiper"},
	{"Haslo", "Kod PIN", "Przesuniecie"},
	{"Passwortsperre", "Pinsperre", "Stibitzen"},
	{"Wachtwoord vergrendeling", "PIN vergrendeling", "Slaan"},
	{"Bloqueo con contraseña", "Bloqueo con PIN", "Apandar"},
	{"Trava por senha", "Trava por PIN", "Pancada forte"},
	{"Trava de senha", "Trava de pino", "Pancada forte"},
	{"Passordlås", "Pin-lås", "Sveip"},
	{"Blocare cu parolă", "Blocare cu PIN", "Bețivan"},
	{"Blocco con password", "Blocco con PIN", "Swipe"},
	{"Защита паролем", "Защита PIN-кодом" "Жест"},
	{"Захист паролем", "Захист PIN-кодом" "Жест"},
	{"密码锁", "PIN锁", "滑动解锁"},
	{"密碼鎖", "PIN鎖", "滑動解鎖"}
};

const char lang_settingsDeveloperOptions[][4][150] = 
{	
	{"Toggle Remote Joy Lite", "Displays your 3DS screen on your computer via USB", "Toggle experimental features", "Dark theme"},
	{"Activer/Désactiver Remote Joy Lite", "Affiche l'écran de votre 3DS sur votre ordinateur par USB", "Activer/Désactiver caractéristiques expérimentales", "Thème noir"},
	{"Wlacz Remote Joy Lite", "Wyswietla obraz z 3DS na komputerze przez USB", "Wlacz eksperymentalne funkcje", "Ciemny motyw"},
	{"Remote Joy Lite ein-/ausschalten", "Zeigt den Bildschirm deiner 3DS via USB auf deinem Computer an", "Experimentelle Funktionen ein-/ausschalten", "Dunkles thema"},
	{"Remote Joy Lite aan/uit", "Geeft je 3DS scherm weer op je computer via USB", "Experimentele functies aan/uit", "Donkere thema"},
	{"Usar Remote Joy Lite", "Muestra la imagen de la pantalla de tu 3DS en tu PC vía USB", "Activar características experimentales", "Tema oscuro"},
	{"Alternar Remote Joy Lite", "Exibe a tela do seu 3DS no seu PC por um cabo USB", "Alternar recursos experimentais", "Tema escuro"},
	{"Alternar Remote Joy Lite", "Exibir a tela de seu 3DS em seu computador via USB", "Alternar recursos experimentais", "Tema escuro"},
	{"Veksle Remote Joy Lite", "Viser 3DS skjermen på din PC gjennom USB", "Veksle eksperimentelle funksjoner", "Mørkt tema"},
	{"Activează Remote Joy Lite", "Afișează ecranul 3DSului pe calculator prin USB", "Activează caracteristici experimentale", "Temă întuneric"},
	{"Attiva Remote Joy Lite", "Visualizza la tua schermata 3DS sul tuo computer tramite USB", "Attiva funzioni sperimentali", "Tema scuro"},
	{"Вкл. Remote Joy Lite", "Отображение изображения с 3DS на компьютер через USB", "Вкл. специальные функции", "Ночной режим"},
	{"Увм. Remote Joy Lite", "Відображення зображення з 3DS на комп'ютер через USB", "Увм. спеціальні функції", "Нічний режим"},
	{"Toggle Remote Joy Lite", "通过USB接口显示你的3DS屏幕", "切换到试验性功能", "暗色主题"},
	{"Toggle Remote Joy Lite", "透過USB介面顯示你的3DS屏幕", "切換到試驗性功能", "暗色主題"}
};

const char lang_quickSettings[][5][100] = 
{	
	{"Wi-Fi", "Power save", "Balanced", "Performance", "Lockscreen"},
	{"Wi-Fi", "Économie de batterie", "Équilibrée", "Performance", "Écran de verrouillage"},
	{"Wi-Fi", "Oszczedzanie baterii", "Zbalansowane", "Wydajnosc", "Ekran blokady"},
	{"WLAN", "Energiesparmodus", "Ausgeglichen", "Leistung", "Bildschirmsperre"},
	{"Wi-Fi", "Accubesparing", "Gebalanceerd", "Prestatie", "Vergrendelscherm"},
	{"Wi-Fi", "Ahorro de Energía", "Balanceado", "Alto Rendimiento", "Pantalla de Bloqueo"},
	{"Wi-Fi", "Power save", "Balanceado", "Desempenho", "Tela de lock"},
	{"Wi-Fi", "Modo econômico", "Equilibrado", "Desempenhado", "Bloqueio de tela"},
	{"Wi-Fi", "Strømsparing", "Balansert", "Ytelse", "Låseskjerm"},
	{"Wi-Fi", "Economisire", "Echilibrat", "Performanță", "Ecran de pornire"},
	{"Wi-Fi", "Risparmio energetico", "Bilanciato", "Prestazioni", "Blocca schermo"},
	{"Wi-Fi", "Энергосберегающий", "Сбалансированный", "Производительность", "Блокировка экрана"},
	{"Wi-Fi", "Енергозберігаючий", "Збалансований", "Продуктивність", "Блокування екрану"},
	{"Wi-Fi", "节能", "平衡", "性能", "锁屏"},
	{"Wi-Fi", "節能", "平衡", "性能", "鎖屏"}
};
