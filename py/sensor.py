import smbus2
import bme280

class Sensor:
  def __init__(self, port=1, address=0x76):
    self.port = port
    self.address = address
    self.bus = smbus2.SMBus(port)

  def calibrate(self):
    return bme280.load_calibration_params(self.bus, self.address)

  def get_data(self):
    calibration_params = self.calibrate()
    return bme280.sample(self.bus, self.address, calibration_params)

  def print_data(self):
    data = self.get_data()
    print('ID: {}'.format(data.id))
    print('Timestamp: {}'.format(data.timestamp))
    print('Temperatura: {}'.format(data.temperature))
    print('Pressão: {}'.format(data.pressure))
    print('Humidade: {}'.format(data.humidity))
