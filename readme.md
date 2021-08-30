Comercial Data Aquisition Systems are very expansive. It requires real time solution on hi throuput of data. 
This project surge from the fact that it's not simple to colect an analog data from a sensor and just send it to a computer throgh a serial emulation port. Tests have been done with this concept and what was realised is that a lot of data can be missed in relatively hi bandwidh. In order to colect and store data with hi bandwidh, low cost and simple solution, this project aims to colect data from STM32F4's analog port and store it in a sdcard in a binary way. In the future, a interface will be developed to colect data from sdcard and upload to a computer through the usb port at lower speed without the necessity to implement any specific device driver.

Goals:
    -> Colect data from ADC port and store it on SD card using DMA
    -> Sample rate of 500K samples per second
    -> Use Arduino framework
    -> Hardware [STM32F4 Blackboard](https://www.ebay.com/itm/373048559227?chn=ps&norover=1&mkevt=1&mkrid=21527-227144-2056-1&mkcid=2&itemid=373048559227&targetid=293946777986&device=c&mktype=pla&googleloc=1001566&poi=&campaignid=6643079506&mkgroupid=79659183035&rlsatarget=pla-293946777986&abcId=&merchantid=119631633&gclid=Cj0KCQjwg7KJBhDyARIsAHrAXaHsNCXM50W3HtEGMealTaFK9PrSlOdB8EiGZXeNj-5dDt56a3A-7okaAkL3EALw_wcB)
    -> Provide parameters like trigger pin, ADC ports to read, Samples qty through USB communication
    -> Upload binary to a computer
    -> Manage binary files from a computer     
