import RPi_I2C_driver
from sensor import *
from time import *

if __name__ == '__main__':
  display = RPi_I2C_driver.lcd()
  sensor = Sensor()

  while True:
    data = sensor.get_data()
    data_str = 'T:{:.2f}C H:{:.2f}% P:{:.2f}hPa'.format(
        data.temperature,
        data.humidity,
        data.pressure
    )
    display.lcd_display_string(data_str[:16], 1)
    display.lcd_display_string(data_str[16:], 2)
    sleep(1)
