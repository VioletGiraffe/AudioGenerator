#include <Arduino_NoMinMax.h>
#include <SPI.h>

#include <MCUFRIEND_kbv.h>
#include <TouchScreen_kbv.h>

#include "FixedPoint.h"
#include "WaveformSin.h"
#include "Generator.h"
#include "QuadratureRotaryEncoder.h"

//Touch For New ILI9341 TP
#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
constexpr int16_t MINPRESSURE = 200, MAXPRESSURE = 1000;

auto ts = TouchScreen_kbv(XP, YP, XM, YM, 300);
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

//static ButtonHandler button(BUTTON_PIN, ButtonHandler::NormalOpen);

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
	display.fillScreen(color<0, 20, 0>);
	display.setTextSize(2);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

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
	auto p = ts.getPointSafe();
	if (p.z > 270 && p.z < 1000)
	{
		p.x = map(p.x, 847, 141, 0, 240);
		p.y = map(p.y, 122, 880, 0, 320);

		display.drawPixel(p.x, p.y, color<0, 255, 100>);
	}
}
