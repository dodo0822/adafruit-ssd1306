#define YOTTA_CFG_MBED_TRACE
#define TRACE_GROUP  "main"

#include "mbed-drivers/mbed.h"
#include "mbed-trace/mbed_trace.h"

#include "adafruit-ssd1306/Adafruit_SSD1306.h"
#include "adafruit-ssd1306/Adafruit_GFX.h"

static void do_nothing(void) {
	tr_debug("hello %s", "world");
}

void app_start(int, char**) {
	mbed_trace_init();
	
	static I2C i2c(YOTTA_CFG_HARDWARE_TEST_PINS_I2C_SDA, YOTTA_CFG_HARDWARE_TEST_PINS_I2C_SCL);
	i2c.frequency(400000);
	static Adafruit_SSD1306_I2c oled(i2c, YOTTA_CFG_HARDWARE_PINS_D2);
	
	//oled.clearDisplay();
	oled.fillRect(0, 0, 128, 64, BLACK);
	//oled.drawChar(0, 0, 'a', WHITE, BLACK, 1);
	oled.printfPos(10, 10, "hello %s", "world");
	oled.display();
	
	minar::Scheduler::postCallback(do_nothing).period(minar::milliseconds(1000));
}