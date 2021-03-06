#include <Arduino_NoMinMax.h>
#include <SPI.h>

#include <MCUFRIEND_kbv.h>
#include <TouchScreen_kbv.h>

#include "FixedPoint.h"
#include "WaveformSin.h"
#include "Generator.h"

//Touch For New ILI9341 TP
#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

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

#define ROT_ENC_PIN_A 51
#define ROT_ENC_PIN_B 49
#define BUTTON_PIN 6

//static ButtonHandler button(BUTTON_PIN, ButtonHandler::NormalOpen);

constexpr uint32_t sinsize = 16;
uint32_t sinus[sinsize];

void setup()
{
	display.begin(display.readID());

	display.setTextColor(color<255, 255, 255>);
	display.fillScreen(color<0, 20, 0>);
	display.setTextSize(2);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	constexpr float k = (float)PI * 2.0f / sinsize;

	for (int i = 0; i < sinsize; ++i)
	{
		constexpr uint32_t chsel = 1 << 28;					// LSB on DAC0, MSB on DAC1 !!
		uint32_t sample = static_cast<uint32_t>(2047.0f * sin(i * k) + 2047.5f);
		sinus[i] = sample | ((sample << 16) | chsel);
		// MSB [31:16]on channel 1
		// LSB [15:0] on chanel 0
	}

	tc_setup();
	dac_setup();
}

void dac_setup()
{
	dacc_reset(DACC);

	DACC->DACC_MR = DACC_MR_TRGEN_EN		// Hardware trigger select
					| DACC_MR_TRGSEL(0b010) // Trigger by TIOA2
					| DACC_MR_TAG_EN		// enable TAG to set channel in CDR
					| DACC_MR_WORD_WORD		// write to both channels
					| DACC_MR_REFRESH(1) | DACC_MR_STARTUP_1216 | DACC_MR_MAXS;

	DACC->DACC_IER |= DACC_IER_TXBUFE; // Interrupt used by PDC DMA

	DACC->DACC_ACR = DACC_ACR_IBCTLCH0(0b10) // For DAC frequency > 500 KHz
					 | DACC_ACR_IBCTLCH1(0b10) | DACC_ACR_IBCTLDACCORE(0b01);

	NVIC_EnableIRQ(DACC_IRQn); // Enable DACC interrupt

	DACC->DACC_CHER = DACC_CHER_CH0	// enable channel 0 = DAC0
					  | DACC_CHER_CH1; // enable channel 1 = DAC1

	/*************   configure PDC/DMA  for DAC *******************/

	// DACC->DACC_TPR = (uint32_t)CWaveformSin::bufferAddress(); // DMA buffer
	// DACC->DACC_TCR = CWaveformSin::numSamples;
	// DACC->DACC_TNPR = (uint32_t)CWaveformSin::bufferAddress(); // next DMA buffer (circular buffer)
	// DACC->DACC_TNCR = CWaveformSin::numSamples;

	DACC->DACC_TPR = (uint32_t)sinus; // DMA buffer
	DACC->DACC_TCR = sinsize;
	DACC->DACC_TNPR = (uint32_t)sinus; // next DMA buffer (circular buffer)
	DACC->DACC_TNCR = sinsize;

	DACC->DACC_PTCR = DACC_PTCR_TXTEN; // Enable PDC Transmit channel request

	pmc_enable_periph_clk(ID_DACC);
}

void DACC_Handler()
{
	DACC->DACC_ISR; // Read and save DAC status register

	// Need to refresh the DMA buffer registers, even if nothing really needs to be done.
	DACC->DACC_TNPR = (uint32_t)sinus;
	DACC->DACC_TNCR = sinsize;
}

void tc_setup()
{
	PMC->PMC_PCER0 |= PMC_PCER0_PID28;					   // TC2 power ON : Timer Counter 0 channel 2 IS TC2
	TC0->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 // MCK/8, clk on rising edge
								| TC_CMR_WAVE			   // Waveform mode
								| TC_CMR_WAVSEL_UP_RC	  // UP mode with automatic trigger on RC Compare
								| TC_CMR_ACPA_CLEAR		   // Clear TIOA2 on RA compare match
								| TC_CMR_ACPC_SET;		   // Set TIOA2 on RC compare match

	//constexpr uint32_t targetSamplingRate = 500000;
	//constexpr uint32_t divider = F_CPU / 8 / targetSamplingRate;
	TC0->TC_CHANNEL[1].TC_RC = 32; //<*********************  Frequency = (Mck/8)/TC_RC
	TC0->TC_CHANNEL[1].TC_RA = 1; //<********************   Any Duty cycle in between 1 and TC_RC

	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_SWTRG | TC_CCR_CLKEN; // Software trigger TC2 counter and enable
}

void loop()
{
	constexpr int16_t MINPRESSURE = 270, MAXPRESSURE = 1000;
	auto p = ts.getPointSafe();
	if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
	{
		p.x = map(p.x, 847, 141, 0, 240);
		p.y = map(p.y, 122, 880, 0, 320);

		display.drawPixel(p.x, p.y, color<0, 255, 100>);
	}
}
