// Автор: geniusz (geniuszly) | Eldar Turakulov
// Система мониторинга влажности почвы с использованием OLED дисплея, светодиода и зуммера для оповещения

#include <Adafruit_SSD1306.h>  // Подключение библиотеки для работы с OLED дисплеем
#include <EEPROM.h>            // Подключение библиотеки для работы с EEPROM

// Определение пинов
#define SENSOR_POWER_PIN 7       // Пин для питания датчика
#define SENSOR_READ_PIN 8        // Пин для считывания данных с датчика
#define LED_PIN 13               // Пин для подключения светодиода
#define BUZZER_PIN 9             // Пин для подключения зуммера

// Параметры OLED дисплея
#define SCREEN_WIDTH 128         // Ширина экрана
#define SCREEN_HEIGHT 64         // Высота экрана
#define OLED_RESET    -1         // Пин сброса OLED дисплея (не используется)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Инициализация дисплея

// Константы
const unsigned long SENSOR_READ_INTERVAL = 1000;  // Интервал считывания данных, 1 секунда
const int SENSOR_ACTIVE = HIGH;                   // Включение датчика
const int SENSOR_INACTIVE = LOW;                  // Отключение датчика
const int MOISTURE_THRESHOLD = 500;               // Критический уровень влажности
#define EEPROM_ADDRESS 0                          // Адрес ячейки памяти EEPROM, где будут храниться данные калибровки

// Функция для инициализации системы
void initializeSystem() {
    EEPROM.begin(512);                // Инициализация EEPROM с 512 байтами
    pinMode(SENSOR_POWER_PIN, OUTPUT); // Установка пина для питания датчика
    powerSensorOff();                  // Изначально датчик выключен
    Serial.begin(9600);                // Начало работы с последовательной передачей данных
    initializeDisplay();               // Инициализация OLED дисплея
    initializeAlertSystem();           // Инициализация системы оповещения (светодиод и зуммер)
    
    // Чтение калибровочных данных из EEPROM
    int storedCalibrationValue = readCalibrationData();
    if (storedCalibrationValue == 255) {
        Serial.println("Данные калибровки не найдены. Пожалуйста, выполните калибровку.");
        calibrateSensor();  // Если данных нет, запускаем калибровку
    } else {
        Serial.println("Калибровочные данные успешно загружены.");
    }
}

// Функция для включения датчика
void powerSensorOn() {
    digitalWrite(SENSOR_POWER_PIN, SENSOR_ACTIVE);  // Включение питания датчика
}

// Функция для выключения датчика
void powerSensorOff() {
    digitalWrite(SENSOR_POWER_PIN, SENSOR_INACTIVE);  // Отключение питания датчика
}

// Функция для получения данных с датчика
int getSensorReading() {
    int sum = 0;
    const int numReadings = 5;  // Количество измерений для усреднения данных
    for (int i = 0; i < numReadings; i++) {
        sum += digitalRead(SENSOR_READ_PIN);  // Считывание данных с датчика
        delay(10);  // Задержка для стабилизации сигнала
    }
    return (sum / numReadings);  // Возврат усредненного значения
}

// Функция для инициализации OLED дисплея
void initializeDisplay() {
    if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {  // Проверка, что дисплей инициализирован
        Serial.println("Ошибка инициализации OLED!");  // Вывод сообщения об ошибке
        return;
    }
    display.clearDisplay();  // Очистка экрана
    display.display();       // Обновление дисплея
}

// Функция для отображения значений датчика на экране OLED
void displaySensorValue(int sensorValue) {
    display.clearDisplay();                // Очистка экрана
    display.setTextSize(1);                // Установка размера текста
    display.setTextColor(WHITE);           // Установка цвета текста
    display.setCursor(0, 0);               // Установка позиции курсора
    display.print("Влажность почвы: ");    // Вывод текста
    display.println(sensorValue);          // Вывод значения с датчика
    display.display();                     // Обновление дисплея
}

// Функция для включения светодиода и зуммера при низком уровне влажности
void triggerAlert() {
    digitalWrite(LED_PIN, HIGH);  // Включение светодиода
    tone(BUZZER_PIN, 1000);       // Включение зуммера на частоте 1000 Гц
}

// Функция для отключения светодиода и зуммера
void disableAlert() {
    digitalWrite(LED_PIN, LOW);   // Выключение светодиода
    noTone(BUZZER_PIN);           // Отключение зуммера
}

// Функция для проверки критического уровня влажности и оповещения
void checkCriticalMoisture(int sensorValue) {
    if (sensorValue < MOISTURE_THRESHOLD) {  // Проверка на критическое значение влажности
        Serial.println("Внимание: низкая влажность почвы!");
        triggerAlert();  // Включение оповещения
    } else {
        disableAlert();  // Отключение оповещения, если влажность в норме
    }
}

// Функция для обработки данных с датчика
void processSensorData() {
    int sensorValue = getSensorReading();  // Получение данных с датчика
    printSensorOutput(sensorValue);        // Вывод значений датчика в консоль
    displaySensorValue(sensorValue);       // Отображение значений на экране OLED
    checkCriticalMoisture(sensorValue);    // Проверка на критическое значение влажности

    if (sensorValue) {
        powerSensorOn();  // Включение питания датчика, если уровень влажности в норме
    } else {
        powerSensorOff();  // Отключение питания датчика
    }
}

// Функция для вывода данных с датчика в консоль
void printSensorOutput(int sensorValue) {
    Serial.print("Значение датчика: ");
    Serial.println(sensorValue);  // Вывод значения в последовательный порт
    Serial.println();
}

// Функция для калибровки датчика
void calibrateSensor() {
    Serial.println("Калибровка датчика...");
    int calibrationValue = analogRead(SENSOR_READ_PIN);  // Считывание текущих данных для калибровки
    Serial.print("Значение калибровки: ");
    Serial.println(calibrationValue);

    // Сохранение калибровочного значения в EEPROM
    saveCalibrationData(calibrationValue);
}

// Функция для сохранения калибровочных данных в EEPROM
void saveCalibrationData(int calibrationValue) {
    EEPROM.write(EEPROM_ADDRESS, calibrationValue);  // Запись данных в EEPROM по указанному адресу
    EEPROM.commit();  // Подтверждение записи данных
    Serial.println("Данные калибровки сохранены.");
}

// Функция для чтения калибровочных данных из EEPROM
int readCalibrationData() {
    int storedCalibrationValue = EEPROM.read(EEPROM_ADDRESS);  // Чтение данных из EEPROM
    Serial.print("Прочитанные данные калибровки: ");
    Serial.println(storedCalibrationValue);
    return storedCalibrationValue;
}

// Функция для инициализации пинов для светодиода и зуммера
void initializeAlertSystem() {
    pinMode(LED_PIN, OUTPUT);     // Установка пина светодиода как выход
    pinMode(BUZZER_PIN, OUTPUT);  // Установка пина зуммера как выход
    digitalWrite(LED_PIN, LOW);   // Изначально светодиод выключен
    digitalWrite(BUZZER_PIN, LOW);// Изначально зуммер выключен
}

// Главная функция цикла
void mainLoop() {
    static unsigned long lastReadTime = 0;  // Переменная для хранения времени последнего измерения
    if (millis() - lastReadTime >= SENSOR_READ_INTERVAL) {  // Проверка интервала считывания
        lastReadTime = millis();  // Обновление времени последнего измерения
        processSensorData();      // Обработка данных с датчика
    }
}

// Функция для инициализации системы
void setup() {
    initializeSystem();  // Инициализация системы
}

// Главная функция
void loop() {
    mainLoop();  // Вызов основной функции цикла
}
