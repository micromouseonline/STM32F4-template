stm32f4-template

- A basic project template for the STM32F405RG processor.
- Written for Rowley CrossStudio 2.3
- Intended to run directly on the STM32F4Discovery board.
- Provides basic setup for the indicator lights on the board as well as a status LED connected to PB2 (Boot1).
- The internal oscillator is used and the processor clock set to 72MHz.
- A 1kHz systick interrupt handler is instantiated which toggles the status LED at 500Hz.
- All the CMSIS headers  (from the V1.1.0 Peripheral library) live in the folder ./cmsis
- All the STM32F4 peripheral library files (V1.1.0) live in the folder ./peripheral-library
- By default, the build will exclude unused code so the binary will be no bigger than it needs to be.
- The following preprocessor definitions have been made: 
    USE_FULL_ASSERT
    INITIALIZE_STACK
    USE_STDPERIPH_DRIVER
    STARTUP_FROM_RESET
- The heap size is set to 4096 bytes
- The stack size is set to 2048 bytes
- The ARM FPU Type is FPv4-SP-D16
- The ARM FP ABI type is 'Hard'  to use the built-in FPU
- printf floating point support is disabled
- printf integer support is set to long
- A pre link command has been set to format the source code on every build
  /usr/local/bin/astyle   "$(ProjectDir)/*.h" "$(ProjectDir)/*.c" 
- The user include directories are set to
    .
    ./cmsis
    ./peripheral-library/include
- The Rowley <cross_studio_io.h> header file has been included in main.c so that debug_printf() will write to the debug console.
- a delay_ms() function uses a counter maintained by the systtick event to give millisecond-resolution timing.
- a software timing function, delay_us(), gives timing independent of the systick event but dependent upon clock speed.
- Assertion failures will halt the processor and blink the status LED after printing a diagnostic message to the debug terminal.
- USE_FULL_ASSERT is not defined in Release mode
 
========================
Peter Harrison  May 2013
www.micromouseonline.com
========================