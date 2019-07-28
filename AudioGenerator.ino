#include <Arduino_NoMinMax.h>
#include <SPI.h>

#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

#include "FixedPoint.h"
#include "WaveformSin.h"
#include "Generator.h"
#include "QuadratureRotaryEncoder.h"
#include "ButtonHandler.h"

//#define TFT_CS 10
//#define TFT_DC 8
//#define TFT_RST 0  // you can also connect this to the Arduino reset, in which case, set this #define pin to 0!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

auto display = MCUFRIEND_kbv{};

#ifndef COLOR_ORDER_BGR
template<uint16_t R, uint16_t G, uint16_t B>
constexpr uint16_t color = ((R & 0xF8u) << 8) | ((G & 0xFCu) << 3) | (B >> 3u);
#else
template<uint16_t R, uint16_t G, uint16_t B>
constexpr uint16_t color = ((B & 0xF8u) << 8) | ((G & 0xFCu) << 3) | (R >> 3u);
#endif

static CGenerator soundGen; 
constexpr uint32_t samplingRate = 24000;

#define ROT_ENC_PIN_A 51
#define ROT_ENC_PIN_B 49
#define BUTTON_PIN 6

static QuadratureRotaryEncoder encoder{ROT_ENC_PIN_A, ROT_ENC_PIN_B};
static ButtonHandler button(BUTTON_PIN, ButtonHandler::NormalOpen);

void playSound()
{
	dac_write(soundGen.nextSample<CWaveformSin, samplingRate>(1000u));
}

// void rotationListener(void*, RotationDirection direction)
// {
// 	display.fillScreen(color<0, 0, 0>);
// 	display.setCursor(0, 0);
// 	display.print(encoder.counterValue());
// }

void setup()
{
	display.begin(display.readID());

	display.setTextColor(color<255, 255, 255>);
	display.fillScreen(color<0, 0, 0>);
	display.setTextSize(2);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	button.setButtonClickListener([]() {
		display.fillScreen(color<0, 0, 0>);
		display.setCursor(0, 0);
		display.print("CLICK");
	});

	button.setButtonLongPressListener([]() {
		display.fillScreen(color<0, 0, 0>);
		display.setCursor(0, 0);
		display.print("LONG PRESS");
	});

	button.setButtonPressListener([]() {
		display.fillScreen(color<0, 0, 0>);
		display.setCursor(0, 0);
		display.print("PRESS");
	});

	button.setButtonReleaseListener([]() {
		display.fillScreen(color<0, 0, 0>);
		display.setCursor(0, 0);
		display.print("RELEASE");
	});

	button.setButtonDoubleClickListener([]() {
		display.fillScreen(color<0, 0, 0>);
		display.setCursor(0, 0);
		display.print("DOUBLE CLICK");
	});

	// Rotary encoder handling
	//encoder.setOnRotationListener(nullptr, &rotationListener);

	dac_setup();

	//Timer3.attachInterrupt(&playSound).setFrequency(samplingRate).start(); // 24 kHz sampling rate
}

void dac_setup()
{
	pmc_enable_periph_clk(DACC_INTERFACE_ID); // start clocking DAC
	DACC->DACC_CR = DACC_CR_SWRST;  // reset DAC

	DACC->DACC_MR =
		0 /* No trigger, else DACC_MR_TRGEN_EN */ | DACC_MR_TRGSEL(0) |
		(0 << DACC_MR_USER_SEL_Pos) |  // select channel 0
		DACC_MR_REFRESH(0x2) |        // Refresh = DAC_CLOCK / (1024 * Fs) (https://cjpnmiscellany.wordpress.com/2015/08/20/settings-for-the-arduino-dac/)
		(24 << DACC_MR_STARTUP_Pos);  // 24 = 1536 cycles which I think is in range 23..45us since DAC clock = 42MHz

	DACC->DACC_IDR = 0xFFFFFFFF; // no interrupts
	DACC->DACC_CHER = DACC_CHER_CH0 << 0; // enable chan0
}

inline void dac_write(int val)
{
	DACC->DACC_CDR = val & 0xFFF;
}

void loop()
{
	if (encoder.checkForEvent())
	{
		display.fillScreen(color<0, 0, 0>);
		display.setCursor(0, 0);
		display.print(encoder.counterValue());
	}
}
