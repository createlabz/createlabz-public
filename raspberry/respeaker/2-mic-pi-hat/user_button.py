import RPi.GPIO as GPIO
import time

# Print Start of test
print("ReSpeaker 2-Mic Pi Button test")

# User button pin
BUTTON = 17
# User button setup
GPIO.setmode(GPIO.BCM)
GPIO.setup(BUTTON, GPIO.IN)

# Save previous state
previousState = GPIO.input(BUTTON)

# Unending Loop (main)
while True:
    # Get button state
    currentState = GPIO.input(BUTTON)
    # Check if any difference
    if currentState != previousState:
        # Store current state as previous
        previousState = currentState
        # Check the current state of the button
        if currentState:
            # Print if button is not clicked
            print("Button is not clicked")
        else:
            # Print if clicked
            print("Button is clicked")