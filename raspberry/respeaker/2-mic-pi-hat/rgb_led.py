from apa102_pi.driver import apa102
import time

# Initialize the library and the strip
strip = apa102.APA102(num_led=3, global_brightness=20, mosi=10, sclk=11,
                      order='rbg')

# Turn off all pixels (sometimes a few light up when the strip gets power)
strip.clear_strip()

# Prepare a few individual pixels
strip.set_pixel_rgb(0, 0xFF0000)  # Red
strip.set_pixel_rgb(1, 0xFFFFFF)  # White
strip.set_pixel_rgb(2, 0x00FF00)  # Green

# Copy the buffer to the Strip (i.e. show the prepared pixels)
strip.show()

# Wait a few Seconds, to check the result
time.sleep(20)

# Clear the strip
strip.clear_strip()
strip.cleanup()