# Non-blocking code for Arduino

## Perplexity Playground Model: codellama-70b-instruct
### Prmompt 3-10-2024 0700:
I'm using Arduino to control up to 8 devices. I need to turn them on and off asynchronously and possibly simultaneously. each device will have a "state" and duration with resolution in microseconds. needs to be non blocking and can't use interrupts. output full code example
LLM served by Perplexity Labs
### Response:

 *    Arduino has a built-in millis() function that returns the number of milliseconds since the Arduino board began running the current program. You can use this function to create a non-blocking timer.
 *    Create a struct to store the state and duration of each device.
 *    Create an array of structs to store the state and duration of all devices.
 *    In the setup() function, initialize the output pins and set the initial state of all devices to off.
 *    In the loop() function, iterate through the array of structs and check the state of each device.
 *    If the device is in the "on" state, check if the current millis() is greater than or equal to the end time of the device. If it is, turn off the device and set its state to "off".
 *    If the device is in the "off" state, check if the current millis() is greater than or equal to the start time of the device. If it is, turn on the device and set its state to "on".
 *    To turn on or off a device, use the digitalWrite() function.
 *    To set the start time and end time of a device, use the millis() function to get the current time and add the duration to it.
 *    To control multiple devices simultaneously, you can use multiple output pins.

Here's an example code:

```
#define DEVICE_COUNT 8

struct Device {
  int pin;
  bool state;
  unsigned long startTime;
  unsigned long endTime;
};

Device devices[DEVICE_COUNT];

void setup() {
  for (int i = 0; i < DEVICE_COUNT; i++) {
    devices[i].pin = i + 2; // Set the output pins
    pinMode(devices[i].pin, OUTPUT);
    devices[i].state = false; // Set the initial state to off
  }
}

void loop() {
  for (int i = 0; i < DEVICE_COUNT; i++) {
    if (devices[i].state) {
      // If the device is in the "on" state
      if (millis() >= devices[i].endTime) {
        // If the current time is greater than or equal to the end time
        digitalWrite(devices[i].pin, LOW); // Turn off the device
        devices[i].state = false; // Set the state to "off"
      }
    } else {
      // If the device is in the "off" state
      if (millis() >= devices[i].startTime) {
        // If the current time is greater than or equal to the start time
        digitalWrite(devices[i].pin, HIGH); // Turn on the device
        devices[i].state = true; // Set the state to "on"
      }
    }
  }
}

// Function to turn on a device for a specified duration
void turnOnDevice(int deviceIndex, unsigned long duration) {
  devices[deviceIndex].startTime = millis(); // Set the start time
  devices[deviceIndex].endTime = devices[deviceIndex].startTime + duration; // Set the end time
}

// Function to turn off a device
void turnOffDevice(int deviceIndex) {
  devices[deviceIndex].state = false; // Set the state to "off"
}
```

### Summary:
To turn on a device, call the turnOnDevice() function with the device index and the duration in milliseconds. To turn off a device, call the turnOffDevice() function with the device index. This code uses a non-blocking timer to control multiple devices asynchronously and simultaneously. It uses a struct to store the state and duration of each device, and an array of structs to store the state and duration of all devices. The loop() function iterates through the array of structs and checks the state of each device. If a device is in the "on" state, it checks if the current time is greater than or equal to the end time of the device. If it is, it turns off the device and sets its state to "off". If a device is in the "off" state, it checks if the current time is greater than or equal to the start time of the device. If it is, it turns on the device and sets its state to "on". The turnOnDevice() function is used to turn on a device for a specified duration. It sets the start time and end time of the device. The turnOffDevice() function is used to turn off a device. It sets the state of the device to "off".

***
