# LilyMcGreenface
watering and monitoring for the hackerspace's first Grünlilie

Open source plant watering and monitoring via MQTT.

Lily is Controlled by a WeMos D1 mini.

Hardware & Connections:
- Capacitive soil moisture sensor v1.2
  - Connected to ADC pin A0
- Water Pump
  - Connected to 5v by a 2N7000 MOSFET
  - Gate is connected to digital pin D4

Lily will send soil moisture level periodically to mqtt_humi_topic
Lily will pump water for n seconds, defined by the messages that arrive to mqtt_water_topic

This is a Reaktor23 Hackerspace project.
More information on our website:
www.reaktor23.org
