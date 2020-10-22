import pyaudio
import wave
import numpy as np

class RecordAudio:
    '''
        Audio Recording
    '''
    # Initialize PyAudio
    pyaud = pyaudio.PyAudio()

    
    def record(self, rate, channels, width, deviceIndex,
            chunk, recordSeconds, fileName, extractChannel):
        '''
            Record Audio
        '''
        
        # Record settings
        stream = self.pyaud.open(
                    rate=rate,
                    format= self.pyaud.get_format_from_width(width),
                    channels=channels,
                    input=True,
                    input_device_index=deviceIndex)

        # Print start of recording
        print("Recording audio")
        
        # Get audio data and save as frame buffer.
        frames = []
        for i in range(0, int(rate / chunk * recordSeconds)):
            # Audio data
            data = stream.read(chunk)
            # For extracted channel
            if extractChannel is not None:
                # Get data for extracted channel
                a = np.frombuffer(data,dtype=np.int16)[extractChannel::channels]
                frames.append(a.tostring())
            # For using both channels
            else:
                # Get audio data from channels
                frames.append(data)
        
        # Close recording
        stream.stop_stream()
        stream.close()
        self.pyaud.terminate()

        # Print end of recording
        print("Done recording, now saving file...")
        
        # Saving file
        wf = wave.open(fileName, 'wb')
        if extractChannel is not None:
            wf.setnchannels(1)
        else:
            wf.setnchannels(channels)
        wf.setsampwidth(self.pyaud.get_sample_size(self.pyaud.get_format_from_width(width)))
        wf.setframerate(rate)
        wf.writeframes(b''.join(frames))
        wf.close()

        print("Done recording and file being saved.")
    
    def getAudioDeviceInfo(self):
        '''
            Audio Device Info
        '''
        # Settings to get device audio info
        info = self.pyaud.get_host_api_info_by_index(0)
        numdevices = info.get('deviceCount')
 
        for i in range(0, numdevices):
                if (self.pyaud.get_device_info_by_host_api_device_index(0, i).get('maxInputChannels')) > 0:
                    print("Input Device id ", i, " - ", self.pyaud.get_device_info_by_host_api_device_index(0, i).get('name'))

# Print Start of test
print("ReSpeaker 2-Mic Pi Audio test")

# Test
recordAudio = RecordAudio()

recordAudio.getAudioDeviceInfo()

# Audio Settings
RESPEAKER_RATE = 16000
RESPEAKER_CHANNELS = 2 
RESPEAKER_WIDTH = 2
RESPEAKER_INDEX = 0  # refer to input device id
CHUNK = 1024
RECORD_SECONDS = 5
WAVE_OUTPUT_FILENAME = "recorded_audio.wav"
EXTRACT_CHANNEL = 0

recordAudio.record(RESPEAKER_RATE,RESPEAKER_CHANNELS,RESPEAKER_WIDTH, 
RESPEAKER_INDEX, CHUNK, RECORD_SECONDS, 
WAVE_OUTPUT_FILENAME, EXTRACT_CHANNEL)