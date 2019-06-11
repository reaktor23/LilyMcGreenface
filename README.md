# LilyMcGreenface
watering and monitoring for the hackerspace's first Grünlilie

Open source plant watering and monitoring via MQTT.

Lily is Controlled by a WeMos D1 mini.

Hardware & Connections:
- [Capacitive soil moisture sensor v1.2](https://de.aliexpress.com/item/32882371718.html?spm=a2g0x.search0104.3.9.27cd1717awQgUo&ws_ab_test=searchweb0_0%2Csearchweb201602_10_10065_10068_10547_319_317_10548_10696_10084_453_10083_454_10618_10304_10307_10820_10821_537_10302_536_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_53%2CppcSwitch_0&algo_expid=dfe48d84-9e84-4e12-83c0-2ab382136e48-1&algo_pvid=dfe48d84-9e84-4e12-83c0-2ab382136e48)
  - Connected to ADC pin `A0`
- [Water Pump](https://de.aliexpress.com/item/33023236950.html?spm=a2g0x.search0104.3.85.2b7f1ab0qKnHMy&ws_ab_test=searchweb0_0%2Csearchweb201602_10_10065_10068_10547_319_317_10548_10696_10084_453_10083_454_10618_10304_10307_10820_10821_537_10302_536_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_53%2CppcSwitch_0&algo_expid=d5335373-96ad-438e-9c6d-b86f28b54d38-12&algo_pvid=d5335373-96ad-438e-9c6d-b86f28b54d38)
  - Connected to 5v by a 2N7000 MOSFET
  - Gate is connected to digital pin `D4`

Lily will send soil moisture level periodically to mqtt_humi_topic

Lily will pump water for n seconds, defined by the messages that arrive to mqtt_water_topic

This is a Reaktor23 Hackerspace project.
More information on our website:
www.reaktor23.org
