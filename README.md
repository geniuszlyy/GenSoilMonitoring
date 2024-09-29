
# EN
**GenSoilMonitoring** - A robust and easy-to-use soil moisture monitoring system that uses an OLED display, LED indicator, and buzzer for real-time alerts. Perfect for keeping track of your soil's moisture levels and maintaining optimal plant health.

## Features

- Real-time monitoring of soil moisture levels
- OLED display for visualizing moisture data
- LED and buzzer alert system for critical moisture levels
- Calibration support using EEPROM for accurate readings
- Easy-to-use and customizable for various environments

## Components

- **Arduino Board** (e.g., Arduino Uno)
- **Soil Moisture Sensor**
- **OLED Display** (compatible with Adafruit SSD1306 library)
- **LED Indicator**
- **Buzzer**
- **EEPROM** (for storing calibration data)

## Installation & Setup

1. **Clone the repository**  
   Download or clone this repository to your local machine:
   ```
   git clone https://github.com/geniuszly/GenSoilMonitoring
   ```

2. **Install Arduino Libraries**  
   Make sure you have the necessary libraries installed for the OLED display and EEPROM functionality.
   - [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
   - [EEPROM](https://www.arduino.cc/en/Reference/EEPROM)

3. **Wiring Components**  
   - Connect the soil moisture sensor to the designated sensor pins.
   - Attach the OLED display to the appropriate I2C pins.
   - Wire the LED and buzzer to their respective pins on the Arduino board.

4. **Upload Code**  
   Open the `.ino` file in the Arduino IDE, select the correct board and port, and upload the code to the Arduino.

5. **Calibrate Sensor**  
   Upon the first run, if no calibration data is found, the system will prompt for calibration. Ensure the sensor is in a known moisture environment, and follow the on-screen instructions to calibrate.

## Usage
The OLED display will show the current soil moisture level. If the moisture drops below a set threshold, the LED will light up, and the buzzer will emit a sound to alert you of low moisture.

### Example Outputs

#### 1. **System Initialization and Calibration**
   Upon powering on the system, the calibration data is loaded, and messages are printed to the Serial Monitor.
   ```
   Инициализация системы...
Данные калибровки успешно загружены.
   ```

   If no calibration data is found:
   ```
   Инициализация системы...
Данные калибровки не найдены. Пожалуйста, выполните калибровку.
Калибровка датчика...
Значение калибровки: 432
Данные калибровки сохранены.
   ```

#### 2. **Real-Time Moisture Readings**
   The system continuously reads the moisture sensor and prints the values to the Serial Monitor:
   ```
   Текущий уровень влажности: 720

Текущий уровень влажности: 465
   ```

#### 3. **Low Moisture Alert Triggered**
   When the moisture level drops below the threshold, an alert is triggered:
   ```
   Текущий уровень влажности: 300

Внимание: недостаточная влажность!
   ```

#### 4. **OLED Display Output**
   The OLED screen shows live updates of the soil moisture level in a clear and readable format:
   ```
   Влажность почвы: 720
   ```
   (Displayed as text on the OLED screen.)

#### 5. **LED and Buzzer Alert for Critical Moisture Level**
   If the moisture level is below the critical threshold, the LED will light up, and the buzzer will emit a sound, alerting the user to water the plants.

# RU
**GenSoilMonitoring** - Надежная и простая в использовании система мониторинга влажности почвы с использованием OLED-дисплея, светодиодного индикатора и зуммера для оповещений в реальном времени. Отличное решение для отслеживания уровня влажности почвы и поддержания здоровья растений.

## Возможности

- Мониторинг уровня влажности почвы в режиме реального времени
- Отображение данных на OLED-дисплее
- Световой и звуковой сигнал при критическом уровне влажности
- Поддержка калибровки с использованием EEPROM для точных показаний
- Простая настройка и адаптация для различных сред

## Компоненты

- **Arduino плата** (например, Arduino Uno)
- **Датчик влажности почвы**
- **OLED-дисплей** (совместим с библиотекой Adafruit SSD1306)
- **Светодиодный индикатор**
- **Зуммер**
- **EEPROM** (для хранения данных калибровки)

## Установка и Настройка

1. **Склонируйте репозиторий**  
   Скачайте или склонируйте данный репозиторий на ваш компьютер:
   ```
   git clone https://github.com/geniuszly/GenSoilMonitoring
   ```

2. **Установите библиотеки Arduino**  
   Убедитесь, что все необходимые библиотеки установлены для работы с OLED-дисплеем и EEPROM.
   - [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
   - [EEPROM](https://www.arduino.cc/en/Reference/EEPROM)

3. **Подключение компонентов**  
   - Подключите датчик влажности почвы к соответствующим пинам.
   - Подсоедините OLED-дисплей к I2C-пинам.
   - Подключите светодиод и зуммер к соответствующим пинам на плате Arduino.

4. **Загрузка кода**  
   Откройте `.ino` файл в Arduino IDE, выберите правильную плату и порт, и загрузите код на Arduino.

5. **Калибровка датчика**  
   При первом запуске, если данные калибровки не обнаружены, система предложит выполнить калибровку. Поместите датчик во влажную или сухую почву и следуйте инструкциям на экране для завершения калибровки.

## Использование
OLED-дисплей будет отображать текущий уровень влажности почвы. Если уровень влажности опустится ниже установленного порога, светодиод загорится, а зуммер издаст звуковой сигнал, предупреждающий о низкой влажности.

---

### Примеры Результатов

#### 1. **Инициализация системы и калибровка**
   При включении системы происходит загрузка данных калибровки, вывод которых отображается в мониторе порта:
   ```
   Инициализация системы...
   Данные калибровки успешно загружены.
   ```

   Если данные калибровки не обнаружены:
   ```
   Инициализация системы...
   Данные калибровки не найдены. Пожалуйста, выполните калибровку.
   Калибровка датчика...
   Значение калибровки: 432
   Данные калибровки сохранены.
   ```

#### 2. **Чтение данных влажности в реальном времени**
   Система непрерывно считывает данные с сенсора влажности и выводит значения в монитор порта:
   ```
   Текущий уровень влажности: 720

   Текущий уровень влажности: 465
   ```

#### 3. **Срабатывание сигнала о низкой влажности**
   Когда уровень влажности опускается ниже установленного порога:
   ```
   Текущий уровень влажности: 300

   Внимание: недостаточная влажность!
   ```

#### 4. **Вывод на OLED-дисплей**
   Экран OLED отображает текущий уровень влажности почвы:
   ```
   Влажность почвы: 720
   ```
   (Отображается в виде текста на экране OLED.)

#### 5. **Световое и звуковое оповещение о критическом уровне влажности**
   Если уровень влажности падает ниже критического порога, светодиод загорится, а зуммер издаст звуковой сигнал, оповещая пользователя о необходимости полива.
